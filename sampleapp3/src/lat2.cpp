#include "lat2.h"

namespace LATCPP::BASIC2 {
    Latihan2::Latihan2(){}
    Latihan2::~Latihan2(){}

    Eigen::MatrixXd Latihan2::frame (
        const Eigen::MatrixXd &x,
        int frame_length,
        int hop_length,
        int axis) {
        Eigen::MatrixXd xw;

        if (x.cols() < frame_length) {
            throw std::invalid_argument(
                "Input is too short for the given frame length"
            );
        }

        if (hop_length < 1) {
            throw std::invalid_argument("Invalid hop_length");
        }

        int target_axis;

        if (axis < 0) {
            target_axis = axis - 1;
        } else {
            target_axis = axis + 1;
        }

        // Calculate the number of frames
        int num_frames = (x.cols() - frame_length) / hop_length + 1;

        // Create the output matrix
        xw.resize(x.rows(), frame_length * num_frames);

        // Populate the frames
        for (int frame_idx = 0; frame_idx < num_frames; ++frame_idx) {
            int start_idx = frame_idx * hop_length;
            int end_idx = start_idx + frame_length;

            for (int row = 0; row < x.rows(); ++row) {
                for (int col = start_idx; col < end_idx; ++col) {
                    xw(row, frame_idx * frame_length + (col - start_idx)) = x(row, col);
                }
            }
        }
        return xw;
    }
    
}