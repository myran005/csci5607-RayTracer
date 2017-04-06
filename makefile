SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
CC = g++
CPPFLAGS += -I$(INC_DIR) 
CFLAGS += -Wall -g
EXE = rayTracer

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJ) *~ */*~
