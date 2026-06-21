/*
 ===========================================================
 File: CartItem.h
 Mô tả: Khai báo lớp CartItem - Mục trong giỏ hàng
 Giỏ hàng chỉ lưu tạm trong RAM, không lưu vào database
 =============================================================
 */

#pragma once

#include "Product.h"

/*
 Lớp CartItem - Đại diện cho một mục trong giỏ hàng
 Giỏ hàng chỉ lưu tạm trong RAM, không lưu vào database
 */
class CartItem {
private:
    Product product;  // Sản phẩm
    int quantity;     // Số lượng mua

public:
    // Constructor mặc định
    CartItem();
    // Constructor với sản phẩm và số lượng
    CartItem(const Product& product, int quantity);

    // --- Getters ---
    const Product& getProduct() const;
    int getQuantity() const;

    // --- Setter ---
    void setQuantity(int quantity);

    // Tính thành tiền = giá * số lượng
    double getSubtotal() const;
};
