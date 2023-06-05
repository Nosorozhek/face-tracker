#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/face/facemarkLBF.hpp>

#include <iostream>


using namespace cv;
using namespace std;


static void detectFacialLandmarks(cv::Mat& grey, const std::vector<cv::Rect_<int> > faces, cv::Mat& frame);


// Create an instance of Facemark
cv::Ptr<cv::face::Facemark> facemark = cv::face::FacemarkLBF::create();


// Initialize FaceDetectorYN
Ptr<FaceDetectorYN> detector =
    FaceDetectorYN::create("data/DNN/yunet_s_320_320.onnx", "", Size(320, 320),
                           0.9,  // Score Threshold
                           0.3,  // NMS Threshold
                           5);


int main(int argc, char** argv)
{
    TickMeter tm;
    float scale = 1.0;

    facemark->loadModel("data/lbfmodel.yaml");

    int frameWidth, frameHeight;
    cv::VideoCapture capture(0);

    if (capture.isOpened())
    {
        frameWidth = int(capture.get(CAP_PROP_FRAME_WIDTH) * scale);
        frameHeight = int(capture.get(CAP_PROP_FRAME_HEIGHT) * scale);
        cout << "width=" << frameWidth << ", height=" << frameHeight << endl;
    }
    else
    {
        cout << "Could not initialize video capturing\n";
        return 1;
    }

    detector->setInputSize(Size(frameWidth, frameHeight));

    for (;;)
    {
        // Get frame
        Mat frame;
        if (!capture.read(frame))
        {
            cerr << "Can't grab frame! Stop\n";
            break;
        }
        resize(frame, frame, Size(frameWidth, frameHeight));

        // Inference
        Mat faces;
        tm.start();
        detector->detect(frame, faces);

        Mat grey;
        cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect_<int>> rects(faces.rows);
        for (int i = 0; i < faces.rows; i++)
        {
            rects[i] = Rect_<int>(
                int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)),
                int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3)));
        }

        detectFacialLandmarks(grey, rects, frame);
        tm.stop();

        std::cout.precision(3);
        std::cout << "FPS : " << tm.getFPS() << std::endl;

        // Visualize results
        imshow("Live", frame);
        int key = waitKey(1);

        if (key > 0) break;
    }
    return 0;
}

static void detectFacialLandmarks(cv::Mat& grey,
                                  const std::vector<cv::Rect_<int>> faces,
                                  cv::Mat& frame)
{
    std::vector<std::vector<cv::Point2f>> landmarks;

    // Run landmark detector
    bool success = facemark->fit(grey, faces, landmarks);
    if (success)
    {
        for (int face = 0; face < landmarks.size(); face++)
        {
            rectangle(frame, cv::Point(faces[face].x, faces[face].y),
                      cv::Point(faces[face].x + faces[face].width,
                                faces[face].y + faces[face].height),
                      cv::Scalar(255, 0, 255), 2, 8, 0);
            int point = 0;
            for (; point < 17; point++)
            {
              circle(frame, landmarks[face][point], 2, cv::Scalar(255, 255, 0),
                     -1, 8);
            }
            for (; point < 22; point++)
            {
              circle(frame, landmarks[face][point], 2, cv::Scalar(0, 255, 0),
                     -1, 8);
            }
            for (; point < 27; point++)
            {
              circle(frame, landmarks[face][point], 2, cv::Scalar(255, 0, 0),
                     -1, 8);
            }
            for (; point < 36; point++)
            {
              circle(frame, landmarks[face][point], 2, cv::Scalar(255, 0, 255),
                     -1, 8);
            }
            for (; point < 48; point++)
            {
              circle(frame, landmarks[face][point], 2, cv::Scalar(0, 0, 255),
                     -1, 8);
            }
            for (; point < 68; point++)
            {
              circle(frame, landmarks[face][point], 2,
                     cv::Scalar(255, 255, 255), -1, 8);
            }
        }
    }
}
