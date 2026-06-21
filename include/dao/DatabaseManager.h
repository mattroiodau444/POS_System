/*
 =============================================================
 File: DatabaseManager.h
 Mô tả: Khai báo lớp DatabaseManager - Singleton Pattern
 Quản lý kết nối và thao tác cơ bản với SQLite
 =============================================================
 */

#pragma once

#include <string>

// Forward declaration - chỉ cần con trỏ sqlite3* trong header
// sqlite3.h chỉ include trong file .cpp nơi gọi API
struct sqlite3;

/*
 Lớp DatabaseManager - Singleton Pattern
 Đảm bảo chỉ có một kết nối database duy nhất trong toàn bộ ứng dụng
 */
class DatabaseManager {
private:
    static DatabaseManager* instance; // Con trỏ instance duy nhất
    sqlite3* db;                      // Con trỏ database SQLite
    std::string dbPath;               // Đường dẫn file database

    // Private constructor - không cho phép tạo từ bên ngoài
    DatabaseManager();
    // Không cho phép copy
    DatabaseManager(const DatabaseManager&);
    DatabaseManager& operator=(const DatabaseManager&);

public:
    // Lấy instance duy nhất của DatabaseManager
    static DatabaseManager& getInstance();

    // Mở kết nối đến file database
    bool open(const std::string& path);
    // Đóng kết nối database
    void close();
    // Lấy con trỏ sqlite3 để thực hiện truy vấn
    sqlite3* getDB();

    // Tạo các bảng nếu chưa tồn tại
    void initTables();
    // Sinh dữ liệu mẫu khi database rỗng
    void seedData();
    // Sao lưu database sang file khác
    bool backupDatabase(const std::string& backupPath);

    // Destructor - đóng kết nối
    ~DatabaseManager();
};
