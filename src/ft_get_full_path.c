/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_full_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:15:56 by xenia             #+#    #+#             */
/*   Updated: 2024/10/24 12:38:30 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_get_full_path(t_map *map, char *cmd)
{
	char **cmd_split;
	char *path;
	int i;

	cmd_split = ft_split(cmd, ' ');
	i = 0;
	while (map->paths[i])
	{
		path = ft_strjoin(map->paths[i], "/");
		map->full_path = ft_strjoin(path, cmd_split[0]);
		free(path);
		if (!access(map->full_path, F_OK) & !access(map->full_path, X_OK))
		{
			ft_free_arr(cmd_split);
			return (0);
		}
		else
		{
			free(map->full_path);
		}
		i++;
	}
	ft_free_arr(cmd_split);
	return(1);
}
