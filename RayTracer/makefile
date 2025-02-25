CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC_DIR = .
BUILD_DIR = build
DEBUG_DIR = debug

TARGET = ray_tracer

CXXFLAGS_DEBUG = -g

SRC = main.cpp ppmWriter.cpp RayTracer.cpp Shape.cpp

OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

debug: CXXFLAGS += $(CXXFLAGS_DEBUG)
debug: $(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
