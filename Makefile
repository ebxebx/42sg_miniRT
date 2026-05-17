NAME = miniRT

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a
PRINTF_FLOAT ?= 0
LIBFT_MAKE = $(MAKE) -C $(LIBFT_DIR) PRINTF_FLOAT=$(PRINTF_FLOAT)

# Source files
SRC = src/main.c
		
# Object files
OBJ =$(SRC:.c=.o)

# Dependency files
DEP = $(OBJ:.o=.d)

# Include .d files only if they exists ignore otherwise
-include $(DEP)

# Compiler and Flags(-MMD generate dependency files to update if .h files are updated -MP prevents errors for .h)
CC = cc
INCLUDES = -I./includes/
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3 $(INCLUDES)

# sets default target
.DEFAULT_GOAL := all

# build the target $(NAMES)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✓ built $(NAME)"

#run with args
run: $(NAME)
	./$(NAME) $(ARGS)

run2: $(NAME)
	./$(NAME) $(ARGS2)

#run with valgrind and run with args
testv: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g"
	-valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS)

testv2: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g"
	-valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS2)

# Compile .c files to .o files and generate dependency files
src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove object and dependency files
clean:
	rm -f $(OBJ) $(DEP)

# Remove program
fclean: clean
	rm -f $(NAME) 
	
# Delete everything and rebuilt from scratch
re: fclean all

# Phony targets (commands and not files)
.PHONY: all clean fclean re testv run run2 

