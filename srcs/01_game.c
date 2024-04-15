/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/15 13:30:04 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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
	return (*game);
}
