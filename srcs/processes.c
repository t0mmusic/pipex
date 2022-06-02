/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:49 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/02 14:46:55 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_command(char *error, char *command)
{
	error_print(error);
	perror(command);
	exit (1);
}

/*	Joins a path to a command, separated by '/'.	*/

char	*join_path(char *path, char *command)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, command);
	free (tmp);
	return (ret);
}

/*	Checks the command entered by the user against all of the possible
	paths. If it finds one that matches, it will set the path in the
	pipex structure and return 1. Otherwise, returns 0.	*/

int	command_valid(t_pipe *pipex)
{
	char	*tmp;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		tmp = join_path(pipex->paths[i], pipex->path);
		if (!access(tmp, 0))
		{
			pipex->path = tmp;
			return (1);
		}
		free (tmp);
		i++;
	}
	return (0);
}

/*	Write process, sets read pipe fd to standard input, sets fd for 
	input file to standard output. Checks command is valid and then
	excecutes the shell command. It applies the command to what has
	been output (into the standard input) by the input process.	*/

void	out_process(t_pipe pipex, char *envp[], char *argv[], int fd)
{
	pipex.commands = ft_split(argv[3], ' ');
	pipex.path = pipex.commands[0];
	dup2(pipex.pipe_fd[0], 0);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	dup2(fd, 1);
	close(fd);
	if (command_valid(&pipex))
	{
		execve(pipex.path, pipex.commands, envp);
	}
	error_command(COMMANDERROR, pipex.commands[0]);
}

/*	Read process, sets read pipe fd to standard output, sets fd for 
	input file to standard input. Checks command is valid and then
	excecutes the shell command.	*/

void	in_process(t_pipe pipex, char *envp[], char *argv[], int fd)
{
	pipex.commands = ft_split(argv[2], ' ');
	pipex.path = pipex.commands[0];
	dup2(pipex.pipe_fd[1], 1);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	dup2(fd, 0);
	close (fd);
	if (command_valid(&pipex))
	{
		execve(pipex.path, pipex.commands, envp);
	}
	error_command(COMMANDERROR, pipex.commands[0]);
}
