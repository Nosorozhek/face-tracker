#pragma once

#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/videoio.hpp>

#include <SFML/Graphics.hpp>

#include <vector>

#include "model.h"

class App
{
   public:
    App();
    ~App();
    void RecognizeLandmarks();
    void GenerateModel();
    void RenderModel();

   private:
    std::list<std::vector<cv::Point2f>> facial_points_;
    Model source_model_;
    Model obtained_model_;
    sf::RenderWindow window_{sf::VideoMode(600, 600), "App"};
    // Variables used in landmark_generator
    cv::Ptr<cv::FaceDetectorYN> face_detector_;
    cv::Ptr<cv::face::Facemark> landmark_detector_;
    cv::VideoCapture capture_{0};
    int frame_width_;
    int frame_height_;
};
