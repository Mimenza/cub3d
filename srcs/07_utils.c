/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:20:58 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/12 18:33:05 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This function creates a double ptr.
char	**ft_create_doubleptr(t_size size)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = (char **)malloc((size.h + 1) * sizeof(char *));
	if (ptr == NULL)
		return (ptr);
	return (ptr);
}

//This function copies a double ptr.
void	ft_copy_doubleptr(char **grid, char **p_grid, t_size size)
{
	int	i;

	i = 0;
	while (i <= (size.h - 1))
	{
		p_grid[i] = ft_strdup(grid[i]);
		i++;
	}
	p_grid[i] = NULL;
}
