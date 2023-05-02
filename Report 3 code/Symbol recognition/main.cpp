#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load the image
    Mat image = imread("symbol.jpg");

    // Convert the image to HSV
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // Define the range of colours to isolate
    Scalar lowerRange(20, 100, 100);
    Scalar upperRange(30, 255, 255);

    // Create a mask by thresholding the image
    Mat mask;
    inRange(hsvImage, lowerRange, upperRange, mask);

    // Find contours in the mask
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Draw the contours on the original image
    drawContours(image, contours, -1, Scalar(0, 0, 255), 2);

    // Display the result
    namedWindow("Symbol Recognition", WINDOW_NORMAL);
    imshow("Symbol Recognition", image);
    waitKey(0);

    return 0;
}
