/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:05 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int mouse_movement(int x, int y, t_game *game)
{
	t_player *player = game->p;
	static int prev_mouse_x = 0;
	int curr_mouse_x = x;

	int delta_x = curr_mouse_x - prev_mouse_x;

	double sensitivity = 0.01;

	player->rad += delta_x * sensitivity;

	ft_print_map(game);

	prev_mouse_x = curr_mouse_x;

	return 0;
}

void	key_press_hook_aux(t_game *game, double move_x, double move_y, int mode)
{
	int			i;
	t_player	*player;

	player = game->p;
	i = 0;

	while (i < 10)
	{
		//printf("%i\n", i);
		if (mode == 1)
		{
			player->pos.x -= move_x * (MOVE_STEP / 10);
			player->pos.y -= move_y * (MOVE_STEP / 10);
		}
		else
		{
			player->pos.x += move_x * (MOVE_STEP / 10);
			player->pos.y += move_y * (MOVE_STEP / 10);
		}
		//printf(" %f %f\n", game->p->pos.x, game->p->pos.y);
		//usleep(300);
		ft_print_map(game);
		i++;
	}
}

int  key_press_hook(int keycode, t_game *game)
{
	t_player	*player;

	player = game->p;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_RIGHT) // Girar a la derecha
	{
		player->rad -= R_SPEED;
		if (player->rad < 0)
			player->rad += 2 * M_PI;
		ft_print_map(game);
	}
	else if (keycode == KEY_LEFT) // Girar a la izquierda
	{
		player->rad += R_SPEED;
		if (player->rad >= 2 * M_PI)
			player->rad -= 2 * M_PI;
		ft_print_map(game);
	}
	else if (keycode == KEY_A) // Mover hacia la izquierda
		key_press_hook_aux(game, cos(player->rad + M_PI / 2), sin(player->rad + M_PI / 2), 1);
	else if (keycode == KEY_S) // Mover hacia atrás
		key_press_hook_aux(game, cos(player->rad), sin(player->rad), 1);
	else if (keycode == KEY_D) // Mover hacia la derecha
		key_press_hook_aux(game, cos(player->rad + M_PI / 2), sin(player->rad + M_PI / 2), 2);
	else if (keycode == KEY_W) // Mover hacia adelante
		key_press_hook_aux(game, cos(player->rad), sin(player->rad), 2);
}
