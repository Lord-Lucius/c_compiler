CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Wextra -g

# Répertoires
INCLUDE_DIR = includes
SRC_DIR = srcs
BUILD_DIR = build

# Détection automatique des fichiers
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")
HEADERS = $(shell find $(INCLUDE_DIR) -name "*.hpp")
OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Executable
TARGET = c_compiler

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

re: clean all

.PHONY: all clean re