/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:36:39 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:48:14 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static char	*get_var_content(char *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**export_split(char const *s, char c)
{
	int		j;
	char	**str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * 3);
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			str[j++] = get_var_name((char *) s, c);
			while (*(s + 1) && *(s + 1) != c)
				s++;
		}
		else
		{
			str[j++] = get_var_content((char *)++s, c);
			break ;
		}
		s++;
	}
	str[j] = NULL;
	return (str);
}

char	*free_strjoin(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}
