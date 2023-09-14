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
- [ ] std::filesystem::is_regular_file
- [ ] std::filesystem::is_directory
- [ ] std::filesystem::create_directory
- [ ] std::filesystem::path
- [ ] std::ifstream and std::ofstream
- [ ] std::stringstream
- [ ] std::count_if
- [ ] iterators -> std::begin, std::end, std::distance
- [ ] std::getline
- [ ] std::map
- [ ] std::map<std::wstring, int>::const_iterator
- [ ] std::signal(SIGINT, signal_callback_handler)
- [ ] std::thread // create 2 thread, which while loop. Simulate this to see when debugging, gdb will interchange one to another thread

## add submodules
- [x] NumCpp
- [ ] observable
- [ ] nlohmann_json

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


