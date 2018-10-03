# Directory

SRC_DIR = lypuppies
INC_DIR = lypuppies/includes
BIN_DIR = bin
OBJ_DIR = obj

# Compiler
CC = gcc
CFLAG_LIB = -O3 -I$(INC_DIR)

# Lypuppies src files
L_SRC = $(filter-out lypuppies/main.c, $(wildcard $(SRC_DIR)/*.c))
L_HEADERS = $(wildcard $(INC_DIR)/*.h)
OBJECTS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(L_SRC))
$(info VAR="$(L_SRC)")
# Rules to make the lib (based on my lymui lib..)

all: clean lib

obj:
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)

bin:
	mkdir -p $(BIN_DIR)/includes

headers: bin
	for fname in $(L_HEADERS); do \
		cp $${fname} $(BIN_DIR)/includes/ ; \
	done

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAG_LIB) -c $< -o $@

lib: obj headers $(OBJECTS)
	ar rcs $(BIN_DIR)/liblypuppies.a $(OBJ_DIR)/$(SRC_DIR)/*.o

clean:
	rm -rf $(OBJ_DIR) && rm -rf $(BIN_DIR)