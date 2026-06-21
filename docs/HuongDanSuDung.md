# Hướng Dẫn Sử Dụng - POS System

Dự án Hệ thống Quản lý Bán hàng (Point of Sale - POS) được viết bằng C++11, sử dụng SQLite để quản lý cơ sở dữ liệu và được thiết kế theo kiến trúc phân tầng (Layered Architecture). 

Tài liệu này hướng dẫn chi tiết cách cài đặt, biên dịch và thao tác với hệ thống.

---

## 1. Yêu Cầu Hệ Thống

- Trình biên dịch hỗ trợ **C++11** trở lên (Khuyến nghị dùng `g++` đi kèm MinGW trên Windows).
- Make tool (`mingw32-make` đối với môi trường Windows).
- Thư viện `sqlite3` (đã được tích hợp sẵn file `.c` và `.h` trong source code).

## 2. Hướng Dẫn Cài Đặt và Biên Dịch

1. Mở Terminal (Command Prompt hoặc PowerShell).
2. Di chuyển (cd) đến thư mục gốc của dự án `POS_System`.
3. Gõ lệnh sau để dọn dẹp các file cũ (nếu có) và biên dịch hệ thống từ đầu:
   ```bash
   mingw32-make clean
   mingw32-make
   ```
4. Đợi quá trình liên kết các file object hoàn tất. Nếu thành công, một file thực thi `pos_system.exe` sẽ được tạo ra.

## 3. Hướng Dẫn Khởi Chạy

Sau khi biên dịch thành công, khởi động hệ thống bằng lệnh:
```bash
mingw32-make run
```
*(Hoặc có thể click đúp vào file `pos_system.exe` hay gõ `./pos_system.exe` trực tiếp vào terminal)*

### Tài khoản đăng nhập mặc định
Nếu là lần đầu chạy, hệ thống sẽ tự động nạp dữ liệu mẫu sau:

**A. Quản trị viên (Admin)** - Quyền cao nhất, được phép quản lý nhân sự, kho, sản phẩm.
- Tên đăng nhập: `admin`
- Mật khẩu: `admin123`

**B. Nhân viên (Staff)** - Quyền giới hạn, được phép bán hàng, xem lịch sử và tra cứu sản phẩm.
- Tên đăng nhập: `nhanvien1` / Mật khẩu: `nv123`
- Tên đăng nhập: `nhanvien2` / Mật khẩu: `nv456`

---

## 4. Các Tính Năng Nổi Bật

### Mẹo thao tác chung
- **Quay lại:** Ở hầu hết mọi dấu nhắc nhập liệu (Ví dụ: Thêm sản phẩm, Tìm kiếm, Xóa, Thêm vào giỏ...), chỉ cần gõ `0` rồi ấn Enter là sẽ ngay lập tức **hủy lệnh** và quay lại menu trước đó mà không sợ bị mắc kẹt.

### Quản lý Sản phẩm (Dành cho Admin)
- Thêm/Sửa/Xóa sản phẩm với mã, tên, giá bán và danh mục.
- **Tìm kiếm:** Sử dụng thuật toán *Binary Search* cho kết quả tức thì (mã sản phẩm).
- **Sắp xếp:** Sử dụng thuật toán *Bubble Sort* để sắp xếp toàn bộ danh sách sản phẩm theo giá bán.

### Quản lý Bán hàng (POS)
- Thêm sản phẩm vào giỏ hàng bằng Số thứ tự (STT) trực quan.
- Tự động cộng dồn số lượng nếu sản phẩm đã tồn tại trong giỏ.
- Hỗ trợ thanh toán: Tự động trừ tồn kho, tính tổng tiền và lưu thành hóa đơn chi tiết.
- In hóa đơn ra màn hình với layout.

### Quản lý Tồn kho & Database
- Tự động cảnh báo các mặt hàng có tồn kho thấp (< 10 sản phẩm).
- Cho phép chỉnh sửa trực tiếp số dư tồn kho.
- **Sao lưu dữ liệu:** Backup an toàn file `.db` sang thư mục `backup/` kèm theo chuỗi ngày giờ (timestamp) chống ghi đè.

---

## 5. Cấu Trúc Thư Mục Hệ Thống (Mới)

Dự án đã được refactor tuân thủ chuẩn Clean Code và chia làm các Module:

```text
POS_System/
├── Makefile                # Kịch bản biên dịch dự án với mingw32-make
├── main.cpp                # Dependency Injection & Bootstrapper
├── README.md               # Tóm tắt dự án ngoài root
│
├── docs/                   # Tài liệu phát triển và hướng dẫn
│   ├── HuongDanSuDung.md   # [File bạn đang đọc]
│   └── TaiLieuThietKe.md
│
├── include/                # Thư mục Header files (*.h)
│   ├── PosSystem.h         # Master header
│   ├── sqlite3.h           
│   ├── models/             # Chứa định nghĩa User, Product, CartItem, Invoice
│   ├── dao/                # Chứa DatabaseManager, UserDAO, ProductDAO...
│   ├── services/           # Chứa AuthService, ProductService...
│   └── ui/                 # Chứa AppUI
│
├── src/                    # Thư mục Source files (*.cpp)
│   ├── models/             
│   ├── dao/                
│   ├── services/           
│   ├── ui/                 
│   └── sqlite3.c           # Core SQLite C implementation
│
├── data/                   # Chứa Database thực tế
└── backup/                 # Nơi lưu các bản sao lưu Database
```

