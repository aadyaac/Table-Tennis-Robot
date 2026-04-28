#pragma once

#include "types.hpp"
#include <opencv2/core.hpp>

class VisionPipeline {
public:
    BallObservation detectBall(const cv::Mat& frame, std::int64_t timestamp_ms) const;
};
