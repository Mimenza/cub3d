/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/14 15:19:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//0 out 1 moving
int	save_mouse_in(int mode, int data)
{
	static int res = 0;

	if (mode == 1)
		res = data;
	else
		return (res);
	return(-1);
}

int mouse_exit(int x, int y, t_game *game)
{
	// Código para manejar el evento de entrada del ratón
	(void)x;
	(void)y;
	(void)game;
	save_mouse_in(1, 0);
	return (0);
}
//Function of the mouse movement
int	mouse_movement(int x, int y, t_game *game)
{
	t_player	*player;
	static int	prev_mouse_x = 0;
	int			curr_mouse_x;
	int			delta_x;
	static	int	delay;

	(void)y;
	delay++;
	player = game->p;
	curr_mouse_x = x;
	if (prev_mouse_x == 0)
		prev_mouse_x = curr_mouse_x;
	else
		delta_x = curr_mouse_x - prev_mouse_x;
	if (0 != save_mouse_in(2, -1))
		player->rad += delta_x * 0.005;
	save_mouse_in(1, 1);
	if (delay == 5)
	{
		ft_render_map(game);
		delay = 0;
	}
	prev_mouse_x = curr_mouse_x;
	return (0);
}

static void	key_press_hook_aux(t_game *game, double move_x, double move_y, int mode)
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
	if (game->map.grid[(int)tmp_y][(int)tmp_x] != '1' && \
	game->map.grid[(int)tmp_y][(int)tmp_x] != ' ')
	{
		player->pos.x = tmp_x;
		player->pos.y = tmp_y;
	}
}

//Main function of the key hooks
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
	return (ft_render_map(game), 0);
}
