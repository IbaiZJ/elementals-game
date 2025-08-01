BUILD_TYPE ?= debug

ifeq ($(BUILD_TYPE), debug)
    CFLAGS += -g -DDEBUG
else ifeq ($(BUILD_TYPE), release)
    CFLAGS += -O2 -DNDEBUG
else
    $(error BUILD_TYPE need to be 'debug' or 'release')
endif

BIN_PATH = bin/
BUILD_PATH = build/
NAME = ELEMENALS

SRC_PATH = src/
SRC = $(shell find $(SRC_PATH) -name '*.c')
OBJ = $(patsubst $(SRC_PATH)%.c, $(BUILD_PATH)%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -g `sdl2-config --cflags` -Isrc
HEADERS = $(shell find $(SRC_PATH) -name '*.h')
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

all: $(BIN_PATH)$(NAME)

$(BIN_PATH)$(NAME): $(OBJ)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Compilation complete.: $(BIN_PATH)$(NAME) (mode: $(BUILD_TYPE))"

$(BUILD_PATH)%.o: $(SRC_PATH)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)$(NAME)
	@echo "Intermediate and binary files deleted."

clean-obj:
	rm -rf $(BUILD_PATH)
	@echo "Object files deleted."

run: all
	./$(BIN_PATH)$(NAME)
