// main.cpp - Điểm vào chính của chương trình POS System

#include "include/PosSystem.h"

using namespace std;

int main() {
    // Hiển thị banner khởi động
    cout << endl;
    cout << "============================================================" << endl;
    cout << "||       HE THONG QUAN LY BAN HANG - POS SYSTEM          ||" << endl;
    cout << "||    Quan ly san pham | Ban hang | Hoa don               ||" << endl;
    cout << "||    Phien ban: 1.0  |  Chuan: C++11                    ||" << endl;
    cout << "============================================================" << endl;
    cout << endl;
    cout << "  [*] Dang khoi dong he thong..." << endl;

    // Khởi tạo Database (Singleton)
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    if (!dbManager.open("data/pos_system.db")) {
        cerr << "  [LOI] Khong the mo co so du lieu!" << endl;
        return 1;
    }
    cout << "  [OK] Ket noi co so du lieu thanh cong." << endl;

    // Tạo bảng và nạp dữ liệu mẫu (nếu DB rỗng)
    dbManager.initTables();
    dbManager.seedData();
    cout << "  [OK] Khoi tao du lieu hoan tat." << endl;

    // Khởi tạo các tầng: DAO -> Service -> UI
    UserDAO userDAO(dbManager);
    ProductDAO productDAO(dbManager);
    InvoiceDAO invoiceDAO(dbManager);

    AuthService authService(userDAO);
    ProductService productService(productDAO);
    InvoiceService invoiceService(invoiceDAO, productDAO);

    AppUI appUI(authService, productService, invoiceService, dbManager);

    // Chạy giao diện chính
    cout << "  [OK] He thong san sang!" << endl << endl;
    appUI.run();

    // Đóng kết nối và kết thúc
    dbManager.close();

    cout << endl;
    cout << "============================================================" << endl;
    cout << "||           CAM ON BAN DA SU DUNG HE THONG!              ||" << endl;
    cout << "||         Hen gap lai - POS System v1.0                  ||" << endl;
    cout << "============================================================" << endl;
    cout << endl;

    return 0;
}
