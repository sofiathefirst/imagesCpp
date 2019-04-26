#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>
//#include"vi2cmd.cpp"
using namespace std;
using namespace cv;
//#include <ros/ros.h>
#define PI 3.1415926535

// Checks if a matrix is a valid rotation matrix.
bool isRotationMatrix(Mat &R)
{
    Mat Rt;
    transpose(R, Rt);
    Mat shouldBeIdentity = Rt * R;
    Mat I = Mat::eye(3,3, shouldBeIdentity.type());
    
    return  norm(I, shouldBeIdentity) < 1e-6;
    
}

// Calculates rotation matrix to euler angles
// The result is the same as MATLAB except the order
// of the euler angles ( x and z are swapped ).
Vec3f rotationMatrixToEulerAngles(Mat &R)
{
    assert(isRotationMatrix(R));
    float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );
    bool singular = sy < 1e-6; // If
    float x, y, z;
    if (!singular)
    {
        x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
        y = atan2(-R.at<double>(2,0), sy);
        z = atan2(R.at<double>(1,0), R.at<double>(0,0));
    }
    else
    {
        x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
        y = atan2(-R.at<double>(2,0), sy);
        z = 0;
    }
    return Vec3f(x, y, z);   
}

int main(int argc, char **argv)
{
    // load camera intrinsic;
	//ros::init(argc,argv,"vi2cmdnode");
    cv::Mat cameraMatrix = cv::Mat::eye(3,3,CV_32F);
    cv::Mat distCoeffs(1,5,CV_32F);
/*
    cameraMatrix.at<float>(0, 0) = 484.76891915593;
    cameraMatrix.at<float>(1, 1) = 484.04700096594;
    cameraMatrix.at<float>(0, 2) = 325.59734300829;
    cameraMatrix.at<float>(1, 2) = 237.65140808607;

    distCoeffs.at<float>(0, 0) = 0.05009914596080058;
    distCoeffs.at<float>(0, 1) = -0.05726109796268716;
    distCoeffs.at<float>(0, 2) = -0.002673513830516165;
    distCoeffs.at<float>(0, 3) = -0.0007785655545231285;
    distCoeffs.at<float>(0, 4) = 0.01591191156670914;
*/
    cameraMatrix.at<float>(0, 0) = 8.4585493880125250e+02;
    cameraMatrix.at<float>(1, 1) = 8.3237579149291980e+02;
    cameraMatrix.at<float>(0, 2) = 3.1675507917286166e+02;
    cameraMatrix.at<float>(1, 2) = 2.5818194017040628e+02;

    distCoeffs.at<float>(0, 0) = -3.5357129501910368e-02;
    distCoeffs.at<float>(0, 1) = 1.1110168134789529e+00;
    distCoeffs.at<float>(0, 2) = -1.7641632747679876e-04;
    distCoeffs.at<float>(0, 3) = -1.3071425287465950e-02;
    distCoeffs.at<float>(0, 4) =  -6.4802613038741050e+00;

    cv::VideoCapture inputVideo;
    inputVideo.open(atoi(argv[1]));
    inputVideo.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    inputVideo.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(7);
	//cv::Mat markerImage= imread;
    


   // Vi2cmd myvi2cmd;
    while (inputVideo.grab()) {
		//ros::spinOnce();
        cv::Mat image, imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);
cv::aruco::drawMarker(dictionary, 34, 200, imageCopy, 1); 
imshow("mak34er", imageCopy);
cv::aruco::drawMarker(dictionary, 23, 200, imageCopy, 1); 
imshow("maker", imageCopy);

        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        // if at least one marker detected
        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, 0.29, cameraMatrix, distCoeffs, rvecs, tvecs);
            
            // draw axis for each marker
            for(int i=0; i<ids.size(); i++){
		//if(ids[i] != 513) continue;
	    	cv::Mat R;
                cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
	    	cv::Rodrigues(rvecs[i], R);
		cv::Vec3f euler_rad = rotationMatrixToEulerAngles(R);
		
		//x(right), y(down), z(forward) 
		float d_x, d_y, d_z, t_x, t_y, t_z;
		d_x = 180*euler_rad(0)/PI;
		d_y = 180*euler_rad(1)/PI;
		d_z = 180*euler_rad(2)/PI;
		t_x = tvecs[i](0);
		t_y = tvecs[i](1);
		t_z = tvecs[i](2);
		
               std::cout<<"T(R_x, R_y, R_z, t_x, t_y, t_z):\n"<<"("<<d_x<<"°, "<<d_y<<"°, "<<d_z<<"°, "<<t_x<<","<<t_y<<","<<t_z<<")"<<std::endl<<std::flush;

		// To Do!
		// CODE SEND POSE TO SERIAL 
		//myvi2cmd.work(d_x, d_y, d_z, t_x, t_y, t_z);
            }
        }
		//else myvi2cmd.stop();
        cv::imshow("o3ut", imageCopy);
        char key = (char) cv::waitKey(1);
        if (key == 27)
            break;
    }
    return 0;
}
