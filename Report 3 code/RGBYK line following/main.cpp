#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
    // initialize video capture object
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Error: Could not open video capture." << endl;
        return -1;
    }

    // initialize image matrices
    Mat frame, hsv, thresholded;

    // initialize values for color thresholds
    int red_low_H = 0, red_high_H = 10, red_low_S = 100, red_high_S = 255, red_low_V = 100, red_high_V = 255;
    int green_low_H = 40, green_high_H = 80, green_low_S = 100, green_high_S = 255, green_low_V = 100, green_high_V = 255;
    int blue_low_H = 100, blue_high_H = 130, blue_low_S = 100, blue_high_S = 255, blue_low_V = 100, blue_high_V = 255;
    int yellow_low_H = 20, yellow_high_H = 30, yellow_low_S = 100, yellow_high_S = 255, yellow_low_V = 100, yellow_high_V = 255;
    int black_low_H = 0, black_high_H = 255, black_low_S = 0, black_high_S = 255, black_low_V = 0, black_high_V = 50;

    // initialize variables for line following
    double Kp = 0.5, Kd = 0.3, Ki = 0.1;
    double previous_error = 0, integral = 0;
    double error, derivative, output;

    while (true) {
        // read frame from video capture
        cap.read(frame);

        // convert to HSV color space
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // threshold for red line
        inRange(hsv, Scalar(red_low_H, red_low_S, red_low_V), Scalar(red_high_H, red_high_S, red_high_V), thresholded);
        // find contours of thresholded image
        vector<vector<Point>> contours;
        findContours(thresholded, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if (!contours.empty()) {
            // find largest contour
            double max_area = 0;
            int max_area_idx = -1;
            for (int i = 0; i < contours.size(); i++) {
                double area = contourArea(contours[i]);
                if (area > max_area) {
                    max_area = area;
                    max_area_idx = i;
                }
            }
            // find centroid of largest contour
            Moments m = moments(contours[max_area_idx]);
            Point centroid(m.m10/m.m00, m.m01/m.m00);

            // calculate error and PID output
            error = centroid.x - frame.cols/2;
            integral += error;
            derivative = error - previous_error;
            output = Kp*error + Ki*integral + Kd*derivative;
            previous_error = error;

            // turn left or right based on output
            if (output < 0) {
                cout << "Turn left." << endl;
            }
            else if (output > 0) {
                cout << "Turn right." << endl;
            }
            else {
                cout << "Go straight." << endl;
            }
        }
