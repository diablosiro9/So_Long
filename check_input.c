/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:51:30 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 18:01:43 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	close_w(int keycode, t_play *play)
{
	(void)keycode;
	// printf("%d\n", keycode);
	mlx_destroy_window(play->vars->mlx, play->vars->win);
	exit(0);
	return (0);
}

int	touching_esc(int keycode, t_play *play)
{
	return (close_w(keycode, play));
}

int complet_collect(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// int checking_a(char **map, t_point player, char key)
// {
// 	if (key == 'A' && (map[player.x - 1][player.y] == '0'
// 			|| map[player.x - 1][player.y] == 'C'))
// 	{
// 		map[player.x - 1][player.y] = 'P';
// 		map[player.x - 1][player.y] = '0';
// 		return (1);
// 	}
// 	if (key == 'A' && map[player.x][player.y - 1] == 'E')
// 	{
// 		if (complet_collect(map, 'C') == 1)
// 			exit(1);
// 		else
// 		{
// 			map[player.x - 1][player.y] = 'P';
// 			map[player.x - 1][player.y] = '0';
// 		}
// 		return (1);
// 	}
// 	if (key == 'A' && map[player.x - 1][player.y] == '1')
// 		return (0);
// 	return (0);
// }

int checking_moove(t_play *play, t_point save, t_point player, char key)
{
	(void)key;
	printf("entre\n");
	printf("map[save.x][save.y] == %c\n", play->map[save.y][save.x]);
	printf("Du save y = %d && x == %d\n", save.y, save.x);
	printf("map[player.x][player.y] == %c\n", play->map[player.y][player.x]);
	printf("y = %d && x == %d\n", player.y, player.x);
	if (key == 'A')
		play->direct = 1;
	else if (key == 'D')
		play->direct = 0;
	if (play->map[player.y][player.x])
	{
		if (play->map[player.y][player.x] == '1')
			return (0);
		else if (play->map[player.y][player.x] == '0' || play->map[player.y][player.x] == 'C')
		{
			play->map[player.y][player.x] = 'P';
			play->map[save.y][save.x] = '0';
			play->player.y = player.y; 
			play->player.x = player.x;
			play->counter = play->counter + 1;
		}
		else if (play->map[player.y][player.x] == 'E')
		{
			if (complet_collect(play->map, 'C') == 1)
			{
				ft_putstr("End's Game!\n");
				exit(1);
			}
			else
				return (0);
		}
	}
	printf("fin checking moove\n");
	return (1);
}

int	checking_possibility(t_play *play, t_point player, char key)
{
	t_point	futur_pos;
	int		i;

	i = 0;
	futur_pos.x = player.x;
	futur_pos.y = player.y;
	// printf("map[save.x][save.y] == %c\n", play->map[player.x][player.y]);
	// printf("map[player.x][player.y] == %c\n", play->map[player.x][player.y -1]);
	printf("COUNTER == %d\n", play->counter);
	printf("KEY == %c\n", key);
	if (key == 'W')
	{
		printf("la\n");
		return (checking_moove(play, player, (t_point){futur_pos.x, futur_pos.y - 1}, key));
	}
	else if (key == 'A')
		return (checking_moove(play, player, (t_point){futur_pos.x - 1, futur_pos.y}, key));
	else if (key == 'S')
		return (checking_moove(play, player, (t_point){futur_pos.x, futur_pos.y + 1}, key));
	else if (key == 'D')
		return (checking_moove(play, player, (t_point){futur_pos.x + 1, futur_pos.y}, key));
	else
		return (0);
}

int	touching_w(int keycode, t_play *play)
{
	t_point		pos;

	pos = play->player;
	// (void)vars;
	printf("pos.y -=- %d\n", pos.y);
	printf("pos.x -=- %d\n", pos.x);
	printf("Keycode == %d\n", keycode);
	if (keycode == 13 || keycode == 126)
		return (checking_possibility(play, play->player , 'W'));
	else if (keycode == 0 || keycode == 123)
	{
		play->direct = 1;
		return (checking_possibility(play, play->player, 'A'));
	}
	else if (keycode == 1 || keycode == 125)
	{
		return (checking_possibility(play, play->player, 'S'));
	}
	else if (keycode == 2 || keycode == 124)
	{
		play->direct = 0;
		return (checking_possibility(play, play->player, 'D'));
	}
	return (0);
}

void	put_map(t_play *play, char **map, t_vars *vars)
{
	int	i;
	int	j;
	void		*exit;
	void		*back;
	void		*img;
	void		*perso;
	void		*collec;
	void		*walk_perso;
	int			width_exit;
	int			height_exit;
	int			width_back;
	int			height_back;
	int			width_collec;
	int			height_collec;
	int			width_perso;
	int			height_perso;
	int			img_width;
	int			img_height;
	int			width_wp;
	int			height_wp;
	void		*down_perso;
	int			width_down;
	int			height_down;
	void		*left_perso;
	int			width_left;
	int			height_left;
	void		*walk_left;
	int			width_wl;
	int			height_wl;
	void		*dust;
	int			width_dust;
	int			height_dust;
	char		*counter;
	int test;
	
	test = 0;
	i = 0;
	j = 0;
	counter = ft_itoa(play->counter);
	printf("COUNTER DU ITOA === %s\n", counter);
	img = mlx_xpm_file_to_image(vars->mlx, "Xpm/wall.xpm", &img_width, &img_height);
	perso = mlx_xpm_file_to_image(vars->mlx, "Xpm/Dude_Monster.xpm", &width_perso, &height_perso);
	exit = mlx_xpm_file_to_image(vars->mlx, "Xpm/Door.xpm", &width_exit, &height_exit);
	collec = mlx_xpm_file_to_image(vars->mlx, "Xpm/Monster-Egg.xpm", &width_collec, &height_collec);
	back = mlx_xpm_file_to_image(vars->mlx, "Xpm/Grass.xpm", &width_back, &height_back);
	walk_perso = mlx_xpm_file_to_image(vars->mlx, "Xpm/Monster_walk.xpm", &width_wp, &height_wp);
	down_perso =  mlx_xpm_file_to_image(vars->mlx, "Xpm/Monsterdown.xpm", &width_down, &height_down);
	left_perso =  mlx_xpm_file_to_image(vars->mlx, "Xpm/Monsterleft.xpm", &width_left, &height_left);
	walk_left =  mlx_xpm_file_to_image(vars->mlx, "Xpm/WalkLeft.xpm", &width_wl, &height_wl);
	dust =  mlx_xpm_file_to_image(vars->mlx, "Xpm/Dust.xpm", &width_dust, &height_dust);
	printf("test == %d\n", test);
	i = 0;
	j = 0;
	int	start;
	int	start2;
	start = 0;
	start2 = 0;
	if (ft_strlen(map[i]) > WINDOW_LEN / 32)
	{
		printf("play->player.x == %d .y == %d\n", play->player.x, play->player.y);
		printf("LA ET WINDOW / 32 == %d\n", WINDOW_LEN / 32);
		if (play->player.x >= (WINDOW_LEN / 32) / 2)
		{
			start = play->player.x - (WINDOW_LEN / 32) / 2;
			start2 = 0;
		}
		if (play->player.y >= (WINDOW_HEIGHT / 32) / 2)
		{
			start2 = play->player.y - (WINDOW_HEIGHT / 32) / 2;
		}
	}
	printf("STARRRT == %d\n", start);
	printf("STARRRT22 == %d\n", start2);
	i = start2;
	int x = 0;
	int y = 0;
	while (map[i])
	{
		j = start;
		// printf("j == %d\n", j);
		x = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, back, x, y);
			else if (map[i][j] == '1')
			{
				mlx_put_image_to_window (vars->mlx, vars->win, img, x, y);
			}
			else if (map[i][j] == 'C')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, back, x, y);
				mlx_put_image_to_window(vars->mlx, vars->win, collec, x, y);
			}
			else if (map[i][j] == 'P')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, back, x, y);
				if (play->direct == 0)
				{
					if (j % 2 == 0)
						mlx_put_image_to_window(vars->mlx, vars->win, perso, x, y);
					else if (i % 2 == 0)
						mlx_put_image_to_window(vars->mlx, vars->win, down_perso, x, y);
					else
						mlx_put_image_to_window(vars->mlx, vars->win, walk_perso, x, y);
					
					mlx_put_image_to_window(vars->mlx, vars->win, dust, x - 12, y);
				}
				else
				{
					if (j % 2 == 0)
						mlx_put_image_to_window(vars->mlx, vars->win, left_perso, x, y);
					else
						mlx_put_image_to_window(vars->mlx, vars->win, walk_left, x, y);
				
					mlx_put_image_to_window(vars->mlx, vars->win, dust, x + 12, y);
				}
			}
			else if (map[i][j] == 'E')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, back, x, y);
				mlx_put_image_to_window(vars->mlx, vars->win, exit, x, y);
			}
			j++;
			x += 32;
		}
		i++;
		test = mlx_string_put(vars->mlx, vars->win, 5, 5, 0xFFAAFFBB, ft_itoa(play->counter));
		y += 32;
	}
}

int	gestion_key_input(t_play *play, int keycode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	
	// if ((play->player.x == save.x - 1 || play->player.x == save.x + 1) || (play->player.y == save.y + 1 || play->player.y == save.y - 1))
	// 	play->map[save.x][save.y] = 'E';
	printf("on est la\n");
	if (keycode ==  13 || keycode == 126 || keycode == 0 || keycode == 1
			|| keycode == 2 || keycode == 123 || keycode == 124 || keycode == 125 || keycode == 53)
	{
		if (keycode == 53)
		{
			ft_putstr("End's Game!\n");
			i = (touching_esc(keycode, play));
			exit(1);
		}
		printf("tes la\n");
		printf("oui\n");
		j = (touching_w(keycode, play));
		put_map(play, play->map, play->vars);
	}
	else 
		return (1);
	return (0);
}
