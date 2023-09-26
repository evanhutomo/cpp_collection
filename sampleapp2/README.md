## sampleapp2

## Structure

```
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── app
│   └── main.cpp
├── configs
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── settings.json
├── inc
│   ├── lat1.h
│   ├── lat2.h
│   └── sambel.h
├── runner
└── src
    ├── lat1.cpp
    ├── lat2.cpp
    └── sambel.cpp
```

## How to cmake build

```
./runner.sh -a
```

## Task lat1
- [x] std::filesystem::exists
- [x] processing epoch time
- [x] std::filesystem::is_regular_file
- [x] std::filesystem::is_directory
- [x] std::filesystem::path
- [x] std::filesystem::create_directory
- [x] std::ifstream (input file stream)
- [x] std::ofstream (output file stream)
- [ ] std::stringstream
- [ ] std::count_if
- [ ] std::getline
- [ ] std::map
- [ ] std::map<T>
- [ ] std::map<std::wstring, int>::const_iterator
- [ ] std::enable_if
- [ ] std::enable_if_t<T>
- [ ] std::decay
- [ ] std::declval
- [ ] std::tuple
- [ ] std::wstring_convert<T>
- [ ] std::wstring
- [ ] std::any_of
- [ ] std::make_move_iterator
- [ ] std::future
- [ ] std::all_of
- [ ] std::unordered_map<T>
	reserve
	try_emplace
- [ ] std::ref<T>
	get
	size
- [ ] std::count
- [ ] std::array<T>
- [ ] std::unique_ptr<T>
- [ ] std::nullopt
- [ ] std::optional<T>
    value
    size
    at
    value_or
- [ ] std::filesystem::path
- [ ] std::string
- [ ] std::string::find_first_of
- [ ] std::string::npos
- [ ] std::copy
- [ ] std::make_unique<T>
- [ ] std::transform
- [ ] std::pow
- [ ] std::valarray<T>
- [ ] iterators -> std::begin, std::end, std::distance
- [ ] std::signal(SIGINT, signal_callback_handler)
- [x] std::thread // create 2 thread, which while loop. Simulate this to see when debugging, gdb will interchange one to another thread
- [x] std::this_thread::sleep_for

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


