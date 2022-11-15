/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharmund <pharmund@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:57:36 by pharmund          #+#    #+#             */
/*   Updated: 2021/10/22 12:06:22 by pharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	int		size;
	long	tmp;

	tmp = n;
	size = 1;
	if (tmp < 0)
	{
		size++;
		tmp = -tmp;
	}
	while (tmp >= 10)
	{
		size++;
		tmp /= 10;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	nbr;
	int		i;
	int		len;

	i = 0;
	len = ft_get_size(nb);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
		str[0] = '-';
	nbr = nb;
	if (nbr < 0)
		nbr = -nbr;
	str[len - i++] = '\0';
	while (nbr >= 10)
	{
		str[len - i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len - i++] = (nbr % 10) + '0';
	return (str);
}
