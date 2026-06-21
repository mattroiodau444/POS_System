# ==============================================================================
# MAKEFILE CHO DỰ ÁN POS SYSTEM
# Biên dịch dự án C++11 đa tầng kèm SQLite
# ==============================================================================

# Trình biên dịch cho C++ và C
CXX = g++
CC = gcc

# Các cờ biên dịch
CXXFLAGS = -std=c++11 -Wall -Iinclude
CFLAGS = -Wall

# Tên file thực thi đầu ra
TARGET = pos_system

# Danh sách các file mã nguồn C++
CXX_SRCS = main.cpp \
           src/models/User.cpp src/models/Product.cpp src/models/CartItem.cpp src/models/Invoice.cpp \
           src/dao/DatabaseManager.cpp src/dao/UserDAO.cpp src/dao/ProductDAO.cpp src/dao/InvoiceDAO.cpp \
           src/services/AuthService.cpp src/services/ProductService.cpp src/services/InvoiceService.cpp \
           src/ui/AppUI.cpp

# Danh sách các file mã nguồn C (SQLite)
C_SRCS = src/sqlite3.c

# Danh sách các file object tương ứng
CXX_OBJS = $(CXX_SRCS:.cpp=.o)
C_OBJS = $(C_SRCS:.c=.o)
ALL_OBJS = $(CXX_OBJS) $(C_OBJS)

# ==============================================================================
# CÁC LUẬT BIÊN DỊCH (TARGETS)
# ==============================================================================

# Target mặc định: biên dịch toàn bộ dự án
all: $(TARGET)

# Luật để tạo ra file thực thi
$(TARGET): $(ALL_OBJS)
	@echo "Dang lien ket cac object files de tao thuc thi..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(ALL_OBJS)
	@echo "Bien dich hoan tat! Chay lenh 'mingw32-make run' de khoi dong."

# Luật để biên dịch các file .cpp thành .o
%.o: %.cpp
	@echo "Dang bien dich file C++: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Luật riêng để biên dịch thư viện SQLite bằng gcc
src/sqlite3.o: src/sqlite3.c
	@echo "Dang bien dich SQLite..."
	$(CC) $(CFLAGS) -c src/sqlite3.c -o src/sqlite3.o

# Chạy chương trình
run: $(TARGET)
	@echo "Dang chay chuong trinh..."
	./$(TARGET)

# Xóa các file trung gian (.o) và file thực thi
clean:
	@echo "Dang don dep cac file biên dich..."
	rm -f $(ALL_OBJS) $(TARGET) $(TARGET).exe

# Xóa tất cả: gồm các file biên dịch và dữ liệu (database, backup)
cleanall: clean
	@echo "Dang xoa file database va thu muc backup..."
	rm -f data/*.db
	rm -f backup/*.db
	@echo "Hoan tat don dep!"