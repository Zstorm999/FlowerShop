CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -pedantic  -g -fsanitize=address
LDFLAGS =  -fsanitize=address -lSDL2

SRC = main.c
OBJ = $(SRC:.c=.o)
EXEC = flower-shop

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)