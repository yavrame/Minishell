/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:54:05 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:50:59 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_builtin(char *cmd)
{
	int			i;
	static char	*all[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit"};

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(all[i], cmd))
			return (all[i]);
		i++;
	}
	return (NULL);
}
