#include "Database.h"

Database::Database(const std::string& path) {
    int result = sqlite3_open(path.c_str(), &db);

    if (result != SQLITE_OK) {
        std::string error = sqlite3_errmsg(db);
        sqlite3_close(db);
        db = nullptr;

        throw std::runtime_error("Failed to open database: " + error);
    }
}

Database::~Database() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::initializeTables() {
    if (!this->db) {
        std::cout << "[DB] Error: could not initialize tables, database connection is null" << std::endl;
        return false;
    }

    if (!executeSqlScript("data/db_creation_statements.sql")) {
        std::cout << "[DB] Error: could not initialize tables from script" << std::endl;
        return false;
    }

    return true;
}

bool Database::insertData() {
    if (!this->db) {
        std::cout << "[DB] Error: could not insert the data, database connection is null" << std::endl;
        return false;
    }

    if (!executeSqlScript("data/mock_data.sql")) {
        std::cout << "[DB] Error: could not insert the data from script" << std::endl;
        return false;
    }

    return true;
}

bool Database::executeQuery(const std::string& query) {
    char *errorMessage = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cout << "[DB] Error executing query: " << errorMessage << std::endl;

        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

bool Database::executeSqlScript(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "[DB] Error: Could not open sql script at: " << path << std::endl;
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string sqlQuery = buffer.str();

    if (bool rc = executeQuery(sqlQuery); !rc) {
        std::cout << "[DB] Error: Could not execute script" << std:: endl;
        return false;
    }

    return true;
}

bool Database::isTableEmpty(const std::string& tableName) {
    std::string sqlQuery = "SELECT COUNT(*) FROM " + tableName + ";";
    sqlite3_stmt* stmt = nullptr;
    bool isEmpty = true;

    if (sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            isEmpty = count == 0;
        }
    } else {
        std::string errorMessage = sqlite3_errmsg(db);
        std::cout << "[DB] Error checking if the table " << tableName << " is empty: " << errorMessage << std::endl;
        throw std::runtime_error("Database query failed: " + errorMessage);
    }

    sqlite3_finalize(stmt);
    return isEmpty;
}