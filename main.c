/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/14 11:59:08 by xenia            ###   ########.fr       */
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
		ft_free_paths(map);
		exit(1);
	}
	// first fork
	(*map)->pid1 = fork();
	if((*map)->pid1 == -1)
	{
		perror("Fork 1");
		ft_free_paths(map);
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
		ft_process_cmd2(map, argv, envp);
		exit(0);
	}
	// parent
	if((*map)->pid1 > 0 && (*map)->pid2 > 0)
	{
		close((*map)->pfd[READ]);
		close((*map)->pfd[WRITE]);
		waitpid((*map)->pid1, &(*map)->state1, 0);
		waitpid((*map)->pid2, &(*map)->state2, 0);
	}

}

int	main(int argc, char *argv[], char *envp[])
{
	// take infile (example.txt), perform wc command, write output to terminal

	t_map	*map;

	if (argc == 5)
	{
		// init map
		ft_init_map(&map);

		// parse input arguments
		ft_parse_files(&map, argc, argv);
		(*map).paths = ft_split(getenv("PATH"), ':');
		ft_pipex(&map, argv, envp);

		ft_free_paths(&map);

		close((*map).infd);
		close((*map).outfd);
		free(map);
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
