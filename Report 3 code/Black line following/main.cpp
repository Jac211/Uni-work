#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Error: could not open camera" << endl;
        return -1;
    }

    Mat frame;
    namedWindow("frame", WINDOW_NORMAL);

    while (true)
    {
        cap >> frame;

        Mat gray, thresh;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        threshold(gray, thresh, 100, 255, THRESH_BINARY);

        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if (contours.size() > 0)
        {
            int largestContourIndex = 0;
            double largestArea = contourArea(contours[0]);

            for (int i = 1; i < contours.size(); i++)
            {
                double area = contourArea(contours[i]);
                if (area > largestArea)
                {
                    largestContourIndex = i;
                    largestArea = area;
                }
            }

            Moments moments = cv::moments(contours[largestContourIndex], true);
            Point centroid(moments.m10 / moments.m00, moments.m01 / moments.m00);

            circle(frame, centroid, 5, Scalar(0, 0, 255), -1);

            if (centroid.x < frame.cols / 2)
            {
                cout << "Turn left" << endl;
                // Add code to turn left here
            }
            else
            {
                cout << "Turn right" << endl;
                // Add code to turn right here
            }
        }

        imshow("frame", frame);

        if (waitKey(30) == 27)
        {
            break;
        }
    }

    return 0;
}
