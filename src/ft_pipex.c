/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/13 17:09:00 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void first_exec(char **argv, char **envp, int *fd, char **path_from_envp, int infile)
{
	char *path;
	char	**cmd;

	path = check_cmd(argv[2], path_from_envp);
	cmd = ft_split(argv[2], ' ');
	close(fd[0]);				// vamos ESCRIBIR en el pipe, asi que se cierra el de lectura
	dup2(infile, STDIN_FILENO); // cierra el STDIN estandar y redirecciona el archivo al STDIN -> esto hará que infile sea el input de execve
	close(infile);
	dup2(fd[1], STDOUT_FILENO); // redirecciona la salida del comando a fd[0] en vez de STDOUT
	close(fd[1]);
	if (execve(path, cmd, envp) < 0)
		exit(errno);
	free_matrix(cmd);
	free(path);
}

static void last_exec(char **argv, char **envp, int *fd, char **path_from_envp, int outfile)
{
	char	*path;
	char	**cmd;
	pid_t	pid;

	path = check_cmd(argv[3], path_from_envp);
	cmd = ft_split(argv[3], ' ');
	pid = fork(); // segundo hijo
	close(fd[1]); // padre lee, así que cerramos el de escritura
	if (pid == 0)
	{
		dup2(outfile, STDOUT_FILENO); // redirecciona el STDOUT al outfile
		dup2(fd[0], STDIN_FILENO);	  // redirecciona el STDIN al fd[1] --> queremos que lea del extremo de lectura del pipe (el que el padre tiene abierto)
		close(fd[0]);
		if (execve(path, cmd, envp) < 0) 
			exit(errno);
	}
	else if (pid == -1) // error
		perror("Fork: ");
	else
		close(fd[0]); // para que se cierre el extremo cuando ya no es necesario
	free_matrix(cmd);
	free(path);
}

void pipex(char **argv, char **envp, char **path, int infile, int outfile)
{
	int		fd[2];
	pid_t 	pid;
	int		status;

	pipe(fd); // Si no devuelve un 0 es que ha habido un error
	pid = fork();
	if (pid == -1) // error
		perror("Fork: ");
	else if (pid == 0) //hijo
		first_exec(argv, envp, fd, path, infile);
	else
		last_exec(argv, envp, fd, path, outfile);
	// un wait para cada hijo
	waitpid(pid, &status, WNOHANG);
	waitpid(pid, &status, WNOHANG);
	// while (1)
	// 	;
	// padre
	// lsof -c pipex -> para ver file descriptors abiertos

}