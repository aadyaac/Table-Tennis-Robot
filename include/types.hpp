#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct BallObservation {
    double x;
    double y;
    std::int64_t timestamp_ms;
};

struct TrajectoryState {
    double vx;
    double vy;
    double projected_x;
    double projected_y;
    std::int64_t intercept_time_ms;
};

struct ShotCommand {
    double pan_deg;
    double tilt_deg;
    int launcher_pwm;
    int dwell_ms;
};

struct TrainingRoutine {
    std::string name;
    std::vector<ShotCommand> sequence;
    bool adaptive_mode;
};
