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

# Compteur pour la barre de progression
TOTAL_FILES = $(words $(OBJECTS))
CURRENT_FILE = 0

# Executable
TARGET = c_compiler

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "🔗 Linking..."
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✅ Done! Executable: $(TARGET)"

$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE = $(shell expr $(CURRENT_FILE) + 1))
	@printf "⏳ Compiling [%3d/%3d] %s\r" $(CURRENT_FILE) $(TOTAL_FILES) $(notdir $<)
	@$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@echo "🧹 Cleaning..."
	@rm -rf $(BUILD_DIR) $(TARGET)
	@echo "✅ Clean done!"

re: clean all

.PHONY: all clean re