/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/16 12:54:37 by emimenza         ###   ########.fr       */
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
	win = ft_new_window(mlx, 25 * PXW, 10 * PXW, "CUB3D");
	game.window = win;
	ft_print_map(&game);
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
