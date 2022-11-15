/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:20:05 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:53:20 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_close(t_command *tmp, int fd0, int fd1)
{
	if (tmp->next)
	{
		dup2(fd0, 0);
		close(fd0);
		close(fd1);
	}
}

static void	std_out_close(int save_stdout)
{
	close(0);
	dup2(save_stdout, 0);
	close(save_stdout);
}

static void	pipe_utils(t_command *tmp, t_envlist *lst)
{
	int	pid;
	int	fd[2];

	if (tmp->next)
		pipe(fd);
	pid = fork();
	if (pid < 0)
		perror("error\n");
	if (pid == 0)
	{
		if (tmp->next)
		{
			close(1);
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		redirection_search(tmp, lst);
		execve_builtin(tmp, lst);
		exit(0);
	}
	close(0);
	pipe_close(tmp, fd[0], fd[1]);
}

static void	status_handler(t_command *tmp)
{
	int			exits;

	while (tmp)
	{
		wait(&exits);
		if (WIFSIGNALED(exits))
		{
			if (WTERMSIG(exits) != 13)
				g_variable.g_exites = 128 + WTERMSIG(exits);
			if (WTERMSIG(exits) == SIGQUIT)
				printf(" Quit\n");
		}
		else
			g_variable.g_exites = WEXITSTATUS(exits);
		tmp = tmp->next;
	}
}

void	pipe_search(t_command *command, t_envlist *lst)
{
	int			save_stdout;
	t_command	*tmp;

	save_stdout = dup(0);
	tmp = command;
	while (tmp)
	{
		pipe_utils(tmp, lst);
		tmp = tmp->next;
	}
	tmp = command;
	status_handler(tmp);
	std_out_close(save_stdout);
}
