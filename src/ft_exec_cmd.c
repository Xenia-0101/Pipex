/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:31:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/25 10:58:46 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_exec_cmd(t_map *map, char *cmd, char *env[])
{
	if (ft_get_full_path(map, cmd) == -1)
	{
		ft_put_error("Path to cmd not found");
		return (1);
	}

	if (execve(map->full_path, map->cmd_args, env) == -1)
	{
		perror("Execve failed");
	};
	free(map->full_path);
	ft_free_arr(map->cmd_args);
}
