/*
 =============================================================
 File: UserDAO.h
 Mô tả: Khai báo lớp UserDAO - Truy xuất dữ liệu bảng users
 =============================================================
 */

#pragma once

#include <vector>
#include <string>
#include "../models/User.h"
#include "DatabaseManager.h"

/*
 Lớp UserDAO - Truy xuất dữ liệu bảng users
 */
class UserDAO {
private:
    DatabaseManager& dbManager;

public:
    // Constructor - nhận tham chiếu đến DatabaseManager
    explicit UserDAO(DatabaseManager& dbManager);

    // Xác thực đăng nhập, trả về User hợp lệ hoặc User rỗng
    User authenticate(const std::string& username, const std::string& password);
    // Tìm user theo username
    User findByUsername(const std::string& username);
    // Lấy danh sách tất cả users
    std::vector<User> getAllUsers();
};
