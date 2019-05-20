#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
int main() {
	VideoCapture camCapLeft(0);
	int i = 0;
	CascadeClassifier face_cascade =
			CascadeClassifier(
					"/home/q/opencv-3.4.6/data/haarcascades/haarcascade_frontalface_default.xml");
	CascadeClassifier eye_cascade = CascadeClassifier(
			"/home/q/opencv-3.4.6/data/haarcascades/haarcascade_eye.xml");
	camCapLeft.set(cv::CAP_PROP_FRAME_WIDTH, 10000);
	camCapLeft.set(cv::CAP_PROP_FRAME_HEIGHT, 10000);
	// int w = (int)mCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	//  int h = (int)mCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

	int w = camCapLeft.get(CV_CAP_PROP_FRAME_WIDTH);
	int h = camCapLeft.get(CV_CAP_PROP_FRAME_HEIGHT);
	printf("cam Resolution%d,%d\n", w, h);
	while (camCapLeft.isOpened()) {
		cv::Mat img;
		camCapLeft >> img;
		imshow("L", img);
		char c = cv::waitKey(1);
		char name[10] = "";
		sprintf(name, "a%d.jpg", i);
		i++;
		//imwrite(name, img1);
		Mat gray;
		cvtColor(img, gray, COLOR_BGR2GRAY);
		std::vector<Rect> faces;
		std::vector<Rect> eyes;
		face_cascade.detectMultiScale(gray, faces, 1.3, 5);
		eye_cascade.detectMultiScale(gray, eyes, 1.3, 5);
		//for(int i =0;i<faces.size();i++)
		cout << face_cascade.empty() << endl;
		//cout << faces.size() << endl;
		cout << eyes.size() << endl;
		if(faces.size()>0)
		{
			for (int i = 0; i < faces.size(); i++)
				rectangle(gray, faces[i], Scalar(255));
			for (int i = 0; i < eyes.size(); i++)
				rectangle(img, eyes[i], Scalar(200, 200, 200));
			//line(L,Point( i*sz[2],0),Point( i*sz[2],sz[2]*sz[0] ),Scalar(255, 0,0));
			//circle(src, recent_Point, 3, Scalar(25, 0, 0), -1);
			imshow("eye", img);
			imshow("faces", gray);
			waitKey(10);
		}
	}
	camCapLeft.release();
	destroyAllWindows();
	return 0;
}


