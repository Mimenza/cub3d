/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:54:46 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/15 12:58:31 by emimenza         ###   ########.fr       */
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
