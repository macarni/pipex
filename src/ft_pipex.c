/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/13 11:30:47 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void first_exec(int infile, char **argv, char **envp, int *fd)
{
	char *path;
	char	**cmd;

	path = check_cmd(argv[2], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found\n", 2);
		free(path);
		exit(127);
	}
	cmd = ft_split(argv[2], ' ');
	close(fd[0]);				// vamos ESCRIBIR en el pipe, asi que se cierra el de lectura
	dup2(infile, STDIN_FILENO); // cierra el STDIN estandar y redirecciona el archivo al STDIN -> esto hará que infile sea el input de execve
	close(infile);
	dup2(fd[1], STDOUT_FILENO); // redirecciona la salida del comando a fd[0] en vez de STDOUT
	close(fd[1]);
	execve(path, cmd, envp); // del primer comando
	free_matrix(cmd);
	free(path);
}

static void last_exec(int outfile, char **argv, char **envp, int *fd)
{
	char	*path;
	char	**cmd;
	pid_t	pid;

	path = check_cmd(argv[3], envp);
	if (!path)
	{	
		ft_putstr_fd("pipex: command not found\n", 2);
		free(path);
		exit(127);
	}
	cmd = ft_split(argv[3], ' ');
	pid = fork(); // segundo hijo
	close(fd[1]); // padre lee, así que cerramos el de escritura
	if (pid == 0)
	{
		dup2(outfile, STDOUT_FILENO); // redirecciona el STDOUT al outfile
		dup2(fd[0], STDIN_FILENO);	  // redirecciona el STDIN al fd[1] --> queremos que lea del extremo de lectura del pipe (el que el padre tiene abierto)
		close(fd[0]);
		execve(path, cmd, envp); // del segundo comando
		free_matrix(cmd);
		free(path);
	}
	else if (pid == -1) // error
		perror("Fork: ");
	else
	{
		close(fd[0]); // para que se cierre el extremo cuando ya no es necesario
	}
}

void pipex(int infile, int outfile, char **argv, char **envp)
{
	int		fd[2];
	pid_t 	pid;
	int		status;

	pipe(fd); // Si no devuelve un 0 es que ha habido un error
	pid = fork();
	if (pid == -1) // error
		perror("Fork: ");
	else if (pid == 0) //hijo
		first_exec(infile, argv, envp, fd);
	else 
		last_exec(outfile, argv, envp, fd);
	// un wait para cada hijo
	waitpid(pid, &status, WNOHANG);
	waitpid(pid, &status, WNOHANG);
	// while (1)
	// 	;
	// padre
	// lsof -c pipex -> para ver file descriptors abiertos

}