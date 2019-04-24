
#include <stdio.h>  
#include <pcl/point_types.h>
//#include <sensor_msgs/Image.h>
//#include <sensor_msgs/PointCloud2.h>
//#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <string.h>

#include <pcl/io/pcd_io.h>
pcl::PointCloud<pcl::PointXYZ> boxcloud; 
pcl::PointXYZ pint;
int main(int argc, char** argv) 
{  
    //pcl::PointXYZ pint(1,2,3);
    FILE *f = fopen("002_00000000.bin","rb");
    float fa[4]={0};
    //unsigned char pos[16];
    //fread(pos,1,11840,f);//1180 char
    fseek (f , 0 , SEEK_END);       
    int lSize = ftell (f);  
    rewind (f); 
    //printf("\nfirst 40 bytes:  " );
    int ll =lSize; //atoi(argv[1]);
    for(int i = 0; i < ll; i+=16)
    {
        fread(fa,4,4,f);// 4 floats 
        // memcpy(fa,&pos[0],16);
        if(fa[3]>0 && fa[3]<=255)
        {
            pcl::PointXYZ pint(fa[0],fa[1],fa[2]);
            boxcloud.points.push_back(pint);
        }
       // printf("\n  i%d %f,%f,%f,%f\n  ",i, fa[0],fa[1],fa[2],fa[3] );
    }

    boxcloud.width = boxcloud.points.size();
    boxcloud.height =1;

    //sensor_msgs::PointCloud2 rosboxcloud;
    //pcl::toROSMsg (boxcloud, rosboxcloud);
    //boxpclpub.publish(rosboxcloud);
    pcl::io::savePCDFileASCII ("mbox.pcd", boxcloud);
    printf("\nsize : %d \n", lSize);
    return 0;  
} 

