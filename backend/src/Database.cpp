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


void executeQuery(const std::string& query);