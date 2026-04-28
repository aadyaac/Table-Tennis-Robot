#pragma once

#include "types.hpp"

class RoutineManager {
public:
    TrainingRoutine defaultRoutine() const;
    ShotCommand computeReturnCommand(const TrainingRoutine& routine, const TrajectoryState& state) const;
};
