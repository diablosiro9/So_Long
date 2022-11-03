/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:45:28 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 16:45:11 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	checking_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '\n')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			ft_error("Error: No man's land on the map. Map can't be played.\n");
		i++;
	}
}

char	**stocking_map(char **map, int fd)
{
	int	i;
	char	save[2];
	int		size;
	char	*line;

	i = 0;
	size = read(fd, save, 1);
	save[1] = '\0';
	line = ft_strdup(save);
	size = read(fd, save, 1);
	save[1] = '\0';
	while (size > 0)
	{
		line = ft_strjoin(line, save);
		size = read(fd, save, 1);
		save[1] = '\0';
	}
	checking_map_line(line);
	map = ft_split(line, '\n');
	return (map);
}

int	key_hook(int keycode, t_play *play)
{
	return (gestion_key_input(play, keycode));
}

void	keep_open(t_play *play, char **map)
{
	(void)map;
	printf("1\n");
	play->vars->mlx = mlx_init();
	play->vars->win = mlx_new_window(play->vars->mlx, WINDOW_LEN, WINDOW_HEIGHT, "Hello world!");
	mlx_key_hook(play->vars->win, key_hook, play);
	mlx_loop(play->vars->mlx);
}

void	do_all(char **map)
{
	// char	**map
	t_play	*play;

	play = malloc(sizeof(t_play));
	play->vars = malloc(sizeof(t_vars));
	play->vars->map = map;
	play->map = map;
	play->player = return_pos(map, 'P');
	play->leave = return_pos(map, 'E');
	play->direct = 0;
	play->counter = 0;
	printf("play->leave.x == %d, .y == %d\n", play->leave.x, play->leave.y);
	printf("play->player.x == %d, .y == %d\n", play->player.x, play->player.y);
	play->vars->mlx = NULL;
	play->vars->win = NULL;
	if (checking_map_is_playable(play->map) == 0)
		return ;
	else
	{
		printf("We got a solid map.\n");
		// USAGE MINILIB affichage de la map;
		keep_open(play, play->map);
		// vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
		// vars.map = map;
		// mlx_key_hook(vars.win, key_hook, &vars);
		printf("see u\n");
		// mlx_mouse_hook(vars.win, key_hook, &vars);
	}
}

void	puterror(int i)
{
	if (i == 500)
	{
		printf("No map found.\n");
		exit (1);
	}
}

int	main(int ac, char **av)
{
	int	fd;
	char	**map;
	int		hauteur_map;

	fd = 0;
	map = NULL;
	hauteur_map = 0;
	if (ac != 2)
	{
		ft_error("No map found.\n");
		return 0;
	}
	else
	{
		if (is_map(av[1]) == 1)
		{
			// printf("On a une map\n");
			fd = open(av[1], O_RDONLY);
			if (fd < 0)
				ft_error("File doesn't exist.\n");
			if (open(av[1], O_DIRECTORY) > 0)	
				ft_error("This is a directory.\n");

			// printf("le open se passe bien, fd == %d\n", fd);
			map = stocking_map(map, fd);
				// return (0);
			// else
			// {
			// 	printf("weird\n");
			// 	printf("Test = %s\n", map[0]);
			// 	printf("tu vas jusaue lq ma caille\n");
			do_all(map);
			// }
		}
	}
	return (0);
}