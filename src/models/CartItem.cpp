// CartItem.cpp - Mục trong giỏ hàng

#include "models/CartItem.h"

CartItem::CartItem() : product(), quantity(0) {}

CartItem::CartItem(const Product& product, int quantity)
    : product(product), quantity(quantity) {}

const Product& CartItem::getProduct() const { return product; }
int CartItem::getQuantity() const { return quantity; }
void CartItem::setQuantity(int quantity) { this->quantity = quantity; }

// Thành tiền = đơn giá * số lượng
double CartItem::getSubtotal() const {
    return product.getPrice() * quantity;
}
