/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/16 16:52:41 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	key_press_hook(int keycode, t_game *game)
{
	t_player	*player;

	player = game->p;
	
	if (keycode == 124) // Girar a la derecha
		player->rad += 0.1;
	else if (keycode == 123) // Girar a la izquierda
		player->rad -= 0.1;
	else if (keycode == KEY_A)
	{
		//moverser hacia izquierda
		player->pos.x += cos(player->rad) * 0.1; // Incremento en la dirección x
		player->pos.y += sin(player->rad) * 0.1; // Incremento en la dirección y
	}
	else if (keycode == KEY_S)
	{
		//moverse hacia detras
		player->pos.x += cos(player->rad - M_PI / 2) * 0.1; // Incremento en la dirección x perpendicular
		player->pos.y += sin(player->rad - M_PI / 2) * 0.1; // Incremento en la dirección y perpendicular
	}
	else if (keycode == KEY_D)
	{
		//moverse hacia derecha
		player->pos.x -= cos(player->rad) * 0.1; // Decremento en la dirección x
		player->pos.y -= sin(player->rad) * 0.1; // Decremento en la dirección y
	}
	else if (keycode == KEY_W)
	{
		//moverse hacia delante
		player->pos.x += cos(player->rad + M_PI / 2) * 0.1; // Incremento en la dirección x perpendicular
		player->pos.y += sin(player->rad + M_PI / 2) * 0.1; // Incremento en la dirección y perpendicular
	}
	printf("el rad es de %fy la posicion %f %f\n", game->p->rad, game->p->pos.x, game->p->pos.y);
	ft_print_map(game);
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
	win = ft_new_window(mlx, 25 * PXW, 10 * PXW, "CUB3D");
	game.window = win;
	get_player(&game);
	ft_print_map(&game);
	//mlx_hook(mlx, 2, 0, *key_press_hook, &game);
	mlx_hook(game.window.win, 2, 0, key_press_hook, &game);
	//mlx_key_hook(game.window.win, *key_press_hook, &game);
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
