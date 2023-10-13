#ifndef DB_H
#define DB_H

#include <string>
#include <pqxx/pqxx>

namespace KOTOBAKOE::DB {
class DatabaseConnector {
public:
    DatabaseConnector(const std::string& connection_string);
    ~DatabaseConnector();

    bool IsTableExists(const std::string& table_name);
    pqxx::result ExecuteQuery(const std::string& query);

private:
    pqxx::connection connection;
};
} // namespace KOTOBAKOE::DB

#endif
