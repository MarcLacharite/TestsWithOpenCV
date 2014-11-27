#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

double diffclock( clock_t clock1, clock_t clock2 )
{

    double diffticks = clock1 - clock2;
    double diffms    = diffticks / ( CLOCKS_PER_SEC / 1000 );

    return diffms;
}

int main(int argc, char* argv[])
{
    const char* fileName = "Test.avi";
//    double fps = 24;

//    clock_t timer;
//    clock_t timer_start;

    remove(fileName);

    VideoCapture cap(0); // open the video camera no.
    double fps = 15;

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
    Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    VideoWriter videoOutput;

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE);

//    timer_start = clock();

    while (1)
    {
//        timer = clock(); //track current time
//        double diff = diffclock(timer, timer_start);
//        if(diff > 40)
//        {
//        timer_start = clock();
//
//        cout << diff << endl;

        Mat frame, grayFrame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        cvtColor(frame, grayFrame, CV_BGR2GRAY);

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        if(!videoOutput.isOpened())
        {
            videoOutput.open(fileName, CV_FOURCC('D','I','V','X'),fps, frameSize,false);
            if(!videoOutput.isOpened())
            {
                cout<<"Error : can't write to file"<<endl;
                return -1;
            }
        }

        imshow("MyVideo", frame); //show the frame in "MyVideo" windowrayed
        imshow("Grayscale", grayFrame);

        videoOutput.write(grayFrame);

        if (waitKey(10) == 1048603) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
        //}


    }

    cap.release();
    videoOutput.release();

    return 0;
}