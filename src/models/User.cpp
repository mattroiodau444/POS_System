// User.cpp - Lớp người dùng hệ thống

#include "models/User.h"

using namespace std;

// Constructor mặc định
User::User() : id(0), username(""), password(""), fullName(""), role("") {}

// Constructor đầy đủ
User::User(int id, const string& username, const string& password,
           const string& fullName, const string& role)
    : id(id), username(username), password(password),
      fullName(fullName), role(role) {}

// Getters
int User::getId() const { return id; }
const string& User::getUsername() const { return username; }
const string& User::getPassword() const { return password; }
const string& User::getFullName() const { return fullName; }
const string& User::getRole() const { return role; }

// Setters
void User::setId(int id) { this->id = id; }
void User::setUsername(const string& username) { this->username = username; }
void User::setPassword(const string& password) { this->password = password; }
void User::setFullName(const string& fullName) { this->fullName = fullName; }
void User::setRole(const string& role) { this->role = role; }

// Kiểm tra quyền admin
bool User::isAdmin() const { return role == "admin"; }

// User hợp lệ khi username không rỗng
bool User::isValid() const { return !username.empty(); }
