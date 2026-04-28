#include "trajectory.hpp"

TrajectoryState TrajectoryPredictor::estimate(const BallObservation& previous, const BallObservation& current) const {
    const double dt_ms = static_cast<double>(current.timestamp_ms - previous.timestamp_ms);
    const double dt = dt_ms <= 0.0 ? 1.0 : dt_ms;

    const double vx = (current.x - previous.x) / dt;
    const double vy = (current.y - previous.y) / dt;

    const std::int64_t lookahead_ms = 180;
    const double projected_x = current.x + vx * lookahead_ms;
    const double projected_y = current.y + vy * lookahead_ms;

    return {vx, vy, projected_x, projected_y, current.timestamp_ms + lookahead_ms};
}
