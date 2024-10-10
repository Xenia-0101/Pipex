/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/10 21:38:23 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int main(int argc, char *argv[])
{
	// take infile (example.txt), perform wc command, write output to terminal

	int i;
	int args_c; 	// how many args are to be passed to execve
	char **args;
	char **cmd;
	char *cmd_path;

	args_c = 2;		// filename and NULL

	// parse command -- argv[2]
	cmd = ft_split(argv[2], ' ');
	i = 0;
	while (cmd[i])
	{
		args_c++;
		i++;
	}
	args = ft_calloc(args_c, sizeof (char *));
	if (!args)
		exit(1);
	i = 0;
	while (i < args_c - 2)
	{
		args[i] = cmd[i];
		i++;
	}
	args[i] = argv[1];		// infile -- argv[1]
	args[i + 1] = NULL;

	// define command path
	cmd_path = ft_strjoin("/bin/", args[0]);
	execve(cmd_path, args, NULL);

	return (0);
}
