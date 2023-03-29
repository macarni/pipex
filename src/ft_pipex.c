/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/29 20:53:38 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * It forks a child process, which executes the first command and writes 
 * its output to a pipe.  It reads the infile from first argument
 * 
 * fd[0] -> read / fd[1] -> write
 * STDIN_FILENO 0 / STDOUT_FILENO 1
 * 
 * fork(): creates a child process and a pipeline between 
 * parent-child process. The parent process reads the data 
 * at one end of the pipe, and the child process writes it at the 
 * other end. In this way, information can be shared between the 
 * two processes. 
 * 
 * @param argv the arguments passed to the program
 * @param envp the environment variables
 * @param fd is the file descriptor for the pipe.
 * @param path_from_envp is the path from the environment variable PATH
 */
static void	first_exec(char **argv, char **envp, int *fd, char **path_from_envp)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		status;

	open_input_file(argv[1]);
	pid = fork();
	if (pid == -1)
		perror("Fork: ");
	else if (pid == 0)
	{
		cmd = ft_split(argv[2], ' ');
		path = check_cmd(cmd, path_from_envp);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, cmd, envp) < 0)
			exit(errno);
		free_matrix(cmd);
		free(path);
	}
	waitpid(pid, &status, WNOHANG);
	close(fd[1]);
}

/**
 * It forks a child process, and in the child process, it executes the 
 * last command and redirects the output of the last argument
 * 
 * @param argv the arguments passed to the program
 * @param envp the environment variables
 * @param fd file descriptor array
 * @param path_from_envp the path from the environment variable PATH
 */
static void	last_exec(char **argv, char **envp, int *fd, char **path_from_envp)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		status;

	open_output_file(argv[4]);
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(argv[3], ' ');
		path = check_cmd(cmd, path_from_envp);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (execve(path, cmd, envp) < 0)
			exit(errno);
		free_matrix(cmd);
		free(path);
	}
	else if (pid == -1)
		perror("Fork: ");
	waitpid(pid, &status, WNOHANG);
	close(fd[0]);
}

/**
 * It creates a pipe, forks, and then executes the first command in the 
 * first child and the second command in the second child
 * 
 * pipe() -> returns two file descriptors: fd[0] -> read / fd[1] -> write
 * pipe() sends the output of the first execve() as input to the second execve()
 * 
 * while (1)
 	;
 * lsof -c pipex -> para ver file descriptors abiertos
 * 
 * @param argv The arguments passed to the command.
 * @param envp the environment variables
 * @param path the path to the executable
 */
void	pipex(char **argv, char **envp, char **path)
{
	int	fd[2];

	if (pipe(fd) == 0)
	{
		first_exec(argv, envp, fd, path);
		last_exec(argv, envp, fd, path);
	}
}
