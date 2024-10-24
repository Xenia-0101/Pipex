/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:31:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/24 13:30:14 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_exec_cmd(t_map *map, char *cmd, char *env[])
{
	int	pfd[2];
	int	pid;

	// create pipe
	// fork
	// child -> process cmd
	//		 -> loop paths and execute
	// parent -> redirect to stdin
	// get cmd path and check access
	if (ft_get_full_path(map, cmd))
	{
		ft_put_error("Get full path failed.");
		return (1);
	}
	if (pipe(pfd) == -1)
	{
		ft_put_error("Pipe failed");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_put_error("Fork failed");
		return (1);
	}
	if (pid == 0)
	{
		// process child
		// handle data flow
		// -- close reading end of the pipe
		close(pfd[0]);
		// -- redirect writing end to stdout
		dup2(pfd[1], STDOUT_FILENO);
		// close(pfd[1]);
		// execute cmd
		if (execve(map->full_path, map->cmd_args, env) == -1)
		{
			perror("Execve failed");
		};
		// free(map->full_path);
		// write(2, "child hello\n", 12);
	}
	if (pid > 0)
	{
		// process parent
		// handle data flow
		// -- close writing end of the pipe
		close(pfd[1]);
		// -- redirect reading end to stdin
		dup2(pfd[0], STDIN_FILENO);
		// close(pfd[0]);
		// exit
		free(map->full_path);
		ft_free_arr(map->cmd_args);
	}
}
