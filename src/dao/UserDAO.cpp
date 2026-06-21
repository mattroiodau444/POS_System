// UserDAO.cpp - Truy xuất dữ liệu bảng users

#include "dao/UserDAO.h"
#include "sqlite3.h"

using namespace std;

UserDAO::UserDAO(DatabaseManager& dbManager) : dbManager(dbManager) {}

// Xác thực đăng nhập, trả về User rỗng nếu thất bại
User UserDAO::authenticate(const string& username, const string& password) {
    User user;
    sqlite3_stmt* stmt = nullptr;

    const char* sql = "SELECT * FROM users WHERE username=? AND password=?;";
    if (sqlite3_prepare_v2(dbManager.getDB(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* uname = (const char*)sqlite3_column_text(stmt, 1);
            const char* pwd   = (const char*)sqlite3_column_text(stmt, 2);
            const char* fname = (const char*)sqlite3_column_text(stmt, 3);
            const char* rl    = (const char*)sqlite3_column_text(stmt, 4);
            user = User(sqlite3_column_int(stmt, 0),
                        uname ? uname : "", pwd ? pwd : "",
                        fname ? fname : "", rl ? rl : "");
        }
    }
    sqlite3_finalize(stmt);
    return user;
}

User UserDAO::findByUsername(const string& username) {
    User user;
    sqlite3_stmt* stmt = nullptr;

    const char* sql = "SELECT * FROM users WHERE username=?;";
    if (sqlite3_prepare_v2(dbManager.getDB(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* uname = (const char*)sqlite3_column_text(stmt, 1);
            const char* pwd   = (const char*)sqlite3_column_text(stmt, 2);
            const char* fname = (const char*)sqlite3_column_text(stmt, 3);
            const char* rl    = (const char*)sqlite3_column_text(stmt, 4);
            user = User(sqlite3_column_int(stmt, 0),
                        uname ? uname : "", pwd ? pwd : "",
                        fname ? fname : "", rl ? rl : "");
        }
    }
    sqlite3_finalize(stmt);
    return user;
}

vector<User> UserDAO::getAllUsers() {
    vector<User> users;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM users;", -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* uname = (const char*)sqlite3_column_text(stmt, 1);
            const char* pwd   = (const char*)sqlite3_column_text(stmt, 2);
            const char* fname = (const char*)sqlite3_column_text(stmt, 3);
            const char* rl    = (const char*)sqlite3_column_text(stmt, 4);
            users.push_back(User(sqlite3_column_int(stmt, 0),
                                 uname ? uname : "", pwd ? pwd : "",
                                 fname ? fname : "", rl ? rl : ""));
        }
    }
    sqlite3_finalize(stmt);
    return users;
}
