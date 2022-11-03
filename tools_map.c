/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:36:37 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 09:05:18 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("{%s}\n", map[i]);
		i++;
	}
}
int	is_map(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < int_strlen(str) - 4)
			i++;
		if (ft_strncmp(&str[i], ".ber", 4) == 0)
			return (1);
		else
			return (0); 
	}
	else
		return (0);
}

int	max_len_map(char **map)
{
	int	i;
	int j = 0;
	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			// printf("MAP[I] == %c\n", map[i][j]);
			j++;
		}
		// printf("OUI = %s\n", map[5]);
		i++;
		// printf("i == %d\n", i);
	}
	return (i);
}

t_point	return_pos(char	**tab, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		j =	0;
		while (tab[i][j])
		{
			if (tab[i][j] == c)
				return ((t_point){j, i});
			j++;
		}
		i++;
	}
	return ((t_point){5000, 5000});
}

int	checking_str(char *str, int	hauteur_map)
{
	int	i;

	i = 0;
	(void)hauteur_map;
	// printf("enntre checking str = %s\n", str);
	if (str == NULL)
		return 1;
	if (str[0] != '1' && str[ft_strlen(str) - 1] != '1')
		return (0);
	// printf("ok tu suis\n");
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'P'
				&& str[i] != 'E' && str[i] != 'C' && str[i] != '\n')
			return (0);
		else
			i++;
	}
	return (1);
}
