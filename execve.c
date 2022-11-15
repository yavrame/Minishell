/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:29:20 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:09:40 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_and_execve(t_command *com, t_envlist *lst, char **buff, int tmp)
{
	if (!ft_strcmp(com->redirection, "<<"))
		com->heredoc = heredoc(com, lst);
	com->execve = execve_from_buff(buff, tmp);
}

char	**execve_from_buff(char **buff, int i)
{
	int		len;
	char	**execve;
	int		j;

	j = 0;
	len = i;
	while (buff[len] && !ft_strchr("|><", buff[len][0]))
		len ++;
	if (!buff[len] && i == 0)
		return (buff);
	execve = malloc(sizeof(char *) * (len - i) + 1);
	while (j <= len - i)
		execve[j++] = ft_strdup(buff[i++]);
	execve[j] = NULL;
	return (execve);
}

static char	**linked_double(t_envlist *lst)
{
	int			len;
	t_envlist	*tmp;
	char		**buff;

	if (!lst)
		return (NULL);
	len = 0;
	tmp = lst;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	buff = malloc(sizeof(char *) * len + 1);
	len = 0;
	while (lst)
	{
		buff[len++] = lst->stock;
		lst = lst->next;
	}
	buff[len] = NULL;
	return (buff);
}

static char	*execve_handler(t_command *command, t_envlist *lst)
{
	char	**buff;
	int		pid;
	int		exit_status;
	int		i;

	i = 0;
	buff = linked_double(lst);
	pid = fork();
	if (pid == 0)
		execve(command->program, command->execve, buff);
	wait(&exit_status);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) != 13)
			g_variable.g_exites = 128 + WTERMSIG(exit_status);
		if (WTERMSIG(exit_status) == SIGQUIT)
			printf(" Quit\n");
	}
	else
		g_variable.g_exites = WEXITSTATUS(exit_status);
	free(buff);
	return (NULL);
}

void	execve_builtin(t_command *com, t_envlist *lst)
{
	if (!com->program)
		return ;
	else if (ft_strchr(com->program, '/') && access(com->program, F_OK) == -1)
		printf("%s: file/program not found\n", com->program);
	else if (!ft_strcmp(com->program, "cd"))
		g_variable.g_exites = cd_command(com, lst);
	else if (!ft_strcmp(com->program, "pwd"))
		g_variable.g_exites = pwd_builtin();
	else if (!ft_strcmp(com->program, "echo"))
		g_variable.g_exites = echo_command(com);
	else if (!ft_strcmp(com->program, "env"))
		g_variable.g_exites = env_builtin(lst);
	else if (!ft_strcmp(com->program, "export"))
		g_variable.g_exites = export_command(lst, com);
	else if (!ft_strcmp(com->program, "unset"))
		g_variable.g_exites = unset_builtin(com, lst);
	else if (com->program)
		execve_handler(com, lst);
}
