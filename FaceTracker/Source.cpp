//#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/face.hpp"
//#include "opencv2/face/facemark.hpp"
//#include "opencv2/face/facemarkLBF.hpp"
//
//#include <iostream>
//#include <cstdio>
//#include <vector>
//#include <algorithm>
//#include <chrono>
//
//
//// Functions for facial feature detection
//static void detectFaces(cv::Mat&, std::vector<cv::Rect_<int> >&, std::string);
//static void detectFacialLandmarks(cv::Mat& img, const std::vector<cv::Rect_<int> > faces, cv::Mat& frame);
//
//std::string face_cascade_path;
//cv::CascadeClassifier face_cascade;
//
//// Create an instance of Facemark
//cv::Ptr<cv::face::Facemark> facemark = cv::face::FacemarkLBF::create();
//
//
//int main(int argc, char** argv)
//{
//    face_cascade_path = "data/haarcascades/haarcascade_frontalface_default.xml";
//
//    facemark->loadModel("data/lbfmodel.yaml");
//
//    if (face_cascade_path != "")
//        face_cascade.load(cv::samples::findFile(face_cascade_path));
//
//    cv::VideoCapture cap(0);
//
//
//    for (;;)
//    {
//        if (!cap.isOpened()) {
//            std::cout << "Video Capture Fail" << std::endl;
//            break;
//        }
//        else {
//            auto t1 = std::chrono::high_resolution_clock::now();
//
//            cv::Mat image, grey;
//            cap >> image;
//
//            resize(image, image, cv::Size(460, 460), 0, 0, cv::INTER_LINEAR_EXACT);
//            cvtColor(image, grey, cv::COLOR_BGR2GRAY);
//
//            std::vector<cv::Rect_<int> > faces;
//            detectFaces(grey, faces, face_cascade_path);
//            detectFacialLandmarks(grey, faces, image);
//
//            namedWindow("Live", cv::WINDOW_AUTOSIZE);
//            imshow("Live", image);
//            cv::waitKey(5);
//
//            auto t3 = std::chrono::high_resolution_clock::now();
//            std::cout << "FPS : " << 1e6 / std::chrono::duration_cast<std::chrono::microseconds>(t3 - t1).count() << std::endl;
//        }
//    }
//}
//
//static void detectFaces(cv::Mat& img, std::vector<cv::Rect_<int> >& faces, std::string cascade_path)
//{
//    if (!face_cascade.empty()) {
//        face_cascade.detectMultiScale(img, faces, 1.15, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(100, 100));
//        if(!faces.size()==0)
//            std::cout << "wow! there is a face!" << std::endl;
//    }
//    return;
//}
//
//static void detectFacialLandmarks(cv::Mat& img, const std::vector<cv::Rect_<int> > faces, cv::Mat& frame) {
//    std::vector<std::vector<cv::Point2f>> landmarks;
//
//    // Run landmark detector
//    bool success = facemark->fit(img, faces, landmarks);
//    if (success) {
//        for (int face = 0; face < landmarks.size(); face++)
//        {
//            rectangle(frame, cv::Point(faces[face].x, faces[face].y),
//                cv::Point(faces[face].x + faces[face].width, faces[face].y + faces[face].height),
//                cv::Scalar(255, 0, 255), 2, 8, 0);
//            int point = 0;
//            for (; point < 17; point++)
//            {
//                circle(frame, landmarks[face][point], 2, cv::Scalar(255, 255, 0), -1, 8);
//            }
//            for (; point < 22; point++)
//            {
//                circle(frame, landmarks[face][point], 2, cv::Scalar(0, 255, 0), -1, 8);
//            }
//            for (; point < 27; point++)
//            {
//                circle(frame, landmarks[face][point], 2, cv::Scalar(255, 0, 0), -1, 8);
//            }
//            for (; point < 36; point++)
//            {
//                circle(frame, landmarks[face][point], 2, cv::Scalar(255, 0, 255), -1, 8);
//            }
//            for (; point < 48; point++)
//            {
//                circle(frame, landmarks[face][point], 2, cv::Scalar(0, 0, 255), -1, 8);
//            }
//            for (; point < 68; point++)
//            {
//                circle(frame, landmarks[face][point], 2, cv::Scalar(255, 255, 255), -1, 8);
//            }
//        }
//    }
//}
//
////
////#include <SFML/Graphics.hpp>
////
////int main()
////{
////    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
////    sf::CircleShape shape(300.f);
////    shape.setFillColor(sf::Color::Green);
////
////    while (window.isOpen())
////    {
////        sf::Event event;
////        while (window.pollEvent(event))
////        {
////            if (event.type == sf::Event::Closed)
////                window.close();
////        }
////
////        window.clear();
////        window.draw(shape);
////        window.display();
////    }
////
////    return 0;
////}