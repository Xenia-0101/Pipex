/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/11/01 20:43:26 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_pipex(t_map *map, char *cmd, char *env[])
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
	{
		perror("Pipe failed");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return ;
	}
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		ft_exec_cmd(map, cmd, env);
	}
	if (pid > 0)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_map	map;
	int		i;

	if (argc < 5)
	{
		perror("Incorrect number of arguments");
		exit(1);
	}
	ft_init_map(&map, argc, argv);
	i = ft_open_files(&map, argv[1], argv[argc - 1]);
	ft_get_paths(&map, envp);
	dup2(map.in_fd, STDIN_FILENO);
	close(map.in_fd);
	while (i < argc - 2)
	{
		ft_pipex(&map, argv[i++], envp);
	}
	dup2(map.out_fd, STDOUT_FILENO);
	ft_exec_cmd(&map, argv[i], envp);
	ft_free_arr(map.paths);
}
