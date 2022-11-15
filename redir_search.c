/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:10:43 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:32:20 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_command *command, t_envlist *lst)
{
	char	*prompt;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		prompt = readline("heredoc > ");
		if (!prompt || !ft_strcmp(command->files->file, prompt))
		{
			free(prompt);
			close(fd[1]);
			return (fd[0]);
		}
		ft_putstr_fd(get_environment(prompt, lst, 0), fd[1]);
		ft_putstr_fd("\n", fd[1]);
	}
}

static void	right_redirection(t_command *command, int output)
{
	if (!ft_strcmp(command->redirection, ">"))
	{
		output = open(command->files->file, O_CREAT | O_RDWR | O_TRUNC, 0666);
		dup2(output, 1);
		close(output);
	}
	else if (!ft_strcmp(command->redirection, ">>"))
	{
		output = open(command->files->file, O_CREAT | O_RDWR | O_APPEND, 0666);
		dup2(output, 1);
		close(output);
	}
}

static void	left_redirection(t_command *command, int file_out)
{
	if (!ft_strcmp(command->redirection, "<"))
	{
		file_out = open(command->files->file, O_RDONLY);
		if (file_out == -1)
		{
			printf("%s: No such file or directory\n", command->files->file);
			exit(1);
		}
		dup2(file_out, 0);
		close(file_out);
	}
	else if (!ft_strcmp(command->redirection, "<<"))
	{
		dup2(command->heredoc, 0);
		close(command->heredoc);
	}
}

void	redirection_search(t_command *command, t_envlist *lst)
{
	int	file_out;

	file_out = 0;
	if (command->files != NULL)
	{
		right_redirection(command, file_out);
		left_redirection(command, file_out);
		command->files = command->files->next;
		redirection_search(command, lst);
	}
}
