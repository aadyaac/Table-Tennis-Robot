# Software Interface for Table Tennis Robot

A C++/OpenCV software interface for designing custom training routines for a table tennis robot. The system captures ball motion, predicts trajectories, computes return targets, and streams actuation commands to an Arduino-backed robot controller.

## Highlights
- **Custom routine programming** with a configurable sequence of shots and timing constraints.
- **Computer vision pipeline** for ball detection and trajectory estimation using OpenCV.
- **Return-path computation** to simulate live gameplay and adaptive response.
- **AWS-ready deployment** using Docker for EC2-hosted control logic.
- **Arduino integration** via serial command protocol optimized for low-latency control loops.

## Architecture
1. `VisionPipeline` reads frames and detects ball coordinates.
2. `TrajectoryPredictor` estimates velocity + bounce timing.
3. `RoutineManager` decides a target return point.
4. `RobotController` emits commands (`PAN,TILT,FIRE`) to Arduino.

## Build (Local)
```bash
cmake -S . -B build
cmake --build build
./build/tt_robot
```

## Deploy on EC2
```bash
docker build -t tt-robot:latest .
docker run --rm -it --device=/dev/ttyUSB0 tt-robot:latest
```

See `scripts/ec2_setup.sh` and `docker-compose.yml` for a reproducible cloud setup.

## Arduino
Upload `arduino/robot_controller.ino` to an Arduino-compatible board controlling pan/tilt servos + launcher motor.
