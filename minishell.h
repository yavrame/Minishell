/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:08:18 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:11:38 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>

# define WHITE_SPACES " \t\v\r\f"
# define DELIMS " \t\v\r\f>|<"

typedef struct s_files
{
	char			*file;
	struct s_files	*next;
}				t_files;

struct	s_minishell
{
	int	g_exites;
	int	is_running;
}		g_variable;

typedef struct s_command
{
	char				*redirection;
	t_files				*files;
	char				*program;
	char				**args;
	char				*options;
	char				**execve;
	int					is_append;
	int					heredoc;
	struct s_command	*next;
}				t_command;

typedef struct s_envlist
{
	char				*var_name;
	char				*var_content;
	char				*stock;
	struct s_envlist	*next;
}				t_envlist;

t_command	*get_command(char **buff, int i, int tmp, t_envlist *lst);
t_envlist	*init_environment_list(char **envp);
t_envlist	*ft_lstnew(char *s);
t_envlist	*ft_lstnew_2(char **s);
t_envlist	*ft_lstlast(t_envlist *lst);
void		ft_lstadd_back(t_envlist **lst, t_envlist *new);
char		**split_args(char **ret, char *s);
int			signal_search(void);
int			tab_len(char **tab);
char		**export_split(char const *s, char c);
int			check_for_quotes(char	*str);
char		**execve_from_buff(char **buff, int i);
int			error_checking(char **buff);
char		*get_environment(char *read, t_envlist *lst, int i);
int			print_environment(t_envlist *lst);
void		pipe_search(t_command *command, t_envlist *lst);
void		redirection_search(t_command *command, t_envlist *lst);
int			heredoc(t_command *command, t_envlist *lst);
void		parser(t_command *command, char **buff, int *i, int *j);
int			find_redir(char *str);
char		*free_strjoin(char *s1, char *s2);
void		command_error(char *s);
char		*find_builtin(char *cmd);
void		execve_builtin(t_command *command, t_envlist *lst);
int			cd_command(t_command *command, t_envlist *lst);
int			export_command(t_envlist *lst, t_command *command);
int			echo_command(t_command *commad);
int			unset_builtin(t_command *commad, t_envlist *lst);
int			env_builtin(t_envlist *lst);
int			pwd_builtin(void);
int			quotes_length(char *str, char quote);
char		*redirect_as_arg(char *str);
void		free_paths(char **others);
void		red_and_execve(t_command *com, t_envlist *lst, char **buff, \
			int tmp);

#endif
