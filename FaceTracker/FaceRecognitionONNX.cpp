//#include <onnxruntime_cxx_api.h>
//
//#include <opencv2/dnn.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/objdetect.hpp>
//
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//static void visualize(Mat& input, int frame, Mat& faces, double fps, int thickness = 2)
//{
//    std::string fpsString = cv::format("FPS : %.2f", (float)fps);
//    if (frame >= 0)
//        cout << "Frame " << frame << ", ";
//    cout << "FPS: " << fpsString << endl;
//    for (int i = 0; i < faces.rows; i++)
//    {
//        // Print results
//        cout << "Face " << i
//            << ", top-left coordinates: (" << faces.at<float>(i, 0) << ", " << faces.at<float>(i, 1) << "), "
//            << "box width: " << faces.at<float>(i, 2) << ", box height: " << faces.at<float>(i, 3) << ", "
//            << "score: " << cv::format("%.2f", faces.at<float>(i, 14))
//            << endl;
//        // Draw bounding box
//        rectangle(input, Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), Scalar(0, 255, 0), thickness);
//        // Draw landmarks
//        circle(input, Point2i(int(faces.at<float>(i, 4)), int(faces.at<float>(i, 5))), 2, Scalar(255, 0, 0), thickness);
//        circle(input, Point2i(int(faces.at<float>(i, 6)), int(faces.at<float>(i, 7))), 2, Scalar(0, 0, 255), thickness);
//        circle(input, Point2i(int(faces.at<float>(i, 8)), int(faces.at<float>(i, 9))), 2, Scalar(0, 255, 0), thickness);
//        circle(input, Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 2, Scalar(255, 0, 255), thickness);
//        circle(input, Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 2, Scalar(0, 255, 255), thickness);
//    }
//    putText(input, fpsString, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
//}
//int main(int argc, char** argv)
//{
//    String fd_modelPath = "data/DNN/yunet_s_320_320.onnx";
//    //String fr_modelPath = "data/DNN/face_recognition_sface_2021dec.onnx";
//    float scoreThreshold = 0.9;
//    float nmsThreshold = 0.3;
//    int topK = 5000;
//    bool save = false;
//    float scale = 1.0;
//    double cosine_similar_thresh = 0.363;
//    double l2norm_similar_thresh = 1.128;
//
//    // Initialize FaceDetectorYN
//    Ptr<FaceDetectorYN> detector = FaceDetectorYN::create(fd_modelPath, "", Size(320, 320), scoreThreshold, nmsThreshold, topK);
//    TickMeter tm;
//
//
//    // If input is an image
//    int frameWidth, frameHeight;
//    cv::VideoCapture capture(0);
//
//    if (capture.isOpened())
//    {
//        frameWidth = int(capture.get(CAP_PROP_FRAME_WIDTH) * scale);
//        frameHeight = int(capture.get(CAP_PROP_FRAME_HEIGHT) * scale);
//        cout << "width=" << frameWidth
//            << ", height=" << frameHeight
//            << endl;
//    }
//    else
//    {
//        cout << "Could not initialize video capturing\n";
//        return 1;
//    }
//    detector->setInputSize(Size(frameWidth, frameHeight));
//    int nFrame = 0;
//    for (;;)
//    {
//        // Get frame
//        Mat frame;
//        if (!capture.read(frame))
//        {
//            cerr << "Can't grab frame! Stop\n";
//            break;
//        }
//        resize(frame, frame, Size(frameWidth, frameHeight));
//
//        // Inference
//        Mat faces;
//        tm.start();
//        detector->detect(frame, faces);
//        tm.stop();
//        Mat result = frame.clone();
//
//        // Draw results on the input image
//        visualize(result, nFrame, faces, tm.getFPS());
//
//        // Visualize results
//        imshow("Live", result);
//        int key = waitKey(1);
//
//        ++nFrame;
//        if (key > 0)
//            break;
//    }
//    cout << "Processed " << nFrame << " frames" << endl;
//
//    cout << "Done." << endl;
//    return 0;
//}