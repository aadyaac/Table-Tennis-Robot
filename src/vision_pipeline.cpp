#include "vision_pipeline.hpp"

#include <opencv2/imgproc.hpp>
#include <stdexcept>

BallObservation VisionPipeline::detectBall(const cv::Mat& frame, std::int64_t timestamp_ms) const {
    if (frame.empty()) {
        throw std::runtime_error("VisionPipeline received an empty frame");
    }

    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    cv::Mat mask;
    cv::inRange(hsv, cv::Scalar(5, 80, 80), cv::Scalar(30, 255, 255), mask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    double best_area = 0.0;
    cv::Point2f center(static_cast<float>(frame.cols / 2), static_cast<float>(frame.rows / 2));

    for (const auto& contour : contours) {
        const double area = cv::contourArea(contour);
        if (area > best_area) {
            cv::Moments moments = cv::moments(contour);
            if (moments.m00 != 0.0) {
                center = cv::Point2f(
                    static_cast<float>(moments.m10 / moments.m00),
                    static_cast<float>(moments.m01 / moments.m00)
                );
                best_area = area;
            }
        }
    }

    return {center.x, center.y, timestamp_ms};
}
