/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:49:15 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/11 17:55:17 by emimenza         ###   ########.fr       */
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
# define PXW 100         //variable for the window size
# define BPP 32         //bites per pixel
# define ANGLE_S -45    //fov start angle
# define ANGLE_E 45     //fov end angle
# define ITER 0.1       //number of iters of the rays (less = more)
# define RES_3D 1
# define RES 1			//scalation of the minimap (pwx % res must return 0)
# define R_SPEED 0.05    //rotation speed
# define MOVE_STEP 0.5
# define VERTICAL_WALL_COLOR 0xFF0000 // Color rojo
# define HORIZONTAL_WALL_COLOR 0x00FF00 // Color verde
# define GRID_SIZE 50

//# define M_PI 3.1415926535897932384
//450 height
//800 width

// Key Codes for MacOS
// # define KEY_ESC	53
// # define KEY_W		13
// # define KEY_A		0
// # define KEY_S		1
// # define KEY_D		2
// # define KEY_UP		126
// # define KEY_DOWN	125
// # define KEY_LEFT	124
// # define KEY_RIGHT	123

// Key Codes for Linux
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_RIGHT	65361
# define KEY_LEFT	65363

# define BLUESTONE		"./textures/bluestone.xpm"
# define COLORSTONE		"./textures/colorstone.xpm"
# define EAGLE			"./textures/eagle.xpm"
# define GREENLIGHT		"./textures/greenlight.xpm"
# define GREYSTONE		"./textures/greystone.xpm"
# define MOSSY			"./textures/mossy.xpm"
# define PILLAR			"./textures/pillar.xpm"
# define PURPLESTONE	"./textures/purplestone.xpm"
# define REDBRICK		"./textures/redbrick.xpm"
# define WOOD			"./textures/wood.xpm"

# define TREAD_FLAG 0
# define EMPTY_FLAG 1
# define G_FLAG 2
# define FD_MAP 3

// Assets location
# define IMG_COUNT	4

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
	double		x;
	double		y;
}			t_position;

typedef struct s_imgs
{
	void	*img;
	int		*addrs;
	int		line_len;
	int		endian;
	int		bpp;
}			t_imgs;

// store all information about the window
typedef struct s_window
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*addrs;
	int		line_len;
	int		endian;
	int		bpp;
	t_size	*size;
	t_imgs	*imgs[IMG_COUNT];
}			t_window;

// store all information about the map
typedef struct s_map
{
	char	**grid;
	t_size	*size;
	int		created;

	int		f_color;
	int		c_color;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}			t_map;

//store all the information about the player
typedef struct s_player
{
	t_position	pos;
	double		rad;
}				t_player;

// store all information about the game
typedef struct s_game
{
	t_window	window;
	t_map		map;
	t_player	*p;
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
int				ft_create_grid(t_map *map, char *strmap, char ***grid);
int				ft_map_coll(char **grid);
void			ft_replace_p(char ***p_grid);
void			fill_w_sp(char	***grid);

//05_WINDOW
t_window		ft_new_window(void *mlx, int widht, int height, char *name);

//06_HOOKS
int				key_press_hook(int keycode, t_game *game);
int				mouse_movement(int x, int y, t_game *game);
//07_UTILS

//08_FREE
void			ft_free_doubleptr(char **grid);

//09_ERROR
void			ft_print_error(int type);
void			ft_print_ok(void);

//10_PRINT_MAP
void		ft_print_grid(char **grid);

//11_COORDINATES
void			get_player(t_game *game);
void			ft_print_grid(char **grid);
void			ft_render_map(t_game *game);

//12 PARSING
int				ft_read_file(t_map *map, char *strmap);

//13 PARSING UTILS
int		assign_data_t(char *line, char **ref);
int		assign_data_c(char *line, int *ref);
int		check_flags(int *flag, int empty_flag);
int		is_empty(char *str);
void	init_data(int (*flags)[4], t_map *map, char **grid_line, char *path);