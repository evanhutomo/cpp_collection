#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <lyra/lyra.hpp>
#include <nlohmann/json.hpp>

#include "data.h"

namespace KOTOBAKOE::MAIN {
int argParse(int argc, const char** argv) {
    // Where we read in the argument value:
    int width = 0;

    // The parser with the one option argument:
    auto cli = lyra::cli();
    cli.add_argument(
        lyra::opt(width, "width")
            .name("-w")
            .name("--width")
            .help("How wide should it be?"));

    // Parse the program arguments:
    auto result = cli.parse({ argc, argv });

    // Check that the arguments where valid:
    if (!result)
    {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        return 1;
    }

    std::cout << "width = " << width << "\n";
    return 0;
}

int readAndParse() {
    std::vector<DataParse> dataVector;

    /* raed and parse */
    std::ifstream file("data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            DataParse entry;
            size_t pos = line.find('-');
            if (pos != std::string::npos) {
                entry.kanji = line.substr(0, pos);
                size_t pos2 = line.find('-', pos + 1);
                if (pos2 != std::string::npos) {
                    entry.kana = line.substr(pos + 1, pos2 - pos - 1);
                    entry.meaning = line.substr(pos2 + 1);
                }
            }
            dataVector.push_back(entry);
        }
        file.close();
    }

    /* convert to JSON */
    nlohmann::json jsonData;
    for (const auto& entry : dataVector) {
        nlohmann::json jsonEntry;
        jsonEntry["id"] = entry.id;
        jsonEntry["kanji"] = entry.kanji;
        jsonEntry["kana"] = entry.kana;
        jsonEntry["meaning"] = entry.meaning;
        jsonData.push_back(jsonEntry);
    }

    /* Write JSON to file */
    std::ofstream outputFile("output.json");
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(4); // The "4" argument is for pretty printing
        outputFile.close();
    } else {
        std::cerr << "Error writing to output.json" << std::endl;
    }
    return 0;
}

} // namespace KOTOBAKOE::MAIN

int main(int argc, const char** argv) {
    auto errcode = KOTOBAKOE::MAIN::argParse(argc, argv);    
    auto errcode2 = KOTOBAKOE::MAIN::readAndParse();

    return errcode;
}
