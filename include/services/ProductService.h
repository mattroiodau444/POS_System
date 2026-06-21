/*
 =============================================================
 File: ProductService.h
 Mô tả: Khai báo lớp ProductService - Xử lý nghiệp vụ sản phẩm
 Bao gồm: CRUD, tìm kiếm (Binary Search), sắp xếp (Bubble Sort)
 =============================================================
 */

#pragma once

#include <vector>
#include <string>
#include "../models/Product.h"
#include "../dao/ProductDAO.h"

/*
 Lớp ProductService - Xử lý nghiệp vụ sản phẩm
 Bao gồm: CRUD, tìm kiếm (Binary Search), sắp xếp (Bubble Sort)
 */
class ProductService {
private:
    ProductDAO& productDAO;

public:
    // Constructor
    explicit ProductService(ProductDAO& productDAO);

    // Thêm sản phẩm mới
    bool addProduct(const std::string& code, const std::string& name,
                    double price, int stock, const std::string& category);
    // Cập nhật sản phẩm
    bool updateProduct(const Product& product);
    // Xóa sản phẩm theo ID
    bool deleteProduct(int id);
    // Lấy danh sách tất cả sản phẩm
    std::vector<Product> getAllProducts();
    // Tìm kiếm sản phẩm theo mã (truy vấn DB trực tiếp)
    Product searchByCode(const std::string& code);

    /**
     * Bubble Sort - Sắp xếp danh sách sản phẩm theo giá tăng dần
     * Độ phức tạp: O(n^2) trung bình và xấu nhất
     * Có tối ưu bằng cờ swapped để dừng sớm
     */
    void sortByPrice(std::vector<Product>& products);

    /**
     * Binary Search - Tìm kiếm sản phẩm theo mã trong danh sách đã sắp xếp
     * Yêu cầu: danh sách phải được sắp xếp theo mã sản phẩm trước
     * Độ phức tạp: O(log n)
     * Trả về chỉ số của sản phẩm, -1 nếu không tìm thấy
     */
    int binarySearchByCode(const std::vector<Product>& products,
                           const std::string& code);

    // Kiểm tra dữ liệu sản phẩm hợp lệ
    bool validateProduct(const std::string& code, const std::string& name,
                         double price, int stock);
};
