NAME = minishell

FLAGS = -g -Wall -Werror -Wextra
FLAGS_READLINE = -lreadline -L ~/.brew/opt/readline/lib

LIBPATH = libft/

HEADERS_DIR = includes/
INC = -I$(HEADERS_DIR) -I ~/.brew/opt/readline/include
INC_LIB = -I$(LIBPATH)
H_FILES = minishell.h
HEADERS = $(addprefix $(HEADERS_DIR), $(H_FILES))

SRC_DIR = ./srcs/
SRC_FILES =	main.c\
	builtins/cd.c\
	builtins/echo.c\
	builtins/env.c\
	builtins/exit.c\
	builtins/export.c\
	builtins/pwd.c\
	builtins/unset.c\
	functions/ft_execve.c\
	functions/redirect.c\
	functions/signal.c\
	functions/pipe.c\
	parser/m_split.c\
	parser/preparser.c\
	parser/parser.c\
	parser/quote_parser.c\
	parser/redirect_parser.c\
	parser/env_parser.c\
	utils/export_utils.c\
	utils/env_utils.c\
	utils/free.c\
	utils/parser_utils.c\
	utils/utils.c
	

SOURCES = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = objects/
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) bonus -C ./libft
	gcc $(FLAGS) $(FLAGS_READLINE) -lncurses $(INC) $(OBJECTS) -L$(LIBPATH) -lft -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)parser
	mkdir -p $(OBJ_DIR)builtins
	mkdir -p $(OBJ_DIR)functions
	mkdir -p $(OBJ_DIR)utils


$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	gcc $(FLAGS) $(INC) $(INC_LIB) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C ./libft 

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re: fclean all
