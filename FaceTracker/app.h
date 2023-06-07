#pragma once

#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#include <SFML/Graphics.hpp>

#include <iostream>
#include <queue>
#include <vector>


#include "structs.h"
#include "model.h"

class App
{
   private:
    
    std::queue<std::vector<cv::Point2f>> facial_points_;
    Model source_model_;
    Model obtained_model_;
    sf::RenderWindow window_ {sf::VideoMode(600, 600), "App"};
    // Variables used in landmark_generator
    cv::Ptr<cv::FaceDetectorYN> face_detector_;
    cv::Ptr<cv::face::Facemark> landmark_detector_;
    cv::VideoCapture capture_;
    int frameWidth_, frameHeight_;


   public:
    App();
    ~App();
    void RecognizeLandmarks();
    void GenerateModel();
    void RenderModel();
};
