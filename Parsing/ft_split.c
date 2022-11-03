/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:02:35 by dojannin          #+#    #+#             */
/*   Updated: 2022/10/29 14:53:20 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	ft_check_c(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	count_char_c(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			count++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	return (count);
}

static char	*ft_alloc_str(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		nb_c;
	char	**dst;

	i = 0;
	nb_c = count_char_c(s, c);
	dst = (char **)malloc(sizeof(char *) * nb_c + 1);
	if (dst == NULL)
		return (NULL);
	nb_c = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			dst[nb_c] = ft_alloc_str((s + i), c);
			nb_c++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	dst[nb_c] = NULL;
	return (dst);
}
