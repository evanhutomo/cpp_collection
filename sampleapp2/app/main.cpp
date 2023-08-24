#include <iostream>
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../inc/sambel.h"
#include "../inc/lat1.h"
#include "../inc/lat2.h"

int main()
{
#if 0
    std::system("cat ../LICENSE");
    auto sambelbawang = Sambel();
    sambelbawang.createSambel(10, true);
    sambelbawang.sajikanSambel(sambelbawang.getSambel());


    // lat1
    std::wstring japstr = L"穫トぞすな域応選こーがク究8生ニソサラ現手ス消団メタカ気今げへっ関航稿マ里非メヲ済欧ぽ政道ツ何産禁リぞす要調浅添さぼリ。";
    std::wstring engstr = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc eleifend dui sem, id sodales sapien fringilla quis.";
    auto a = std::make_unique<LATCPP::BASIC1::Latihan1>();
    a->exampleStrncpy(engstr);
    a->getWindowsPath();
    a->getExecutablePath();
    a->t_strcopy({1,2,3,4});
#endif    

#if 1
    // lat 2
    Eigen::MatrixXd input(2, 10); // Example input matrix
    input << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
             11, 12, 13, 14, 15, 16, 17, 18, 19, 20;

    int frame_length = 4;
    int hop_length = 2;

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