#include "robot_controller.hpp"

#include <iostream>
#include <sstream>

RobotController::RobotController(std::string serial_port)
    : serial_port_(std::move(serial_port)) {}

std::string RobotController::encode(const ShotCommand& command) const {
    std::ostringstream buffer;
    buffer << "PAN=" << command.pan_deg
           << ";TILT=" << command.tilt_deg
           << ";PWM=" << command.launcher_pwm
           << ";DWELL=" << command.dwell_ms
           << "\n";
    return buffer.str();
}

void RobotController::send(const ShotCommand& command) const {
    const std::string payload = encode(command);
    // Replace stdout with serial write (termios/libserialport) in production.
    std::cout << "[SERIAL " << serial_port_ << "] " << payload;
}
