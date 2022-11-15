/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:36:01 by pharmund          #+#    #+#             */
/*   Updated: 2021/10/11 15:36:01 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*bytes;

	bytes = malloc(size * count);
	if (bytes == NULL)
		return (bytes);
	ft_bzero(bytes, size * count);
	return (bytes);
}
