POS System - Hệ thống quản lý bán hàng
Giới thiệu

POS System là ứng dụng quản lý bán hàng được phát triển bằng ngôn ngữ C++11 kết hợp cơ sở dữ liệu SQLite. Hệ thống hỗ trợ quản lý sản phẩm, bán hàng, quản lý hóa đơn, tồn kho và sao lưu dữ liệu.

Đây là đồ án môn Kỹ thuật Lập trình nhằm vận dụng kiến thức về:

Lập trình hướng đối tượng (OOP)
Cấu trúc dữ liệu và giải thuật
Cơ sở dữ liệu SQLite
Tổ chức dự án nhiều mô-đun
Chức năng chính
Đăng nhập và phân quyền người dùng
Quản lý sản phẩm (Thêm, sửa, xóa)
Tìm kiếm sản phẩm
Sắp xếp sản phẩm theo giá
Bán hàng (POS)
Quản lý lịch sử hóa đơn
Quản lý tồn kho
Sao lưu cơ sở dữ liệu
Công nghệ sử dụng
C++11
SQLite3
MinGW g++
mingw32-make
Cấu trúc dự án
include/    : Header files
src/        : Source files
data/       : SQLite database
backup/     : Database backups
docs/       : Tài liệu dự án
Hướng dẫn biên dịch
mingw32-make
Chạy chương trình
.\pos_system.exe
Tài khoản mặc định
Username: admin
Password: admin123
