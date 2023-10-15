# Kotobakoe
Simple vocabulary flash card apps for private use.

# TODO
- [x] try to write neat cmake file
- [x] compose data struct for save to json later
- [x] create feature parse my own vocabulary data text (notion) to JSON
- [x] explore examples of FTXUI
- [x] try to implement FTXUI
- [x] find event on FTXUI
- [x] create db, 1 table (id, word, meaning, example, created_at, updated_at)
- [ ] feature no duplication 
      - input is json kanjis which is created before, parse the data to vector of struct 
      - SELECT query all kanji_cards records and put it into vector of struct
      - compare 2 vectors, if there is a duplication, skip it
        if not, insert it to db

- [ ] add sample code from FTXUI to this project
- [ ] create a menu 1. parse to JSON (input: txt file with xx-xx-xx format, output: json file, err code) 
- [ ] create a menu 2. DB (input: json file, output: records in DB, err code)

# Learn material
- [x] lyra
- [x] spdlog
- [x] nlohmann-json
- [x] FTXUI
- [x] pqxx
- [ ] toml
- [ ] visit_struct