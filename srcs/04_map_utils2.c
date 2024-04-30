/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_map_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:32:43 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/29 20:56:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Read the file and return the line with all the content
static char	*ft_read_file(char *strmap, char *t_line)
{
	char	*path;
	int		fdmap;
	char	*line;
	char	*tmp;

	path = ft_strjoin("./maps/", strmap);
	fdmap = open(path, O_RDONLY);
	free(path);
	if (fdmap == -1)
		return (NULL);
	while (1)
	{
		line = get_next_line(fdmap);
		if (line != NULL)
		{
			tmp = ft_strdup(t_line);
			free(t_line);
			t_line = ft_strjoin(tmp, line);
			free(line);
			free(tmp);
		}
		else
			break;
	}
	close(fdmap);
	return (t_line);
}

//Create the map grid 
int	ft_create_grid(char *strmap, char ***grid)
{
	char	*file_content;

	file_content = ft_strdup("");
	file_content = ft_read_file(strmap, file_content);
	if (file_content == NULL)
	{
		ft_print_error(2);
		return (0);
	}
	*grid = ft_split(file_content, '\n');
	free(file_content);
	if (*grid == NULL)
	{
		ft_print_error(3);
		return (0);
	}
	return (1);
}

//Check the map collectables and player/exit
int	ft_map_coll(char **grid)
{
	int		x;
	int		y;
	int		player;

	printf("CHECKING ONLY 1 PLAYER...");
	y = 0;
	player = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (0 == ft_count_item(grid[y][x], &player))
				return (0);
			x++;
		}
		y++;
	}
	if (ft_check_item(0, &player) == 0)
		return (0);
	printf("\033[0;32m [OK] \033[0m\n\n");
	return (1);
}

//Replace the horientation with P
void	ft_replace_p(char ***p_grid)
{
	int			x;
	int			y;
	char		**grid;

	grid = (*p_grid);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'N' || grid[y][x] == 'S' || grid[y][x] == 'E' || grid[y][x] == 'W')
				grid[y][x] = '0';
			x++;
		}
		y++;
	}
}

//Returns the size of the longest line
static size_t	max_line(char **grid)
{
	size_t max;
	int	i;

	i = 0;
	max = 0;
	while (grid[i])
	{
		if (max < ft_strlen(grid[i]))
			max = ft_strlen(grid[i]);
		i++;
	}
	return (max);
}

//Fills the blank spaces till is rectangular
void	fill_w_sp(char	***grid)
{
	size_t	len;
	size_t	max;
	int		x;
	int		y;
	char	*tmp;

	max = max_line(*grid) - 1;
	x = -1;
	while ((*grid)[++x])
	{
		y = -1;
		tmp = (*grid)[x];
		len = ft_strlen((*grid)[x]);
		(*grid)[x] = (char *)malloc(sizeof(char *) * (max + 1));
		(*grid)[x][max + 1] = '\0';
		while (++y <= max)
		{
			if (y < len)
				(*grid)[x][y] = tmp[y];
			else
				(*grid)[x][y] = ' ';
		}
		free(tmp);
	}
}
