#pragma once

#include "../Common/Common.h"

	
    

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("shapes.jpg", IMREAD_COLOR);
    imshow("IMREAD_COLOR", src);

    Mat gray;
    cvtColor(src, gray, COLOR_RGB2GRAY);
    imshow("COLOR_RGB2GRAY", gray);

    Mat binary;
    threshold(gray, binary, 200, 255, THRESH_BINARY);
    imshow("binary", binary);

    bitwise_not(binary, binary);
    imshow("bitwise_not", binary);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);

    drawContours(src, contours, -1, Scalar(0, 0, 0), 4);
    imshow("drawContours", src);

    for (size_t i = 0; i < contours.size(); i++) {
        double epsilon = 0.01 * arcLength(contours[i], true);
        vector<Point> approx;
        approxPolyDP(contours[i], approx, epsilon, true);

        drawContours(src, vector<vector<Point>>{approx}, 0, Scalar(0, 0, 0), 2);

        int contour_area = approx.size();
       

        putText(src, "index is =" + to_string(i), Point(approx[0].x, approx[0].y + 30), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 0), 1);
        putText(src, to_string(contour_area), approx[0], FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 0), 1);

        if (contour_area == 4) {
            cout << "사각형" << endl;
            putText(src, "square", Point(approx[0].x, approx[0].y + 50), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 0), 1);
        }
        else if (contour_area == 3) {
            cout << "삼각형" << endl;
            putText(src, "triangle", Point(approx[0].x, approx[0].y + 50), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 0), 1);
        }
        else if (contour_area > 10) {
            cout << "원" << endl;
            putText(src, "circle", Point(approx[0].x, approx[0].y + 50), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 0), 1);
        }
        else {
            cout << "지정되지 않은 도형" << endl;
        }

        double area = contourArea(contours[i]);
        cout << "도형의 면적: " << area << endl;

        Rect bounding_rect = boundingRect(contours[i]);
        rectangle(src, bounding_rect, Scalar(0, 255, 0), 2);
        int width = bounding_rect.width;
        int height = bounding_rect.height;
        cout << "가로 길이: " << width << endl;
        cout << "세로 길이: " << height << endl;
        // 도형의 가로세로
    }

    imshow("src", src);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
