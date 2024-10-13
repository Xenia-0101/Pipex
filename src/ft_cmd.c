/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:13:18 by xenia             #+#    #+#             */
/*   Updated: 2024/10/13 22:54:43 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_get_cmd(t_map **map, char *arg)
{
	int	i;
	char *path;

	(*map)->args = ft_split(arg, ' ');
	// if the binary is accessible, set vals and return
	if(!access(((*map)->args)[0], 0))
	{
		(*map)->cmd_n = ((*map)->args)[0];
		// ToDo: use cmd args ("wc -l")
		// ToDo: free map.args
		return (0);
	}
	(*map)->cmd_n = ft_strjoin("/", ((*map)->args)[0]);
	i = 0;
	while((*map)->paths[i])
	{
		(*map)->cmd_p = ft_strjoin((*map)->paths[i], (*map)->cmd_n);
		perror((*map)->cmd_p);
		if(!access((*map)->cmd_p, F_OK))
		{
			// ToDo: use cmd args ("wc -l")
			// ToDo: free map.args
			perror("access cmd binary");
			return(0);
		}
		i++;
	}
	// ToDo: free all
	return(1);
}

void	ft_process_cmd1(t_map **map, char *argv[], char *envp[])
{
	close((*map)->pfd[0]);
	// dup2 redirects infile to stdin
	dup2((*map)->infd, 0);
	// redirect write side of pipe to stdout
	dup2((*map)->pfd[1], 1);
	if(ft_get_cmd(map, argv[2]))
	{
		// ToDo: free all and exit with error
		perror("Get cmd1");
		exit(1);
	}
	if(execve((*map)->cmd_p, (*map)->args, envp) == -1)
	{
		// ToDo: free all and exit with error
		perror("Execute cmd1");
		exit(1);
	}
	exit(0);
}

void	ft_process_cmd2(t_map **map, char *argv[], char *envp[])
{
	// close writing end of the pipe
	close((*map)->pfd[1]);
	// redirect reading end of the pipe to stdin
	dup2((*map)->pfd[0], 1);
	close((*map)->pfd[0]);
	// set outfile as stdout
	dup2((*map)->outfd, 0);
	close((*map)->outfd);
	if(ft_get_cmd(map, argv[3]))
	{
		// ToDo: free all and exit with error
		perror("Get cmd2");
		exit(1);
	}
	if(execve((*map)->cmd_p, (*map)->args, envp) == -1)
	{
		// ToDo: free all and exit with error
		perror("Execute cmd2");
		exit(1);
	}
	exit(0);
}
