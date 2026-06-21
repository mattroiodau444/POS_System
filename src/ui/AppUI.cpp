// AppUI.cpp - Giao dien nguoi dung console (Presentation Layer)

#include "ui/AppUI.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

// === CONSTRUCTOR ===

AppUI::AppUI(AuthService& authService, ProductService& productService,
             InvoiceService& invoiceService, DatabaseManager& dbManager)
    : authService(authService), productService(productService),
      invoiceService(invoiceService), dbManager(dbManager) {}

// === TIEN ICH HIEN THI ===

void AppUI::printLine(char ch, int length) {
    for (int i = 0; i < length; i++) cout << ch;
    cout << endl;
}

void AppUI::printHeader(const string& title) {
    printLine('=', 60);
    int padding = (60 - (int)title.length()) / 2;
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << title << endl;
    printLine('=', 60);
}

void AppUI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void AppUI::pause() {
    cout << "\nNhấn Enter để tiếp tục...";
    cin.get();
}

// === TIEN ICH NHAP LIEU ===

// Nhap so nguyen, tra ve -1 neu nhap sai
int AppUI::getIntInput(const string& prompt) {
    cout << prompt;
    int value;
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Nhap so thuc, tra ve -1.0 neu nhap sai
double AppUI::getDoubleInput(const string& prompt) {
    cout << prompt;
    double value;
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1.0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Nhap chuoi (doc ca dong)
string AppUI::getStringInput(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

// === HAM CHAY CHINH ===

void AppUI::run() {
    bool running = true;
    while (running) {
        clearScreen();
        showLoginScreen();

        if (authService.isLoggedIn()) {
            if (authService.isAdmin())
                showAdminMenu();
            else
                showStaffMenu();
            authService.logout();
        } else {
            running = false;
        }
    }
    clearScreen();
    printHeader("CẢM ƠN BẠN ĐÃ SỬ DỤNG HỆ THỐNG POS");
    cout << endl;
}

// === DANG NHAP ===

void AppUI::showLoginScreen() {
    while (true) {
        clearScreen();
        printHeader("ĐĂNG NHẬP HỆ THỐNG");
        cout << endl;
        cout << "  Nhập '0' vào tên đăng nhập để thoát." << endl << endl;

        string username = getStringInput("  Tên đăng nhập: ");
        if (username == "0") return;

        string password = getStringInput("  Mật khẩu: ");

        if (authService.login(username, password)) {
            cout << "\n  >> Đăng nhập thành công! Xin chào, "
                 << authService.getCurrentUser().getFullName() << "!" << endl;
            cout << "  >> Vai trò: " << (authService.isAdmin() ? "Quản trị viên" : "Nhân viên") << endl;
            pause();
            return;
        } else {
            cout << "\n  >> [LỖI]: Sai tên đăng nhập hoac mật khẩu!" << endl;
            cout << "\n  1. Thu lại\n  0. Thoát" << endl;
            if (getIntInput("  Lựa chọn: ") == 0) return;
        }
    }
}

// === MENU QUAN TRI VIEN ===

void AppUI::showAdminMenu() {
    while (true) {
        clearScreen();
        printHeader("MENU QUẢN TRỊ VIÊN");
        cout << "  Xin chào, " << authService.getCurrentUser().getFullName() << "!" << endl;
        cout << endl;
        cout << "  1. Quản lý sản phẩm" << endl;
        cout << "  2. Tìm kiếm sản phẩm" << endl;
        cout << "  3. Sắp xếp sản phẩm theo giá" << endl;
        cout << "  4. Bán hàng (POS)" << endl;
        cout << "  5. Lịch sử hóa đơn" << endl;
        cout << "  6. Quản lý tồn kho" << endl;
        cout << "  7. Backup cơ sở dữ liệu" << endl;
        cout << "  0. Đăng xuất" << endl;
        printLine('-', 60);

        switch (getIntInput("  Lựa chọn: ")) {
            case 1: showProductManagement(); break;
            case 2: showSearchProduct(); break;
            case 3: showSortProducts(); break;
            case 4: showSalesMenu(); break;
            case 5: showInvoiceHistory(); break;
            case 6: showInventoryManagement(); break;
            case 7: showBackupDatabase(); break;
            case 0: return;
            default:
                cout << "  >> Lựa chọn không hợp lệ!" << endl;
                pause();
        }
    }
}

// === MENU NHAN VIEN ===

void AppUI::showStaffMenu() {
    while (true) {
        clearScreen();
        printHeader("MENU NHÂN VIÊN");
        cout << "  Xin chào, " << authService.getCurrentUser().getFullName() << "!" << endl;
        cout << endl;
        cout << "  1. Xem danh sách sản phẩm" << endl;
        cout << "  2. Tìm kiếm sản phẩm" << endl;
        cout << "  3. Sắp xếp sản phẩm theo giá" << endl;
        cout << "  4. Bán hàng (POS)" << endl;
        cout << "  5. Lịch sử hóa đơn" << endl;
        cout << "  0. Đăng xuất" << endl;
        printLine('-', 60);

        switch (getIntInput("  Lựa chọn: ")) {
            case 1: showProductList(); pause(); break;
            case 2: showSearchProduct(); break;
            case 3: showSortProducts(); break;
            case 4: showSalesMenu(); break;
            case 5: showInvoiceHistory(); break;
            case 0: return;
            default:
                cout << "  >> Lựa chọn không hợp lệ!" << endl;
                pause();
        }
    }
}

// === QUAN LY SAN PHAM ===

void AppUI::showProductManagement() {
    while (true) {
        clearScreen();
        printHeader("QUẢN LÝ SẢN PHẨM");
        cout << endl;
        cout << "  1. Thêm sản phẩm" << endl;
        cout << "  2. Sửa sản phẩm" << endl;
        cout << "  3. Xóa sản phẩm" << endl;
        cout << "  4. Xem danh sách sản phẩm" << endl;
        cout << "  0. Quay lại" << endl;
        printLine('-', 60);

        switch (getIntInput("  Lựa chọn: ")) {
            case 1: showAddProduct(); break;
            case 2: showEditProduct(); break;
            case 3: showDeleteProduct(); break;
            case 4: showProductList(); pause(); break;
            case 0: return;
            default:
                cout << "  >> Lựa chọn không hợp lệ!" << endl;
                pause();
        }
    }
}

void AppUI::showAddProduct() {
    clearScreen();
    printHeader("THÊM SẢN PHẨM MỚI");
    cout << endl;

    string code = getStringInput("  Mã sản phẩm (nhập '0' để hủy): ");
    if (code == "0") return;
    
    string name     = getStringInput("  Tên sản phẩm: ");
    double price    = getDoubleInput("  Giá bán: ");
    int stock       = getIntInput("  Số lượng tồn kho: ");
    string category = getStringInput("  Danh mục: ");

    if (!productService.validateProduct(code, name, price, stock)) {
        cout << "\n  >> [LỖI]: Dữ liệu không hợp lệ!" << endl;
        cout << "     - Mã và tên không được rỗng" << endl;
        cout << "     - Giá > 0, tồn kho >= 0" << endl;
        pause();
        return;
    }

    if (productService.addProduct(code, name, price, stock, category))
        cout << "\n  >> Thêm sản phẩm thành công!" << endl;
    else
        cout << "\n  >> [LỖI]: Mã sản phẩm có thể đã tồn tại!" << endl;
    pause();
}

void AppUI::showEditProduct() {
    clearScreen();
    printHeader("SỬA THÔNG TIN SẢN PHẨM");
    cout << endl;
    showProductList();

    cout << endl;
    int id = getIntInput("  Nhập ID sản phẩm cần sửa (0 để hủy): ");
    if (id <= 0) return;

    // Tim san pham theo ID
    vector<Product> products = productService.getAllProducts();
    Product found;
    bool exists = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            found = products[i];
            exists = true;
            break;
        }
    }

    if (!exists) {
        cout << "  >> [LỖI]: Không tìm thấy ID = " << id << endl;
        pause();
        return;
    }

    // Hien thi thong tin hien tai
    cout << endl;
    printLine('-', 60);
    cout << "  Thông tin hiện tại:" << endl;
    cout << "  Mã SP   : " << found.getCode() << endl;
    cout << "  Tên SP   : " << found.getName() << endl;
    cout << "  Giá      : " << fixed << setprecision(0) << found.getPrice() << " VND" << endl;
    cout << "  Tồn kho  : " << found.getStock() << endl;
    cout << "  Danh mục : " << found.getCategory() << endl;
    printLine('-', 60);
    cout << "  (Nhập rỗng = giữ nguyên chuỗi, 0/am = giữ nguyên số)" << endl << endl;

    string newCode     = getStringInput("  Mã SP mới: ");
    string newName     = getStringInput("  Tên SP mới: ");
    double newPrice    = getDoubleInput("  Giá mới: ");
    int newStock       = getIntInput("  Tồn kho mới: ");
    string newCategory = getStringInput("  Danh mục mới: ");

    // Giu nguyen gia tri cu neu nguoi dung khong nhap
    if (newCode.empty()) newCode = found.getCode();
    if (newName.empty()) newName = found.getName();
    if (newPrice <= 0) newPrice = found.getPrice();
    if (newStock < 0) newStock = found.getStock();
    if (newCategory.empty()) newCategory = found.getCategory();

    Product updated(id, newCode, newName, newPrice, newStock, newCategory);

    if (productService.updateProduct(updated))
        cout << "\n  >> Cập nhật thành công!" << endl;
    else
        cout << "\n  >> [LỖI]: Không thể cập nhật!" << endl;
    pause();
}

void AppUI::showDeleteProduct() {
    clearScreen();
    printHeader("XÓA SẢN PHẨM");
    cout << endl;
    showProductList();

    cout << endl;
    int id = getIntInput("  Nhập ID sản phẩm cần xóa (0 để hủy): ");
    if (id <= 0) return;

    string confirm = getStringInput("  Xác nhận xóa? (y/n): ");
    if (confirm == "y" || confirm == "Y") {
        if (productService.deleteProduct(id))
            cout << "\n  >> Xóa thành công!" << endl;
        else
            cout << "\n  >> [LỖI]: ID không tồn tại!" << endl;
    } else {
        cout << "  >> Đã hủy." << endl;
    }
    pause();
}

// === HIEN THI DANH SACH SAN PHAM ===

void AppUI::showProductList() {
    vector<Product> products = productService.getAllProducts();

    cout << endl;
    printHeader("DANH SÁCH SẢN PHẨM");

    if (products.empty()) {
        cout << "  >> Không có sản phẩm nào." << endl;
        return;
    }

    cout << left
         << setw(6)  << "  ID"
         << setw(12) << "Mã SP"
         << setw(25) << "Tên SP"
         << right
         << setw(12) << "Giá"
         << setw(10) << "Tồn Kho"
         << "  "
         << left
         << setw(15) << "Danh mục"
         << endl;
    printLine('-', 82);

    for (size_t i = 0; i < products.size(); i++) {
        cout << left
             << "  " << setw(4)  << products[i].getId()
             << setw(12) << products[i].getCode()
             << setw(25) << products[i].getName()
             << right
             << setw(12) << fixed << setprecision(0) << products[i].getPrice()
             << setw(10) << products[i].getStock()
             << "  "
             << left
             << setw(15) << products[i].getCategory()
             << endl;
    }

    printLine('-', 82);
    cout << "  Tổng cộng: " << products.size() << " sản phẩm" << endl;
}

// === TIM KIEM (Binary Search) ===

void AppUI::showSearchProduct() {
    clearScreen();
    printHeader("TÌM KIẾM SẢN PHẨM");
    cout << endl;

    string code = getStringInput("  Nhập mã sản phẩm (nhập '0' để hủy): ");
    if (code == "0") return;

    if (code.empty()) {
        cout << "  >> Mã sản phẩm không được rỗng!" << endl;
        pause();
        return;
    }

    // Sap xep theo ma de dung Binary Search
    vector<Product> products = productService.getAllProducts();
    sort(products.begin(), products.end(),
         [](const Product& a, const Product& b) {
             return a.getCode() < b.getCode();
         });

    int index = productService.binarySearchByCode(products, code);

    if (index >= 0) {
        const Product& p = products[index];
        cout << endl;
        printLine('-', 60);
        cout << "  >> Tìm thấy!" << endl;
        printLine('-', 60);
        cout << "  ID       : " << p.getId() << endl;
        cout << "  Mã SP    : " << p.getCode() << endl;
        cout << "  Tên SP   : " << p.getName() << endl;
        cout << "  Giá      : " << fixed << setprecision(0) << p.getPrice() << " VND" << endl;
        cout << "  Tồn kho  : " << p.getStock() << endl;
        cout << "  Danh mục : " << p.getCategory() << endl;
        printLine('-', 60);
    } else {
        cout << "\n  >> Không tìm thấy mã: " << code << endl;
    }
    pause();
}

// === SAP XEP (Bubble Sort) ===

void AppUI::showSortProducts() {
    clearScreen();
    printHeader("SẮP XẾP SẢN PHẨM THEO GIÁ");

    vector<Product> products = productService.getAllProducts();
    if (products.empty()) {
        cout << "\n  >> Không có sản phẩm nào." << endl;
        pause();
        return;
    }

    productService.sortByPrice(products);

    cout << "\n  Đã sắp xếp theo giá tăng dần:\n" << endl;

    cout << left
         << setw(6)  << "  ID"
         << setw(12) << "Mã SP"
         << setw(25) << "Tên SP"
         << right
         << setw(12) << "Giá"
         << setw(10) << "Tồn Kho"
         << "  "
         << left
         << setw(15) << "Danh mục"
         << endl;
    printLine('-', 82);

    for (size_t i = 0; i < products.size(); i++) {
        cout << left
             << "  " << setw(4)  << products[i].getId()
             << setw(12) << products[i].getCode()
             << setw(25) << products[i].getName()
             << right
             << setw(12) << fixed << setprecision(0) << products[i].getPrice()
             << setw(10) << products[i].getStock()
             << "  "
             << left
             << setw(15) << products[i].getCategory()
             << endl;
    }

    printLine('-', 82);
    cout << "  Tổng cộng: " << products.size() << " sản phẩm" << endl;
    pause();
}

// === BAN HANG (POS) ===

void AppUI::showSalesMenu() {
    while (true) {
        clearScreen();
        printHeader("BÁN HÀNG (POS)");

        int cartSize = (int)invoiceService.getCart().size();
        cout << "  Giỏ hàng: " << cartSize << " sản phẩm" << endl;
        cout << endl;
        cout << "  1. Thêm sản phẩm vào giỏ" << endl;
        cout << "  2. Xem giỏ hàng" << endl;
        cout << "  3. Thanh toán" << endl;
        cout << "  4. Hủy đơn hàng" << endl;
        cout << "  0. Quay lại" << endl;
        printLine('-', 60);

        switch (getIntInput("  Lựa chọn: ")) {
            case 1: showAddToCart(); break;
            case 2: showViewCart(); break;
            case 3: showCheckout(); break;
            case 4: {
                string confirm = getStringInput("  Xác nhận hủy đơn? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    invoiceService.cancelOrder();
                    cout << "  >> Đã hủy đơn hàng!" << endl;
                }
                pause();
                break;
            }
            case 0: return;
            default:
                cout << "  >> Lựa chọn không hợp lệ!" << endl;
                pause();
        }
    }
}

void AppUI::showAddToCart() {
    clearScreen();
    printHeader("THÊM SẢN PHẨM VÀO GIỎ");
    cout << endl;

    vector<Product> products = productService.getAllProducts();
    if (products.empty()) {
        cout << "  >> Không có sản phẩm nào!" << endl;
        pause();
        return;
    }

    // Hien thi danh sach co STT
    cout << left
         << setw(6)  << "  STT"
         << setw(12) << "Mã SP"
         << setw(30) << "Tên Sản Phẩm"
         << right
         << setw(12) << "Giá Bán"
         << setw(10) << "Tồn Kho"
         << endl;
    printLine('-', 75);

    for (size_t i = 0; i < products.size(); i++) {
        cout << left
             << "  " << setw(4) << (i + 1)
             << setw(12) << products[i].getCode()
             << setw(30) << products[i].getName()
             << right
             << setw(12) << fixed << setprecision(0) << products[i].getPrice()
             << setw(10) << products[i].getStock()
             << endl;
    }
    printLine('-', 75);

    int stt = getIntInput("  Nhập STT (0 để hủy): ");
    if (stt <= 0 || stt > (int)products.size()) {
        cout << "  >> STT không hợp lệ!" << endl;
        pause();
        return;
    }

    Product product = products[stt - 1];

    // Hien thi san pham da chon
    cout << endl;
    printLine('-', 60);
    cout << "  Sản phẩm: " << product.getName() << endl;
    cout << "  Giá     : " << fixed << setprecision(0) << product.getPrice() << " VND" << endl;
    cout << "  Tồn kho : " << product.getStock() << endl;
    printLine('-', 60);

    if (product.getStock() <= 0) {
        cout << "  >> Sản phẩm đã hết hàng!" << endl;
        pause();
        return;
    }

    int quantity = getIntInput("  Nhập số lượng: ");
    if (quantity <= 0) {
        cout << "  >> Số lượng phải > 0!" << endl;
        pause();
        return;
    }
    if (quantity > product.getStock()) {
        cout << "  >> Vượt quá tồn kho! (Còn: " << product.getStock() << ")" << endl;
        pause();
        return;
    }

    if (invoiceService.addToCart(product, quantity))
        cout << "\n  >> Đã thêm " << quantity << " x " << product.getName() << " vào giỏ!" << endl;
    else
        cout << "\n  >> [LỖI]: Không thể thêm vào giỏ!" << endl;
    pause();
}

void AppUI::showViewCart() {
    clearScreen();
    printHeader("GIỎ HÀNG HIỆN TẠI");

    const vector<CartItem>& cart = invoiceService.getCart();
    if (cart.empty()) {
        cout << "\n  >> Giỏ hàng đang trống!" << endl;
        pause();
        return;
    }

    cout << endl;
    cout << left
         << setw(6)  << "  STT"
         << setw(12) << "Mã SP"
         << setw(30) << "Tên Sản Phẩm"
         << right
         << setw(12) << "Giá Bán"
         << setw(6)  << "SL"
         << setw(14) << "Thành Tiền"
         << endl;
    printLine('-', 80);

    double total = 0;
    for (size_t i = 0; i < cart.size(); i++) {
        double subtotal = cart[i].getSubtotal();
        total += subtotal;
        cout << left
             << "  " << setw(4) << (i + 1)
             << setw(12) << cart[i].getProduct().getCode()
             << setw(30) << cart[i].getProduct().getName()
             << right
             << setw(12) << fixed << setprecision(0) << cart[i].getProduct().getPrice()
             << setw(6)  << cart[i].getQuantity()
             << setw(14) << fixed << setprecision(0) << subtotal
             << endl;
    }

    printLine('-', 80);
    cout << right << setw(64) << "TỔNG CỘNG: "
         << setw(14) << fixed << setprecision(0) << total << " VND" << endl;
    printLine('=', 80);

    cout << endl;
    int removeStt = getIntInput("  Nhập STT để xóa (0 để bỏ qua): ");
    if (removeStt > 0 && removeStt <= (int)cart.size()) {
        if (invoiceService.removeFromCart(removeStt - 1))
            cout << "  >> Đã xóa khỏi giỏ!" << endl;
        else
            cout << "  >> [LỖI]: Không thể xóa!" << endl;
    } else if (removeStt != 0) {
        cout << "  >> STT không hợp lệ!" << endl;
    }
    pause();
}

void AppUI::showCheckout() {
    clearScreen();
    printHeader("THANH TOÁN");

    const vector<CartItem>& cart = invoiceService.getCart();
    if (cart.empty()) {
        cout << "\n  >> Giỏ hàng trống! Không thể thanh toán." << endl;
        pause();
        return;
    }

    // Hien thi tom tat don hang
    cout << "\n  --- TÓM TẮT ĐƠN HÀNG ---\n" << endl;
    cout << left
         << setw(6)  << "  STT"
         << setw(12) << "Mã SP"
         << setw(22) << "Tên SP"
         << right
         << setw(12) << "Giá"
         << setw(6)  << "SL"
         << setw(14) << "Thành Tiền"
         << endl;
    printLine('-', 72);

    double total = 0;
    for (size_t i = 0; i < cart.size(); i++) {
        double subtotal = cart[i].getSubtotal();
        total += subtotal;
        cout << left
             << "  " << setw(4)  << (i + 1)
             << setw(12) << cart[i].getProduct().getCode()
             << setw(22) << cart[i].getProduct().getName()
             << right
             << setw(12) << fixed << setprecision(0) << cart[i].getProduct().getPrice()
             << setw(6)  << cart[i].getQuantity()
             << setw(14) << fixed << setprecision(0) << subtotal
             << endl;
    }

    printLine('-', 72);
    cout << right << setw(58) << "TỔNG CỘNG: "
         << setw(14) << fixed << setprecision(0) << total << " VND" << endl;
    printLine('=', 72);

    cout << endl;
    string confirm = getStringInput("  Xác nhận thanh toán? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << "  >> Đã hủy thanh toán." << endl;
        pause();
        return;
    }

    int invoiceId = invoiceService.checkout(
        authService.getCurrentUser().getId(),
        authService.getCurrentUser().getFullName()
    );

    if (invoiceId > 0) {
        cout << "\n  >> Thanh toán thành công!\n" << endl;
        Invoice invoice = invoiceService.getInvoiceDetail(invoiceId);
        printInvoice(invoice);
    } else {
        cout << "\n  >> [LỖI]: Thanh toán thất bại!" << endl;
    }
    pause();
}

// === LICH SU HOA DON ===

void AppUI::showInvoiceHistory() {
    clearScreen();
    printHeader("LỊCH SỬ HOÁ ĐƠN");

    vector<Invoice> invoices = invoiceService.getInvoiceHistory();
    if (invoices.empty()) {
        cout << "\n  >> Chưa có hóa đơn nào." << endl;
        pause();
        return;
    }

    cout << endl;
    cout << left
         << setw(6)  << "  ID"
         << setw(12) << "Mã HD"
         << setw(20) << "Nhân viên"
         << setw(22) << "Ngày giờ"
         << right
         << setw(14) << "Tổng tiền"
         << endl;
    printLine('-', 74);

    for (size_t i = 0; i < invoices.size(); i++) {
        cout << left
             << "  " << setw(4)  << invoices[i].getId()
             << setw(12) << invoices[i].getInvoiceCode()
             << setw(20) << invoices[i].getCashierName()
             << setw(22) << invoices[i].getDateTime()
             << right
             << setw(14) << fixed << setprecision(0) << invoices[i].getTotalAmount()
             << endl;
    }

    printLine('-', 74);
    cout << "  Tổng cộng: " << invoices.size() << " hóa đơn" << endl;

    cout << endl;
    int id = getIntInput("  Nhập ID để xem chi tiết (0 để bỏ qua): ");
    if (id > 0) {
        Invoice invoice = invoiceService.getInvoiceDetail(id);
        if (invoice.getId() > 0) {
            cout << endl;
            printInvoice(invoice);
        } else {
            cout << "  >> Không tìm thấy ID = " << id << endl;
        }
        pause();
    }
}

void AppUI::showInvoiceDetail() {
    clearScreen();
    printHeader("CHI TIẾT HOÁ ĐƠN");
    cout << endl;

    int id = getIntInput("  Nhập ID hóa đơn: ");
    if (id <= 0) {
        cout << "  >> ID không hợp lệ!" << endl;
        pause();
        return;
    }

    Invoice invoice = invoiceService.getInvoiceDetail(id);
    if (invoice.getId() > 0) {
        cout << endl;
        printInvoice(invoice);
    } else {
        cout << "  >> Không tìm thấy ID = " << id << endl;
    }
    pause();
}

// === QUAN LY TON KHO ===

void AppUI::showInventoryManagement() {
    clearScreen();
    printHeader("QUẢN LÝ TỒN KHO");

    vector<Product> products = productService.getAllProducts();
    if (products.empty()) {
        cout << "\n  >> Không có sản phẩm nào." << endl;
        pause();
        return;
    }

    cout << endl;
    cout << left
         << setw(6)  << "  ID"
         << setw(12) << "Mã SP"
         << setw(25) << "Tên SP"
         << right
         << setw(10) << "Tồn Kho"
         << "  "
         << left
         << setw(15) << "Trạng Thái"
         << endl;
    printLine('-', 70);

    for (size_t i = 0; i < products.size(); i++) {
        string status = (products[i].getStock() < 10) ? "CẦN NHẬP THÊM" : "Đủ hàng";

        cout << left
             << "  " << setw(4)  << products[i].getId()
             << setw(12) << products[i].getCode()
             << setw(25) << products[i].getName()
             << right
             << setw(10) << products[i].getStock()
             << "  "
             << left
             << setw(15) << status
             << endl;
    }

    printLine('-', 70);

    cout << endl;
    int id = getIntInput("  Nhập ID để cập nhật tồn kho (0 để bỏ qua): ");
    if (id <= 0) return;

    // Tim san pham
    Product found;
    bool exists = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            found = products[i];
            exists = true;
            break;
        }
    }

    if (!exists) {
        cout << "  >> [LỖI]: Không tìm thấy ID = " << id << endl;
        pause();
        return;
    }

    cout << "  " << found.getName() << " (Hiện tại: " << found.getStock() << ")" << endl;
    int newStock = getIntInput("  Tồn kho mới: ");

    if (newStock < 0) {
        cout << "  >> [LỖI]: Tồn kho phải >= 0!" << endl;
        pause();
        return;
    }

    Product updated(found.getId(), found.getCode(), found.getName(),
                    found.getPrice(), newStock, found.getCategory());

    if (productService.updateProduct(updated))
        cout << "\n  >> Cập nhật: " << found.getName()
             << " (" << found.getStock() << " -> " << newStock << ")" << endl;
    else
        cout << "\n  >> [LỖI]: Không thể cập nhật!" << endl;
    pause();
}

// === BACKUP ===

void AppUI::showBackupDatabase() {
    clearScreen();
    printHeader("SAO LƯU CƠ SỞ DỮ LIỆU");
    cout << endl;

    // Sinh ten file voi timestamp
    time_t now = time(0);
    struct tm* t = localtime(&now);
    char ts[20];
    strftime(ts, sizeof(ts), "%Y%m%d_%H%M%S", t);

    string backupPath = "backup/pos_backup_" + string(ts) + ".db";

    cout << "  Đang sao lưu..." << endl;
    cout << "  File: " << backupPath << endl << endl;

    if (dbManager.backupDatabase(backupPath)) {
        cout << "  >> Sao lưu thành công!" << endl;
        cout << "  >> " << backupPath << endl;
    } else {
        cout << "  >> [LỖI]: Sao lưu thất bại!" << endl;
    }
    pause();
}

// === IN HOA DON ===

void AppUI::printInvoice(const Invoice& invoice) {
    cout << endl;
    cout << "  ============ HÓA ĐƠN BÁN HÀNG ============" << endl;
    cout << "  Mã HD     : " << invoice.getInvoiceCode() << endl;
    cout << "  Nhân viên : " << invoice.getCashierName() << endl;
    cout << "  Ngày      : " << invoice.getDateTime() << endl;
    cout << "  ===========================================" << endl;

    cout << "  " << left
         << setw(5)  << "STT"
         << setw(10) << "Mã SP"
         << setw(18) << "Tên SP"
         << right
         << setw(10) << "Giá"
         << setw(5)  << "SL"
         << setw(12) << "Thành tiền"
         << endl;
    cout << "  -------------------------------------------" << endl;

    const vector<CartItem>& items = invoice.getItems();
    for (size_t i = 0; i < items.size(); i++) {
        cout << "  " << left
             << setw(5)  << (i + 1)
             << setw(10) << items[i].getProduct().getCode()
             << setw(18) << items[i].getProduct().getName()
             << right
             << setw(10) << fixed << setprecision(0) << items[i].getProduct().getPrice()
             << setw(5)  << items[i].getQuantity()
             << setw(12) << fixed << setprecision(0) << items[i].getSubtotal()
             << endl;
    }

    cout << "  ===========================================" << endl;
    cout << "  TỔNG CỘNG: " << right << setw(28) << fixed << setprecision(0)
         << invoice.getTotalAmount() << " VND" << endl;
    cout << "  ===========================================" << endl;
    cout << endl;
}
