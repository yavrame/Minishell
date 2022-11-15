/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:36:12 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:08:34 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **others)
{
	int	i;

	i = 0;
	while (others[i])
		free(others[i++]);
	free(others);
}

int	print_environment(t_envlist *lst)
{
	if (!lst)
		return (1);
	while (lst != NULL)
	{
		printf("declare -x %s=\"%s\"\n", lst->var_name, lst->var_content);
		lst = lst->next;
	}
	return (0);
}

int	env_builtin(t_envlist *lst)
{
	if (!lst)
		return (1);
	while (lst != NULL)
	{
		printf("%s=%s\n", lst->var_name, lst->var_content);
		lst = lst->next;
	}
	return (0);
}
