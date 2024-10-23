/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:31:00 by xenia             #+#    #+#             */
/*   Updated: 2024/10/17 07:40:00 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_paths(t_map *map)
{
	int	i;

	i = 0;
	while(map->paths[i])
	{
		free(map->paths[i]);
		i++;
	}
	free(map->paths);
}

void	ft_free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_map(t_map *map, int flag)
{
	if(flag == 1)
	{
		ft_free_arr(map->paths);
		ft_free_arr(map->args);
	}
	if(flag == 2)
	{
		ft_free_arr(map->paths);
		ft_free_arr(map->args);
		// free(map->cmd_n);
		free(map->cmd_f);
	}
}

