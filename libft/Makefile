NAME = libft.a

SRC = 	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_itoa.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_split.c \
	ft_strmapi.c \
	get_next_line.c

BONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c

OBJ = $(SRC:.c=.o)

BONUSOBJ = $(BONUS:.c=.o)

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
so:
	gcc -fPIC -c $(SRC) $(BONUS)
	gcc -shared -o libft.so $(OBJ) $(BONUSOBJ)
	
bonus:	$(OBJ) $(BONUSOBJ)
	ar rc $(NAME) $(OBJ) $(BONUSOBJ)
	ranlib $(NAME)
clean:
	rm -f $(OBJ) $(BONUSOBJ)

fclean: clean
	rm -f $(NAME) libft.so

re: fclean all

.PHONY: all, clean, fclean, re
