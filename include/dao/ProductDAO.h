/*
 =============================================================
 File: ProductDAO.h
 Mô tả: Khai báo lớp ProductDAO - Truy xuất dữ liệu bảng products
 =============================================================
 */

#pragma once

#include <vector>
#include <string>
#include "../models/Product.h"
#include "DatabaseManager.h"

/*
 Lớp ProductDAO - Truy xuất dữ liệu bảng products
 */
class ProductDAO {
private:
    DatabaseManager& dbManager;

public:
    // Constructor - nhận tham chiếu đến DatabaseManager
    explicit ProductDAO(DatabaseManager& dbManager);

    // Thêm sản phẩm mới vào database
    bool addProduct(const Product& product);
    // Cập nhật thông tin sản phẩm
    bool updateProduct(const Product& product);
    // Xóa sản phẩm theo ID
    bool deleteProduct(int id);
    // Tìm sản phẩm theo ID
    Product findById(int id);
    // Tìm sản phẩm theo mã
    Product findByCode(const std::string& code);
    // Lấy danh sách tất cả sản phẩm
    std::vector<Product> getAllProducts();
    // Cập nhật số lượng tồn kho
    bool updateStock(int id, int newStock);
    // Kiểm tra mã sản phẩm đã tồn tại chưa
    bool isCodeExists(const std::string& code);
    // Đếm tổng số sản phẩm
    int countProducts();
};
