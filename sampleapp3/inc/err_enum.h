#pragma once
#include <string>

namespace KOTOBAKOE::UTILITY::ERROR_ENUM {
    enum class Err {
        NO_ERROR = 0,
        // Database errors
        ERR_FAILED_TO_CONNECT_DB_CONNECTION = 1000,

    };

    inline std::string errDesc(const Err &e) {
        switch (e)
        {
        case Err::NO_ERROR:
            return "No error";
            break;
        
        default:
            break;
        }
    }
}