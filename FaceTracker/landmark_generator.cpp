 #include <opencv2/dnn.hpp>
 #include <opencv2/imgproc.hpp>
 #include <opencv2/highgui.hpp>

#include <iostream>

#include "app.h"

static void Visualize(cv::Mat& frame, std::vector<cv::Rect_<int>> faces,
                      std::vector<std::vector<cv::Point2f>> landmarks);

void App::RecognizeLandmarks()
{
    cv::Mat frame;
    if (!capture_.read(frame))
    {
        std::cerr << "Can't grab frame! Stop\n";
    }
    //cv::resize(frame, frame, cv::Size(frameWidth, frameHeight));

    // Inference
    cv::Mat faces;
    cv::TickMeter tm;

    tm.start();
    face_detector_->detect(frame, faces);

    cv::Mat grey;
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect_<int>> rects(faces.rows);
    for (int i = 0; i < faces.rows; i++)
    {
        rects[i] =
            cv::Rect_<int>(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)),
                           int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3)));
    }

    std::vector<std::vector<cv::Point2f>> landmarks;

    // Run landmark detector
    bool success = landmark_detector_->fit(grey, rects, landmarks);
    

    // Visualize results
    Visualize(frame, rects, landmarks);
}

static void Visualize(cv::Mat& frame, std::vector<cv::Rect_<int>> faces,
                      std::vector<std::vector<cv::Point2f>> landmarks)
{
    for (int face = 0; face < landmarks.size(); face++)
    {
        rectangle(frame, cv::Point(faces[face].x, faces[face].y),
                  cv::Point(faces[face].x + faces[face].width,
                            faces[face].y + faces[face].height),
                  cv::Scalar(255, 0, 255), 2, 8, 0);
        int point = 0;
        for (; point < 17; point++)
        {
            circle(frame, landmarks[face][point], 2, cv::Scalar(255, 255, 0),
                   -1, 8);
        }
        for (; point < 22; point++)
        {
            circle(frame, landmarks[face][point], 2, cv::Scalar(0, 255, 0), -1,
                   8);
        }
        for (; point < 27; point++)
        {
            circle(frame, landmarks[face][point], 2, cv::Scalar(255, 0, 0), -1,
                   8);
        }
        for (; point < 36; point++)
        {
            circle(frame, landmarks[face][point], 2, cv::Scalar(255, 0, 255),
                   -1, 8);
        }
        for (; point < 48; point++)
        {
            circle(frame, landmarks[face][point], 2, cv::Scalar(0, 0, 255), -1,
                   8);
        }
        for (; point < 68; point++)
        {
            circle(frame, landmarks[face][point], 2, cv::Scalar(255, 255, 255),
                   -1, 8);
        }
    }
    imshow("Live", frame);
}