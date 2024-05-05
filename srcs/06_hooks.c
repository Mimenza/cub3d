/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/05 14:52:34 by anurtiag         ###   ########.fr       */
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

int  key_press_hook(int keycode, t_game *game)
{
	t_player	*player;

	player = game->p;

	system("clear");
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	if (keycode == KEY_RIGHT) // Girar a la derecha
	{
		player->rad -= R_SPEED;
		if (player->rad < 0)
			player->rad += 2 * M_PI;
	}
	else if (keycode == KEY_LEFT) // Girar a la izquierda
	{
		player->rad += R_SPEED;
		if (player->rad >= 2 * M_PI)
			player->rad -= 2 * M_PI;
	}
	else if (keycode == KEY_A) // Mover hacia la izquierda
	{
		player->pos.x -= cos(player->rad + M_PI / 2) * MOVE_STEP;
		player->pos.y -= sin(player->rad + M_PI / 2) * MOVE_STEP;
	}
	else if (keycode == KEY_S) // Mover hacia atrás
	{
		player->pos.x -= cos(player->rad) * MOVE_STEP;
		player->pos.y -= sin(player->rad) * MOVE_STEP;
	}
	else if (keycode == KEY_D) // Mover hacia la derecha
	{
		player->pos.x += cos(player->rad + M_PI / 2) * MOVE_STEP;
		player->pos.y += sin(player->rad + M_PI / 2) * MOVE_STEP;
	}
	else if (keycode == KEY_W) // Mover hacia adelante
	{
		player->pos.x += cos(player->rad) * MOVE_STEP;
		player->pos.y += sin(player->rad) * MOVE_STEP;
	}
	//printf("El radian es de %f y la posición %f %f\n", player->rad, player->pos.x, player->pos.y);
	ft_print_map(game);
}
