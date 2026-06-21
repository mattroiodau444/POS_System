// DatabaseManager.cpp - Quản lý kết nối SQLite (Singleton)

#include "dao/DatabaseManager.h"
#include "sqlite3.h"
#include <iostream>
#include <fstream>

using namespace std;

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() : db(nullptr), dbPath("") {}

DatabaseManager::~DatabaseManager() { close(); }

DatabaseManager& DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return *instance;
}

bool DatabaseManager::open(const string& path) {
    dbPath = path;
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        cerr << "[LỖI] Không thể mở database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
        return false;
    }
    return true;
}

void DatabaseManager::close() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

sqlite3* DatabaseManager::getDB() { return db; }

void DatabaseManager::initTables() {
    const char* sqlUsers =
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "full_name TEXT NOT NULL, "
        "role TEXT NOT NULL);";

    const char* sqlProducts =
        "CREATE TABLE IF NOT EXISTS products("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "code TEXT UNIQUE NOT NULL, "
        "name TEXT NOT NULL, "
        "price REAL NOT NULL CHECK(price > 0), "
        "stock INTEGER NOT NULL CHECK(stock >= 0), "
        "category TEXT DEFAULT '');";

    const char* sqlInvoices =
        "CREATE TABLE IF NOT EXISTS invoices("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "invoice_code TEXT UNIQUE NOT NULL, "
        "user_id INTEGER REFERENCES users(id), "
        "cashier_name TEXT NOT NULL, "
        "date_time TEXT NOT NULL, "
        "total_amount REAL NOT NULL);";

    const char* sqlInvoiceItems =
        "CREATE TABLE IF NOT EXISTS invoice_items("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "invoice_id INTEGER REFERENCES invoices(id), "
        "product_code TEXT NOT NULL, "
        "product_name TEXT NOT NULL, "
        "price REAL NOT NULL, "
        "quantity INTEGER NOT NULL, "
        "subtotal REAL NOT NULL);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sqlUsers, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "[LỖI] Tạo bảng users: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    if (sqlite3_exec(db, sqlProducts, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "[LỖI] Tạo bảng products: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    if (sqlite3_exec(db, sqlInvoices, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "[LỖI] Tạo bảng invoices: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    if (sqlite3_exec(db, sqlInvoiceItems, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "[LỖI] Tạo bảng invoice_items: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

// Nạp dữ liệu mẫu nếu DB rỗng (chạy lần đầu)
void DatabaseManager::seedData() {
    sqlite3_stmt* stmt = nullptr;

    // Kiểm tra bảng users
    int userCount = 0;
    if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users;", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW)
            userCount = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    stmt = nullptr;

    if (userCount == 0) {
        const char* sql = "INSERT INTO users(username, password, full_name, role) VALUES(?, ?, ?, ?);";
        string users[][4] = {
            {"admin",     "admin123", "Nguyễn Đức Trọng", "admin"},
            {"nhanvien1", "nv123",    "Nguyễn Văn Đức",  "staff"},
            {"nhanvien2", "nv456",    "Trần Thị Lan",    "staff"}
        };
        for (int i = 0; i < 3; i++) {
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, users[i][0].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 2, users[i][1].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 3, users[i][2].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 4, users[i][3].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_step(stmt);
            }
            sqlite3_finalize(stmt);
            stmt = nullptr;
        }
    }

    // Kiểm tra bảng products
    int productCount = 0;
    if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM products;", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW)
            productCount = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    stmt = nullptr;

    if (productCount == 0) {
        const char* sql = "INSERT INTO products(code, name, price, stock, category) VALUES(?, ?, ?, ?, ?);";
        string codes[]      = {"SP001","SP002","SP003","SP004","SP005","SP006","SP007","SP008","SP009","SP010"};
        string names[]      = {"Coca Cola 330ml","Pepsi 330ml","Mi Hao Hao","Banh Oreo","Sua Vinamilk 180ml","Nuoc suoi Lavie 500ml","Snack Oishi","Dau an Neptune 1L","Gao ST25 5kg","Bot giat OMO 3kg"};
        double prices[]     = {10000,10000,4000,15000,7000,5000,8000,45000,120000,95000};
        int stocks[]        = {100,80,200,50,120,150,90,30,25,40};
        string categories[] = {"Nuoc uong","Nuoc uong","Thuc pham","Banh keo","Sua","Nuoc uong","Banh keo","Gia vi","Thuc pham","Hoa pham"};

        for (int i = 0; i < 10; i++) {
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, codes[i].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 2, names[i].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_double(stmt, 3, prices[i]);
                sqlite3_bind_int(stmt, 4, stocks[i]);
                sqlite3_bind_text(stmt, 5, categories[i].c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_step(stmt);
            }
            sqlite3_finalize(stmt);
            stmt = nullptr;
        }
    }
}

// Sao lưu database (copy byte-by-byte)
bool DatabaseManager::backupDatabase(const string& backupPath) {
    ifstream src(dbPath, ios::binary);
    if (!src.is_open()) {
        cerr << "[LỖI] Không thể mở file nguồn: " << dbPath << endl;
        return false;
    }

    ofstream dst(backupPath, ios::binary);
    if (!dst.is_open()) {
        cerr << "[LỖI] Không thể tạo file backup: " << backupPath << endl;
        src.close();
        return false;
    }

    char ch;
    while (src.get(ch)) dst.put(ch);

    src.close();
    dst.close();
    return true;
}
