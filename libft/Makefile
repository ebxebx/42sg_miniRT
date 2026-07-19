NAME = libft.a
SRCS = 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c \
		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strcmp.c  ft_strncmp.c \
		ft_strchr.c ft_strrchr.c ft_strndup.c\
		ft_chrcnt.c\
		ft_toupper.c ft_tolower.c \
		ft_atoi.c ft_atol.c ft_atof.c \
		ft_bzero.c \
		ft_memset.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
		ft_calloc.c ft_realloc.c \
		ft_strdup.c ft_strarr_len.c ft_strarr_free.c \
		ft_itoa.c ft_split.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstlast.c  ft_lstpop.c  ft_lstpop_back.c \
		ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_abs.c ft_min.c ft_max.c ft_minf.c ft_maxf.c \
		ft_printf.c ft_printf_helper1.c ft_printf_helper2.c \
		ft_vprintf.c \
		get_next_line.c get_next_line_utils.c

PRINTF_FLOAT ?= 0
ifeq ($(PRINTF_FLOAT),1)
SRCS += ft_printf_float.c
else
SRCS += ft_printf_float_stub.c
endif

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2

DEPFLAGS = -MMD -MP
DEPS = $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re
