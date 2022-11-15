/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:49:38 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:02:14 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	*print_error(char **out)
{
	printf("export: `%s': invalid param name\n", out[0]);
	return (NULL);
}

static char	**export_spliter(t_command *command, int i)
{
	char	**out;
	char	*tmp;

	out = NULL;
	if (!command->args[i])
		return (out);
	if (!ft_strchr(command->args[i], '+'))
	{
		command->is_append = 0;
		out = export_split(command->args[i], '=');
		if (!ft_isalpha(out[0][0]))
			return (print_error(out));
		else if (!ft_strcmp(command->args[i], out[0]))
			return (NULL);
	}
	else if (ft_strchr(command->args[i], '+') != NULL)
	{
		command->is_append = 1;
		out = export_split(command->args[i], '+');
		tmp = out[1];
		out[1] = ft_strdup(ft_strchr(out[1], '=') + 1);
		free(tmp);
	}
	return (out);
}

static void	add_var_to_env(char **tab, t_envlist *lst, t_command *command)
{
	t_envlist	*tmp;
	char		*to_free;

	tmp = lst;
	to_free = NULL;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->var_name, tab[0]) && !command->is_append)
		{
			free(tmp->var_content);
			tmp->var_content = ft_strdup(tab[1]);
			return ;
		}
		else if (!ft_strcmp(tmp->var_name, tab[0]) && command->is_append == 1)
		{
			to_free = tmp->var_content;
			tmp->var_content = ft_strjoin(tmp->var_content, tab[1]);
			free(to_free);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&lst, ft_lstnew_2(tab));
}

int	export_command(t_envlist *lst, t_command *command)
{
	char	**tab;
	int		tablen;
	int		i;

	i = 0;
	tablen = 0;
	if (!command->args || !command->args[0])
		return (print_environment(lst));
	tablen = tab_len(command->args);
	while (tablen != 0)
	{
		tab = export_spliter(command, i);
		if (!tab)
			return (1);
		add_var_to_env(tab, lst, command);
		tablen--;
		i++;
		free(tab[0]);
		free(tab[1]);
		free(tab);
	}
	return (0);
}
