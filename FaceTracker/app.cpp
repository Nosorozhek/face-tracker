#include "app.h"

App::App()
{
    cv::VideoCapture capture_(0); //This thing recieves pictures from camera
    frameWidth_ = int(capture_.get(cv::CAP_PROP_FRAME_WIDTH));
    frameHeight_ = int(capture_.get(cv::CAP_PROP_FRAME_HEIGHT));
    // Some AI tracking faces on the frame
    face_detector_ = cv::FaceDetectorYN::create("data/DNN/yunet_s_320_320.onnx", "",
                                          cv::Size(320, 320),
                                          0.9,  // Score Threshold
                                          0.3,  // NMS Threshold
                                          5     //topK
                                          );
    face_detector_->setInputSize(cv::Size(frameWidth_, frameHeight_));
    // Some AI to find landmarks on received faces
    landmark_detector_ = cv::face::FacemarkLBF::create();
    landmark_detector_->loadModel("data/lbfmodel.yaml");

    source_model_ = Model("path");
    obtained_model_ = Model("path");
}

App::~App()
{ return; }
