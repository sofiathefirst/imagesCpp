#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;

//点击鼠标返回相应坐标位置并存到txtpoints2文件中
#define WINDOW "source image"
Mat src;
void On_mouse(int event, int x, int y, int flags, void*);
Point recent_Point;
ofstream file("point2.txt", ios::out | ios::binary);
int main()
{
    src = imread("000000.jpg");
    namedWindow(WINDOW, WINDOW_NORMAL);
    setMouseCallback(WINDOW, On_mouse);
    //while (1)
    imshow(WINDOW, src);//点击的开始
    waitKey(0);
    file.close();
    return 0;

}
void On_mouse(int event, int x, int y, int flags, void*)//每次点击左键，将将当前点坐标存储到txt文件中，并在相应位置画红点
{
    
    if (event == EVENT_LBUTTONDOWN) 
    {
        recent_Point = Point(x, y);
        file << recent_Point.x << " " << recent_Point.y<<" ";
        circle(src, recent_Point, 3, Scalar(25, 0, 0), -1);    
        imshow(WINDOW, src);
		printf("%d,%d\n",x,y);
        
    }
}
