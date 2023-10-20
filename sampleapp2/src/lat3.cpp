#include "lat3.h"
#include <iostream>
#include <observable/observable.hpp>

using namespace std;
using namespace observable;

namespace LATCPP::BASIC3 {
    Latihan3::Latihan3(){}
    Latihan3::~Latihan3(){}
    void Latihan3::testLat3() {
        cout << "Latihan3" << "\n";
        // do the observable chore here
        auto sub = subject<void(string)> { };
        sub.subscribe([](auto const &s) { cout << s << endl; });

        // hello world will printed to stdout
        sub.notify("Hello world");
        auto a = value<int> { 5 };
        auto b = value<int> { 5 };        
        auto avg = observe(
                        (a + b) / 2.0f
                );
        auto eq_msg = observe(
                        select(a == b, "equal", "not equal")
                    );

        avg.subscribe([](auto val) { cout << val << endl; });
        eq_msg.subscribe([](auto const & msg) { cout << msg << endl; });

        // "10" and "not equal" will be printed to stdout in an
        // unspecified order.
        b = 15;
    }
}