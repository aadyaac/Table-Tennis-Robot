#include "routine_manager.hpp"

#include <algorithm>

TrainingRoutine RoutineManager::defaultRoutine() const {
    TrainingRoutine routine;
    routine.name = "Warmup-Topspin";
    routine.adaptive_mode = true;
    routine.sequence = {
        {0.0, 8.0, 155, 140},
        {-12.0, 10.0, 165, 130},
        {12.0, 10.0, 165, 130},
        {0.0, 12.0, 175, 120},
    };
    return routine;
}

ShotCommand RoutineManager::computeReturnCommand(const TrainingRoutine& routine, const TrajectoryState& state) const {
    if (routine.sequence.empty()) {
        return {0.0, 8.0, 150, 120};
    }

    const ShotCommand base = routine.sequence[static_cast<std::size_t>(state.intercept_time_ms % routine.sequence.size())];
    ShotCommand command = base;

    if (routine.adaptive_mode) {
        command.pan_deg = std::clamp(base.pan_deg + state.projected_x * 0.04, -40.0, 40.0);
        command.tilt_deg = std::clamp(base.tilt_deg + state.projected_y * 0.03, 0.0, 45.0);
        command.launcher_pwm = std::clamp(base.launcher_pwm + static_cast<int>(state.vy * 0.2), 120, 220);
    }

    return command;
}
