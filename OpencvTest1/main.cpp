#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <opencv2/video/background_segm.hpp>
using namespace cv;
using namespace std;


VideoCapture stream1(0);

Mat cameraFrame1;
Mat cameraFrame2;
int flag;


void RectangleDetection (Mat obj, Mat color, Point a,Point b){
    
    rectangle(color, a, b, Scalar(255,0,0));
    for(int x = a.x; x<b.x; x++){
        for(int y = a.y; y<b.y; y++){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]>0){//detected
                cout << "Triggered" << endl;
                rectangle(color, a, b, Scalar(0,0,255));
            }
            else cout << "Nothing" << endl;
        }
    }
    
}

int main() {
    namedWindow("cam",1);
    stream1.read(cameraFrame2);
    while (true) {
        stream1.read(cameraFrame1);
        Mat diff = cameraFrame2 - cameraFrame1;
        //imshow("cam1", cameraFrame1);
        //imshow("cam2", cameraFrame2);
        cvtColor(diff,diff,CV_RGB2GRAY);
        
        //Scalar colour = diff.at<uchar>(Point(100,100));
        //if(colour.val[0]>0) cout << colour.val[0] << endl;
        
        threshold(diff, diff, 30, 255, CV_THRESH_BINARY);
        //circle(diff, Point(50,50), 10, Scalar(100,100,100));
        
        RectangleDetection(diff, cameraFrame1,Point(80,80),Point(120,120));
        
        imshow("cam", cameraFrame1);
        stream1.read(cameraFrame2);
        if(waitKey(10)==27) break;
    }
    return 0;
}



