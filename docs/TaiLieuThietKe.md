# TÀI LIỆU THIẾT KẾ HỆ THỐNG QUẢN LÝ BÁN HÀNG (POS SYSTEM)

## 1. Giới thiệu đề tài
Hệ thống Quản lý Bán hàng (Point of Sale - POS) là phần mềm đóng vai trò thiết yếu trong việc vận hành các cửa hàng bán lẻ hiện đại. Nhằm đáp ứng nhu cầu quản lý tự động, chính xác và chuyên nghiệp, đề tài này tập trung vào việc xây dựng một hệ thống POS bằng ngôn ngữ C++ (chuẩn C++11) kết hợp cơ sở dữ liệu SQLite. Đây là đồ án môn học Kỹ thuật Lập trình, hướng tới việc thực hành các khái niệm lập trình nâng cao, tổ chức mã nguồn và làm việc với CSDL.

## 2. Mục tiêu hệ thống
- **Tự động hóa bán hàng:** Cho phép tạo giỏ hàng, tính tổng tiền và thanh toán một cách nhanh chóng.
- **Quản lý sản phẩm và tồn kho:** Thêm, sửa, xóa sản phẩm, theo dõi số lượng tồn kho và cảnh báo khi sắp hết hàng.
- **Lưu trữ dữ liệu an toàn:** Lưu trữ toàn bộ thông tin tài khoản, danh sách sản phẩm và lịch sử hóa đơn bằng CSDL SQLite cục bộ (offline).
- **Phân quyền người dùng:** Đảm bảo an toàn thông tin với hai mức quyền: Quản trị viên (Admin) và Nhân viên (Staff).

## 3. Phân tích yêu cầu
**Yêu cầu chức năng:**
- Đăng nhập/Đăng xuất theo phân quyền.
- Quản lý danh mục sản phẩm (CRUD).
- Tìm kiếm, sắp xếp danh sách sản phẩm.
- Lập hóa đơn bán hàng, tự động trừ tồn kho.
- Xem lịch sử hóa đơn.
- Sao lưu dữ liệu thủ công.

**Yêu cầu phi chức năng:**
- Giao diện Console dễ nhìn, menu rõ ràng.
- Xử lý mượt mà, không gặp lỗi rò rỉ bộ nhớ (Memory Leak).
- Hệ thống có tính bắt lỗi (Validation) để không crash khi nhập sai định dạng.

## 4. Nguyên lý tổ chức chương trình
Chương trình tuân thủ các nguyên lý:
- **Single Responsibility Principle (SRP):** Mỗi lớp/module chỉ chịu trách nhiệm giải quyết một vấn đề cụ thể (VD: DAO chỉ thao tác CSDL, UI chỉ lo giao diện).
- **Dependency Injection (DI):** Các Service được truyền các lớp DAO cần thiết qua hàm khởi tạo (Constructor), giúp dễ dàng thay thế hoặc mở rộng khi cần.

## 5. Kiến trúc nhiều tầng (Multi-tier Architecture)
Chương trình áp dụng kiến trúc 4 tầng rõ rệt:
1. **Model Layer:** Định nghĩa các thực thể (User, Product, Invoice, CartItem). Không chứa logic truy xuất dữ liệu.
2. **DAO (Data Access Object) Layer:** Giao tiếp trực tiếp với SQLite để truy vấn và cập nhật dữ liệu.
3. **Service Layer:** Nhận dữ liệu từ UI, kiểm tra tính hợp lệ (Validation), thực thi thuật toán (sắp xếp, tìm kiếm) và gọi các hàm DAO tương ứng.
4. **UI Layer:** Tương tác với người dùng qua Console (cin/cout), không chứa các logic truy xuất cơ sở dữ liệu trực tiếp.

## 6. Thiết kế cơ sở dữ liệu (Database Design)
CSDL SQLite bao gồm 4 bảng chính:
- **users:** `id` (PK), `username` (Unique), `password`, `full_name`, `role`.
- **products:** `id` (PK), `code` (Unique), `name`, `price`, `stock`, `category`.
- **invoices:** `id` (PK), `invoice_code` (Unique), `user_id` (FK -> users.id), `cashier_name`, `date_time`, `total_amount`.
- **invoice_items:** `id` (PK), `invoice_id` (FK -> invoices.id), `product_code`, `product_name`, `price`, `quantity`, `subtotal`.

## 7. Thiết kế lớp (Class Diagram Overview)
- **Model Classes:** `User`, `Product`, `Invoice`, `CartItem`.
- **Database Classes:** `DatabaseManager` (Singleton), `UserDAO`, `ProductDAO`, `InvoiceDAO`.
- **Service Classes:** `AuthService`, `ProductService`, `InvoiceService`.
- **UI Class:** `AppUI`.

Sơ đồ phụ thuộc cơ bản: `AppUI` -> `Service` -> `DAO` -> `DatabaseManager` -> SQLite.

## 8. Thiết kế luồng xử lý (Workflow)
**Luồng thanh toán giỏ hàng (Checkout):**
1. User chọn thanh toán từ `AppUI`.
2. `AppUI` gọi `InvoiceService::checkout()`.
3. `InvoiceService` kiểm tra xem giỏ hàng có rỗng không.
4. Lặp qua các `CartItem` trong giỏ, dùng `ProductDAO` kiểm tra tồn kho mới nhất trong DB.
5. Nếu đủ hàng, `InvoiceService` tính tổng tiền, tạo đối tượng `Invoice`.
6. Gọi `InvoiceDAO` sinh mã hóa đơn và `INSERT` vào bảng `invoices`. Nhận lại `invoiceId`.
7. `InvoiceService` lưu từng `CartItem` vào bảng `invoice_items` thông qua `InvoiceDAO`. Đồng thời cập nhật lại số lượng tồn kho qua `ProductDAO`.
8. Trả về thông báo thành công cho `AppUI` để in hóa đơn.

## 9. Thuật toán sử dụng
- **Sắp xếp nổi bọt tối ưu (Optimized Bubble Sort):** Được sử dụng trong `ProductService::sortByPrice()` để sắp xếp sản phẩm theo giá tăng dần. Có sử dụng cờ (flag) để kết thúc sớm nếu mảng đã có thứ tự. Độ phức tạp trung bình: O(N^2).
- **Tìm kiếm nhị phân (Binary Search):** Được sử dụng trong `ProductService::binarySearchByCode()` để tìm nhanh sản phẩm theo mã. Yêu cầu danh sách sản phẩm phải được sắp xếp trước theo mã. Độ phức tạp: O(log N).

## 10. Kỹ thuật lập trình sử dụng
- **Lập trình hướng đối tượng (OOP):** Tính đóng gói (Encapsulation), Constructors.
- **Thư viện chuẩn (STL):** Sử dụng `std::vector` để thay thế mảng tĩnh, `std::string` cho chuỗi văn bản.
- **Const Correctness:** Truyền tham chiếu hằng (`const type&`) và khai báo hàm hằng (`const` member functions) để đảm bảo an toàn bộ nhớ.
- **Con trỏ hàm / Lambda Expressions:** Dùng cùng hàm `std::sort` trong C++11 để sắp xếp custom object.
- **Mẫu thiết kế (Design Pattern):** Áp dụng mẫu *Singleton* cho `DatabaseManager`.

## 11. Kiểm thử chương trình
- **Kiểm thử logic nhập xuất:** Nếu nhập số âm cho số lượng, nhập chữ vào trường bắt buộc nhập số, chương trình sẽ không văng (crash) mà xử lý báo lỗi và yêu cầu nhập lại.
- **Kiểm thử nghiệp vụ:** Khi bán hàng, nếu số lượng mua vượt mức tồn kho hiện tại, hệ thống chặn thanh toán.
- **Kiểm thử đồng bộ CSDL:** Sau khi mua hàng xong, số lượng tồn kho cập nhật chính xác và lịch sử hóa đơn được lưu giữ đầy đủ ngay cả khi tắt mở lại chương trình.

## 12. Kết luận
Đồ án đã thiết kế và hoàn thiện thành công một hệ thống POS đầy đủ các tính năng cơ bản và nâng cao, phù hợp với môi trường bán lẻ quy mô nhỏ.
Việc áp dụng kiến trúc đa tầng (Multi-tier) và tích hợp hệ quản trị cơ sở dữ liệu SQLite giúp mã nguồn trở nên gọn gàng, dễ bảo trì, và có khả năng mở rộng (Scale up) trong tương lai. Hệ thống hoàn toàn đáp ứng tốt các yêu cầu của một đồ án môn Kỹ thuật Lập trình.
