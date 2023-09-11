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

#ifdef NUMCPP_EXAMPLE
#include "NumCpp.hpp"
#include <filesystem>
#include <iostream>
#endif

#ifdef LYRA_EXAMPLE_2
// Run a process, sub-command data.
struct run_command 
{
    std::vector<std::string> command; 
    bool verbose = false;
    bool show_help = false;

    run_command(lyra::cli & cli) 
    {
        cli.add_argument(
            lyra::command("run",
                [this](const lyra::group & g) { this->do_command(g); }) 
                .help("Execute the given command.")
                .add_argument(lyra::help(show_help))
                .add_argument(
                    lyra::opt(verbose)
                        .name("-v")
                        .name("--verbose")
                        .optional()
                        .help(
                            "Show additional output as to what we are doing."))
                .add_argument(
                    lyra::arg(command, "command")
                        .required()
                        .help(
                            "The command, and arguments, to attempt to run.")));
    }

    void do_command(const lyra::group & g)
    {
        if (show_help)
            std::cout << g; 
        else
        {
            std::cout << "RUN: "
                      << "verbose=" << (verbose ? "true" : "false");
            for (auto c : command) std::cout << " " << c;
            std::cout << "\n";
        }
    }
};

// Kill a named process, sub-command data.
struct kill_command 
{
    std::string process_name;
    int signal = 9;
    bool show_help = false;

    kill_command(lyra::cli & cli)
    {
        cli.add_argument(
            lyra::command(
                "kill", [this](const lyra::group & g) { this->do_command(g); })
                .help("Terminate the process with the given name.")
                .add_argument(lyra::help(show_help))
                .add_argument(
                    lyra::opt(signal, "signal")
                        .name("-s")
                        .name("--signal")
                        .optional()
                        .help(
                            "The signal integer to post to the running process."))
                .add_argument(
                    lyra::arg(process_name, "process_name")
                        .required()
                        .help(
                            "The name of the process to search and signal.")));
    }

    void do_command(const lyra::group & g)
    {
        if (show_help)
            std::cout << g;
        else
            std::cout << "KILL:"
                      << " signal=" << signal << " process=" << process_name
                      << "\n";
    }
};
#endif

int main(int argc, char *argv[])
{
    
#ifdef NUMCPP_EXAMPLE
    // Containers
    nc::NdArray<int> a0 = { { 1, 2 }, { 3, 4 } };
    nc::NdArray<int> a1 = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    a1.reshape(2, 3);
    auto a2 = a1.astype<double>();

    // Initializers
    auto a3 = nc::linspace<int>(1, 10, 5);
    auto a4 = nc::arange<int>(3, 7);
    auto a5 = nc::eye<int>(4);
    auto a6 = nc::zeros<int>(3, 4);
    auto a7 = nc::NdArray<int>(3, 4) = 0;
    auto a8                          = nc::ones<int>(3, 4);
    auto a9 = nc::NdArray<int>(3, 4) = 1;
    auto a10                         = nc::nans(3, 4);
    auto a11 = nc::NdArray<double>(3, 4) = nc::constants::nan;
    auto a12                             = nc::empty<int>(3, 4);
    auto a13                             = nc::NdArray<int>(3, 4);

    // Slicing/Broadcasting
    auto                  a14      = nc::random::randInt<int>({ 10, 10 }, 0, 100);
    [[maybe_unused]] auto value    = a14(2, 3);
    auto                  slice    = a14({ 2, 5 }, { 2, 5 });
    auto                  rowSlice = a14(a14.rSlice(), 7);
    auto                  values   = a14[a14 > 50];
    a14.putMask(a14 > 50, 666);

    // random
    nc::random::seed(666);
    auto a15 = nc::random::randN<double>({ 3, 4 });
    auto a16 = nc::random::randInt<int>({ 3, 4 }, 0, 10);
    auto a17 = nc::random::rand<double>({ 3, 4 });
    auto a18 = nc::random::choice(a17, 3);

    // Concatenation
    auto a = nc::random::randInt<int>({ 3, 4 }, 0, 10);
    auto b = nc::random::randInt<int>({ 3, 4 }, 0, 10);
    auto c = nc::random::randInt<int>({ 3, 4 }, 0, 10);

    auto a19 = nc::stack({ a, b, c }, nc::Axis::ROW);
    auto a20 = nc::vstack({ a, b, c });
    auto a21 = nc::hstack({ a, b, c });
    auto a22 = nc::append(a, b, nc::Axis::COL);

    // Diagonal, Traingular, and Flip
    auto d   = nc::random::randInt<int>({ 5, 5 }, 0, 10);
    auto a23 = nc::diagonal(d);
    auto a24 = nc::triu(a);
    auto a25 = nc::tril(a);
    auto a26 = nc::flip(d, nc::Axis::ROW);
    auto a27 = nc::flipud(d);
    auto a28 = nc::fliplr(d);

    // iteration
    for (auto it = a.begin(); it < a.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (auto& arrayValue : a)
    {
        std::cout << arrayValue << " ";
    }
    std::cout << std::endl;

    // Logical
    auto                  a29 = nc::where(a > 5, a, b);
    auto                  a30 = nc::any(a);
    auto                  a31 = nc::all(a);
    auto                  a32 = nc::logical_and(a, b);
    auto                  a33 = nc::logical_or(a, b);
    auto                  a34 = nc::isclose(a15, a17);
    [[maybe_unused]] auto a35 = nc::allclose(a, b);

    // Comparisons
    auto a36 = nc::equal(a, b);
    auto a37 = a == b;
    auto a38 = nc::not_equal(a, b);
    auto a39 = a != b;

#ifdef __cpp_structured_bindings
    auto [rows, cols] = nc::nonzero(a);
#else
    auto  rowsCols = nc::nonzero(a);
    auto& rows     = rowsCols.first;
    auto& cols     = rowsCols.second;
#endif

    // Minimum, Maximum, Sorting
    auto value1 = nc::min(a);
    auto value2 = nc::max(a);
    auto value3 = nc::argmin(a);
    auto value4 = nc::argmax(a);
    auto a41    = nc::sort(a, nc::Axis::ROW);
    auto a42    = nc::argsort(a, nc::Axis::COL);
    auto a43    = nc::unique(a);
    auto a44    = nc::setdiff1d(a, b);
    auto a45    = nc::diff(a);

    // Reducers
    auto value5 = nc::sum<int>(a);
    auto a46    = nc::sum<int>(a, nc::Axis::ROW);
    auto value6 = nc::prod<int>(a);
    auto a47    = nc::prod<int>(a, nc::Axis::ROW);
    auto value7 = nc::mean(a);
    auto a48    = nc::mean(a, nc::Axis::ROW);
    auto value8 = nc::count_nonzero(a);
    auto a49    = nc::count_nonzero(a, nc::Axis::ROW);

    // I/O
    a.print();
    std::cout << a << std::endl;

    auto tempDir = std::filesystem::temp_directory_path();
    auto tempTxt = (tempDir / "temp.txt").string();
    a.tofile(tempTxt, '\n');
    auto a50 = nc::fromfile<int>(tempTxt, '\n');

    auto tempBin = (tempDir / "temp.bin").string();
    nc::dump(a, tempBin);
    auto a51 = nc::load<int>(tempBin);

    // Mathematical Functions

    // Basic Functions
    auto a52 = nc::abs(a);
    auto a53 = nc::sign(a);
    auto a54 = nc::remainder(a, b);
    auto a55 = nc::clip(a, 3, 8);
    auto xp  = nc::linspace<double>(0.0, 2.0 * nc::constants::pi, 100);
    auto fp  = nc::sin(xp);
    auto x   = nc::linspace<double>(0.0, 2.0 * nc::constants::pi, 1000);
    auto f   = nc::interp(x, xp, fp);

    // Exponential Functions
    auto a56 = nc::exp(a);
    auto a57 = nc::expm1(a);
    auto a58 = nc::log(a);
    auto a59 = nc::log1p(a);

    // Power Functions
    auto a60 = nc::power<int>(a, 4);
    auto a61 = nc::sqrt(a);
    auto a62 = nc::square(a);
    auto a63 = nc::cbrt(a);

    // Trigonometric Functions
    auto a64 = nc::sin(a);
    auto a65 = nc::cos(a);
    auto a66 = nc::tan(a);

    // Hyperbolic Functions
    auto a67 = nc::sinh(a);
    auto a68 = nc::cosh(a);
    auto a69 = nc::tanh(a);

    // Classification Functions
    auto a70 = nc::isnan(a.astype<double>());
    // nc::isinf(a);

    // Linear Algebra
    auto a71 = nc::norm<int>(a);
    auto a72 = nc::dot<int>(a, b.transpose());

    auto                  a73    = nc::random::randInt<int>({ 3, 3 }, 0, 10);
    auto                  a74    = nc::random::randInt<int>({ 4, 3 }, 0, 10);
    auto                  a75    = nc::random::randInt<int>({ 1, 4 }, 0, 10);
    [[maybe_unused]] auto value9 = nc::linalg::det(a73);
    auto                  a76    = nc::linalg::inv(a73);
    auto                  a77    = nc::linalg::lstsq(a74, a75);
    auto                  a78    = nc::linalg::matrix_power<int>(a73, 3);
    auto                  a79    = nc::linalg::multi_dot<int>({ a, b.transpose(), c });

    nc::NdArray<double> u;
    nc::NdArray<double> s;
    nc::NdArray<double> vt;
    nc::linalg::svd(a.astype<double>(), u, s, vt);
#endif

#ifdef LYRA_EXAMPLE_2
    auto cli = lyra::cli();
    std::string command;
    bool show_help = false;
    cli.add_argument(lyra::help(show_help));
    kill_command kill { cli };
    run_command run { cli };
    auto result = cli.parse({ argc, argv }); 
    if (show_help)
    {
        std::cout << cli;
        return 0;
    }
    if (!result) 
    {
        std::cerr << result.message() << "\n";
    }
    return result ? 0 : 1;
#endif

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
    std::cout << "result = " << result.value() << std::endl;
    
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