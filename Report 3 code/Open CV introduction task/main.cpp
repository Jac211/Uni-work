#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Load image
    Mat img = imread("example.jpg");

    // Convert image to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Apply Gaussian blur to remove noise
    Mat blur;
    GaussianBlur(gray, blur, Size(5, 5), 0);

    // Apply Canny edge detection
    Mat edges;
    Canny(blur, edges, 50, 150);

    // Display result
    namedWindow("edges", WINDOW_NORMAL);
    imshow("edges", edges);
    waitKey(0);
    destroyAllWindows();

    return 0;
}

