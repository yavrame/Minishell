# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 19:42:19 by pharmund          #+#    #+#              #
#    Updated: 2022/06/28 14:21:54 by pharmund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CFLAGS = -Wall  -Wextra  -Werror

HEADER = minishell.h

RM = rm -rf

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@ -I $(HEADER)


SRCS = 	minishell.c\
		split_args2.c\
		environment_list.c\
		get_environment.c\
		split_args.c\
		cd.c\
		echo.c\
		error_search.c\
		execve.c\
		export.c\
		get_command.c\
		built_in.c\
		libft_bonus.c\
		parser.c\
		pipe_search.c\
		pwd.c\
		redir_search.c\
		signal_search.c\
		export_split.c\
		unset.c\

OBJS = $(SRCS:.c=.o) ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) -L$(shell brew --prefix readline)/lib -lreadline $(OBJS) -o $(NAME)

$(OBJS): minishell.h Makefile ./libft/*.c ./libft/*.h ./libft/Makefile

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean:	clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re