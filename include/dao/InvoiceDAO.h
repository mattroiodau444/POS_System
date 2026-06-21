/*
 =============================================================
 File: InvoiceDAO.h
 Mô tả: Khai báo lớp InvoiceDAO - Truy xuất dữ liệu
          bảng invoices và invoice_items
 =============================================================
 */

#pragma once

#include <vector>
#include <string>
#include "../models/Invoice.h"
#include "../models/CartItem.h"
#include "DatabaseManager.h"

/*
 Lớp InvoiceDAO - Truy xuất dữ liệu bảng invoices và invoice_items
 */
class InvoiceDAO {
private:
    DatabaseManager& dbManager;

public:
    // Constructor - nhận tham chiếu đến DatabaseManager
    explicit InvoiceDAO(DatabaseManager& dbManager);

    // Tạo hóa đơn mới, trả về ID của hóa đơn vừa tạo (-1 nếu lỗi)
    int createInvoice(const Invoice& invoice);
    // Thêm chi tiết hóa đơn (một dòng sản phẩm)
    bool addInvoiceItem(int invoiceId, const CartItem& item);
    // Lấy danh sách tất cả hóa đơn
    std::vector<Invoice> getAllInvoices();
    // Lấy hóa đơn theo ID (bao gồm chi tiết)
    Invoice getInvoiceById(int id);
    // Lấy danh sách chi tiết của một hóa đơn
    std::vector<CartItem> getInvoiceItems(int invoiceId);
    // Sinh mã hóa đơn tự động (HD0001, HD0002, ...)
    std::string generateInvoiceCode();
};
