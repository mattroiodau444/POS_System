/*
 =============================================================
 File: Product.h
 Mô tả: Khai báo lớp Product - Đại diện cho sản phẩm
 Ràng buộc: price > 0, stock >= 0, code không trùng
 =============================================================
 */

#pragma once

#include <string>

/*
 Lớp Product - Đại diện cho sản phẩm trong cửa hàng
 Ràng buộc: price > 0, stock >= 0, code không trùng
 */
class Product {
private:
    int id;
    std::string code;    // Mã sản phẩm (duy nhất)
    std::string name;    // Tên sản phẩm
    double price;        // Giá bán
    int stock;           // Số lượng tồn kho
    std::string category; // Danh mục sản phẩm

public:
    // Constructor mặc định
    Product();
    // Constructor đầy đủ tham số
    Product(int id, const std::string& code, const std::string& name,
            double price, int stock, const std::string& category);

    // --- Getters ---
    int getId() const;
    const std::string& getCode() const;
    const std::string& getName() const;
    double getPrice() const;
    int getStock() const;
    const std::string& getCategory() const;

    // --- Setters ---
    void setId(int id);
    void setCode(const std::string& code);
    void setName(const std::string& name);
    void setPrice(double price);
    void setStock(int stock);
    void setCategory(const std::string& category);

    // Kiểm tra dữ liệu sản phẩm hợp lệ (price > 0, stock >= 0, code và name không rỗng)
    bool isValid() const;
};
