/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:13:18 by xenia             #+#    #+#             */
/*   Updated: 2024/10/14 11:42:26 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_get_cmd_a(t_map **map)
{
	int i;
	i = 0;
	while((*map)->args[i])
	{
		i++;
	}
	(*map)->cmd_a = ft_calloc(i + 1, sizeof (char *));
	i = 0;
	while((*map)->args[i])
	{
		(*map)->cmd_a[i] = ft_strdup((*map)->args[i]);
		i++;
	}
	(*map)->cmd_a[i] = (*map)->infd_n;
	(*map)->cmd_a[i] = NULL;
}

int	ft_get_cmd(t_map **map, char *arg, char *envp[])
{
	int	i;

	(*map)->args = ft_split(arg, ' ');
	(*map)->cmd_n = ft_strjoin("/", ((*map)->args)[0]);
	ft_get_cmd_a(map);
	i = 0;
	while((*map)->paths[i])
	{
		(*map)->cmd_p = ft_strjoin((*map)->paths[i], (*map)->cmd_n);
		execve((*map)->cmd_p, (*map)->cmd_a, envp);
		if (execve((*map)->cmd_p, (*map)->cmd_a, envp) == -1)
		{
			free((*map)->cmd_p);
		}
		i++;
	}
	// ToDo: free all
	return(1);
}

void	ft_process_cmd1(t_map **map, char *argv[], char *envp[])
{
	close((*map)->pfd[READ]);
	// dup2 redirects infile to stdin
	dup2((*map)->infd, STDIN_FILENO);
	close((*map)->infd);
	// redirect write side of pipe to stdout
	dup2((*map)->pfd[WRITE], STDOUT_FILENO);
	close((*map)->pfd[WRITE]);
	if(ft_get_cmd(map, argv[2], envp))
	{
		// ToDo: free all and exit with error
		perror("Get cmd1");
		exit(1);
	}
}

void	ft_process_cmd2(t_map **map, char *argv[], char *envp[])
{
	// close writing end of the pipe
	close((*map)->pfd[WRITE]);
	// redirect reading end of the pipe to stdin
	dup2((*map)->pfd[READ], STDIN_FILENO);
	close((*map)->pfd[READ]);
	// set outfile as stdout
	dup2((*map)->outfd, STDOUT_FILENO);
	close((*map)->outfd);
	if(ft_get_cmd(map, argv[3], envp))
	{
		// ToDo: free all and exit with error
		perror("Get cmd2");
		exit(1);
	}
	exit(0);
}
