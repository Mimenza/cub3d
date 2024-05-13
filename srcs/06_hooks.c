/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/13 12:25:42 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	mouse_movement(int x, int y, t_game *game)
{
	t_player	*player;
	static int	prev_mouse_x;
	int			curr_mouse_x;
	int			delta_x;

	(void)y;
	player = game->p;
	curr_mouse_x = x;
	delta_x = curr_mouse_x - prev_mouse_x;
	player->rad += delta_x * 0.03;
	ft_render_map(game);
	usleep(200);
	prev_mouse_x = curr_mouse_x;
	return (0);
}

void	key_press_hook_aux(t_game *game, double move_x, double move_y, int mode)
{
	t_player	*player;
	double		tmp_x;
	double		tmp_y;

	tmp_x = 0;
	tmp_y = 0;
	player = game->p;
	if (mode == 1)
	{
		tmp_x = player->pos.x - (move_x * (MOVE_STEP / 10));
		tmp_y = player->pos.y - (move_y * (MOVE_STEP / 10));
	}
	else
	{
		tmp_x = player->pos.x + (move_x * (MOVE_STEP / 10));
		tmp_y = player->pos.y + (move_y * (MOVE_STEP / 10));
	}
	//printf("player curr x: %f e y: %f\n", player->pos.x, player->pos.y);
	//printf("player next pos x: %f e y: %f\n", tmp_x, tmp_y);
	if (game->map.grid[(int)tmp_y][(int)tmp_x] != '1' && game->map.grid[(int)tmp_y][(int)tmp_x] != ' ')
	{
		player->pos.x = tmp_x;
		player->pos.y = tmp_y;
	}
}

int	key_press_hook(int keycode, t_game *game)
{
	t_player	*p;

	p = game->p;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_RIGHT)
	{
		p->rad -= R_SPEED;
		if (p->rad < 0)
			p->rad += 2 * M_PI;
	}
	else if (keycode == KEY_LEFT)
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
	return (0);
}
