// ProductService.cpp - Nghiệp vụ sản phẩm (CRUD, Bubble Sort, Binary Search)

#include "services/ProductService.h"

using namespace std;

ProductService::ProductService(ProductDAO& productDAO)
    : productDAO(productDAO) {}

// Thêm sản phẩm: validate -> kiểm tra trùng mã -> thêm vào DB
bool ProductService::addProduct(const string& code, const string& name,
                                double price, int stock, const string& category) {
    if (!validateProduct(code, name, price, stock)) return false;
    if (productDAO.isCodeExists(code)) return false;

    Product product(0, code, name, price, stock, category);
    return productDAO.addProduct(product);
}

bool ProductService::updateProduct(const Product& product) {
    if (!product.isValid()) return false;
    return productDAO.updateProduct(product);
}

bool ProductService::deleteProduct(int id) {
    return productDAO.deleteProduct(id);
}

vector<Product> ProductService::getAllProducts() {
    return productDAO.getAllProducts();
}

Product ProductService::searchByCode(const string& code) {
    return productDAO.findByCode(code);
}

// Bubble Sort: sắp xếp theo giá tăng dần, tối ưu bằng cờ swapped
// Input:  products - vector sản phẩm cần sắp xếp (tham chiếu, sửa trực tiếp)
// Output: products được sắp xếp theo giá tăng dần
void ProductService::sortByPrice(vector<Product>& products) {
    int n = products.size();  // n: tổng số phần tử

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // swapped: cờ đánh dấu có hoán đổi trong lượt này

        for (int j = 0; j < n - 1 - i; j++) {
            if (products[j].getPrice() > products[j + 1].getPrice()) {
                swap(products[j], products[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;  // Danh sách đã sắp xếp, dừng sớm
    }
}

// Binary Search: tìm sản phẩm theo mã trong danh sách đã sắp xếp
// Input:  products - vector đã sắp xếp theo mã (tăng dần)
//         code     - mã sản phẩm cần tìm
// Output: trả về index nếu tìm thấy, -1 nếu không
int ProductService::binarySearchByCode(const vector<Product>& products,
                                       const string& code) {
    int low = 0;                         // low: biên dưới
    int high = (int)products.size() - 1; // high: biên trên

    while (low <= high) {
        int mid = (low + high) / 2;      // mid: vị trí giữa

        if (products[mid].getCode() == code)
            return mid;
        else if (products[mid].getCode() < code)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Validate: mã và tên không rỗng, giá > 0, tồn kho >= 0
bool ProductService::validateProduct(const string& code, const string& name,
                                     double price, int stock) {
    return !code.empty() && !name.empty() && price > 0 && stock >= 0;
}
