/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:33:17 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 18:07:37 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_length(char *str, char quote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[++i] != quote)
		len++;
	return (len);
}

char	*redirect_as_arg(char *str)
{
	char	*ret;
	char	*tmp;
	char	*joined;
	char	ch;
	int		len;

	len = 0;
	ret = malloc(sizeof(char) * 2);
	ret[0] = 7;
	ret[1] = '\0';
	ch = str[len];
	len++;
	while (str[len] != ch)
		len++;
	tmp = malloc(sizeof(char) * len + 1);
	ft_strlcpy(tmp, str + 1, len);
	tmp[len] = '\0';
	joined = ft_strjoin(ret, tmp);
	free(ret);
	free(tmp);
	return (joined);
}
