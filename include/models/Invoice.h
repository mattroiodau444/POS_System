/*
 =============================================================
 File: Invoice.h
 Mô tả: Khai báo lớp Invoice - Đại diện cho hóa đơn bán hàng
 Chứa thông tin hóa đơn và danh sách các mặt hàng đã mua
 =============================================================
 */

#pragma once

#include <string>
#include <vector>
#include "CartItem.h"

/*
 Lớp Invoice - Đại diện cho hóa đơn bán hàng
 Chứa thông tin hóa đơn và danh sách các mặt hàng đã mua
 */
class Invoice {
private:
    int id;
    std::string invoiceCode;   // Mã hóa đơn (tự sinh)
    int userId;                // ID nhân viên bán hàng
    std::string cashierName;   // Tên nhân viên
    std::string dateTime;      // Ngày giờ tạo hóa đơn
    double totalAmount;        // Tổng tiền
    std::vector<CartItem> items; // Danh sách chi tiết hóa đơn

public:
    // Constructor mặc định
    Invoice();
    // Constructor đầy đủ tham số (không bao gồm items)
    Invoice(int id, const std::string& invoiceCode, int userId,
            const std::string& cashierName, const std::string& dateTime,
            double totalAmount);

    // --- Getters ---
    int getId() const;
    const std::string& getInvoiceCode() const;
    int getUserId() const;
    const std::string& getCashierName() const;
    const std::string& getDateTime() const;
    double getTotalAmount() const;
    const std::vector<CartItem>& getItems() const;

    // --- Setters ---
    void setId(int id);
    void setItems(const std::vector<CartItem>& items);

    // Thêm một mục vào danh sách chi tiết
    void addItem(const CartItem& item);
};
