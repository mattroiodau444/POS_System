// Invoice.cpp - Lớp hóa đơn bán hàng

#include "models/Invoice.h"

using namespace std;

// Constructor mặc định
Invoice::Invoice()
    : id(0), invoiceCode(""), userId(0),
      cashierName(""), dateTime(""), totalAmount(0) {}

// Constructor đầy đủ
Invoice::Invoice(int id, const string& invoiceCode, int userId,
                 const string& cashierName, const string& dateTime,
                 double totalAmount)
    : id(id), invoiceCode(invoiceCode), userId(userId),
      cashierName(cashierName), dateTime(dateTime), totalAmount(totalAmount) {}

// Getters
int Invoice::getId() const { return id; }
const string& Invoice::getInvoiceCode() const { return invoiceCode; }
int Invoice::getUserId() const { return userId; }
const string& Invoice::getCashierName() const { return cashierName; }
const string& Invoice::getDateTime() const { return dateTime; }
double Invoice::getTotalAmount() const { return totalAmount; }
const vector<CartItem>& Invoice::getItems() const { return items; }

// Setters
void Invoice::setId(int id) { this->id = id; }
void Invoice::setItems(const vector<CartItem>& items) { this->items = items; }

void Invoice::addItem(const CartItem& item) {
    items.push_back(item);
}
