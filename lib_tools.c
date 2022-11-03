/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:40:41 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 09:10:51 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while ((c1[i] != '\0' || c2[i] != '\0') && i < n)
	{
		if ((c1[i] - c2[i]) != 0)
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(0, &str[i], 1);
		i++;
	}
}

int	doublon(char **map, char c, t_point pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("la\n");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c && (i != pos.y || j != pos.x))
				return (0);
			j++;
		}
		i++;
	}
	printf("plus la\n");
	return (1);
}

void	ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (dstsize != 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

