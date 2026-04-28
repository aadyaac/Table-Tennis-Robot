#include "robot_controller.hpp"
#include "routine_manager.hpp"
#include "trajectory.hpp"
#include "vision_pipeline.hpp"

#include <chrono>
#include <iostream>
#include <opencv2/videoio.hpp>
#include <thread>

int main() {
    VisionPipeline vision;
    TrajectoryPredictor predictor;
    RoutineManager planner;
    RobotController robot("/dev/ttyUSB0");

    const TrainingRoutine routine = planner.defaultRoutine();

    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Unable to open camera feed\n";
        return 1;
    }

    BallObservation previous{0.0, 0.0, 0};
    bool has_previous = false;

    for (int i = 0; i < 200; ++i) {
        cv::Mat frame;
        camera >> frame;

        const auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now()
        ).time_since_epoch().count();

        BallObservation current = vision.detectBall(frame, now);

        if (has_previous) {
            const TrajectoryState state = predictor.estimate(previous, current);
            const ShotCommand command = planner.computeReturnCommand(routine, state);
            robot.send(command);
        }

        previous = current;
        has_previous = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }

    return 0;
}
