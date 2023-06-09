#include "app.h"

App::App()
{
    frame_width_ = static_cast<int>(capture_.get(cv::CAP_PROP_FRAME_WIDTH));
    frame_height_ = static_cast<int>(capture_.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Some AI tracking faces on the frame
    face_detector_ = cv::FaceDetectorYN::create("data/DNN/yunet_s_320_320.onnx", "",
                                          cv::Size(320, 320),
                                          0.9f,  // Score Threshold
                                          0.3f,  // NMS Threshold
                                          5     // topK
                                          );
    face_detector_->setInputSize(cv::Size(frame_width_, frame_height_));

    // Some AI to find landmarks on received faces
    landmark_detector_ = cv::face::FacemarkLBF::create();
    landmark_detector_->loadModel("data/lbfmodel.yaml");

    source_model_ = Model("path");
    obtained_model_ = Model("path");

    window_.setActive(true);
}

App::~App()
{ return; }
