/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/08 22:35:10 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int mouse_movement(int x, int y, t_game *game)
{
	t_player	*player;
	static int	prev_mouse_x;
	int			curr_mouse_x;
	int			delta_x;
	
	player = game->p;
	curr_mouse_x = x;

	delta_x = curr_mouse_x - prev_mouse_x;
		player->rad += delta_x * 0.03;
	ft_render_map(game);
	prev_mouse_x = curr_mouse_x;
	return (0);
}

void	key_press_hook_aux(t_game *game, double move_x, double move_y, int mode)
{
	t_player	*player;

	player = game->p;
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
}

int  key_press_hook(int keycode, t_game *game)
{
	t_player	*p;

	p = game->p;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_RIGHT) // Girar a la derecha
	{
		p->rad -= R_SPEED;
		if (p->rad < 0)
			p->rad += 2 * M_PI;
	}
	else if (keycode == KEY_LEFT) // Girar a la izquierda
	{
		p->rad += R_SPEED;
		if (p->rad >= 2 * M_PI)
			p->rad -= 2 * M_PI;
	}
	else if (keycode == KEY_A)
		key_press_hook_aux(game, cos(p->rad + M_PI / 2), sin(p->rad + M_PI / 2), 1);
	else if (keycode == KEY_S)
		key_press_hook_aux(game, cos(p->rad), sin(p->rad), 1);
	else if (keycode == KEY_D)
		key_press_hook_aux(game, cos(p->rad + M_PI / 2), sin(p->rad + M_PI / 2), 2);
	else if (keycode == KEY_W)
		key_press_hook_aux(game, cos(p->rad), sin(p->rad), 2);
	ft_render_map(game);
}
