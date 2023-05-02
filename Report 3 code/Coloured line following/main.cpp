#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened()) // check if camera opened successfully
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    while (1)
    {
        Mat frame;
        cap.read(frame);

        Mat hsv, mask;
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(20, 50, 50), Scalar(30, 255, 255), mask);

        Moments M = moments(mask);
        if (M.m00 > 0)
        {
            int cx = M.m10 / M.m00;
            int cy = M.m01 / M.m00;
            circle(frame, Point(cx, cy), 4, Scalar(0, 255, 0), -1);

            if (cx < frame.cols / 2)
            {
                cout << "Turn Left" << endl;
            }
            else
            {
                cout << "Turn Right" << endl;
            }
        }

        imshow("Frame", frame);
        imshow("Mask", mask);

        if (waitKey(1) == 27) // press Esc to exit
        {
            break;
        }
    }

    cap.release(); // release the video capture object
    destroyAllWindows(); // close all windows
    return 0;
}
