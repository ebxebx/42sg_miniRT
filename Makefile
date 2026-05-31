NAME = miniRT
ARGS = ./scenes/minimalist.rt --save minimalist.ppm
ARGS2 = ./scenes/full.rt --save full.ppm

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a
PRINTF_FLOAT ?= 1
LIBFT_MAKE = $(MAKE) -C $(LIBFT_DIR) PRINTF_FLOAT=$(PRINTF_FLOAT)

# Source directory
SRCS_DIR = srcs

# Source files
SRCS = $(SRCS_DIR)/miniRT.c \
       $(SRCS_DIR)/vec3/vec3_ops1.c $(SRCS_DIR)/vec3/vec3_ops2.c \
	   $(SRCS_DIR)/vec3/vec3_helper.c \
       $(SRCS_DIR)/parse/parse_and_free_scene.c \
       $(SRCS_DIR)/parse/parse_line.c \
       $(SRCS_DIR)/parse/parse_elements.c \
       $(SRCS_DIR)/parse/parse_light.c \
       $(SRCS_DIR)/parse/parse_shapes.c \
       $(SRCS_DIR)/parse/parse_utils.c \
       $(SRCS_DIR)/parse/parse_utils_split.c

# Object files
OBJS =$(SRCS:.c=.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Include .d files only if they exists ignore otherwise
-include $(DEPS)

# Compiler and Flags(-MMD generate dependency files to update if .h files are updated -MP prevents errors for .h)
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3 $(INCLUDES)
INCLUDES = -I./includes/
LIB_FLAGS = -L$(LIBFT_DIR) -lft -lm
ifeq ($(PRINTF_FLOAT),1)
	LIB_FLAGS += -lm
endif
# Add dependency flags and derived files
DEPFLAGS = -MMD -MP

# sets default target
.DEFAULT_GOAL := all

# build the target $(NAMES)
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)
	@echo "✓ built $(NAME)"

$(LIBFT):
	$(LIBFT_MAKE)

# Ensure make will run libft's build to check if its source files were modified
libft:
	$(LIBFT_MAKE)

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
srcs/%.o: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove object and dependency files
clean:
	rm -f $(OBJS) $(DEPS)

# Remove program
fclean: clean
	rm -f $(NAME) $(LIBFT)

# Delete everything and rebuilt from scratch
re: fclean all

# Phony targets (commands and not files)
.PHONY: all clean fclean re testv run run2 