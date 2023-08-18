#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Load image
    Mat img = imread("sample.jpg", IMREAD_GRAYSCALE);

    if (img.empty())
    {
        cout << "Could not read image file" << endl;
        return -1;
    }

    // Set threshold value for detecting stars
    double thresh = 200;

    // Perform binary thresholding to detect stars
    Mat binary_img;
    threshold(img, binary_img, thresh, 255, THRESH_BINARY);

    // Create a SimpleBlobDetector object
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();

    // Detect blobs (stars) in the binary image
    vector<KeyPoint> keypoints;
    detector->detect(binary_img, keypoints);

    // Draw circles around detected stars
    Mat output_img;
    cvtColor(img, output_img, COLOR_GRAY2BGR);
    for (int i = 0; i < keypoints.size(); i++)
    {
        Point center(keypoints[i].pt.x, keypoints[i].pt.y);
        int radius = keypoints[i].size / 2;
        circle(output_img, center, radius, Scalar(0, 0, 255), 2);
    }

    // Display output image with detected stars
    imshow("Star Detection", output_img);
    waitKey(0);

    return 0;
}

