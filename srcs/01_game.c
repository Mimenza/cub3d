/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/06 16:50:02 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This functions loads the imgs.
static t_imgs	*ft_load(t_game *game, char *path, int i)
{
	int		h;
	int		w;
	t_imgs	*img;

	img = (t_imgs *)malloc(sizeof(t_imgs));
	if (!img || path == NULL)
	{
		printf("ERROR\n");
		return (NULL);
	}

	printf("path %s\n", path);
	// printf("en la vuelta %d hemos maloqueado un %p\n", i, img);
	img->img = mlx_xpm_file_to_image(game->window.mlx, path, &w, &h);
	img->addrs = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (img->img == NULL)
	{
		printf("ERROR LOADING IMGS%i\n", i);
		return (NULL);
	}
	return(img);
}

static void	ft_cpy_imgs(char files[IMG_COUNT][42], t_game *game)
{
	int	i;

	i = IMG_COUNT - 1;
	while (i >= 0)
	{
		game->window.imgs[i] = ft_load(game, files[i], i);
		i--;
	}
}

//This function loads the imgs path into the array.
static void	ft_load_imgs(t_game *game)
{
	char	files[IMG_COUNT][42];

	ft_strlcpy(files[0], game->map.no_texture, 41);
	ft_strlcpy(files[1], game->map.so_texture, 41);
	ft_strlcpy(files[2], game->map.ea_texture, 41);
	ft_strlcpy(files[3], game->map.we_texture, 41);
	// ft_strlcpy(files[4], GREYSTONE, 41);
	// ft_strlcpy(files[5], MOSSY, 41);
	// ft_strlcpy(files[6], PILLAR, 41);
	// ft_strlcpy(files[7], PURPLESTONE, 41);
	// ft_strlcpy(files[8], REDBRICK, 41);
	// ft_strlcpy(files[9], WOOD, 41);
	ft_cpy_imgs(files, game);
}

//Main function which starts the game.
static void	ft_start_game(t_game game)
{
	void		*mlx;
	t_window	win;

	mlx = mlx_init();
	if (!mlx)
	{
		ft_print_error(1);
		exit(EXIT_FAILURE);
	}
	win = ft_new_window(mlx, (16 * PXW), (9 * PXW), "CUB3D");
	game.window = win;
	ft_load_imgs(&game);
	get_player(&game);
	ft_replace_p(&(game.map.grid));
	ft_print_map(&game);
	//mlx_hook(mlx, 2, 0, *key_press_hook, &game);
	//mlx_hook(game.window.win, 2, 0, key_press_hook, &game); //WINDOW HOLD
	//mlx_hook(game.window.win, 6, 0, mouse_movement, &game);
	mlx_key_hook(game.window.win, *key_press_hook, &game); //LINUX  TAP
	mlx_loop(mlx);
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
	ft_start_game(*game);
	return (*game);
}
