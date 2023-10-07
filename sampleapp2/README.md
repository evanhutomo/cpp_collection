## sampleapp2
just sample app to drill myself how to handle with common c++ std lib.  

## How to cmake build

```
./runner.sh -a
```
or just implement configs/ to .vscode/ directory.

## Task lat1
- [x] std::filesystem::exists
- [x] processing epoch time
- [x] std::filesystem::is_regular_file
- [x] std::filesystem::is_directory
- [x] std::filesystem::path
- [x] std::filesystem::create_directory
- [x] std::ifstream (input file stream)
- [x] std::ofstream (output file stream)
- [x] std::filesystem::path
- [x] std::string
- [x] std::unique_ptr<T>
- [x] std::make_unique<T> 
- [x] std::thread
- [x] std::this_thread::sleep_for
- [x] std::string::find_first_of
- [x] std::string::npos
- [x] std::sort
- [x] std::vector<T>
- [x] std::reverse
- [x] std::nullopt
- [x] std::optional<T>::value()
- [x] std::optional<T>::value_or()
- [x] iterators -> std::begin, std::end, std::distance
- [x] std::unordered_map<T>
- [x] std::unordered_map<T>::reserve() -> preallocate the memory
- [x] std::unordered_map<T>::bucket_count() -> get the bucket count
- [x] std::unordered_map<T>::try_emplace()
- [x] std::map<T>
- [x] std::map<std::wstring, int>::const_iterator 
- [x] std::array<T>
- [x] std::valarray<T>
- [x] std::getline -> get one line on std::ifstream
- [x] std::wstring
- [x] std::count_if
- [x] std::enable_if
- [x] std::find_if
- [x] std::any_of -> check if any element in a sequence (e.g., a container or a range) satisfies a given condition
- [x] std::copy_if ->  copy elements from one range (e.g., a container or a range defined by two iterators) to another range based on a specified condition.
- [x] std::back_inserter -> iterator adapter that is used in combination with algorithms like std::copy_if to insert elements at the end of a container
- [x] std::all_of -> checks if all elements in a range satisfy a given condition.
- [x] std::count -> counts the occurrences of a specific value in a range.
- [x] std::copy -> copies elements from one range to another.
- [x] std::transform ->  applies a function to each element in a range and stores the results in another range.
- [x] std::pow -> computes the power of a number.
- [x] std::deque<T> -> is a sequence container that, like a vector (std::vector), supports random access to its elements.
- [x] std::stringstream -> is a stream class to operate on strings.
- [x] std::wstring_convert<T>

- [ ] std::decay
- [ ] std::declval
- [ ] std::tuple
- [ ] std::future
- [ ] std::make_move_iterator
- [ ] getopt
- [ ] std::signal(SIGINT, signal_callback_handler)

- [ ] std::enable_if_t<T> -> is a type trait that can be used to conditionally enable or disable template specializations.
- [ ] std::ref<T>
- [ ] std::lock_guard<std::mutex>
- [ ] std::unordered_multimap<T>

## add submodules
- [x] NumCpp
- [ ] observable
- [ ] nlohmann_json

## add design pattern
- [x] visitor
- [ ] observer
- [ ] singleton
- [ ] factory
- [ ] builder
- [ ] adapter

## algorithm
- [ ] hash function
- [ ] linked list
- [ ] binary tree
- [ ] graph
- [ ] stack
- [ ] queue
- [ ] heap
- [ ] priority queue
- [ ] sort
- [ ] search
- [ ] dynamic programming

## other
- [ ] predicate function

## Study case
```1.
inline std::wstring String2WideString(const std::string& str) {
    using a = std::codecvt_utf8_utf16<wchar_t>;                 // learn this pattern
    std::wstring_convert<convert_typeX, wchar_t> converterX;    // learn this pattern
    return converterX.from_bytes(str);
}
```

```2.
std::optional<std::map<std::wstring, int>> arg1;
auto a = SomeFunc(*arg1, arg2);     // pass by reference?? 
```

```3. 
std::vector<structA> contents(10); // let say there are 10 elements
std::vector<SOME::SomeStruct> _variable(contents.begin(), contents.end());  // put the contents into _variable
std::sort(std::begin(_variable), std::end(_variable), someFunc);  // use someFunc to sort the _variable

bool someFunc(std::vector<structA> a, std::vector<structA> b) {
    return a.member1 < b.member1;
}
```

```4. iterate and change the value
    std::string someString = "01011";
    std::vector<bool> result;
    std::transform(someString.begin(), someString.end(), result.begin(), [](auto x) {
        return x == '1' ? true : false;
        });
    return result;
```

```5. 
namespace std {
    template <>
    struct hash<MyKey> {
        std::size_t operator()(const MyKey &key) const {
            return std::hash<std::string>()(key.getName()) ^ std::hash<int>()(key.getId());
        }
    };
}
```
