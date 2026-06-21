# POS System - Hệ thống quản lý bán hàng

## Giới thiệu
**POS System** là ứng dụng quản lý bán hàng được phát triển bằng ngôn ngữ **C++11** kết hợp với cơ sơ dữ liệu **SQLite**. Hệ thống hỗ trợ đắc lực trong việc quản lý sản phẩm, xử lý bán hàng, quản lý hóa đơn, kiểm soát tồn kho và tự động sao lưu dữ liệu.

Đây là đồ án môn **Kỹ thuật Lập trình** nhằm vận dụng và tối ưu các kiến thức:
* **Lập trình hướng đối tượng (OOP):** Thiết kế các lớp đối tượng, quản lý tính đóng gói và kế thừa.
* **Cấu trúc dữ liệu và giải thuật:** Tối ưu hóa mảng, danh sách và thuật toán tìm kiếm/sắp xếp.
* **Cơ sở dữ liệu SQLite:** Tổ chức lưu trữ dữ liệu quan hệ gọn nhẹ, nhất quán.
* **Tổ chức dự án đa mô-đun:** Chia tách code rõ ràng giữa header (`.h`) và source (`.cpp`).

---

## Chức năng chính
*  **Hệ thống:** Đăng nhập bảo mật và phân quyền người dùng (Admin/Staff).
*  **Quản lý sản phẩm:** Thêm, sửa, xóa thông tin hàng hóa.
*  **Bộ lọc thông minh:** Tìm kiếm sản phẩm nhanh chóng, sắp xếp sản phẩm linh hoạt theo giá cả.
*  **Bán hàng (POS):** Tạo đơn hàng, tính tiền, cập nhật số lượng trực tiếp.
*  **Lịch sử & Thống kê:** Quản lý và truy xuất lịch sử hóa đơn đã xuất.
*  **Quản lý tồn kho:** Cảnh báo và kiểm soát số lượng hàng hóa trong kho.
*  **An toàn dữ liệu:** Tự động hoặc chủ động sao lưu (backup) cơ sở dữ liệu.

---

## 🛠️ Công nghệ sử dụng
* **Ngôn ngữ:** C++11
* **Cơ sở dữ liệu:** SQLite3
* **Trình biên dịch:** MinGW g++
* **Công cụ xây dựng:** mingw32-make

---

## Cấu trúc dự án
```text
├── include/     # Các file định nghĩa (Header files .h)
├── src/         # Các file hiện thực hàm (Source files .cpp)
├── data/        # Nơi lưu trữ file cơ sở dữ liệu SQLite (.db)
├── backup/      # Nơi lưu trữ các bản sao lưu database (.db)
├── docs/        # Tài liệu hướng dẫn và báo cáo dự án
└── Makefile     # File cấu hình biên dịch bằng make
