#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{


	Mat srcImage = imread("a.bmp");
	imshow("img",srcImage);
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat dstImage;
	erode(srcImage,dstImage,element);
	imshow("erode img",dstImage);

    Mat pairs = Mat(srcImage.rows, srcImage.cols * 2, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < srcImage.cols; i++)
    {
        srcImage.col(i).copyTo(pairs.col(i));
        dstImage.col(i).copyTo(pairs.col(srcImage.cols + i));
    }
	imshow("erode img",pairs);
imwrite("pairs.bmp",pairs);
	waitKey(2000);
	return 0;
}
