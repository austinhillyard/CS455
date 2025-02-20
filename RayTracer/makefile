CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC_DIR = .
BUILD_DIR = build

TARGET = ray_tracer

SRC = main.cpp ppmWriter.cpp RayTracer.cpp

OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
