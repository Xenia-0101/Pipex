/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_full_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:15:56 by xenia             #+#    #+#             */
/*   Updated: 2024/10/26 22:24:08 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_get_full_path(t_map *map, char *cmd)
{
	char	*path;
	int		i;

	map->cmd_args = ft_split(cmd, ' ');
	map->full_path = ft_strdup(cmd);
	i = 0;
	while (map->paths[i])
	{
		if (!access(map->full_path, F_OK) & !access(map->full_path, X_OK))
		{
			return (0);
		}
		else
		{
			free(map->full_path);
		}
		path = ft_strjoin(map->paths[i], "/");
		map->full_path = ft_strjoin(path, map->cmd_args[0]);
		free(path);
		i++;
	}
	free(map->full_path);
	ft_free_arr(map->cmd_args);
	return (1);
}
