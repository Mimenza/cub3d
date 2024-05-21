/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/21 11:06:26 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static void	key_press_aux(t_game *game, double move_x, double move_y, int mode)
{
	t_player	*player;
	double		tmp_x;
	double		tmp_y;
	static int	move = 0;

	move++;
	if (move == 10)
		
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
	if (game->map.grid[(int)(tmp_y)][(int)(tmp_x)] != '1' && \
	game->map.grid[(int)tmp_y][(int)tmp_x] != ' ')
	{
		player->pos.x = tmp_x;
		player->pos.y = tmp_y;
	}
}

//Main function of the key hooks
int	key_press_hook(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		ft_close(g);
	if (keycode == KEY_RIGHT)
	{
		g->p->rad -= R_SPEED;
		if (g->p->rad < 0)
			g->p->rad += 2 * M_PI;
	}
	else if (keycode == KEY_LEFT)
	{
		g->p->rad += R_SPEED;
		if (g->p->rad >= 2 * M_PI)
			g->p->rad -= 2 * M_PI;
	}
	else if (keycode == KEY_A)
		key_press_aux(g, cos(g->p->rad + M_PI / 2), \
		sin(g->p->rad + M_PI / 2), 1);
	else if (keycode == KEY_S)
		key_press_aux(g, cos(g->p->rad), sin(g->p->rad), 1);
	else if (keycode == KEY_D)
		key_press_aux(g, cos(g->p->rad + M_PI / 2), \
		sin(g->p->rad + M_PI / 2), 2);
	else if (keycode == KEY_W)
		key_press_aux(g, cos(g->p->rad), sin(g->p->rad), 2);
	return (ft_render_map(g), 0);
}
