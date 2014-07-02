#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <opencv2/video/background_segm.hpp>
#include "InitMidi.h"
#include <unistd.h>


using namespace cv;
using namespace std;


VideoCapture stream1(0);
VideoCapture stream2(0);

Mat CF1;
Mat CF2;
int ThreshLevel=20;
int hullcount;
int inputkey;
bool picked = 0;
Scalar rec1;
bool Showtext = false;
vector<int> hull;
vector<Point> points;
string PlayingChordName;

string chord (Mat obj, int startX, int startY, int squaresizeX, int squaresizeY, int gap){
    int xx = startX + 3*(squaresizeX + gap);
    int yy = startY;
    
    for(int x = xx; x<xx + squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy + squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "C";
        }
    }
    xx = xx - squaresizeX - gap;
    for(int x = xx; x<xx+squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy+squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "Bm";
        }
    }
    xx = xx - squaresizeX - gap;
    for(int x = xx; x<xx+squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy+squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "Am";
        }
    }
    xx = xx - squaresizeX - gap;
    for(int x = xx; x<xx+squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy+squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "G";
        }
    }
    yy = yy + squaresizeY + gap;
    xx = startX + 3*(squaresizeX + gap);
    for(int x = xx; x<xx + squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy + squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "F";
        }
    }
    xx = xx - squaresizeX - gap;
    for(int x = xx; x<xx+squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy+squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "Em";
        }
    }
    xx = xx - squaresizeX - gap;
    for(int x = xx; x<xx+squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy+squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "Dm";
        }
    }
    xx = xx - squaresizeX - gap;
    for(int x = xx; x<xx+squaresizeX; x = x + squaresizeX/4){
        for(int y = yy; y<yy+squaresizeY; y = y + squaresizeY/4){
            Scalar colour = obj.at<uchar>(Point(x,y));
            if(colour.val[0]!=0) return "C";
        }
    }
    return "N";
}

void SendChord(String chord){
    if (chord == "C") ChordMajor(60);
    else if (chord == "Dm") ChordMinor(62);
    else if (chord == "Em") ChordMinor(64);
    else if (chord == "Am") ChordMinor(69);
    else if (chord == "Bm") ChordMinor(71);
    else if (chord == "F") ChordMajor(65);
    else if (chord == "G") ChordMajor(67);
}


void RD (Mat obj, cv::Point a,cv::Point b){
    for(int x = a.x; x<b.x; x+=3){
        for(int y = a.y; y<b.y; y+=3){
            Scalar colour = obj.at<uchar>(cv::Point(x,y));
            if(colour.val[0]!=0){
                if (!picked){
                   SendChord(chord(obj, 830, 250, 70, 70, 30));
                }
                picked = true;
                return;
            }
            picked= false;
        }
    }
    return;
}

void hmm(Mat obj){
    rectangle(obj, Point(500,320), Point(600,360), Scalar(255,0,0));
    rectangle(obj, Point(1200,250), Point(1130,320), Scalar(255,0,0));
    rectangle(obj, Point(1100,250), Point(1030,320), Scalar(255,0,0));
    rectangle(obj, Point(1000,250), Point( 930,320), Scalar(255,0,0));
    rectangle(obj, Point( 900,250), Point( 830,320), Scalar(255,0,0));
    rectangle(obj, Point(1200,360), Point(1130,430), Scalar(255,0,0));
    rectangle(obj, Point(1100,360), Point(1030,430), Scalar(255,0,0));
    rectangle(obj, Point(1000,360), Point( 930,430), Scalar(255,0,0));
    rectangle(obj, Point( 900,360), Point( 830,430), Scalar(255,0,0));
    flip(obj  , obj, 1);
    putText(CF1, "C", Point(80,320), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "Bm", Point(180,320), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "Am", Point(280,320), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "G", Point(380,320), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "F", Point(80,420), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "Em", Point(180,420), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "Dm", Point(280,420), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "C", Point(380,420), 1, 3, Scalar(0,0,255),2);
    putText(CF1, "PICK", Point(690,350), 1, 2, Scalar(0,0,255),3);

    imshow("cam", obj);
}

int main() {
    stream2.read(CF2);
    midiout->openPort( 0 );
    while (true) {
        Showtext = false;
        stream1.read(CF1);
        Mat diff2 = CF2 - CF1;
        Mat diff = CF1 - CF2;
        diff2 = (diff+diff2)/2;
        cvtColor(diff2,diff2,CV_RGB2GRAY);
        threshold(diff2, diff2, ThreshLevel, 255, THRESH_BINARY);
        
        RD(diff2, Point(500,320), Point(600,340));
        hmm(CF1);
        
        inputkey = waitKey(1);
        switch (inputkey) {
            case 27:
                stream1.release();
                stream2.release();
                return 0;
                break;
            case 63232://up
                stream2.read(CF2);
                break;
            default:
                break;
        }
    } 
    return 0;
}


