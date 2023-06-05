#include "app.h"

App::App()
{
    landmark_detector_ = cv::face::FacemarkLBF::create();
    face_detector_ = cv::FaceDetectorYN::create("data/DNN/yunet_s_320_320.onnx", "",
                                          cv::Size(320, 320),
                                          0.9,  // Score Threshold
                                          0.3,  // NMS Threshold
                                          5);
    source_model_ = Model("path");
    obtained_model_ = source_model_;
}