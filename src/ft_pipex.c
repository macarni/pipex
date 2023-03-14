/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/14 20:13:22 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void first_exec(char **argv, char **envp, int *fd, char **path_from_envp)
{
	char 	*path;
	char	**cmd;
	int 	infile;
	pid_t 	pid;
	int		status;

	infile = 0;
	pid = fork();
	//close(fd[1]);
	if (pid == -1) // error
		perror("Fork: ");
	else if (pid == 0) //hijo
	{
		get_input_file(argv[1], &infile);
		cmd = ft_split(argv[2], ' ');
		path = check_cmd(cmd, path_from_envp);
		dup2(infile, STDIN_FILENO); // cierra el STDIN estandar y redirecciona el archivo al STDIN -> esto hará que infile sea el input de execve
		close(infile);
		close(fd[0]);				// vamos ESCRIBIR en el pipe, asi que se cierra el de lectura
		dup2(fd[1], STDOUT_FILENO); // redirecciona la salida del comando a fd[0] en vez de STDOUT
		close(fd[1]);
		if (execve(path, cmd, envp) < 0)
			exit(errno);
		free_matrix(cmd);
		free(path);
	}
	waitpid(pid, &status, WNOHANG);
	
}

static void last_exec(char **argv, char **envp, int *fd, char **path_from_envp)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		outfile;
	int		status;

	outfile = 0;
	get_output_file(argv[4], &outfile);
	cmd = ft_split(argv[3], ' ');
	path = check_cmd(cmd, path_from_envp);
	pid = fork(); // segundo hijo
	close(fd[1]); // padre lee, así que cerramos el de escritura
	if (pid == 0)
	{
		dup2(outfile, STDOUT_FILENO); // redirecciona el STDOUT al outfile
		dup2(fd[0], STDIN_FILENO);	  // redirecciona el STDIN al fd[1] --> queremos que lea del extremo de lectura del pipe (el que el padre tiene abierto)
		close(fd[0]);
		//close(outfile);
		if (execve(path, cmd, envp) < 0) 
			exit(errno);
	}
	else if (pid == -1) // error
		perror("Fork: ");	
	waitpid(pid, &status, WNOHANG);
	close(fd[0]); // para que se cierre el extremo cuando ya no es necesario
	close(outfile);
	free_matrix(cmd);
	free(path);
}

void pipex(char **argv, char **envp, char **path)
{
	int		fd[2];

	if (pipe(fd) == 0) // Si no devuelve un 0 es que ha habido un error
	{
		first_exec(argv, envp, fd, path);
		last_exec(argv, envp, fd, path);
	}
	// un wait para cada hijo
	// while (1)
	// 	;
	// lsof -c pipex -> para ver file descriptors abiertos
	//Por qué cuando comento los cierres no me aparecen en lsof -c pipex
}