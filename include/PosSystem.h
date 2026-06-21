/*
 =============================================================
 HỆ THỐNG QUẢN LÝ BÁN HÀNG POS (Point of Sale)
 =============================================================
 File: PosSystem.h
 Mô tả: Master header - Include tất cả các header trong hệ thống
          Giữ tương thích ngược cho các file sử dụng header tổng hợp
 Kiến trúc: UI -> Service -> DAO -> DatabaseManager -> SQLite
 Chuẩn: C++11
 ==============================================================
 */

#ifndef POS_SYSTEM_H
#define POS_SYSTEM_H

// ================================================================
//                    STANDARD LIBRARY HEADERS
// Các thư viện chuẩn C++ được sử dụng trong toàn bộ dự án
// ================================================================
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <limits>

// ================================================================
//                    THƯ VIỆN SQLITE
// ================================================================
#include "sqlite3.h"

// ================================================================
//                    MODEL HEADERS
// ================================================================
#include "models/User.h"
#include "models/Product.h"
#include "models/CartItem.h"
#include "models/Invoice.h"

// ================================================================
//                    DAO HEADERS
// Data Access Object - Tầng truy xuất dữ liệu
// ================================================================
#include "dao/DatabaseManager.h"
#include "dao/UserDAO.h"
#include "dao/ProductDAO.h"
#include "dao/InvoiceDAO.h"

// ================================================================
//                    SERVICE HEADERS
// Tầng xử lý nghiệp vụ - logic chính của ứng dụng
// ================================================================
#include "services/AuthService.h"
#include "services/ProductService.h"
#include "services/InvoiceService.h"

// ================================================================
//                    UI HEADERS
// Tầng giao diện - hiển thị menu và xử lý tương tác console
// ================================================================
#include "ui/AppUI.h"

#endif // POS_SYSTEM_H
