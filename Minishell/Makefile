##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## psu
##

SRC 	=	./lib/my_putchar.c \
			./lib/my_putstr.c \
			./lib/my_strlen.c \
			./lib/my_strcmp.c \
			./lib/my_strcpy.c \
			./lib/my_strncpy.c \
			./lib/my_env_to_word_array.c \
			./lib/my_path_to_word_array.c \
			./lib/my_strdup.c \
			./lib/my_strcat.c \
			./lib/my_strncmp.c \
\
			./src/builtin_management/count_argument.c \
			./src/builtin_management/env_and_printenv_command.c \
			./src/builtin_management/setenv_command.c \
			./src/builtin_management/unsetenv_command.c \
			./src/builtin_management/cd/cd_command.c \
			./src/builtin_management/cd/cd_utils.c \
			./src/builtin_management/run_builtin.c \
\
			./src/binaries_management/find_bin.c \
			./src/binaries_management/my_exec.c \
			./src/binaries_management/path_handling.c \
\
			./src/separator_and_redirection/set_separator.c \
			./src/separator_and_redirection/separate_by_separator.c \
			./src/separator_and_redirection/who_to_send.c \
			./src/separator_and_redirection/run_pipe.c \
			./src/separator_and_redirection/verify_pipe_and_redirection.c \
			./src/separator_and_redirection/run_right_redirect.c \
			./src/separator_and_redirection/pipe_and_redirect_utils.c \
			./src/separator_and_redirection/run_left_redirect.c \
			./src/separator_and_redirection/pipe_loop.c \
			./src/separator_and_redirection/pipe_with_builtin.c \
			./src/separator_and_redirection/simple_pipe.c \
\
			./src/shell/fill_struct.c \
			./src/shell/shell_utils.c \
			./src/shell/separate_argument.c \
			./src/shell/prompt_loop.c \
\
			./src/error_handling.c \
			./src/main.c \

NAME 	=	mysh

CC 	=	gcc

RM	=	rm -f

CFLAGS 	=	-Wall -Wextra

CPPFLAGS 	=	-iquote ./include

OBJ 	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

debug: CFLAGS	+=	-g3
debug: clean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME)_debug

re:	fclean all

.PHONY: all clean fclean re debug
