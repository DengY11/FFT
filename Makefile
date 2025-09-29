# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -lm -pthread

# Directories
SRC_DIR = src
BUILD_DIR = build
TARGET = music_visual

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compiling source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean