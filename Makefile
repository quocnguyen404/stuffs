CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC_DIR = src
BUILD_DIR = build

SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cpp=.o)))

TARGET = $(BUILD_DIR)/main.exe

# ===== main-only build =====
MAIN_OBJ = $(BUILD_DIR)/main.o
MAIN_TARGET = $(BUILD_DIR)/main_only.exe

# ===== default =====
all: build

# ===== full build =====
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# ===== main-only build =====
main: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(MAIN_OBJ) -o $(MAIN_TARGET) $(LDFLAGS)

# ===== compile rules =====

# for src/*.cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# for root *.cpp (like main.cpp)
$(BUILD_DIR)/%.o: %.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===== run =====
run: build
	$(TARGET)

run-main: main
	$(MAIN_TARGET)

# ===== clean =====
clean:
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)

.PHONY: all build main run run-main clean