#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <numeric> // For std::iota

// Assuming you have the Eigen library for array manipulation
#include <Eigen/Dense>

namespace LATCPP::BASIC2 {
    class Latihan2 {
        public:
            Latihan2();
            ~Latihan2();
        Eigen::MatrixXd frame(
            const Eigen::MatrixXd &x,
            int frame_length,
            int hop_length,
            int axis = -1
        );
    };
}