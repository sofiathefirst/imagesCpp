#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//用图像的暗色部分erode高亮部分．
int main()
{
	Mat srcImage = imread("/home/a/workspace1/opencv3/a.jpg");
	imshow("img",srcImage);
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat dstImage;
	erode(srcImage,dstImage,element);
	imshow("erode img",dstImage);
	waitKey(1);
	//imwrite("a.bmp",img);

	return 0;
}
