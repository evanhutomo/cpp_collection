#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

// External module
#include <lyra/lyra.hpp>
#include <nlohmann/json.hpp>

// Internal module
#include "data.h"
#include "db.h"
#include "err_enum.h"

// FTXUI
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/util/ref.hpp"



namespace ftxui{
    void createComponent() {
        std::string first_name;
        std::string last_name;
        std::string password;

        Component input_first_name = Input(&first_name, "First name");
        Component input_last_name = Input(&last_name, "Last name");

        InputOption password_option;
        password_option.password = true;
        Component input_password = Input(&password, "Password", password_option);

        auto component = Container::Vertical({
            input_first_name,
            input_last_name,
            input_password,
        });

        auto renderer = Renderer(component, [&] {
            return vbox({
                text("Hello " + first_name + " " + last_name + "!"),
                separator(),
                hbox(text("First name: "), input_first_name->Render()),
                hbox(text("Last name: "), input_last_name->Render()),
                hbox(text("Password: "), input_password->Render()),                      
            }) | border;
        });

        auto screen = ScreenInteractive::TerminalOutput();
        screen.Loop(renderer);
    }
}

namespace KOTOBAKOE::DB {
    int insertKotobaVector(std::vector<KOTOBAKOE::DATA::Kotoba> &vec_kanji_card) {
        try {
            // Set your PostgreSQL connection string.
            // std::string connection_string = "dbname=belugabox_qa user=postgres password=postgres host=127.0.0.1 port=5439";
            std::string connection_string = "dbname=kotobakoe_db user=kotobakoe_usr password=kotobakoe_pwd host=127.0.0.1 port=5439";

            // Establish a connection to the PostgreSQL database.
            pqxx::connection connection(connection_string);

            if (connection.is_open()) {
                std::cout << "Connected to the database successfully." << std::endl;

                // Insert data into a table.
                std::string table_name = "kotoba";  // Replace with your actual table name.

                // Define the SQL query for insertion.
                std::string select_query = "SELECT * FROM " + table_name + ";";

                std::vector<KOTOBAKOE::DATA::Kotoba> data;

                // Prepare a transaction for the insertion.
                pqxx::work txn(connection);

                pqxx::result result = txn.exec(select_query);

                // Process the query result and populate the vector.
                for (const auto& row : result) {
                    KOTOBAKOE::DATA::Kotoba item;
                    item.id = row["id"].as<int>();
                    item.kanji = row["kanji"].as<std::string>();
                    item.kana = row["kana"].as<std::string>();                
                    item.description = row["description"].as<std::string>();
                    data.push_back(item);
                }

                // Commit the transaction.
                txn.commit();

                // You now have 'data' populated with the retrieved records.
                for (const auto& item : data) {
                    std::cout << "ID: " << item.id << ", Kanji: " << item.kanji << std::endl;
                }

                // compare vec_kanji_card value and data、if not equal, insert data to db
                for (const auto& item : vec_kanji_card) {
                    bool isExist = false;
                    for (const auto& item2 : data) {
                        std::cout << "item.kanji: " << item.kanji << ", item2.kanji: " << item2.kanji << std::endl;
                        if (item.kanji == item2.kanji) {
                            isExist = true;
                            break;
                        }
                    }
                    if (!isExist) {
                        std::cout << "insert data to db" << std::endl;
                        pqxx::work txn(connection);
                        std::string insert_query = "INSERT INTO " + table_name + " (kana, kanji, description, updated_date) VALUES ('"+ item.kana +"', '"+ item.kanji +"', '"+ item.description +"', CURRENT_DATE)";
                        txn.exec(insert_query);
                        txn.commit();
                    }
                }

                // Execute the insertion query.
                // txn.exec_params(insert_query);

                // // Commit the transaction to save the changes.
                // txn.commit();

                std::cout << "Data inserted successfully." << std::endl;            

                // Don't need to close the connection explicitly; it will be closed when the 'connection' object goes out of scope.
            } else {
                std::cerr << "Failed to connect to the database." << std::endl;

                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
        return 0;
    } 
}

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

std::vector<KOTOBAKOE::DATA::Kotoba> readKotobaFromTxt() {
    std::vector<KOTOBAKOE::DATA::Kotoba> dataVector;

    /* read and parse */
    std::ifstream file("data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            KOTOBAKOE::DATA::Kotoba entry;
            size_t pos = line.find('-');
            if (pos != std::string::npos) {
                entry.kanji = line.substr(0, pos);
                size_t pos2 = line.find('-', pos + 1);
                if (pos2 != std::string::npos) {
                    entry.kana = line.substr(pos + 1, pos2 - pos - 1);
                    entry.description = line.substr(pos2 + 1);
                }
            }
            dataVector.push_back(entry);
        }
        file.close();
    }
    return dataVector;
}

int readAndParseToJSON() {
    std::vector<KOTOBAKOE::DATA::Kotoba> dataVector;

    /* read and parse */
    std::ifstream file("data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            KOTOBAKOE::DATA::Kotoba entry;
            size_t pos = line.find('-');
            if (pos != std::string::npos) {
                entry.kanji = line.substr(0, pos);
                size_t pos2 = line.find('-', pos + 1);
                if (pos2 != std::string::npos) {
                    entry.kana = line.substr(pos + 1, pos2 - pos - 1);
                    entry.description = line.substr(pos2 + 1);
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
        jsonEntry["description"] = entry.description;
        jsonData.push_back(jsonEntry);
    }

    /* Write JSON to file */
    std::ofstream outputFile("kotoba.json");
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(4); // The "4" argument is for pretty printing
        outputFile.close();
    } else {
        std::cerr << "Error writing to kotoba.json" << std::endl;
    }
    return 0;
}

void printKotobaVector(const std::vector<KOTOBAKOE::DATA::Kotoba>& dataVector) {
    if (!dataVector.empty()) {
        try{
            for (const auto& entry : dataVector) {
                std::cout << "ID: " << entry.id << std::endl;
                std::cout << "Kanji: " << entry.kanji << std::endl;
                std::cout << "Kana: " << entry.kana << std::endl;
                std::cout << "Description: " << entry.description << std::endl;
                std::cout << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error while iterating over vec_kanji_card: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "vec_kanji_card is empty or null." << std::endl;        
    }
} // namespace KOTOBAKOE::MAIN

int main(int argc, const char** argv) {
    KOTOBAKOE::MAIN::argParse(argc, argv);
    auto vec_kanji_card = KOTOBAKOE::MAIN::readKotobaFromTxt();
    KOTOBAKOE::MAIN::printKotobaVector(vec_kanji_card);

#if 1

#endif
    return 0;
}

// int main(int argc, const char** argv) {
//     std::string connection_string = "dbname=belugabox_qa user=postgres password=postgres host=127.0.0.1 port=5439";

//     try {
//         // Create a unique_ptr for the DatabaseConnector class.
//         std::unique_ptr<KOTOBAKOE::DB::DatabaseConnector> p_db = std::make_unique<KOTOBAKOE::DB::DatabaseConnector>(connection_string);

//         // Check if a table exists in the database.
//         std::string table_name = "kanji_cards"; // Replace with the actual table name.
//         if (p_db->IsTableExists(table_name)) {
//             std::cout << "Table '" << table_name << "' exists in the database." << std::endl;
//         } else {
//             std::cout << "Table '" << table_name << "' does not exist in the database." << std::endl;
//         }

//         // Execute a sample query.
//         std::string query = "SELECT * FROM kanji_cards"; // Replace with your actual query.
//         pqxx::result result = p_db->ExecuteQuery(query);

//         // Process the query result.
//         for (const auto& row : result) {
//             for (const auto& field : row) {
//                 std::cout << field.c_str() << "\t";
//             }
//             std::cout << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }


    // KOTOBAKOE::MAIN::argParse(argc, argv);    
    // KOTOBAKOE::MAIN::readAndParse();
//     ftxui::createComponent();

//     return 0;
// }
