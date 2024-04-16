/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:49:15 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/15 15:42:09 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../libs/minilibx/mlx.h"
# include "../libs/gnl/get_next_line.h"
# include "../libs/Libft/libft.h"
// ----------------------------------
// MACROS
# define PX 50
// Key Codes for MacOS
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_LEFT	123
# define KEY_RIGHT	124

// Assets location
# define IMG_COUNT	20

// ----------------------------------

typedef struct s_coords
{
	int		a;
	int		b;
	int		r;
	int		l;
}			t_coords;

typedef struct s_size
{
	int		w;
	int		h;
}			t_size;

typedef struct s_position
{
	int		x;
	int		y;
}			t_position;

// store all information about the window
typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_size	*size;
	void	*img[IMG_COUNT];
}			t_window;

// store all information about the map
typedef struct s_map
{
	char	**grid;
	t_size	*size;
	int		created;
}			t_map;

//store all the information about the player
typedef struct s_player
{
	t_position	pos;
	int			angle;
}				t_player;

// store all information about the game
typedef struct s_game
{
	t_window	window;
	t_map		map;
	t_player	p;
	int			created;
}			t_game;

#endif


//00_MAIN

//01_GAME
t_game			ft_create_game(char *strmap, t_game *game);

//02_MAP
t_map			ft_create_map(char *strmap);

//03_MAP_UTILS1
int				ft_reachable(char **grid, char *strmap);
int				ft_count_item(char c, int *player);
int				ft_check_item(char c, int *player);

//04_MAP_UTILS2
int				ft_create_grid(char *strmap, char ***grid);
int				ft_map_coll(char **grid);
void			ft_replace_p(char ***p_grid);

//05_WINDOW
t_window	ft_new_window(void *mlx, int widht, int height, char *name);
//06_HOOKS

//07_UTILS

//08_FREE
void		ft_free_doubleptr(char **grid);

//09_ERROR
void		ft_print_error(int type);

//10_PRINT_MAP
void		ft_print_grid(char **grid);