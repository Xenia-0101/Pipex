/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/13 14:49:46 by xenia            ###   ########.fr       */
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



void	ft_free_map(t_map **map)
{
	int i;
	i = 0;
	while((*map)->args1[i])
	{
		free((*map)->args1[i]);
		i++;
	}
	free((*map)->args1);
	i = 0;
	while((*map)->paths[i])
	{
		free((*map)->paths[i]);
		i++;
	}
	free((*map)->paths);
	i = 0;
	free((*map)->cmd1);
	free(*map);
}

void	ft_parse_files(t_map **map, char *argv[])
{
	// check proper access to infile and outfile
	if (access(argv[1], F_OK)  | access(argv[1], R_OK))
	{
		perror("Infile permissions: ");
		exit(1);
		// ToDo: error handling - file does not exist or can't be read
	}
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
	{
		perror("Outfile permissions: ");
		exit(1);
		// ToDo: error handling - can't write to file
	}
	(*map)->infd = open(argv[1], O_RDONLY);
	 // set mode when creating file to 0644 - owner: rw, others: r
	(*map)->outfd = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
}

void	ft_parse_cmd(t_map **map, char *argv[])
{
	int i;
	int cmd_c; // cmd + args count
	char **cmd_split;

	i = 0;
	cmd_c = 0;
	cmd_split = ft_split(argv[2], ' ');
	(*map)->cmd1 = ft_strdup(cmd_split[0]);
	while(cmd_split[i])
	{
		i++;
		cmd_c++;
	}
	(*map)->args1 = ft_calloc(cmd_c + 2, sizeof (char *));
	if (!(*map)->args1)
	{
		perror("Memory for map.args1 was not allocated. ");
		exit(1); // ToDo: error handling - calloc fail
	}
	i = 0;
	while(cmd_split[i])
	{
		(*map)->args1[i] = ft_strdup(cmd_split[i]);
		i++;
	}
	(*map)->args1[i] = ft_strdup(argv[1]);
	(*map)->args1[i + 1] = NULL;
	i = 0;
	while(cmd_split[i])
	{
		free(cmd_split[i]);
		i++;
	}
	free(cmd_split);

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
	{
		perror("Fork Fail: ");
		exit(1);
	}
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

	// /  *** free and clean ***
	if (pid > 0)
	{
		wait(NULL);
		ft_free_map(&map);
	}
	return (0);
}
