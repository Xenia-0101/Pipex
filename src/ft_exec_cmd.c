/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:31:14 by xenia             #+#    #+#             */
/*   Updated: 2024/11/01 20:41:51 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Get executable file path and execute command with proper arguments.
 *
 * Call ft_get_full_path
 * 	on failure - free memory set proper error msg and exit.
 * 	if successfull - map.full_path is set and the command is executed.
 *
 * @param map	Project data struct
 * @param cmd	Command to be executed
 * @param env	Environment variables
 */
void	ft_exec_cmd(t_map *map, char *cmd, char *env[])
{
	if (ft_get_full_path(map, cmd))
	{
		ft_free_arr(map->paths);
		perror("command not found");
		exit (127);
	}
	if (execve(map->full_path, map->cmd_args, env) == -1)
	{
		perror("Execve failed");
		exit(127);
	}
}
