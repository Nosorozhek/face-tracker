#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "app.h"

// This func finds biggest face of all in the frame
cv::Rect2i GetBiggestFace(cv::Mat& faces);

void Visualize(cv::Mat& frame, const std::vector<cv::Point2f>& landmarks);

void App::RecognizeLandmarks()
{
    // Get frame
    cv::Mat frame;
    if (!capture_.read(frame))
    {
        std::cout << "Can't grab the frame" << std::endl;
        return;
    }
    resize(frame, frame, cv::Size(frame_width_, frame_height_));
    // Inference
    cv::Mat all_faces;
    face_detector_->detect(frame, all_faces);
    if (all_faces.rows == 0)
    {
        std::cout << "No faces detected" << std::endl;
        return;
    }
    const cv::Rect2i face = GetBiggestFace(all_faces);
    std::vector<std::vector<cv::Point2f>> landmarks;
    cv::Mat grey;
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

    landmark_detector_->fit(grey, std::vector<cv::Rect2i>{face},
                            landmarks);
    facial_points_.push(landmarks[0]);
    if (facial_points_.size() > 3)
    {
        facial_points_.pop();
    }

    Visualize(frame, landmarks[0]);
}


//Finds biggest face of all in the frame
cv::Rect2i GetBiggestFace(cv::Mat& faces)
{
    int right_face = 0;
    int max_height = 0;
    for (int face = 0; face < faces.rows; face++)
    {
        const int height = (faces.at<int>(face, 0)) - (faces.at<int>(face, 2));
        if (height > max_height)
        {
            right_face = face;
            max_height = height;
        }
    }
    
    return {static_cast<int>(faces.at<float>(right_face, 0)),
            static_cast<int>(faces.at<float>(right_face, 1)),
            static_cast<int>(faces.at<float>(right_face, 2)),
            static_cast<int>(faces.at<float>(right_face, 3))};
}

// Displays landmarks just for debugging
void Visualize(cv::Mat& frame, const std::vector<cv::Point2f>& landmarks)
{
    int point = 0;
    // Face contour and chin
    for (; point < 17; point++)
    {
        circle(frame, landmarks[point], 2, cv::Scalar(255, 255, 0), -1, 8);
    }
    // Left eyebrow
    for (; point < 22; point++)
    {
        circle(frame, landmarks[point], 2, cv::Scalar(0, 255, 0), -1, 8);
    }
    // Right eyebrow
    for (; point < 27; point++)
    {
        circle(frame, landmarks[point], 2, cv::Scalar(255, 0, 0), -1, 8);
    }
    // Nose
    for (; point < 36; point++)
    {
        circle(frame, landmarks[point], 2, cv::Scalar(255, 0, 255), -1, 8);
    }
    // Eyes
    for (; point < 48; point++)
    {
        circle(frame, landmarks[point], 2, cv::Scalar(0, 0, 255), -1, 8);
    }
    // Lips contour
    for (; point < 68; point++)
    {
        circle(frame, landmarks[point], 2, cv::Scalar(255, 255, 255), -1, 8);
    }
    cv::imshow("Landmarks", frame);
}
