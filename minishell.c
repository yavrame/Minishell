/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:15:05 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:12:06 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_next_cmd(t_envlist *lst)
{
	char		*read;
	t_command	*command;
	char		**buff;
	int			i;

	i = 0;
	read = readline("MINISHELL > ");
	if (!read)
	{
		printf("exit");
		exit(1);
	}
	if (ft_strlen(read) > 0)
		add_history(read);
	read = get_environment(read, lst, 0);
	buff = split_args(NULL, read);
	if (!error_checking(buff))
		return (NULL);
	if (!buff || !buff[0])
		return (NULL);
	free(read);
	command = get_command(buff, -1, 0, lst);
	return (command);
}

static void	free_cmd(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	free(command->program);
	while (command->args && command->args[i])
		free(command->args[i++]);
	i = 0;
	while (command->execve[i])
		free(command->execve[i++]);
	while (command->files)
	{
		free(command->files->file);
		free(command->files);
		command->files = command->files->next;
	}
	free(command->execve);
	free(command->args);
	free(command->options);
	free(command->redirection);
	free(command);
	command = command->next;
	free_cmd(command);
}

static void	command_roots(t_command *command, t_envlist *lst)
{
	g_variable.is_running = 1;
	if (command->next || command->redirection)
		pipe_search(command, lst);
	else
		execve_builtin(command, lst);
	g_variable.is_running = 0;
}

static void	ft_exit(t_command *command)
{
	if (command && command->program && !ft_strcmp(command->program, "exit"))
	{
		write(1, "exit\n", 5);
		free_cmd(command);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	t_envlist	*lst;

	(void)argc;
	(void)argv;
	lst = init_environment_list(envp);
	signal_search();
	while (1)
	{
		command = get_next_cmd(lst);
		ft_exit(command);
		if (command)
			command_roots(command, lst);
		free_cmd(command);
		command = NULL;
	}
	rl_clear_history();
	return (0);
}
