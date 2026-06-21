// InvoiceService.cpp - Quản lý giỏ hàng, thanh toán, hóa đơn

#include "services/InvoiceService.h"
#include <ctime>

using namespace std;

InvoiceService::InvoiceService(InvoiceDAO& invoiceDAO, ProductDAO& productDAO)
    : invoiceDAO(invoiceDAO), productDAO(productDAO) {}

// Thêm sản phẩm vào giỏ; nếu đã có thì cộng dồn số lượng
bool InvoiceService::addToCart(const Product& product, int quantity) {
    if (quantity <= 0 || product.getStock() < quantity)
        return false;

    // Tìm sản phẩm đã có trong giỏ theo mã
    for (int i = 0; i < (int)cart.size(); i++) {
        if (cart[i].getProduct().getCode() == product.getCode()) {
            cart[i].setQuantity(cart[i].getQuantity() + quantity);
            return true;
        }
    }

    cart.push_back(CartItem(product, quantity));
    return true;
}

bool InvoiceService::removeFromCart(int index) {
    if (index < 0 || index >= (int)cart.size()) return false;
    cart.erase(cart.begin() + index);
    return true;
}

void InvoiceService::clearCart() { cart.clear(); }

const vector<CartItem>& InvoiceService::getCart() const { return cart; }

double InvoiceService::getCartTotal() const {
    double total = 0;
    for (int i = 0; i < (int)cart.size(); i++)
        total += cart[i].getSubtotal();
    return total;
}

// Thanh toán: kiểm tra tồn kho -> trừ kho -> tạo hóa đơn -> xóa giỏ
// Input:  userId      - ID nhân viên bán hàng
//         cashierName - tên nhân viên
// Output: ID hóa đơn nếu thành công, -1 nếu thất bại
int InvoiceService::checkout(int userId, const string& cashierName) {
    if (cart.empty()) return -1;

    // Kiểm tra tồn kho mới nhất cho từng sản phẩm
    for (int i = 0; i < (int)cart.size(); i++) {
        Product fresh = productDAO.findByCode(cart[i].getProduct().getCode());
        if (fresh.getStock() < cart[i].getQuantity())
            return -1;  // Không đủ tồn kho
    }

    // Trừ tồn kho
    for (int i = 0; i < (int)cart.size(); i++) {
        Product fresh = productDAO.findByCode(cart[i].getProduct().getCode());
        productDAO.updateStock(fresh.getId(), fresh.getStock() - cart[i].getQuantity());
    }

    // Sinh mã hóa đơn và lấy ngày giờ hiện tại
    string invoiceCode = invoiceDAO.generateInvoiceCode();

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", t);

    // Tạo và lưu hóa đơn
    Invoice invoice(0, invoiceCode, userId, cashierName, string(buf), getCartTotal());
    int invoiceId = invoiceDAO.createInvoice(invoice);
    if (invoiceId == -1) return -1;

    // Lưu chi tiết từng mặt hàng
    for (int i = 0; i < (int)cart.size(); i++)
        invoiceDAO.addInvoiceItem(invoiceId, cart[i]);

    cart.clear();
    return invoiceId;
}

void InvoiceService::cancelOrder() { clearCart(); }

vector<Invoice> InvoiceService::getInvoiceHistory() {
    return invoiceDAO.getAllInvoices();
}

Invoice InvoiceService::getInvoiceDetail(int id) {
    return invoiceDAO.getInvoiceById(id);
}
