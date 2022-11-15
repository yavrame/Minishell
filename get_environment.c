/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:06:13 by pharmund          #+#    #+#             */
/*   Updated: 2022/06/29 17:27:03 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*finder(char *find, t_envlist *lst)
{
	if (!ft_strcmp(find, "?"))
		return (ft_itoa(g_variable.g_exites));
	while (lst)
	{
		if (!ft_strcmp(find, lst->var_name))
		{
			free(find);
			return (ft_strdup(lst->var_content));
		}
		lst = lst->next;
	}
	return (NULL);
}

static char	*cutter(char *tofind, int *index)
{
	int		len;
	char	*ret;
	int		i;

	i = 0;
	len = 0;
	while (tofind[len] && (ft_isalnum(tofind[len])
			|| tofind[len] == '_' || tofind[len] == '?'))
		len++;
	ret = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		ret[i] = tofind[i];
		i++;
	}
	ret[i] = 0;
	(*index) += ft_strlen(ret);
	return (ret);
}

static char	*joiner(char *s1, char *s2, t_envlist *lst)
{
	int		len;
	int		i;
	char	*ret;

	i = -1;
	len = 0;
	s2 = finder(s2, lst);
	if (s2 == NULL)
	{
		free(s2);
		return (s1);
	}
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (s1 != NULL)
	{
		while (s1[++i])
			ret[i] = s1[i];
	}
	while (s2[len])
		ret[i++] = s2[len++];
	ret[i] = 0;
	free(s1);
	free(s2);
	return (ret);
}

static char	*add_char(char *s, char c)
{
	int		i;
	char	*ret;

	i = 0;
	if (!s)
	{
		ret = malloc(sizeof(char) * 2);
		ret[0] = c;
		ret[1] = 0;
		return (ret);
	}
	ret = malloc(sizeof(char) * ft_strlen(s) + 2);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i++] = c;
	ret[i] = 0;
	free(s);
	return (ret);
}

char	*get_environment(char *read, t_envlist *lst, int i)
{
	char	*ret;
	int		count1;
	int		count2;
	char	*tmp;

	ret = NULL;
	count1 = 0;
	count2 = 0;
	while (read[i])
	{
		if (read[i] == '\'' && count2 % 2 == 0)
			count1++;
		if (read[i] == '\"' && count1 % 2 == 0)
			count2++;
		if (read[i] == '$' && count1 % 2 == 0)
		{
			tmp = cutter(&read[++i], &i);
			ret = joiner(ret, tmp, lst);
		}
		else
			ret = add_char(ret, read[i++]);
	}
	free(read);
	return (ret);
}
