# Makefile for CMPT-276 Project
# Use with: make or mingw32-make 

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data
TEST_DIR = tests

# Source files
SOURCES = main.cpp menu.cpp vessel.cpp vesselASM.cpp sailing.cpp sailingASM.cpp \
          reservation.cpp reservationASM.cpp vehicleASM.cpp utils.cpp

# Object files in build directory
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))

# Target executable
TARGET = $(BUILD_DIR)/easy_book.exe

# Test files that actually exist
TEST_SOURCES = test_sailing_functionality.cpp test_sailing.cpp test_vehicle.cpp \
               vehicle_test.cpp testVesselGetHCLL.cpp testFileOps.cpp
TEST_TARGETS = $(addprefix $(BUILD_DIR)/, $(TEST_SOURCES:.cpp=.exe))

# Default target
all: $(TARGET)

# Create necessary directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# Build main application
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build complete! Run with: $(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build tests (optional - exclude main.o to avoid multiple main functions)
$(BUILD_DIR)/%.exe: $(TEST_DIR)/%.cpp $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS)) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build all tests
tests: $(TEST_TARGETS)

# Run the application
run: $(TARGET) | $(DATA_DIR)
	$(TARGET)

# Clean build artifacts
clean:
	del /Q "$(BUILD_DIR)\*.o" 2>nul || echo "No object files to clean"
	del /Q "$(BUILD_DIR)\*.exe" 2>nul || echo "No executables to clean"

# Clean everything including directories
distclean: clean
	rmdir /S /Q $(BUILD_DIR) 2>nul || echo "Build directory cleaned"
	rmdir /S /Q $(DATA_DIR) 2>nul || echo "Data directory cleaned"

# Help
help:
	@echo "Available targets:"
	@echo "  all        - Build the main application (default)"
	@echo "  tests      - Build all test executables"
	@echo "  run        - Build and run the main application"
	@echo "  test-sailing - Build and run sailing functionality tests"
	@echo "  clean      - Remove build artifacts"
	@echo "  distclean  - Remove build directory completely"
	@echo "  help       - Show this help"
	@echo ""
	@echo "Project structure:"
	@echo "  src/       - Source files (.cpp)"
	@echo "  include/   - Header files (.h)"
	@echo "  tests/     - Test files"
	@echo "  data/      - Data files (.dat)"
	@echo "  build/     - Build artifacts"

.PHONY: all tests run test-sailing clean distclean help
