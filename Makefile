# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic -lm

# Directories
BUILD_DIR = build
SRC_DIR = src

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Executable
EXE = nn

# Build executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Clean object files and executable
clean:
	rm -f $(OBJ) $(EXE)
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: run build

# Default target
default: build

# Target for running the executable
run: $(EXE)
	./$(EXE)

# Target for building the executable
build: $(EXE)
