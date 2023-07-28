#include "app.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <gl/GLU.h>

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

    source_model_ = Model("images/model.obj");
    obtained_model_ = Model("images/model.obj");

    // prepare OpenGL surface for HSR
    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 300.0f);  // fov, aspect, zNear, zFar
}

App::~App()
{ return; }
