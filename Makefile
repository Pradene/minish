BUILTIN_FILES	= builtin.c \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				print_export.c \
				pwd.c \
				unset.c

EXEC_FILES =	cmd.c \
				exec_cmd.c \
				exec_utils.c \
				exec_sep.c \
				path.c

MINISHELL_FILES	= error.c \
				get_env.c \
				prompt.c \
				signal.c \
				terminal.c \
				utils.c

PARSING_FILES =	clean.c \
				expand.c \
				free_tree.c \
				parser.c \
				heredoc.c \
				print_tree.c \
				token.c \
				wild_cards.c \
				tmp.c

UTILS_FILES	= addchar.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_lst.c \
			ft_memcpy.c \
			ft_split.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_substr.c \
			ft_strnstr.c \
			ft_itoa.c

MAIN	= main.c

SRCS	+= $(addprefix srcs/builtin/, $(BUILTIN_FILES))
SRCS	+= $(addprefix srcs/exec/, $(EXEC_FILES))
SRCS	+= $(addprefix srcs/minishell/, $(MINISHELL_FILES))
SRCS	+= $(addprefix srcs/parsing/, $(PARSING_FILES))
SRCS	+= $(addprefix srcs/utils/, $(UTILS_FILES))
SRCS	+= $(addprefix srcs/, $(MAIN))

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g

NAME	= minishell

.SILENT:

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: re fclean clean all
