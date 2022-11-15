/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:21:37 by pharmund          #+#    #+#             */
/*   Updated: 2021/11/10 19:33:10 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (src[size])
		size += 1;
	if (dstsize < 1)
		return (size);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src [i];
		i += 1;
	}
	dst [i] = '\0';
	return (size);
}
