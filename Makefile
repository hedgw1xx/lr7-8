# Cross-platform Makefile
CC = g++
CFLAGS = -march=native -O2 -pipe -I src
TARGET = main
SRC_DIR = src
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
LOGFILE = $(BUILD_DIR)/build.log
ERRORLOG = $(BUILD_DIR)/error.log
HEADERS = $(wildcard $(SRC_DIR)/*.hpp)

# Detect OS
ifeq ($(OS),Windows_NT)
    EXECUTABLE = $(BUILD_DIR)\$(TARGET).exe
    RM = rmdir /S /Q
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RUN_CMD = .\$(EXECUTABLE)
    SHELL := cmd
    .SHELLFLAGS := /C
else
    EXECUTABLE = $(BUILD_DIR)/$(TARGET)$(EXE_EXT)
    RM = rm -rf
    MKDIR = mkdir -p $(BUILD_DIR)
    EXE_EXT =
    RUN_CMD = ./$(EXECUTABLE)
endif

all: clean $(BUILD_DIR) $(EXECUTABLE)
	@echo Running $(TARGET)... >> $(LOGFILE)
	@$(RUN_CMD) 2>> $(ERRORLOG)

$(BUILD_DIR):
	@$(MKDIR)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking $(TARGET)... >> $(LOGFILE)
	@$(CC) $(OBJECTS) -o $(EXECUTABLE) >> $(LOGFILE) 2>> $(ERRORLOG) || \
	( echo "Compilation error: check $(ERRORLOG)"; exit 1 )

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 2>> $(ERRORLOG)

clean:
	-@$(RM) $(BUILD_DIR) > /dev/null 2>&1

.PHONY: all clean
