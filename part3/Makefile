CC = gcc
COMP_FLAGS = -Wall -c -O0 -g3 -gdwarf-4
LINK_FLAGS = 
OUTPUT = skip
SRC_FILES = $(wildcard *.c)
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(SRC_FILES:.c=.o)
SRC_DEPS = $(SRC_FILES:.c=.d)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(LINK_FLAGS) -o $(OUTPUT) $(OBJ_FILES)

-include $(SRC_DEPS)

%.o:%.c
	$(CC) $(COMP_FLAGS) $< -o $@
	$(CC) $(COMP_FLAGS) -MM $< -o $*.d

clean:
	rm $(OBJ_FILES) $(OUTPUT)
