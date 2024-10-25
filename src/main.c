/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/25 11:03:10 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_clean_exit(t_map *map, int status)
{
	ft_free(map);
	exit(status);
}

void	ft_pipex(t_map *map, char *cmd, char *env[])
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
	{
		ft_put_error("Pipe failed");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_put_error("Fork failed");
		return ;
	}
	if (pid == 0)
	{
		write(2, "here\n", 5);

		// process child
		// handle data flow
		// -- close reading end of the pipe
		close(pfd[0]);
		// -- redirect writing end to stdout
		dup2(pfd[1], STDOUT_FILENO);
		// execute cmd
		ft_exec_cmd(map, cmd, env);
		// free(map->full_path);
		// write(2, "child hello\n", 12);
	}
	if (pid > 0)
	{
		write(2, "pppp\n", 5);
		// process parent
		// handle data flow
		// -- close writing end of the pipe
		close(pfd[1]);
		// -- redirect reading end to stdin
		dup2(pfd[0], STDIN_FILENO);
		// close(pfd[0]);
		// exit
	}

}

int	main(int argc, char *argv[], char *envp[])
{
	t_map	map;
	int		i;

	if (argc < 5)
	{
		ft_put_error("Incorrect number of arguments");
		exit(1);
	}
	ft_init_map(&map);
	// check and open files
	if (ft_open_files(&map, argv[1], argv[argc - 1]))
	{
		ft_put_error("Files could not be opened");
		exit(1);
		// ft_clean_exit(&map, 1);
	}
	// get paths
	if (ft_get_paths(&map, envp))
	{
		ft_put_error("PATH error");
		exit(1);
	}
	// redirect infile to stdin
	dup2(map.in_fd, STDIN_FILENO);
	close(map.in_fd);
/* 	i = 2;
	// execute commands
	while (i < argc - 2)
	{
		ft_exec_cmd(&map, argv[i], envp);
		i++;
	} */
	// execute one command
	ft_pipex(&map, argv[2], envp);
	dup2(map.out_fd, STDOUT_FILENO);
	// close(map.out_fd);
	ft_exec_cmd(&map, argv[3], envp);
	// // ft_get_full_path(&map, argv[i]);
	// ft_get_full_path(&map, argv[3]);
	// execve(map.full_path, map.cmd_args, envp);
	ft_free_arr(map.paths);

}
