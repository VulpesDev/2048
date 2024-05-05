# Compiler
CC = cc

# Warning flags
CFLAGS = -Wall -Werror -Wextra

# Library
LIBS = -lncurses

# Executable name
EXEC = 2048  # Replace with your desired program name

# Object files
OBJECTS = algorithm.o frontend.o grid_utility.o main.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(EXEC)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(EXEC)
re: fclean all

.PHONY: all clean fclean re
