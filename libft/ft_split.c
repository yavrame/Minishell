/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:54:27 by pharmund          #+#    #+#             */
/*   Updated: 2021/11/01 13:54:27 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_space(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (-1);
}

static int	count_words(const char *str, char set)
{
	int	i;
	int	letters;

	letters = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == set || str[i + 1] == '\0')
			&& (str[i] == set || str[i] == '\0') == 0)
			letters += 1;
		i += 1;
	}
	return (letters);
}

static void	write_word(char *dest, const char *src, char set)
{
	int	i;

	i = 0;
	while ((src[i] == set || src[i] == '\0') == 0)
	{
		dest[i] = src[i];
		i += 1;
	}
	dest[i] = '\0';
}

static int	make_split(char **array, const char *str, char set)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] == set || str[i] == '\0')
			i += 1;
		else
		{
			j = 0;
			while ((str[i + j] == set || str[i + j] == '\0') == 0)
				j += 1;
			array[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (array[word] == NULL)
				return (free_space(array, word - 1));
			write_word(array[word], str + i, set);
			i += j;
			word += 1;
		}
	}
	return (0);
}

char	**ft_split(const char *str, char c)
{
	char	**array;
	int		words;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
		return (NULL);
	array[words] = 0;
	if (make_split(array, str, c) == -1)
		return (NULL);
	return (array);
}
