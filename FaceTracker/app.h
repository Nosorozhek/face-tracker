#pragma once

#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facemark.hpp>

#include <SFML/Graphics.hpp>

#include <queue>
#include <vector>
#include <opencv2/videoio.hpp>

#include "structs.h"
#include "model.h"

class App
{
   private:
    cv::Ptr<cv::FaceDetectorYN> face_detector_;
    cv::Ptr<cv::face::Facemark> landmark_detector_;
    cv::VideoCapture capture_;
    std::queue<std::vector<Vector2F>> facial_points_;
    Model source_model_;
    Model obtained_model_;
    const sf::RenderWindow& window_ =
        sf::RenderWindow(sf::VideoMode(600, 600), "App");

   public:
    App();
    ~App();
    void RecognizeLandmarks();
    void GenerateModel();
    void RenderModel();
};
