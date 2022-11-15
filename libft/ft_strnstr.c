/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:04:52 by pharmund          #+#    #+#             */
/*   Updated: 2021/10/11 12:04:52 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	pos;
	size_t	i;

	if (!*to_find)
		return ((char *)str);
	pos = 0;
	while (str[pos] != '\0' && pos < len)
	{
		if (str[pos] == to_find[0])
		{
			i = 1;
			while (to_find[i] != '\0' && str[pos + i] == to_find[i] && \
			(pos + i) < len)
				++i;
			if (to_find[i] == '\0')
				return ((char *)&str[pos]);
		}
		pos += 1;
	}
	return (0);
}
