/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_full_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:15:56 by xenia             #+#    #+#             */
/*   Updated: 2024/10/28 16:41:46 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Free memory and possibly exit, based on option.
 */
void	ft_free_exit(t_map *map, int option)
{
	if (option == 1)
	{
		ft_free_arr(map->paths);
		ft_free_arr(map->cmd_args);
		exit(1);
	}
	if (option == 2)
	{
		free(map->full_path);
		ft_free_arr(map->cmd_args);
	}
}

/**
 * @brief	Get path to the executable file for the command.
 *
 * Split cmd by space to separate command from its arguments.
 * Save cmd in map.full_path - to check if the command by itself
 * 	is not the path to the executable.
 * Loop through paths and check:
 * 	if map.full_path is NULL - free memory and exit pipex
 * 	if map.full_path is accessible for execution - return success
 * 	else - free map.full_path
 * 	set map.full_path as path + / + command name and free path
 * If no executable file is found, free memory and return failure
 *
 * @param map	Map data struct
 * @param cmd	Command as passed in to pipex
 *
 * @return	int: 0 on success, 1 on failure
 */
int	ft_get_full_path(t_map *map, char *cmd)
{
	char	*path;
	int		i;

	map->cmd_args = ft_split(cmd, ' ');
	map->full_path = ft_strdup(cmd);
	i = 0;
	while (i < ft_arrlen(map->paths) + 1)
	{
		if (!map->full_path)
			ft_free_exit(map, 1);
		if (!access(map->full_path, F_OK) & !access(map->full_path, X_OK))
			return (0);
		else
			free(map->full_path);
		path = ft_strjoin(map->paths[i], "/");
		map->full_path = ft_strjoin(path, map->cmd_args[0]);
		free(path);
		i++;
	}
	ft_free_exit(map, 2);
	return (1);
}
