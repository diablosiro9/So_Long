/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:21:04 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 16:45:15 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../includes/so_long.h"

char	**filling(char **tab, char c, t_point size, int colonne, int ligne)
{
	if (colonne < 0 || ligne < 0 || colonne >= size.y || ligne >= size.x)
		return (tab);
	if (tab[colonne][ligne] == 'F' || tab[colonne][ligne] == '1')
		return (tab);
	tab[colonne][ligne] = 'F';
	tab = filling(tab, c, size, colonne - 1, ligne);
	tab = filling(tab, c, size, colonne + 1, ligne);
	tab = filling(tab, c, size, colonne, ligne - 1);
	tab = filling(tab, c, size, colonne, ligne + 1);
	return (tab);
}

char	**filling_reverse(char **tab, char c, t_point size, int colonne, int ligne)
{
	if (colonne < 0 || ligne < 0 || colonne >= size.y || ligne >= size.x)
		return (tab);
	if (tab[colonne][ligne] == '0' || tab[colonne][ligne] == '1' || tab[colonne][ligne] == 'P')
		return (tab);
	tab[colonne][ligne] = '0';
	tab = filling_reverse(tab, c, size, colonne - 1, ligne);
	tab = filling_reverse(tab, c, size, colonne + 1, ligne);
	tab = filling_reverse(tab, c, size, colonne, ligne - 1);
	tab = filling_reverse(tab, c, size, colonne, ligne + 1);
	return (tab);
}


t_point	*pos_collect(char **map)
{
	t_point	*tab_pos;
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	tab_pos = malloc(sizeof(t_point *) * 500);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
				tab_pos[index].y = i;
				tab_pos[index].x = j;
				index++;
			}
			j++;
		}
		i++;
	}
	return (tab_pos);
}

char	**flood_fill(char **tab, t_point size, t_point begin)
{
	char	c;

	c = tab[begin.x][begin.y];
	// printf("c == %c\n", c);
	// printf("tab[0] == %s\n", tab[0]);
	tab = filling(tab, c, size, begin.x, begin.y);
	// while(tab[i])
	// {
	// 	printf("tab[i]= %s\n", tab[i]);
	// 	i++;
	// }	
	return (tab);
}

char	**flood_fill_reverse(char **tab, t_point size, t_point begin)
{
	char	c;

	c = tab[begin.x][begin.y];
	printf("entree reverse\n");
	// printf("c == %c\n", c);
	// printf("tab[0] == %s\n", tab[0]);
	tab = filling_reverse(tab, c, size, begin.x, begin.y);
	// while(tab[i])
	// {
	// 	printf("tab[i]= %s\n", tab[i]);
	// 	i++;
	// }	
	return (tab);
}

int	checking_after_fill(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
			j++;
		}	
		i++;
	}
	return (1);
}

int	number_collect(char **map)
{
	int	i;
	int	j;
	int	tot;

	i = 0;
	j = 0;
	tot = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				tot++;
			j++;
		}
		i++;
	} 
	return (tot);
}

int	map_is_not_split(char **map, char **stock)
{
	int		i;
	t_point	pos;
	t_point save;
	t_point	*stock_pos_c;
	char	**tmp;
	
	tmp = stock;
	i = number_collect(map) - 1;
	stock_pos_c = pos_collect(map);
	pos = return_pos(map, 'P');
	save = return_pos(map, 'E');
	map[save.y][save.x] = '1';
	map[pos.y][pos.x] = '0';
	printf("oop\n");
	tmp = flood_fill(map, (t_point){ft_strlen(map[1]), max_len_map(map)}, (t_point){ pos.y , pos.x });
	printf("la ]\n");
	if (checking_after_fill(map) == 0)
		return (0);
	if (map[pos.y][pos.x] == '0')
	{
		printf("Error: Player is locked at starting. Be careful, let him free.\n");
		exit (1);
	}
	tmp = flood_fill_reverse(map, (t_point){ft_strlen(map[1]), max_len_map(map)}, (t_point){ pos.y , pos.x });
	printf("ici\n");
	while (i + 1)
	{
		map[stock_pos_c[i].y][stock_pos_c[i].x] = 'C';
		i--;
	}
	printf("sorti\n");
	map[pos.y][pos.x] = 'P';
	map[save.y][save.x] = 'E';
	free(stock_pos_c);
	return (1); 
}
