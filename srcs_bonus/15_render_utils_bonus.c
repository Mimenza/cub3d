/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:59:40 by anurtiag          #+#    #+#             */
/*   Updated: 2024/05/15 11:19:11 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Places a pixel
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if ((x < 0 || x > game->window.size->w) \
	|| (y < 0 || y > game->window.size->h))
		return ;
	dst = game->window.addrs + (y * game->window.line_len) \
	+ (x * (game->window.bpp / 8));
	*(unsigned int *) dst = color;
}

int	static_int(int num, int mode)
{
	static int	number = 0;

	if (mode == 0)
		number = num;
	return (number);
}

double	static_double(double num, int mode)
{
	static double	number = 0;

	if (mode == 0)
		number = num;
	return (number);
}

// Main function which prints the map into the window.
void	ft_render_map(t_game *game)
{
	int		rel_pos[2];

	rel_pos[X] = game->p->pos.x * GRID_SIZE;
	rel_pos[Y] = game->p->pos.y * GRID_SIZE;
	mlx_clear_window(game->window.mlx, game->window.win);
	draw_fov(game, rel_pos);
	mlx_put_image_to_window(game->window.mlx, \
	game->window.win, game->window.img, 0, 0);
}
