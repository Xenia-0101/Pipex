/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/13 11:35:56 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_init_map(t_map **map)
{
	(*map) = ft_calloc(1, sizeof (t_map));
	(*map)->args1 = NULL;
	(*map)->args2 = NULL;
	(*map)->cmd1 = NULL;
	(*map)->cmd2 = NULL;
	(*map)->paths = NULL;
	(*map)->infd = 0;
	(*map)->outfd = 0;
}

void	ft_parse_files(t_map **map, char *argv[])
{
	// check proper access to infile and outfile
	if (access(argv[1], F_OK)  | access(argv[1], R_OK))
	{
		exit(1);
		// ToDo: error handling - file does not exist or can't be read
	}
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
	{
		exit(1);
		// ToDo: error handling - can't write to file
	}
	(*map)->infd = open(argv[1], O_RDONLY);
	(*map)->outfd = open(argv[4], O_CREAT | O_TRUNC | O_RDWR);
}

void	ft_parse_cmd(t_map **map, char *argv[])
{
	int i;
	int cmd_c; // cmd + args count
	char **cmd_split;

	i = 0;
	cmd_c = 0;
	cmd_split = ft_split(argv[2], ' ');
	while(cmd_split[i])
	{
		i++;
		cmd_c++;
	}
	(*map)->args1 = ft_calloc(cmd_c + 2, sizeof (char *));
	if (!(*map)->args1)
	{
		exit(1); // ToDo: error handling - calloc fail
	}
	i = 0;
	while(cmd_split[i])
	{
		(*map)->args1[i] = cmd_split[i];
		i++;
	}
	(*map)->args1[i] = argv[1];
	(*map)->args1[i + 1] = NULL;
	(*map)->cmd1 = cmd_split[0];
}

void	ft_parse_args(t_map **map, char *argv[], char *envp[])
{
	ft_parse_files(map, argv);
	ft_parse_cmd(map, argv);
	(*map)->paths = ft_split(getenv("PATH"), ':');
}


int	main(int argc, char *argv[], char *envp[])
{
	// take infile (example.txt), perform wc command, write output to terminal

	char **cmd;
	t_map	*map;

	// init map
	ft_init_map(&map);

	// parse input arguments
	ft_parse_args(&map, argv, envp);

	/// execute command and continue with the program
	char *cmd_path;
	pid_t pid;
	int pfd[2];
	int i;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pipe(pfd) == -1)
		exit(1);

	// *** child process ***
	if (pid == 0)
	{
		close(pfd[0]);
		// dup2 redirects infile to stdin
		dup2(map->infd, 0);
		close(map->infd);



		// execute cmd at each path
		i = 0;
		while(map->paths[i])
		{
			cmd_path = ft_strjoin_free(ft_strjoin_free(map->paths[i], "/"), map->args1[0]);
			execve(cmd_path, map->args1, envp);
			free(cmd_path);
			i++;
		}
		exit(1);
	}
	// *** parent process ***
	if(pid > 0)
	{
		close(pfd[1]);
		dup2(map->outfd, 1); // outfile is stdout
		close(map->outfd);
		dup2(pfd[0], 0); // pipe output is stdin
		close(pfd[0]);
	}
	dup2(pfd[0], 1);

	///  *** free and clean ***
	// if (pid > 0)
	// {
	// 	free(args);
	// 	i = 0;
	// 	while(paths[i])
	// 	{
	// 		free(paths[i]);
	// 		i++;
	// 	}
	// 	free(paths);
	// 	i = 0;
	// 	while(cmd[i])
	// 	{
	// 		free(cmd[i]);
	// 		i++;
	// 	}
	// 	free(cmd);
	// }
	return (0);
}
