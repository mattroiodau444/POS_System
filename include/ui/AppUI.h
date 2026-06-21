/*
 =============================================================
 File: AppUI.h
 Mô tả: Khai báo lớp AppUI - Giao diện người dùng console
 Điều phối toàn bộ luồng tương tác với người dùng
 =============================================================
 */

#pragma once

#include <string>
#include "../models/Invoice.h"
#include "../services/AuthService.h"
#include "../services/ProductService.h"
#include "../services/InvoiceService.h"
#include "../dao/DatabaseManager.h"

/*
 Lớp AppUI - Giao diện người dùng dạng console
 Điều phối toàn bộ luồng tương tác với người dùng
 */
class AppUI {
private:
    AuthService& authService;
    ProductService& productService;
    InvoiceService& invoiceService;
    DatabaseManager& dbManager;

    // --- Màn hình đăng nhập ---
    void showLoginScreen();

    // --- Menu chính theo vai trò ---
    void showAdminMenu();
    void showStaffMenu();

    // --- Quản lý sản phẩm (chỉ Admin) ---
    void showProductManagement();
    void showAddProduct();
    void showEditProduct();
    void showDeleteProduct();

    // --- Hiển thị, tìm kiếm, sắp xếp sản phẩm (Admin + Staff) ---
    void showProductList();
    void showSearchProduct();
    void showSortProducts();

    // --- Bán hàng (Admin + Staff) ---
    void showSalesMenu();
    void showAddToCart();
    void showViewCart();
    void showCheckout();

    // --- Hóa đơn ---
    void showInvoiceHistory();
    void showInvoiceDetail();

    // --- Tồn kho (chỉ Admin) ---
    void showInventoryManagement();

    // --- Backup (chỉ Admin) ---
    void showBackupDatabase();

    // --- Tiện ích hiển thị ---
    void printInvoice(const Invoice& invoice);
    void printLine(char ch = '=', int length = 60);
    void printHeader(const std::string& title);
    void clearScreen();
    void pause();

    // --- Tiện ích nhập liệu có validate ---
    int getIntInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);

public:
    // Constructor - Dependency Injection
    AppUI(AuthService& authService, ProductService& productService,
          InvoiceService& invoiceService, DatabaseManager& dbManager);

    // Khởi chạy ứng dụng
    void run();
};
