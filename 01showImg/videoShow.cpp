#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{

    VideoCapture camCapLeft(0); ;
    while (camCapLeft.isOpened() )
    {
        cv::Mat img1;
        camCapLeft >> img1;
        imshow("L", img1);
        char c = cv::waitKey(1);
				if(c=='s')
			{
printf("s\n");
imwrite("a.jpg", img1);
			}
    }
    camCapLeft.release();
    return 0;
}
