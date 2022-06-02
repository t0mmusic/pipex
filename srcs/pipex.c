/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:30:10 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/02 14:53:59 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_print(char *error)
{
	ft_printf("%s", error);
}

void	init_pipex(t_pipe *pipex, char *envp[])
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	pipex->paths = ft_split(*envp + 5, ':');
}

void	fork_output(t_pipe pipex, char *envp[], char *argv[], int fd)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		in_process(pipex, envp, argv, fd);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	int		fd_in;
	int		fd_out;
	int		pid[2];

	if (argc != 5)
	{
		error_print(ERROR);
		return (1);
	}
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	init_pipex(&pipex, envp);
	pipe(pipex.pipe_fd);
	fork_output(pipex, envp, argv, fd_in);
	pid[0] = fork();
	if (!pid[0])
	{
		out_process(pipex, envp, argv, fd_out);
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
