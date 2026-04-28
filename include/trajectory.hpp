#pragma once

#include "types.hpp"

class TrajectoryPredictor {
public:
    TrajectoryState estimate(const BallObservation& previous, const BallObservation& current) const;
};
