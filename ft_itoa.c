/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:09:41 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 13:47:28 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static long int	ft_noneg(long int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static int	ft_intlen(long int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * (-1);
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	int			sign;
	long int	nb;
	char		*str;

	nb = n;
	sign = 0;
	len = ft_intlen(nb);
	if (nb < 0)
		sign = -1;
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + ft_noneg(nb % 10);
		nb = ft_noneg(nb / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
