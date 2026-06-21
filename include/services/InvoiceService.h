/*
 =============================================================
 File: InvoiceService.h
 Mô tả: Khai báo lớp InvoiceService - Xử lý giỏ hàng,
          thanh toán, hóa đơn
 =============================================================
 */

#pragma once

#include <vector>
#include <string>
#include "../models/CartItem.h"
#include "../models/Invoice.h"
#include "../dao/InvoiceDAO.h"
#include "../dao/ProductDAO.h"

/*
 Lớp InvoiceService - Xử lý nghiệp vụ bán hàng và hóa đơn
 Quản lý giỏ hàng (lưu tạm trong RAM), thanh toán, hóa đơn
 */
class InvoiceService {
private:
    InvoiceDAO& invoiceDAO;
    ProductDAO& productDAO;
    std::vector<CartItem> cart; // Giỏ hàng - chỉ lưu trong RAM

public:
    // Constructor
    InvoiceService(InvoiceDAO& invoiceDAO, ProductDAO& productDAO);

    // Thêm sản phẩm vào giỏ hàng (chỉ kiểm tra tồn kho, không trừ)
    bool addToCart(const Product& product, int quantity);
    // Xóa sản phẩm khỏi giỏ theo vị trí (0-indexed)
    bool removeFromCart(int index);
    // Xóa toàn bộ giỏ hàng
    void clearCart();
    // Lấy danh sách giỏ hàng hiện tại
    const std::vector<CartItem>& getCart() const;
    // Tính tổng tiền giỏ hàng
    double getCartTotal() const;

    /**
     * Thanh toán - Xử lý giao dịch bán hàng
     * - Trừ tồn kho cho từng sản phẩm
     * - Tạo hóa đơn và chi tiết hóa đơn trong database
     * - Xóa giỏ hàng sau khi thanh toán thành công
     * Trả về ID hóa đơn nếu thành công, -1 nếu thất bại
     */
    int checkout(int userId, const std::string& cashierName);

    /**
     * Hủy đơn hàng
     * - Không ghi dữ liệu hóa đơn
     * - Không thay đổi tồn kho
     * - Xóa toàn bộ giỏ hàng
     */
    void cancelOrder();

    // Lấy lịch sử tất cả hóa đơn
    std::vector<Invoice> getInvoiceHistory();
    // Lấy chi tiết một hóa đơn theo ID
    Invoice getInvoiceDetail(int id);
};
