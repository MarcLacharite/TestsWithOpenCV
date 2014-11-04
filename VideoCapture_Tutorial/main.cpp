#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    string filePath = "Test.avi";
    double fps = 30;

    remove("Test.avi");

    VideoCapture cap(0); // open the video camera no. 0
    cap.set(CV_CAP_PROP_FPS,30);

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

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        if(!videoOutput.isOpened())
        {
            videoOutput.open(filePath, CV_FOURCC('P','I','M','1'),fps, frameSize,true);
            if(!videoOutput.isOpened())
            {
                cout<<"Error : can't write to file"<<endl;
                return -1;
            }
        }

        videoOutput.write(frame);

        imshow("MyVideo", frame); //show the frame in "MyVideo" window

        if (waitKey(10) == 1048603) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }


    }

    cap.release();
    videoOutput.release();

    return 0;
}