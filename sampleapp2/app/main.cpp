// HEADERS
#include <iostream>
#include <csignal>
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <valarray>
#include <type_traits>
#include <deque>
#include <locale>
#include <codecvt>
#include <tuple>
#include <future>
#include <thread>
// #include <unordered_set>
#include "../inc/sambel.h"
#include "../inc/lat1.h"
#include "../inc/lat2.h"
#include "../inc/lat5.h"
#include <pqxx/pqxx>
#include <spdlog/spdlog.h>
#include <lyra/lyra.hpp>
#include "visit_struct.hpp"
#include "visitor_pattern.h"
#ifdef NUMCPP_EXAMPLE
#include "NumCpp.hpp"
#include <filesystem>
#include <iostream>
#endif

// MACROS
#define PRINT_STR(x) std::cout << x << std::endl
#define PRINT_FUNC_NAME() \
    do { \
        for (std::size_t i = 0; i < sizeof(__func__) - 1; ++i) { \
            std::cout << "-"; \
        } \
        std::cout << "\n" << __func__ << std::endl; \
        for (std::size_t i = 0; i < sizeof(__func__) - 1; ++i) { \
            std::cout << "-"; \
        } \
        std::cout << std::endl; \
    } while (0)

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

void stdFilesystemExist() {
    std::string pathExample = "example.txt";
    if (std::filesystem::exists(pathExample)) {
        std::cout << "File exists" << std::endl;
    } else {
        std::cout << "File does not exist" << std::endl;
    }   
}

void epochTime() {
    // Unix epoch timestamp
    std::time_t timestamp = 1694542961;

    // convert the timestamp to a struct tm (timeinfo)
    struct tm* timeinfo;
    timeinfo = std::gmtime(&timestamp);
    
    // buffer to hold the formatted time
    char buffer[80];

    // format the date and time as a string
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    std::cout << "Unix Timestamp: " << timestamp << std::endl;
    std::cout << "Human-Readable Date and Time (UTC): " << buffer << std::endl;
}

void regularFileChecker() {
    std::filesystem::path pathToCheck("test.txt");
    if (std::filesystem::is_regular_file(pathToCheck)) {
        std::cout << pathToCheck << " is a regular file" << std::endl;
    } else if (std::filesystem::is_directory(pathToCheck)) {
        std::cout << pathToCheck << " is a directory" << std::endl;
    } else {
        std::cout << pathToCheck << " is neither a regular file nor directory" << std::endl;
    }    
}

void createDirectory() {
    std::filesystem::path newDirectoryPath("new_directory");
    try {
        if (std::filesystem::create_directory(newDirectoryPath))
            std::cout << "Directory created\n";
        else
            std::cout << "Failed to create directory\n";
    } catch (std::filesystem::filesystem_error& e) {
        std::cout << e.what() << '\n';
    }    
}

void outputStreamTextFile() {
    // Create an instance of std::ofstream and open a file for writing
    std::ofstream outputFile("outputstream.txt");

    // Check if the file opened successfully
    if (!outputFile.is_open()) {
        spdlog::error("Error opening the file.");
    }

    // Write data to the file
    outputFile << "Hello, World!" << std::endl;
    outputFile << "This is a sample line of text." << std::endl;

    // Close the file
    outputFile.close();

    // Optionally, you can check if the file was closed successfully
    if (outputFile.good()) {
        spdlog::info("File closed successfully.");
    } else {
        spdlog::error("Error closing the file.");    
    }    
}

void inputStreamTextFile() {
    spdlog::info("entering streamTextFile()");
    try {
        std::ifstream inputFile;
        inputFile.open("test.txt");
        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                spdlog::info(line);
            }
            inputFile.close();
        } else {
            spdlog::info("Unable to open file");
        }
    } catch (std::ifstream::failure& e) {
        std::cout << e.what() << std::endl;
    }
}

// Function that will be executed by the first thread
void threadFunction1() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Thread 1: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void threadFunction2() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Thread 2: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }    
}


// Define a class that holds a japanese char
class Kotoba {
public: 
    Kotoba(const std::wstring& kana) : _kana(kana) {
        std::wcout << L"Constructing Kana: " << _kana << std::endl;
    }

    ~Kotoba() {
        std::wcout << L"Destructing Kana: " << _kana << std::endl;
    }

    std::wstring getKana() const {
        return _kana;
    }

private:
    std::wstring _kana;
};

void stdThread() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);
    // wait for both thread to finish
    t1.join();
    t2.join();
    std::cout << "both threads have finished execution." << std::endl;
    // flow: create function -> create thread -> join thread -> finish execution

    // std::vector<T>
    std::vector<Kotoba> vectorOfChar;
    vectorOfChar.push_back(Kotoba(L"大学"));
    vectorOfChar.push_back(Kotoba(L"労働"));
    vectorOfChar.push_back(Kotoba(L"組合"));
    for(const auto& kana : vectorOfChar) {
        std::wcout << kana.getKana() << std::endl;
    }
}

void char2Find() {
    std::string text = "Hello, World!";
    std::string charactersToFind = "aeiou";

    // Find the first occurrence of any vowel in the string.
    size_t foundPos = text.find_first_of(charactersToFind);

    if (foundPos != std::string::npos) {
        std::cout << "Found a vowel at position " << foundPos << ": " << text[foundPos] << std::endl;
    } else {
        std::cout << "No vowel found in the string." << std::endl;
    }    
}

void stdSort_1() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};

    // Sort the vector in ascending order
    std::sort(numbers.begin(), numbers.end());

    // Print the sorted vector
    for (auto number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // Sort the vector in descending order
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());

    // Print the sorted vector
    for (auto number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void stdReverse() {
    std::vector<int> myVector = {1, 2, 3, 4, 5, 6, 7};

    // Reverse only the elements from index 2 to 5 (inclusive)
    auto start = myVector.begin() + 2; // Iterator pointing to element 3
    auto end = myVector.begin() + 5;   // Iterator pointing to element 6

    std::reverse(start, end + 1); // +1 to include the end element in the reverse

    // Print the reversed vector
    for (int num : myVector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void stdDistance() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    // Calculate the distance between the beginning and end of the vector
    std::ptrdiff_t distance = std::distance(std::begin(myVector), std::end(myVector));

    std::cout << "Number of elements in the vector: " << distance << std::endl;
}

struct TestStruct {
    int value1;
    double value2;
    char value3;
};

void stdOptional() {
    std::optional<TestStruct> myOptional;

    // Check if the optional has a value using std::nullopt
    if (!myOptional.has_value()) {
        std::cout << "myOptional is empty" << std::endl;
    } else {
        // Accessing the value if it's present (not recommended without checking)
        TestStruct myValue = myOptional.value();
        std::cout << "myOptional contains a value: " << myValue.value1 << ", " << myValue.value2 << ", " << myValue.value3 << std::endl;
    }

    // Assign a value to the optional
    TestStruct newValue = {42, 3.14, 'A'};
    myOptional = newValue;

    // Check again after assigning a value
    if (myOptional.has_value()) {
        TestStruct myValue = myOptional.value();
        std::cout << "myOptional now contains a value: " << myValue.value1 << ", " << myValue.value2 << ", " << myValue.value3 << std::endl;
    }

    // Using std::nullopt to reset the optional to empty
    myOptional = std::nullopt;

    // Check if it's empty again
    if (!myOptional.has_value()) {
        std::cout << "myOptional is empty again" << std::endl;
    }

    // value_or 
    std::optional<int> myOptional2 = 42;

    // Using std::optional::value_or() with a default value
    int value = myOptional2.value_or(-1);
    std::cout << "myOptional2: " << value << std::endl;

    // Using value_or() with an empty optional
    std::optional<int> emptyOptional;
    int defaultValue = emptyOptional.value_or(-1);
    std::cout << "Default Value: " << defaultValue << std::endl;   
}

// std::unordered_map
namespace std_unordered_map_example {
   class MyKey {
    public:
        MyKey(const std::string& name, int id) : name_(name), id_(id) {}

        const std::string& getName() const {
            return name_;
        }

        int getId() const {
            return id_;
        }

        bool operator==(const MyKey& other) const {
            return name_ == other.name_ && id_ == other.id_;
        }

    private:
        std::string name_;
        int id_;
    };

    // Define a custom hash function for MyKey
    struct MyKeyHash {
        std::size_t operator()(const MyKey& key) const {
            // Combine the hash values of name_ and id_
            return std::hash<std::string>()(key.getName()) ^ std::hash<int>()(key.getId());
        }
    };

    // Define a custom equality comparator for MyKey
    struct MyKeyEqual {
        bool operator()(const MyKey& key1, const MyKey& key2) const {
            return key1 == key2;
        }
    };

    void runExample_1() {
        PRINT_FUNC_NAME();
        // Create an unordered_map with MyKey as the key type and int as the value type
        std::unordered_map<MyKey, int, MyKeyHash, MyKeyEqual> myMap;

        // Insert key-value pairs into the unordered_map
        MyKey key1("apple", 1);
        MyKey key2("banana", 2);
        MyKey key3("cherry", 3);

        myMap[key1] = 5;
        myMap[key2] = 3;
        myMap[key3] = 7;

        // Access and print values using keys
        MyKey keyToFind("banana", 2);
        if (myMap.find(keyToFind) != myMap.end()) {
            std::cout << "Value for key (" << keyToFind.getName() << ", " << keyToFind.getId() << "): " << myMap[keyToFind] << std::endl;
        } else {
            std::cout << "Key (" << keyToFind.getName() << ", " << keyToFind.getId() << ") not found in the map." << std::endl;
        }

        // Iterate through the unordered_map
        std::cout << "Contents of the unordered_map:" << std::endl;
        for (const auto& pair : myMap) {
            // first is representation of key, second is representation of value
            std::cout << "Key (" << pair.first.getName() << ", " << pair.first.getId() << "), Value: " << pair.second << std::endl;
        }
    }

    void runExample_2() {
        PRINT_FUNC_NAME();
        std::unordered_map<std::string, int> myMap;

        // Reserve memory for a specific number of elements
        myMap.reserve(100); // Reserve space for 100 elements

        // Insert key-value pairs into the unordered_map
        myMap["apple"] = 5;
        myMap["banana"] = 3;
        myMap["cherry"] = 7;

        // Access and print values using keys
        std::string keyToFind = "banana";
        // search the keys, if the key is found, find will return an iterator pointing to the location
        if (myMap.find(keyToFind) != myMap.end()) {
            std::cout << "Value for key '" << keyToFind << "': " << myMap[keyToFind] << std::endl;
        } else {
            std::cout << "Key '" << keyToFind << "' not found in the map." << std::endl;
        }

        // Iterate through the unordered_map
        std::cout << "Contents of the unordered_map:" << std::endl;
        for (const auto& pair : myMap) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }        

        std::size_t numBuckets = myMap.bucket_count();

        // Calculate an estimate of unused buckets (not exact)
        std::size_t unusedBuckets = numBuckets - myMap.size();

        std::cout << "Current number of buckets: " << numBuckets << std::endl;
        std::cout << "Estimate of unused buckets: " << unusedBuckets << std::endl;
    }

    void runExample_3() {
        PRINT_FUNC_NAME();
        std::unordered_map<std::string, int> myMap;

        auto res1 = myMap.insert({"apple", 5});
        auto res2 = myMap.try_emplace("banana", 3);
        if (res1.second) {
            std::cout << "Value for key '" << res1.first->first << "': " << res1.first->second << std::endl;
        }
        if (res2.second) {
            std::cout << "Value for key '" << res2.first->first << "': " << res2.first->second << std::endl;
        }
    }
} // namespace std_unordered_map_example

namespace std_array_example {
    void runExample_1() {
        PRINT_FUNC_NAME();
        std::array<int, 5> myArray;
        for(int i = 0; i < myArray.size(); i++) {
            myArray[i] = i * 10;
        }

        // print the array
        for (const auto &element : myArray) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

namespace std_map_example {
    void runExample_1() {
        PRINT_FUNC_NAME();
        std::map<std::string, int> myMap;
        
        myMap["apple"] = 5;
        myMap["banana"] = 3;
        
        std::string keyToFind = "banana";
        if (myMap.find(keyToFind) != myMap.end()) {
            std::cout << "Value for key '" << keyToFind << "': " << myMap[keyToFind] << std::endl;
        } else {
            std::cout << "Key '" << keyToFind << "' not found in the map." << std::endl;
        }

        // iterate through map
        std::cout << "Contents of the map:" << std::endl;
        for (const auto& pair : myMap) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }

    void runExample_2() {
        PRINT_FUNC_NAME();
        std::map<std::wstring, int> myMap;

        // Insert key-value pairs into the map
        myMap[L"AA"] = 5;
        myMap[L"BB"] = 3;
        myMap[L"CC"] = 7;

        // Using a const_iterator to access elements
        std::cout << "Contents of the map using const_iterator:" << std::endl;
        for (std::map<std::wstring, int>::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
            std::wcout << L"Key: " << it->first << L", Value: " << it->second << std::endl;
        }
    }    
}

namespace std_valarray_example {
    void runExample_1() {
        PRINT_FUNC_NAME();
        // Create a valarray of integers
        std::valarray<int> myValArray = {1, 2, 3, 4, 5};

        // Print the original valarray
        std::cout << "Original valarray: ";
        for (const auto& element : myValArray) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // shift(): Shift elements to the right by 2 positions
        myValArray = myValArray.shift(-2);
        // Result: {0,0,1,2,3}

        // Print the valarray after shift
        std::cout << "Shifted valarray: ";
        for (const auto& element : myValArray) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // cshift(): Circular shift elements to the left by 1 position
        myValArray = myValArray.cshift(1);
        // Result: {0,1,2,3,0}

        // Print the valarray after circular shift
        std::cout << "Circularly shifted valarray: ";
        for (const auto& element : myValArray) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // apply(): Apply a function to each element (e.g., square each element)
        myValArray = myValArray.apply([](int x) { return x * x; });
        // Result: {0, 1, 4, 9, 0}

        // Print the valarray after applying the function
        std::cout << "Valarray after applying the function: ";
        for (const auto& element : myValArray) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // sum(): Compute the sum of elements
        int sum = myValArray.sum();
        // Result: 14

        // min(): Find the minimum element
        int minValue = myValArray.min();
        // Result: 0

        // max(): Find the maximum element
        int maxValue = myValArray.max();
        // Result: 9

        // Print the summary statistics
        std::cout << "Sum: " << sum << std::endl;
        std::cout << "Min Value: " << minValue << std::endl;
        std::cout << "Max Value: " << maxValue << std::endl;        
    }
}

namespace StructWithCons {
    int SomeFuncWithReturnInt() {
        return 10;
    }

    struct SomeStruct {
        int test;

        SomeStruct() : test(SomeFuncWithReturnInt()) {}
    };

    int main2() {
        SomeStruct some_struct;
        std::cout << "a.test = " << some_struct.test << std::endl; // Output: a.test = 10
        return 0;
    }
}

namespace std_2 {
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, void>::type
    printSquare(T x) {
        std::cout << "Square of " << x << " is " << x * x << std::endl;
    }

    void enableIf() {
        PRINT_FUNC_NAME();
        int num = 5;
        double pi = 3.14;
        std::string str = "adnajdbakdhb";
        printSquare(num);
        printSquare(pi);
    }

    void countIf() {
        PRINT_FUNC_NAME();
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int evenCount = std::count_if(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; });
        std::cout << "Number of even numbers: " << evenCount << std::endl;
    }

    void findIf() {
        PRINT_FUNC_NAME();
        // Create a vector of integers
        std::vector<int> numbers = {1, 3, 5, 2, 7, 8, 9, 10};

        int evenCount = 0; // Counter for even numbers found
        std::vector<int>::iterator it = numbers.begin();

        while (evenCount < 2 && it != numbers.end()) {
            it = std::find_if(it, numbers.end(), [](int x) {return x % 2 == 0;}); // Find the next even number

            if (it != numbers.end()) {
                ++evenCount;
                if (evenCount == 2) {
                    std::cout << "Second even number found: " << *it << std::endl;
                }
                ++it; // Move to the next element to continue searching
            }
        }

        if (evenCount < 2) {
            std::cout << "Less than two even numbers found." << std::endl;
        }
    }

    bool isGreaterThanThreshold(int num, int threshold) {
        return num > threshold;
    }

    void anyOf() {
        PRINT_FUNC_NAME();
        std::vector<int> numbers = {1, 3, 5, 2, 7, 8, 9, 10};
        int threshold = 6;
        bool anyGreaterThanThreshold = std::any_of(numbers.begin(), numbers.end(), [threshold](int num) {
            return isGreaterThanThreshold(num, threshold);
        });

        /* NOTE
        complementary of lambda func below in function shape is
            [threshold](int num) {
                return isGreaterThanThreshold(num, threshold);
            };
        is

        bool isGreaterThanThreshold(int num, int threshold) {
            return num > threshold;
        }
        */

        // check the result
        if (anyGreaterThanThreshold) {
            std::cout << "There is at least one number greater than " << threshold << std::endl;
        } else {
            std::cout << "There are no numbers greater than " << threshold << std::endl;
        }
    }

    void anyOf_2() {
        PRINT_FUNC_NAME();
        // Create a vector of integers
        std::vector<int> numbers = {1, 3, 5, 2, 7, 8, 9, 10};
        
        int threshold = 6; // Threshold value to check against

        // Create a vector to collect values greater than the threshold
        std::vector<int> greaterThanThreshold;

        // Use std::copy_if with std::any_of to collect values greater than the threshold
        std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(greaterThanThreshold), 
                    [threshold](int num) {
                        return num > threshold;
                    });

        // Check if any values were collected
        if (!greaterThanThreshold.empty()) {
            std::cout << "Values greater than " << threshold << ": ";
            for (int num : greaterThanThreshold) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No values greater than " << threshold << " found." << std::endl;
        }        
    }

    void stdAllOf() {
        PRINT_FUNC_NAME();        
        std::vector<int> numbers = {1, 2, 3, 4, 5};

        bool allEven = std::all_of(numbers.begin(), numbers.end(), [](int num) {
            return num % 2 == 0;
        });

        if (allEven) {
            std::cout << "All numbers are even." << std::endl;
        } else {
            std::cout << "Not all numbers are even." << std::endl;
        }        
    }

    void stdCount() {
        PRINT_FUNC_NAME();
        std::vector<int> numbers = {1, 2, 2, 3, 2, 4, 5};

        int countTwos = std::count(numbers.begin(), numbers.end(), 2);

        std::cout << "Number of twos: " << countTwos << std::endl;        
    }

    void stdCopy() {
        PRINT_FUNC_NAME();        
        std::vector<int> source = {1, 2, 3, 4, 5};
        std::vector<int> target(source.size());

        std::copy(source.begin(), source.end(), target.begin());

        for (int num : target) {
            std::cout << num << " ";
        }
        std::cout << std::endl;        
    }

    void stdTransform() {
        PRINT_FUNC_NAME();        
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::vector<int> squared(numbers.size());

        std::transform(numbers.begin(), numbers.end(), squared.begin(), [](int num) {
            return num * num;
        });

        for (int square : squared) {
            std::cout << square << " ";
        }
        std::cout << std::endl;        
    }

    void stdPower() {
        PRINT_FUNC_NAME();
        double base = 2.0;
        double exponent = 3.0;
        double result = std::pow(base, exponent);
        std::cout << base << " raised to the power of " << exponent << " is " << result << std::endl;
    }

    void stdDeque() {
        PRINT_FUNC_NAME();
        std::deque<int> deque;
        deque.push_back(1);
        deque.push_front(2);
        deque.push_back(3);
        std::cout << "Front: " << deque.front() << ", Back: " << deque.back() << std::endl; // Prints Front: 2, Back: 3
    }

    void stdStringStream() {
        PRINT_FUNC_NAME();
        int num = 42;
        std::stringstream ss;

        ss << "The answer is: " << num;

        std::string result = ss.str();
        std::cout << result << std::endl; // Prints "The answer is: 42"
    }

    void stdWstringConvert() {
        PRINT_FUNC_NAME();
        std::wstring wideStr = L"Hello, World!";
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        std::string narrowStr = converter.to_bytes(wideStr);
        std::wstring convertedWideStr = converter.from_bytes(narrowStr);

        // Convert narrow string to wide string and then print
        std::wcout << L"Narrow String: " << std::wstring(narrowStr.begin(), narrowStr.end()) << std::endl;
        std::wcout << L"Converted Wide String: " << convertedWideStr << std::endl;
    }

    void stdTuple() {       
        PRINT_FUNC_NAME(); 
        auto result = []() {
            return std::make_tuple(42, 3.14159, "Hello");
        };

        // Invoke the lambda to get the tuple
        auto tupleResult = result();

        int intValue = std::get<0>(tupleResult);
        double doubleValue = std::get<1>(tupleResult);
        std::string stringValue = std::get<2>(tupleResult);

        std::cout << "Int: " << intValue << ", Double: " << doubleValue << ", String: " << stringValue << std::endl;
    }

    void stdFuture() {
        PRINT_FUNC_NAME();        
        std::future<int> result = std::async([]() {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 42;
        });
        std::cout << "Waiting for the result..." << std::endl;
        int value = result.get();
        std::cout << "Result: " << value << std::endl;        
    }

    void stdMakeMoveIterator() {
        PRINT_FUNC_NAME();
        std::vector<std::string> source = {"apple", "banana", "cherry"};
        std::vector<std::string> target;

        // Use std::make_move_iterator to create move iterators
        auto start = std::make_move_iterator(source.begin());
        auto end = std::make_move_iterator(source.end());
        auto dest = std::back_inserter(target);

        // Move elements from source to target using move iterators
        std::move(start, end, dest);

        // After the move, source is in a valid but unspecified state
        for (const std::string& item : target) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    [[maybe_unused]]
    void signal_callback_handler(int signum) {
        std::cout << "Signal (" << signum << ") received." << std::endl;
        // terminate the program
        exit(signum); 
    }

    void stSignal_1() {
        // std::signal(SIGINT, signal_callback_handler);
        std::signal(SIGINT, [](int signum) {
            std::cerr << "Signal (" << signum << ") received." << std::endl << std::flush;
            exit(0);
        });

        std::cout << "Press Ctrl+C to trigger the SIGINT signal." << std::endl << std::flush;
        int i = 0;
        while (true) {
            std::cout << "i = " << i << std::endl << std::flush;
            sleep(1);
            i++;
        }
    }
    


}

int main(int argc, char *argv[]) {
#ifdef VISITOR_PATTERN_EXAMPLE
    // Create shapes
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    // Create a visitor
    AreaVisitor areaVisitor;

    // Accept the visitor for each shape
    circle.accept(areaVisitor);
    rectangle.accept(areaVisitor);
#endif

#ifdef STD_EXAMPLE
    // std::filesystem::exists
    // stdFilesystemExist();
    
    // processing epoch time
    // epochTime();
    
    // regular file checker
    // regularFileChecker();

    // creating a directory
    // createDirectory();

    // input stream txt file
    // inputStreamTextFile();

    // output stream 
    // outputStreamTextFile();

    // thread
    // create 2 thread and start executing the thread function 
    // stdThread();

    // find occurence char
    // char2Find();    

    // std::sort
    // stdSort_1();

    // std::reverse
    // stdReverse();

    // std::distance
    // stdDistance();

    // std::optional, std::nullopt
    // stdOptional();

    // struct with constructor inside
    // auto a = StructWithCons::main2();

    // std::unordered_map
    // std_unordered_map_example::runExample_1();
    // std_unordered_map_example::runExample_2();
    // std_unordered_map_example::runExample_3();

    // std::array
    // std_array_example::runExample_1();

    // std::map
    // std_map_example::runExample_1();
    // std_map_example::runExample_2();

    // std::valarray
    // std_valarray_example::runExample_1();

    // std::enable_if
    // std_2::enableIf();
    // std_2::countIf();
    // std_2::findIf();
    // std_2::anyOf();
    // std_2::anyOf_2();
    // std_2::stdAllOf();
    // std_2::stdCount();
    // std_2::stdCopy();
    // std_2::stdTransform();
    // std_2::stdPower();
    // std_2::stdDeque();
    // std_2::stdStringStream();
    // std_2::stdWstringConvert();
    // std_2::stdWstringConvert();
    // std_2::stdTuple();
    // std_2::stdFuture();
    // std_2::stdMakeMoveIterator();
    std_2::stSignal_1();


#endif

#ifdef LYRA_EXAMPLE_3

    std::string mode;
    bool aaOneTime = false;
    bool bbOneTime = false;
    bool bbService = false;

    // Define the command line parser using Lyra
    auto cli = lyra::cli();

    // Define the "mode" flag with two possible values: "aa" and "bb"
    cli |= lyra::opt(mode, "mode")["--mode"]
        ("Select mode: aa or bb")
        .required();

    // Define options based on the selected mode
    cli |= lyra::opt(aaOneTime)["--aa_one_time"]
        ("Enable aa_one_time flag");

    cli |= lyra::opt(bbOneTime)["--bb_one_time"]
        ("Enable bb_one_time flag");

    cli |= lyra::opt(bbService)["--bb_service"]
        ("Enable bb_service flag");

    // Parse the command line arguments
    auto result = cli.parse({argc, argv});

    // Check for errors or display help
    if (!result) {
        std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
        std::cerr << cli << std::endl; // Display help
        return 1;
    }

    // Check the selected mode and print options accordingly
    if (mode == "aa") {
        std::cout << "Mode: aa" << std::endl;
        std::cout << "aa_one_time: " << aaOneTime << std::endl;
    } else if (mode == "bb") {
        std::cout << "Mode: bb" << std::endl;
        if (bbOneTime == bbService) {
            std::cerr << "Error: bb_one_time and bb_service cannot be enabled at the same time" << std::endl;
            return 1;
        }
        std::cout << "bb_one_time: " << bbOneTime << std::endl;
        std::cout << "bb_service: " << bbService << std::endl;
    }

#endif

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

#if LYRA_EXAMPLE_2
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

#if LYRA_EXAMPLE
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
    std::wstring japstr = L"大学労働組合";
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