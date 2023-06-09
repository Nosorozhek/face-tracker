#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

#include "app.h"

// This func finds biggest face of all in the frame
cv::Rect_<int> BiggestFace(cv::Mat faces);

void App::RecognizeLandmarks()
{
    // Get frame
    cv::Mat frame;
    if (!capture_.read(frame))
    {
        std::cout << "Can't grab the frame" << std::endl;
        return;
    }
    resize(frame, frame, cv::Size(frame_width_, frame_height_), 0, 0,
           cv::INTER_LINEAR_EXACT);
    // Inference
    cv::Mat all_faces;
    face_detector_->detect(frame, all_faces);
    if (all_faces.rows == 0)
    {
        std::cout << "No faces detected" << std::endl;
        return;
    }
    const cv::Rect_<int> face = BiggestFace(all_faces);
    std::vector<std::vector<cv::Point2f>> landmarks;
    cv::Mat grey;
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

    landmark_detector_->fit(grey, std::vector<cv::Rect_<int>>(1, face),
                            landmarks);
    facial_points_.push(landmarks[0]);
    if (facial_points_.size() > 3)
    {
        facial_points_.pop();
    }
}


//This func finds biggest face of all in the frame
cv::Rect_<int> BiggestFace(cv::Mat faces)
{
    int right_face = 0;
    int max_height = 0;
    for (int face = 0; face < faces.rows; face++)
    {
        const int height = static_cast<int>(faces.at<float>(face, 0)) -
                           static_cast<int>(faces.at<float>(face, 2));
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
