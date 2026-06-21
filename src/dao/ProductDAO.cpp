// ProductDAO.cpp - Truy xuất dữ liệu bảng products

#include "dao/ProductDAO.h"
#include "sqlite3.h"
#include <iostream>

using namespace std;

ProductDAO::ProductDAO(DatabaseManager& dbManager) : dbManager(dbManager) {}

// Hàm tiện ích: đọc một Product từ kết quả truy vấn hiện tại
static Product readProduct(sqlite3_stmt* stmt) {
    int id           = sqlite3_column_int(stmt, 0);
    const char* code = (const char*)sqlite3_column_text(stmt, 1);
    const char* name = (const char*)sqlite3_column_text(stmt, 2);
    double price     = sqlite3_column_double(stmt, 3);
    int stock        = sqlite3_column_int(stmt, 4);
    const char* cat  = (const char*)sqlite3_column_text(stmt, 5);
    return Product(id, code ? code : "", name ? name : "",
                   price, stock, cat ? cat : "");
}

bool ProductDAO::addProduct(const Product& product) {
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;
    const char* sql = "INSERT INTO products(code,name,price,stock,category) VALUES(?,?,?,?,?);";

    if (sqlite3_prepare_v2(dbManager.getDB(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, product.getCode().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, product.getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 3, product.getPrice());
        sqlite3_bind_int(stmt, 4, product.getStock());
        sqlite3_bind_text(stmt, 5, product.getCategory().c_str(), -1, SQLITE_TRANSIENT);
        ok = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!ok) cerr << "[LỖI] Thêm sản phẩm: " << sqlite3_errmsg(dbManager.getDB()) << endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

bool ProductDAO::updateProduct(const Product& product) {
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;
    const char* sql = "UPDATE products SET code=?,name=?,price=?,stock=?,category=? WHERE id=?;";

    if (sqlite3_prepare_v2(dbManager.getDB(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, product.getCode().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, product.getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 3, product.getPrice());
        sqlite3_bind_int(stmt, 4, product.getStock());
        sqlite3_bind_text(stmt, 5, product.getCategory().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 6, product.getId());
        ok = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!ok) cerr << "[LỖI] Cập nhật sản phẩm: " << sqlite3_errmsg(dbManager.getDB()) << endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

bool ProductDAO::deleteProduct(int id) {
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;

    if (sqlite3_prepare_v2(dbManager.getDB(), "DELETE FROM products WHERE id=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        ok = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!ok) cerr << "[LỖI] Xóa sản phẩm: " << sqlite3_errmsg(dbManager.getDB()) << endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

Product ProductDAO::findById(int id) {
    Product product;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM products WHERE id=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW)
            product = readProduct(stmt);
    }
    sqlite3_finalize(stmt);
    return product;
}

Product ProductDAO::findByCode(const string& code) {
    Product product;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM products WHERE code=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, code.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW)
            product = readProduct(stmt);
    }
    sqlite3_finalize(stmt);
    return product;
}

vector<Product> ProductDAO::getAllProducts() {
    vector<Product> products;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM products ORDER BY id;", -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW)
            products.push_back(readProduct(stmt));
    }
    sqlite3_finalize(stmt);
    return products;
}

bool ProductDAO::updateStock(int id, int newStock) {
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;

    if (sqlite3_prepare_v2(dbManager.getDB(), "UPDATE products SET stock=? WHERE id=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, newStock);
        sqlite3_bind_int(stmt, 2, id);
        ok = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!ok) cerr << "[LỖI] Cập nhật tồn kho: " << sqlite3_errmsg(dbManager.getDB()) << endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

bool ProductDAO::isCodeExists(const string& code) {
    sqlite3_stmt* stmt = nullptr;
    int count = 0;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT COUNT(*) FROM products WHERE code=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, code.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW)
            count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return (count > 0);
}

int ProductDAO::countProducts() {
    sqlite3_stmt* stmt = nullptr;
    int count = 0;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT COUNT(*) FROM products;", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW)
            count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count;
}
