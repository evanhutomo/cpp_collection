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
- [ ] std::ifstream and std::ofstream
- [ ] std::stringstream
- [ ] std::filesystem::exists
- [ ] std::filesystem::is_regular_file
- [ ] std::filesystem::is_directory
- [ ] std::filesystem::create_directory
- [ ] iterators -> std::begin, std::end, std::distance
- [ ] std::getline
- [ ] std::map
- [ ] std::map<std::wstring, int>::const_iterator
- [ ] std::filesystem::path

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


