/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/17 07:55:36 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/*
// adding some useless comment to test git merge >:o-|-<
void	ft_pipex(t_map *map, char *argv[], char *envp[])
{
	// create pipe for the first process
	if (pipe(map->pfd) == -1)
	{
		perror("Pipe");
		ft_free_paths(map);
		exit(1);
	}
	// first fork
	map->pid1 = fork();
	if(map->pid1 == -1)
	{
		perror("Fork 1");
		ft_free_paths(map);
		exit(1);
	}
	if(!map->pid1)
	{
		// first command
		ft_process_cmd1(map, argv, envp);
	}

	// second fork
	map->pid2 = fork();
	if(map->pid2 == -1)
	{
		perror("Fork 2");
		exit(1);
	}
	if(!map->pid2)
	{
		ft_process_cmd2(map, argv, envp);
		exit(0);
	}
	// parent
	if(map->pid1 > 0 && map->pid2 > 0)
	{

		close(map->pfd[READ]);
		close(map->pfd[WRITE]);
		// waitpid(map->pid1, &map->state1, 0);
		waitpid(map->pid2, &map->state2, 0);
	}
}

 */
void	ft_pipex(t_map *map,int argc, char *argv[])
{
	map->pid = fork(); // ToDo: Handle failure
	pipe(map->pfd); // ToDo: Handle failure

	if(map->pid == 0)
	{
		// child process
		close(map->pfd[R]);
		dup2(map->infd, STDIN_FILENO);
		close(map->infd);
		dup2(map->pfd[W], STDOUT_FILENO);
		if(execve(map->cmd_f, map->args, map->envp) == -1)
		{
			exit(1);
		}
	}
	if(map->pid > 0)
	{
		// parse outfile
		close(map->pfd[W]);
		dup2(map->pfd[R], STDIN_FILENO);
		dup2(map->outfd, STDOUT_FILENO);
		close(map->outfd);
		if (ft_parse_cmd(map, argv[argc - 2]))
		{
			write(2, "pipex: ", 7);
			perror(map->cmd_n + 1);
			ft_free_map(map, 1);
			exit(1);
		};
		ft_free_map(map, 2);
		exit(0);
	}
}

int	main(int argc, char *argv[], char *envp[])
{

	t_map	map;

	if (argc == 5)
	{
		ft_init_map(&map);
		map.envp = envp;
		// ***
		// parse input arguments
		// -- check filenames
		ft_parse_files(&map, argc, argv);
		// -- get paths			--> to be freed
		map.paths = ft_split(getenv("PATH"), ':');
		// -- parse cmds
		//    -- cmd name, cmd args, full path
		if (ft_parse_cmd(&map, argv[2]))
		{
			write(2, "pipex: ", 7);
			perror(map.cmd_n + 1);
			ft_free_map(&map, 1);
			exit(1);
		};
		// ***
		// run pipex with proper args
		ft_pipex(&map, argc, argv);
		// ***
		// free paths

/* 		ft_parse_files(&map, argc, argv);
		map.paths = ft_split(getenv("PATH"), ':');
		ft_pipex(&map, argv, envp);

		ft_free_paths(&map);

		close(map.infd);
		close(map.outfd); */

		// free(&map);
	}
	return (0);
}
