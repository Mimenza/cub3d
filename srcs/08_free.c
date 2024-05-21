/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:54:46 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/21 10:34:59 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This functions frees a double ptr.
void	ft_free_doubleptr(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_map(t_map *map)
{
	free(map->ea_texture);
	free(map->no_texture);
	free(map->so_texture);
	free(map->we_texture);
}

long	ft_atol(const char *str, int *control)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		*control = false;
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if ((str[i] == ',' || str[i] == '\n') && (num <= 255))
		return (num);
	if ((str[i] != '\0' || ft_strlen(str) == 0 || (str[i] == '\0'\
	&& (str[i - 1] == '-' || str[i - 1] == '+'))))
		*control = false;
	return (num);
}
