//
//  test.cpp
//  OpencvTest1
//
//  Created by Kevin Yen on 6/24/14.
//  Copyright (c) 2014 Kevin Yen. All rights reserved.
//
#include <cv.h>
#include <highgui.h>

#include <time.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    // OpenCV Capture object to grab frames
    CvCapture *capture = cvCaptureFromCAM(0);
    
    // start and end times
    time_t start, end;
    
    // fps calculated using number of frames / seconds
    double fps;
    
    // frame counter
    int counter = 0;
    
    // floating point seconds elapsed since start
    double sec;
    
    // start the clock
    time(&start);
    
    IplImage *frame;
    
    CvFont font=cvFont(2,2);
    char buf[32];
    
    while(cvGrabFrame(capture))
    {
        // grab a frame
        frame = cvRetrieveFrame(capture);
        
        // see how much time has elapsed
        time(&end);
        
        // calculate current FPS
        ++counter;
        sec = difftime (end, start);
        
        fps = counter / sec;
        sprintf(buf, "%.0f\n", fps);
        
        cvPutText(frame, buf, cvPoint(5, 35), &font, cvScalar(0,255,255));
        
        // will print out Inf until sec is greater than 0
        cvShowImage("Webcam",frame);
        //printf("FPS = %.2f\n", fps);
    }
    
    cvReleaseCapture(&capture);
    return 0;
}