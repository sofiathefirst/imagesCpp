#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main() {

	VideoCapture camCapLeft(0);
	int i = 0;
	camCapLeft.set(cv::CAP_PROP_FRAME_WIDTH, 10000);
	camCapLeft.set(cv::CAP_PROP_FRAME_HEIGHT, 10000);
	Size s(3, 4);
	cout << s;
	s.height = 6;
	s.width = 9;
	cout << s;
	int w = camCapLeft.get(CV_CAP_PROP_FRAME_WIDTH);
	int h = camCapLeft.get(CV_CAP_PROP_FRAME_HEIGHT);
	bool found = false;
	cv::Mat img1;
	vector<Point2f> pointBuf;
	int chessBoardFlags = CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE;
	//    int chessBoardFlags = cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK;
	printf("cam Resolution%d,%d\n", w, h);
	vector<vector<Point2f> > imagePoints;
	Mat cameraMatrix, distCoeffs;
	vector<Mat> rvecs, tvecs;
	Size boardSize(6, 9);
	float squareSize = 3;
	while (camCapLeft.isOpened()) {
		camCapLeft >> img1;
		found = false;
		found = findChessboardCorners(img1, boardSize, pointBuf,
				chessBoardFlags);
		//found = findCirclesGrid( img1,boardSize, pointBuf,cv::CALIB_CB_SYMMETRIC_GRID,cv::SimpleBlobDetector::create());
		if (found) {
			cv::drawChessboardCorners(img1, boardSize, cv::Mat(pointBuf),
					found);
			imagePoints.push_back(pointBuf);
		}
		imshow("L", img1);
		char c = cv::waitKey(1);
		if (c > 'a' && c < 'z')
			printf("c=%c\n", c);
		//imwrite(name, img1);
	}

	camCapLeft.release();
	return 0;
}

