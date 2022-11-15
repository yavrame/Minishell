/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:43:45 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:15:54 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cltr_c(int sig)
{
	printf("\n");
	g_variable.g_exites = 128 + sig;
	if (!g_variable.is_running)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	signal_search(void)
{
	signal(SIGINT, cltr_c);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
