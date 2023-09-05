#include <iostream>
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../inc/sambel.h"
#include "../inc/lat1.h"
#include "../inc/lat2.h"
#include <pqxx/pqxx>
#include <spdlog/spdlog.h>
#include <lyra/lyra.hpp>

int main(int argc, char *argv[])
{
#ifdef LYRA_EXAMPLE
    int width = 0;
    std::string name;
    std::string path;
    bool help_flag = false;

    // The parser with the one option argument:
    auto cli = lyra::help(help_flag)
        | lyra::opt(path, "path")
              ["-p"]["--path"]("path of your file?")        
        | lyra::opt(name, "name")
              ["-n"]["--name"]("Namamu?")    
        | lyra::opt(width, "width")
              ["-w"]["--width"]("How wide should it be?");

    // Parse the program arguments:
    auto result = cli.parse({ argc, argv });

    // Check that the arguments where valid:
    if (!result)
    {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        return 1;
    }

    if (help_flag)
    {
        std::cout << cli << "\n";
        return 0;
    }

    std::cout << "width = " << width << "\n";
    std::cout << "name = " << name << "\n";
    std::cout << "path = " << path << "\n";
#endif    

#ifdef SPDLOG_EXAMPLE
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    std::string connectionString = "host=127.0.0.1 port=5432 dbname=test1 user=postgres password=postgres";

    try{
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);
        pqxx::result response = worker.exec("SELECT * FROM users");

        for(size_t i = 0; i < response.size(); i++) {
            std::cout << "id: " << response[i][0].as<int>() << std::endl; 
            std::cout << "username: " << response[i][1].as<std::string>() << std::endl;
            std::cout << "password : " << response[i][2].as<std::string>() << std::endl;
            std::cout << "email : " << response[i][3].as<std::string>() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

#endif

#ifdef SAMBEL_EXAMPLE
    std::system("cat ../LICENSE");
    auto sambelbawang = std::make_unique<Sambel>(); 
    sambelbawang->createSambel(10, true);
    sambelbawang->sajikanSambel(sambelbawang->getSambel());
#endif

#ifdef LAT1_EXAMPLE
    // lat1
    std::wstring japstr = L"穫トぞすな域応選こーがク究8生ニソサラ現手ス消団メタカ気今げへっ関航稿マ里非メヲ済欧ぽ政道ツ何産禁リぞす要調浅添さぼリ。";
    std::wstring engstr = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc eleifend dui sem, id sodales sapien fringilla quis.";
    auto a = std::make_unique<LATCPP::BASIC1::Latihan1>();
    a->exampleStrncpy(engstr);
    a->getWindowsPath();
    a->getExecutablePath();
    a->t_strcopy({1,2,3,4});
    a->tryMap1();
#endif    

#ifdef LAT2_EXAMPLE
    // lat 2
    Eigen::MatrixXd input(1, 10); // Example input matrix
    input << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    int frame_length = 3;
    int hop_length = 1;

    try {   
        auto b = std::make_unique<LATCPP::BASIC2::Latihan2>();     
        Eigen::MatrixXd framed = b->frame(input, frame_length, hop_length);

        std::cout << "Framed matrix:\n" << framed << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
#endif

    return 0;
}