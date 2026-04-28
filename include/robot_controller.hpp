#pragma once

#include "types.hpp"
#include <string>

class RobotController {
public:
    explicit RobotController(std::string serial_port);
    std::string encode(const ShotCommand& command) const;
    void send(const ShotCommand& command) const;

private:
    std::string serial_port_;
};
