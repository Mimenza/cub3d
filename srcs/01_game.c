/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/30 14:07:36 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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
	get_player(&game);
	ft_replace_p(&(game.map.grid));
	ft_print_map(&game);
	//mlx_hook(mlx, 2, 0, *key_press_hook, &game);
	mlx_hook(game.window.win, 2, 0, key_press_hook, &game); //WINDOW HOLD
	//mlx_key_hook(game.window.win, *key_press_hook, &game); //LINUX  TAP
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
