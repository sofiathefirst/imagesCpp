#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{

	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(7);

	cv::Mat   imageCopy;

	cv::aruco::drawMarker(dictionary,atoi( argv[1]),atoi(  argv[2]), imageCopy, 1); 
	imshow("mak34er", imageCopy);
	char name[10];
	sprintf(name , "maker%d_%d.jpg", atoi( argv[1]),atoi(  argv[2]));
	imwrite(name, imageCopy);
	char key = (char) cv::waitKey(4000);

	return 0;
}
