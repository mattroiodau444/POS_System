/*
 =============================================================
 File: User.h
 Mô tả: Khai báo lớp User - Đại diện cho người dùng hệ thống
 Vai trò: admin (quản trị viên) hoặc staff (nhân viên)
 =============================================================
 */

#pragma once

#include <string>

/*
 Lớp User - Đại diện cho người dùng hệ thống
 Vai trò: admin (quản trị viên) hoặc staff (nhân viên)
 */
class User {
private:
    int id;
    std::string username;
    std::string password;
    std::string fullName;
    std::string role; // "admin" hoặc "staff"

public:
    // Constructor mặc định
    User();
    // Constructor đầy đủ tham số
    User(int id, const std::string& username, const std::string& password,
         const std::string& fullName, const std::string& role);

    // --- Getters ---
    int getId() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getFullName() const;
    const std::string& getRole() const;

    // --- Setters ---
    void setId(int id);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setFullName(const std::string& fullName);
    void setRole(const std::string& role);

    // Kiểm tra có phải admin không
    bool isAdmin() const;
    // Kiểm tra dữ liệu user có hợp lệ không (username không rỗng)
    bool isValid() const;
};
