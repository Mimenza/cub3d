/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_coordinates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:20:29 by anurtiag          #+#    #+#             */
/*   Updated: 2024/05/12 18:34:37 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

size_t	ft_mtxlen(const char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_get_player_dir(t_player **player, char **map, size_t i, size_t j)
{
	if (map[i][j] == 'N')
	{
		(*player)->rad = 270 * M_PI / 180;
	}
	else if (map[i][j] == 'S')
	{
		(*player)->rad = 90 * M_PI / 180;
	}
	else if (map[i][j] == 'E')
	{
		(*player)->rad = 0 * M_PI / 180;
	}
	else if (map[i][j] == 'W')
	{
		(*player)->rad = 180 * M_PI / 180;
	}
}

void	ft_get_player_pos(t_player **player, char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'E' || \
			map[i][j] == 'N' || map[i][j] == 'S')
			{
				ft_get_player_dir(player, map, i, j);
				(*player)->pos.x = j + 0.5;
				(*player)->pos.y = i + 0.5;
				return ;
			}
		}
	}
}

void	get_player(t_game *game)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return ;
	game->p = player;
	ft_get_player_pos(&player, game->map.grid);
	return ;
}
