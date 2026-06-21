// Product.cpp - Lớp sản phẩm

#include "models/Product.h"

using namespace std;

// Constructor mặc định
Product::Product() : id(0), code(""), name(""), price(0), stock(0), category("") {}

// Constructor đầy đủ
Product::Product(int id, const string& code, const string& name,
                 double price, int stock, const string& category)
    : id(id), code(code), name(name),
      price(price), stock(stock), category(category) {}

// Getters
int Product::getId() const { return id; }
const string& Product::getCode() const { return code; }
const string& Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
const string& Product::getCategory() const { return category; }

// Setters
void Product::setId(int id) { this->id = id; }
void Product::setCode(const string& code) { this->code = code; }
void Product::setName(const string& name) { this->name = name; }
void Product::setPrice(double price) { this->price = price; }
void Product::setStock(int stock) { this->stock = stock; }
void Product::setCategory(const string& category) { this->category = category; }

// Hợp lệ khi: mã và tên không rỗng, giá > 0, tồn kho >= 0
bool Product::isValid() const {
    return !code.empty() && !name.empty() && price > 0 && stock >= 0;
}
