/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:31:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/25 22:43:23 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_cmd(t_map *map, char *cmd, char *env[])
{
	if (ft_get_full_path(map, cmd))
	{
		ft_free_arr(map->paths);
		exit (1);
	}
	if (execve(map->full_path, map->cmd_args, env) == -1)
	{
		perror("Execve failed");
		exit(1);
	}
}
