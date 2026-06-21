// InvoiceDAO.cpp - Truy xuất dữ liệu bảng invoices và invoice_items

#include "dao/InvoiceDAO.h"
#include "sqlite3.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

InvoiceDAO::InvoiceDAO(DatabaseManager& dbManager) : dbManager(dbManager) {}

// Tạo hóa đơn, trả về ID mới (-1 nếu lỗi)
int InvoiceDAO::createInvoice(const Invoice& invoice) {
    sqlite3_stmt* stmt = nullptr;
    int invoiceId = -1;
    const char* sql =
        "INSERT INTO invoices(invoice_code,user_id,cashier_name,date_time,total_amount) "
        "VALUES(?,?,?,?,?);";

    if (sqlite3_prepare_v2(dbManager.getDB(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, invoice.getInvoiceCode().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, invoice.getUserId());
        sqlite3_bind_text(stmt, 3, invoice.getCashierName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, invoice.getDateTime().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 5, invoice.getTotalAmount());

        if (sqlite3_step(stmt) == SQLITE_DONE)
            invoiceId = (int)sqlite3_last_insert_rowid(dbManager.getDB());
        else
            cerr << "[LỖI] Tạo hóa đơn: " << sqlite3_errmsg(dbManager.getDB()) << endl;
    }
    sqlite3_finalize(stmt);
    return invoiceId;
}

bool InvoiceDAO::addInvoiceItem(int invoiceId, const CartItem& item) {
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;
    const char* sql =
        "INSERT INTO invoice_items(invoice_id,product_code,product_name,price,quantity,subtotal) "
        "VALUES(?,?,?,?,?,?);";

    if (sqlite3_prepare_v2(dbManager.getDB(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, invoiceId);
        sqlite3_bind_text(stmt, 2, item.getProduct().getCode().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, item.getProduct().getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 4, item.getProduct().getPrice());
        sqlite3_bind_int(stmt, 5, item.getQuantity());
        sqlite3_bind_double(stmt, 6, item.getSubtotal());
        ok = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!ok) cerr << "[LỖI] Thêm chi tiết hóa đơn: " << sqlite3_errmsg(dbManager.getDB()) << endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

vector<Invoice> InvoiceDAO::getAllInvoices() {
    vector<Invoice> invoices;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM invoices ORDER BY id DESC;", -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* code = (const char*)sqlite3_column_text(stmt, 1);
            const char* name = (const char*)sqlite3_column_text(stmt, 3);
            const char* dt   = (const char*)sqlite3_column_text(stmt, 4);
            invoices.push_back(Invoice(
                sqlite3_column_int(stmt, 0), code ? code : "",
                sqlite3_column_int(stmt, 2), name ? name : "",
                dt ? dt : "", sqlite3_column_double(stmt, 5)));
        }
    }
    sqlite3_finalize(stmt);
    return invoices;
}

Invoice InvoiceDAO::getInvoiceById(int id) {
    Invoice invoice;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM invoices WHERE id=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* code = (const char*)sqlite3_column_text(stmt, 1);
            const char* name = (const char*)sqlite3_column_text(stmt, 3);
            const char* dt   = (const char*)sqlite3_column_text(stmt, 4);
            invoice = Invoice(
                sqlite3_column_int(stmt, 0), code ? code : "",
                sqlite3_column_int(stmt, 2), name ? name : "",
                dt ? dt : "", sqlite3_column_double(stmt, 5));
            invoice.setItems(getInvoiceItems(invoice.getId()));
        }
    }
    sqlite3_finalize(stmt);
    return invoice;
}

vector<CartItem> InvoiceDAO::getInvoiceItems(int invoiceId) {
    vector<CartItem> items;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT * FROM invoice_items WHERE invoice_id=?;", -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, invoiceId);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* pcode = (const char*)sqlite3_column_text(stmt, 2);
            const char* pname = (const char*)sqlite3_column_text(stmt, 3);
            // Tạo Product tạm (stock=0, category rỗng vì không cần trong hóa đơn)
            Product p(0, pcode ? pcode : "", pname ? pname : "",
                      sqlite3_column_double(stmt, 4), 0, "");
            items.push_back(CartItem(p, sqlite3_column_int(stmt, 5)));
        }
    }
    sqlite3_finalize(stmt);
    return items;
}

// Sinh mã hóa đơn: HD0001, HD0002, ...
string InvoiceDAO::generateInvoiceCode() {
    sqlite3_stmt* stmt = nullptr;
    int count = 0;

    if (sqlite3_prepare_v2(dbManager.getDB(), "SELECT COUNT(*) FROM invoices;", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW)
            count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    stringstream ss;
    ss << "HD" << setfill('0') << setw(4) << (count + 1);
    return ss.str();
}
