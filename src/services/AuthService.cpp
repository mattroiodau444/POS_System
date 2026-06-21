// AuthService.cpp - Xử lý xác thực và phân quyền

#include "services/AuthService.h"

using namespace std;

AuthService::AuthService(UserDAO& userDAO)
    : userDAO(userDAO), currentUser(), loggedIn(false) {}

// Đăng nhập: xác thực qua DAO, lưu user nếu thành công
bool AuthService::login(const string& username, const string& password) {
    User user = userDAO.authenticate(username, password);
    if (user.isValid()) {
        currentUser = user;
        loggedIn = true;
        return true;
    }
    return false;
}

void AuthService::logout() {
    loggedIn = false;
    currentUser = User();
}

const User& AuthService::getCurrentUser() const { return currentUser; }
bool AuthService::isLoggedIn() const { return loggedIn; }
bool AuthService::isAdmin() const { return loggedIn && currentUser.isAdmin(); }
