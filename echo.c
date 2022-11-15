/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:02:09 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:04:26 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_command(t_command *command)
{
	int	i;
	int	tablen;

	tablen = tab_len(command->args);
	i = 0;
	if (!command->args[0] && !command->options)
		printf("\n");
	else if (command->options && !ft_strcmp(command->options, "-n"))
	{
		while (!ft_strcmp(command->args[i], "-n"))
			i++;
		while (i < tablen - 1)
			printf("%s ", command->args[i++]);
		if (tablen >= 1)
			printf("%s", command->args[i]);
	}
	else if (!command->options && command->args)
	{
		while (i < tablen - 1)
			printf("%s ", command->args[i++]);
		if (tablen >= 1)
			printf("%s\n", command->args[i]);
	}
	return (0);
}
