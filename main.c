/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/14 00:36:55 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"


// adding some useless comment to test git merge >:o-|-<
void	ft_pipex(t_map **map, char *argv[], char *envp[])
{

	// create pipe for the first process
	if (pipe((*map)->pfd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
	// first fork
	(*map)->pid1 = fork();
	if((*map)->pid1 == -1)
	{
		perror("Fork 1");
		exit(1);
	}
	if(!(*map)->pid1)
	{
		// first command
		ft_process_cmd1(map, argv, envp);
	}

	// second fork
	(*map)->pid2 = fork();
	if((*map)->pid2 == -1)
	{
		perror("Fork 2");
		exit(1);
	}
	if(!(*map)->pid2)
	{
		printf("child process 2\n\n");
		ft_process_cmd2(map, argv, envp);
		exit(0);
	}
	// parent

}

int	main(int argc, char *argv[], char *envp[])
{
	// take infile (example.txt), perform wc command, write output to terminal

	char **cmd;
	t_map	*map;

	if (argc == 5)
	{
		// init map
		ft_init_map(&map);

		// parse input arguments
		ft_parse_files(&map, argc, argv);
		(*map).paths = ft_split(getenv("PATH"), ':');
		ft_pipex(&map, argv, envp);
	}

	// *** free and clean ***
/* 	if ((*map).pid1 > 0 && (*map).pid2)
	{
		// wait(NULL);
		// wait(NULL);
		// ft_free_map(&map);
	} */
	return (0);
}
