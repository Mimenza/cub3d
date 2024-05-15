/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/15 12:37:27 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This functions loads the imgs.
static t_imgs	*ft_load_img(t_game *game, char *path)
{
	int		h;
	int		w;
	t_imgs	*img;

	img = (t_imgs *)malloc(sizeof(t_imgs));
	if (img == NULL || path == NULL)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->window.mlx, path, &w, &h);
	if (img->img == NULL)
	{
		printf("\033[1;31m [KO] \033[0m \
		\nError loading the img with the path: %s\n", path);
		free(img);
		return (NULL);
	}
	img->addrs = (int *)mlx_get_data_addr(img->img, &img->bpp, \
	&img->line_len, &img->endian);
	return (img);
}

static int	ft_cpy_imgs(char files[IMG_COUNT][42], t_game *game)
{
	int		i;
	t_imgs	*img;

	i = IMG_COUNT - 1;
	while (i >= 0)
	{
		img = ft_load_img(game, files[i]);
		if (img == NULL)
		{
			while (++i < IMG_COUNT)
			{
				free(game->window.imgs[i]->img);
				free(game->window.imgs[i]);
			}
			return (0);
		}
		game->window.imgs[i] = img;
		i--;
	}
	return (1);
}

//This function loads the imgs path into the array.
static int	ft_load_imgs(t_game *game)
{
	char	files[IMG_COUNT][42];

	printf("LOADING THE IMGS...");
	ft_strlcpy(files[0], game->map.no_texture, 41);
	ft_strlcpy(files[1], game->map.so_texture, 41);
	ft_strlcpy(files[2], game->map.ea_texture, 41);
	ft_strlcpy(files[3], game->map.we_texture, 41);
	if (ft_cpy_imgs(files, game) == 0)
		return (ft_free_doubleptr(game->map.grid), free(game->window.mlx), \
	free(game->window.win), free(game->window.img), free(game->window.size), \
		free_map(&game->map), free(game->map.size), 0);
	return (ft_print_ok(), 1);
}

//Main function which starts the game.
static void	ft_start_game(t_game *game)
{
	t_window	win;
	void		*mlx;

	mlx = mlx_init();
	if (!mlx)
	{
		ft_print_error(1);
		exit(EXIT_FAILURE);
	}
	
	win = ft_new_window(mlx, (16 * PXW), (9 * PXW), "CUB3D");
	game->window = win;
	if (ft_load_imgs(game) == 0)
		return ;
	get_player(game);
	ft_replace_p(&(game->map.grid));
	ft_render_map(game);
	mlx_hook(game->window.win, 2, (1L << 0), key_press_hook, game);
	mlx_hook(game->window.win, 6, (1L << 6), mouse_movement, game);
	mlx_hook(game->window.win, 8, (1L << 5), mouse_exit, game);
	mlx_hook(game->window.win, 17, 0, ft_close, game);
	mlx_loop(game->window.mlx);
}

//Main function which creates the game struct.
t_game	ft_create_game(char *strmap, t_game *game)
{
	t_map	map;

	map = ft_create_map(strmap);
	if (map.created == 0)
	{
		game->created = 0;
		return (*game);
	}
	game->map = map;
	game->created = 1;
	ft_start_game(game);
	return (*game);
}
