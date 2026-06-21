/*
 =============================================================
 File: AuthService.h
 Mô tả: Khai báo lớp AuthService - Xử lý xác thực và phân quyền
 =============================================================
 */

#pragma once

#include <string>
#include "../models/User.h"
#include "../dao/UserDAO.h"

/*
 Lớp AuthService - Xử lý nghiệp vụ xác thực và phân quyền
 */
class AuthService {
private:
    UserDAO& userDAO;       // Tham chiếu đến UserDAO
    User currentUser;       // Thông tin user đang đăng nhập
    bool loggedIn;          // Trạng thái đăng nhập

public:
    // Constructor
    explicit AuthService(UserDAO& userDAO);

    // Đăng nhập với username và password
    bool login(const std::string& username, const std::string& password);
    // Đăng xuất
    void logout();
    // Lấy thông tin user đang đăng nhập
    const User& getCurrentUser() const;
    // Kiểm tra đã đăng nhập chưa
    bool isLoggedIn() const;
    // Kiểm tra user hiện tại có quyền admin không
    bool isAdmin() const;
};
