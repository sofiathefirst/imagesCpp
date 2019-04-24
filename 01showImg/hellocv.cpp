#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{

 VideoCapture camCapLeft(0); ;
printf("v\n");
   // camCapRight.open(ids[1]);
 VideoCapture camCapRight(1);


	while (camCapLeft.isOpened() && camCapRight.isOpened())
	{
		//framenum++;
		cv::Mat img1;
		cv::Mat img2;
printf("1\n");
		camCapLeft >> img1;
printf("2\n");
		camCapRight >> img2;
	imshow("L", img1);
	imshow("R", img2);
	cv::waitKey(1);
	}


	Mat srcImage = imread("/home/a/workspace1/opencv3/a.jpg");
	imshow("img",srcImage);
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat dstImage;
	erode(srcImage,dstImage,element);
	imshow("erode img",dstImage);
	waitKey(0);
	//imwrite("a.bmp",img);

	return 0;
}
