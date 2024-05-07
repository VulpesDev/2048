# Compiler
CC = cc

# Warning flags
CFLAGS = -Wall -Werror -Wextra

# Library
LIBS = -lncurses

# Executable name
EXEC = 2048  # Replace with your desired program name

# Source directory
SRCDIR = src

# Object directory
OBJDIR = obj

# Object files
OBJECTS = $(OBJDIR)/algorithm.o $(OBJDIR)/frontend.o $(OBJDIR)/grid_utility.o $(OBJDIR)/main.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(EXEC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
