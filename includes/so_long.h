/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:44:42 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/03 16:38:49 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mlx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define WINDOW_LEN 800
# define WINDOW_HEIGHT 600

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	char	**map;
}				t_vars;

typedef	struct s_point
{
	int	x;
	int	y;
}t_point;

typedef	struct s_data
{
	int		x;
	int		y;
	char	c;
	/* data */
}t_data;

typedef struct s_play
{
	t_vars	*vars;
	char	**map;
	t_point	player;
	t_point leave;
	void	*exit;
	void	*back;
	void	*img;
	void	*perso;
	void	*collec;
	int		width_exit;
	int		height_exit;
	int		width_back;
	int		height_back;
	int		width_collec;
	int		height_collec;
	int		width_perso;
	int		height_perso;
	int		img_width;
	int		img_height;
	int		counter;
	int		direct;
}t_play;

// POUR GNL
int		int_strlen(char *s);
int	max_len_map(char **map);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*make_save(int fd, char *save, char *buffer);
char	**ft_split(char const *s, char c);
// static char	*ligne(char *save);
// static char	*newline(char *save);

int	checking_str(char *str, int	hauteur_map);
t_point	return_pos(char	**tab, char c);
int	doublon(char **map, char c, t_point pos);
int	map_is_not_split(char **map, char **stock);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	checking_map_is_playable(char **map);
void	ft_putstr(char *str);
void	print_map(char **map);
int	is_map(char *str);
void	ft_error(char *msg);
char	**copy_map(char **map, char **copy);
char	*ft_itoa(int n);

//Inputs
int	gestion_key_input(t_play *play, int keycode);

#endif