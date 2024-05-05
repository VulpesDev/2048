NAME := 2048

SRCDIR := src
_SRC := main.c grid_utility.c frontend.c algorithm.c
SRC := $(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR := obj
_OBJ := $(_SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(_OBJ))

# LIBFTDIR := libft
# LIBFT := $(LIBFTDIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -I$(SRCDIR) -I$(LIBFTDIR)
# LDFLAGS :=  -L$(LIBFTDIR) -lft
LDFLAGS := -lncursus
RM := /bin/rm -f

all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/grid_utility.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJ)
	$(RM) -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY:
	all clean fclean re