#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{


 

    Mat pairs = imread("000000.jpg");
 
rectangle (pairs, Point(1782, 401), Point(1827, 524), Scalar(0, 255, 255), 1, 8, 0);//黄色矩形镶边
rectangle (pairs, Point(1797, 394), Point(1886, 434), Scalar(0, 255, 255), 1, 8, 0);
 
rectangle (pairs, Point(697, 445), Point(824, 552), Scalar(0, 255, 255), 1, 8, 0);
 rectangle (pairs, Point(1435, 398), Point(1513, 552), Scalar(0, 255, 255), 1, 8, 0);

	imshow("erode img",pairs);
//imwrite("pairs.bmp",pairs);
	waitKey(20000);
	return 0;
}
