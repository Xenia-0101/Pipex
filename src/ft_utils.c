/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:53 by xenia             #+#    #+#             */
/*   Updated: 2024/11/01 20:58:53 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			i++;
		}
	}
	return (i);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_init_map(t_map *map, int argc, char *argv[])
{
	map->in_fd = 0;
	map->out_fd = 0;
	map->argv = argv;
	map->argc = argc;
	map->paths = NULL;
	map->full_path = NULL;
}
