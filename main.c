/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/14 00:27:01 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"


// adding some useless comment to test git merge >:o-|-<
int main(int argc, char *argv[], char *envp[])
{
	// take infile (example.txt), perform wc command, write output to terminal

	int i;
	int args_c; 	// how many args are to be passed to execve
	char **args;
	char **cmd;

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

	// *** define command path ***
	char *env_path;
	char **paths;
	char *cmd_path;

	env_path = getenv("PATH"); // get path var from env
	paths = ft_split(env_path, ':');

	/// parsing finished

	/// execute command and continue with the program
	pid_t pid;
	int pfd[2];
	int infd;
	int outfd;

	infd = open(argv[1], O_RDONLY);
	outfd = open("outfile.txt", O_CREAT | O_RDWR);
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
		dup2(infd, 0);
		close(infd);



		// execute cmd at each path
		i = 0;
		while(paths[i])
		{
			cmd_path = ft_strjoin_free(ft_strjoin_free(paths[i], "/"), args[0]);
			execve(cmd_path, args, envp);
			free(cmd_path);
			i++;
		}
		exit(1);
	}
	// *** parent process ***
	if(pid > 0)
	{
		close(pfd[1]);
		dup2(outfd, 1); // outfile is stdout
		close(outfd);
		dup2(pfd[0], 0); // pipe output is stdin
		close(pfd[0]);

	}
	dup2(pfd[0], 1);

	///  *** free and clean ***
	if (pid > 0)
	{
		free(args);
		i = 0;
		while(paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
		i = 0;
		while(cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
	return (0);
}
