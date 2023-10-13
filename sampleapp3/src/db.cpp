#include "db.h"

namespace KOTOBAKOE::DB {
DatabaseConnector::DatabaseConnector(const std::string& connection_string) {
    try {
        connection = pqxx::connection(connection_string);
        if (!connection.is_open()) {
            throw std::runtime_error("Failed to open database connection.");
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Database connection error: " + std::string(e.what()));
    }
}

DatabaseConnector::~DatabaseConnector() {
    connection.close();
}

bool DatabaseConnector::IsTableExists(const std::string& table_name) {
    try {
        pqxx::work txn(connection);
        pqxx::result result = txn.exec(
            "SELECT EXISTS ("
            "  SELECT 1 "
            "  FROM information_schema.tables "
            "  WHERE table_name = " + txn.quote(table_name) +
            ");"
        );
        txn.commit();
        
        return result[0][0].as<bool>();
    } catch (const std::exception& e) {
        throw std::runtime_error("Table existence check failed: " + std::string(e.what()));
    }
}

pqxx::result DatabaseConnector::ExecuteQuery(const std::string& query) {
    try {
        pqxx::work txn(connection);
        pqxx::result result = txn.exec(query);
        txn.commit();
        return result;
    } catch (const std::exception& e) {
        throw std::runtime_error("Query execution failed: " + std::string(e.what()));
    }
}
} // namespace KOTOBAKOE::DB