NAME := libft.a
CC := cc
CFLAGS:= -Wall -Wextra -Werror
SRC := ft_bzero.c ft_isalnum.c ft_isalpha.c	ft_isdigit.c \
	   ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c \
	   ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	   ft_isascii.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	   ft_toupper.c ft_tolower.c ft_memchr.c ft_strnstr.c \
	   ft_atoi.c ft_memcmp.c ft_calloc.c ft_strdup.c \
	   ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	   ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   get_next_line.c get_next_line_utils.c ft_puthex.c \
	   ft_printf.c ft_putascii.c ft_putptr.c ft_free.c

SRCBON := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

OBJBON := $(SRC:%.c=%.o) $(SRCBONC:%.c=%.o)

OBJ := $(SRC:%.c=%.o)

all: $(NAME)

bonus: $(OBJBON)
	ar rcs libft.a $(OBJ) $(OBJBON)

$(NAME): $(OBJ)
	ar rcs libft.a $(OBJ)

$(OBJ): $(SRC)
	$(CC) -c $(CFLAGS) $(SRC)

re: fclean all

so:
	$(CC) -fPIC $(CFLAGS) $(SRC) test.c
	gcc -shared -o libft.so $(OBJ) $(OBJBON)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

