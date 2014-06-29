#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <opencv2/video/background_segm.hpp>
#include "InitMidi.h"


using namespace cv;
using namespace std;


VideoCapture stream1(0);
VideoCapture stream2(0);

Mat cameraFrame1;
Mat cameraFrame2;
int ThreshLevel=20;
int buf;



void RectangleDetection (Mat obj, Mat color, cv::Point a,cv::Point b){
    rectangle(color, a, b, Scalar(255,0,0));
    for(int x = a.x; x<b.x; x++){
        for(int y = a.y; y<b.y; y++){
            Scalar colour = obj.at<uchar>(cv::Point(x,y));
            if(colour.val[0]>0){
                rectangle(color, a, b, Scalar(0,0,255));
                SendMidi(60, 90);
            }
        }
    }
}



int main() {
    
    //Initmidi();
    
    
    stream2.read(cameraFrame2);
    while (true) {
        
        stream1.read(cameraFrame1);
        Mat diff2 = cameraFrame2 - cameraFrame1;
        Mat diff = cameraFrame1 - cameraFrame2;
        diff2 = (diff+diff2)/2;
        cvtColor(diff2,diff2,CV_RGB2GRAY);
        threshold(diff2, diff2, ThreshLevel, 255, THRESH_BINARY);
        RectangleDetection(diff2, cameraFrame1, Point(95,95), Point(105,105));
        imshow("cam", cameraFrame1);
        
        stream2.read(cameraFrame2);
        
        buf = waitKey(10);
        switch (buf) {
            case 27:
                stream1.release();
                stream2.release();
                return 0;
                break;
//            case 63232://up
//                Ho();
//            case 63233://down
//                ThreshLevel--;
//                cout << ThreshLevel << endl;
            default:
                break;
        }
        
    } 
    return 0;
}


