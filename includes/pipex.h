/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:28:15 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/02 14:45:25 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "ft_printf.h"

# define ERROR "Incorrect inputs\n"
# define INERROR "Infile"
# define OUTERROR "Outfile"
# define PIPEERROR "Pipe"
# define COMMANDERROR "Command not found.\n"

typedef struct s_pipe
{
	int		pipe_fd[2];
	char	*path;
	char	**paths;
	char	**commands;
}	t_pipe;

void	error_print(char *error);
void	in_process(t_pipe pipex, char *envp[], char *argv[], int fd);
void	out_process(t_pipe pipex, char *envp[], char *argv[], int fd);

#endif