#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

#include "app.h"

void App::GenerateModel()
{
    // Averaging facial points
    std::vector<cv::Point2f> avg_facial_points(facial_points_.front().size());
    for (auto& landmarks : facial_points_)
    {
        for (size_t point = 0; point < avg_facial_points.size(); ++point)
        {
            avg_facial_points[point] += landmarks[point];
        }
    }
    for (auto& point : avg_facial_points)
    {
        point /= static_cast<int>(facial_points_.size());
    }
    /*
     * These are the positions of all 68 points of the face.
     * Their indexes in the array coincide with the numbers in the image.
     * We need only some of them.
     ________________________________________________________________________
     |                                                                      |
     |                    19                          24                    |
     |               18        20                23        25               |
     |           17                 21      22                 26           |
     |                                                                      |
     |                    37  38        27        43  44                    |
     |    00           36        39            42        45           16    |
     |                    41  40                  47  46                    |
     |                                  28                                  |
     |                                                                      |
     |    01                                                          15    |
     |                                  29                                  |
     |                                                                      |
     |                                                                      |
     |     02                           30                           14     |
     |                            31          35                            |
     |                               32 33 34                               |
     |                                                                      |
     |      03                       50    52                       13      |
     |                           49     51     53                           |
     |                     48 60     61 62 63     64 54                     |
     |                                                                      |
     |         04               59   67 66 65   55               12         |
     |                              58      56                              |
     |                                  57                                  |
     |              05                                      11              |
     |                                                                      |
     |                                                                      |
     |                    06                          10                    |
     |                                                                      |
     |                          07              09                          |
     |                                  08                                  |
     |                                                                      |
     |______________________________________________________________________|
     */

    // Actual 2D image points
    std::vector<cv::Point2d> image_points;
    image_points.push_back(avg_facial_points[30]);  // Nose tip
    image_points.push_back(avg_facial_points[8]);   // Chin
    image_points.push_back(avg_facial_points[36]);  // Left eye left corner
    image_points.push_back(avg_facial_points[45]);  // Right eye right corner
    image_points.push_back(avg_facial_points[48]);  // Left Mouth corner
    image_points.push_back(avg_facial_points[54]);  // Right mouth corner

    // These are the spatial coordinates of the facial points of a real person.
    // At least, they are roughly like this.
    std::vector<cv::Point3d> model_points;
    model_points.emplace_back(0.0, 0.0, 0.0);          // Nose tip
    model_points.emplace_back(0.0, -330.0, -65.0);     // Chin
    model_points.emplace_back(-225.0, 170.0, -135.0);  // Left eye left corner
    model_points.emplace_back(225.0, 170.0, -135.0);   // Right eye right corner
    model_points.emplace_back(-150.0, -150.0, -125.0);  // Left Mouth corner
    model_points.emplace_back(150.0, -150.0, -125.0);   // Right mouth corner

    // Camera internals
    const double focal_length = frame_width_;
    const auto center = cv::Point2d(static_cast<double>(frame_width_) / 2,
                                    static_cast<double>(frame_height_) / 2);
    const cv::Mat camera_matrix =
        (cv::Mat_<double>(3, 3) << focal_length, 0, center.x, 0, focal_length,
         center.y, 0, 0, 1);
    const cv::Mat distance_coefficients =
        cv::Mat::zeros(4, 1, cv::DataType<double>::type);

    // Output rotation and translation
    cv::Mat rotation_vector;  // Rotation in axis-angle form
    cv::Mat translation_vector;

    // Solve for pose
    cv::solvePnP(model_points, image_points, camera_matrix,
                 distance_coefficients, rotation_vector, translation_vector);
}