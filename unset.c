/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:29:57 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:20:24 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_var_from_env(t_envlist *lst, char *tab)
{
	while (lst != NULL)
	{
		if (lst->next && !ft_strcmp(lst->next->var_name, tab))
		{
			free(lst->next);
			lst->next = lst->next->next;
			return ;
		}
		lst = lst->next;
	}
}

int	unset_builtin(t_command *commad, t_envlist *lst)
{
	int			tablen;
	int			i;
	t_envlist	*tmp;

	if (!commad->args)
		return (1);
	i = 0;
	tablen = tab_len(commad->args);
	while (i < tablen)
	{
		tmp = lst;
		del_var_from_env(tmp, commad->args[i]);
		i++;
	}
	return (0);
}
