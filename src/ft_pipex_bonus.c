
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/14 16:44:35 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//fd[0] -> read / fd[1] -> write
// STDIN_FILENO 0
// STDOUT_FILENO 1

static void first_exec(char **argv, char **envp, int *fd)
{
	char 	*path;
	char	**cmd;
	int 	infile;
	pid_t 	pid;
	int		status;

	infile = 0;
	get_input_file(argv[1], &infile);
	dup2(infile, STDIN_FILENO); // cierra el STDIN estandar y redirecciona el archivo al STDIN -> esto hará que infile sea el input de execve
	close(infile);
	pid = fork();
	if (pid == -1) // error
		perror("Fork: ");
	else if (pid == 0)
	{
		cmd = ft_split(argv[2], ' ');
		path = check_cmd_bonus(cmd, envp);
		close(fd[0]);				// se cierra después de leer dle archivo
		dup2(fd[1], STDOUT_FILENO); // redirecciona la salida del comando a fd[0] en vez de STDOUT
		close(fd[1]);
		if (execve(path, cmd, envp) < 0)
			exit(errno);
		free_matrix(cmd);
		free(path);
	}
	waitpid(pid, &status, WNOHANG);
	close(fd[1]); //necesito cerrar esto porque no tengo que escrir nada pero necesito el fd[0] para leer el resultado del comando a través del otro lado del pipe
}

static void last_exec(char **argv, char **envp, int *fd, int argc)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		outfile;
	int		status;

	outfile = 0;
	get_output_file(argv[argc - 1], &outfile);
	dup2(outfile, STDOUT_FILENO); // redirecciona el STDOUT al outfile
	close(outfile);
	pid = fork(); // segundo hijo
	//close(fd[1]); // padre lee, así que cerramos el de escritura
	if (pid == 0)
	{
		cmd = ft_split(argv[argc - 2], ' ');
		path = check_cmd_bonus(cmd, envp);
		dup2(fd[0], STDIN_FILENO);	  // redirecciona el STDIN al fd[0] --> queremos que lea del extremo de lectura del pipe (el que el pipe anterior que está abierto)
		close(fd[0]);
		// while (1)
		// 	;
		if (execve(path, cmd, envp) < 0) 
			exit(errno);
		free_matrix(cmd);
		free(path);	
	}
	else if (pid == -1) // error
		perror("Fork: ");
	wait(&status);
	//waitpid(pid, &status, WNOHANG);
	close(fd[0]); // para que se cierre el extremo cuando ya no es necesario
}

//fd2[0] -> read / fd2[1] -> write
//fd[0] -> extremo lectura pipe anterior / fd[1] -> extremo escritura pipe anterior

static void middle_exec_2(char *argv, char **envp, int *fd)
{
	char 	*path;	
	char	**cmd;
	pid_t	pid;
	int		fd2[2];
	int		status;

	pipe(fd2);
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(argv, ' ');
		path = check_cmd_bonus(cmd, envp);
		close(fd2[0]);
		dup2(fd[0], STDIN_FILENO); //leemos del fd[0] pipe anterior
		close(fd[0]);
		dup2(fd2[1], STDOUT_FILENO); //escribimos en el nuevo fd[1] del pipe
		close(fd2[1]);
		if (execve(path, cmd, envp) < 0) 
			exit(errno);
		free_matrix(cmd);
		free(path);
	}
	else if (pid == -1)
		perror("Fork: ");
	waitpid(pid, &status, WNOHANG);
	close(fd[0]); //el padre no necesita leer nada al terminar el pipe
	close(fd2[1]); //necesitamos leer del padre (del pipe anterior) y escribir en el pipe nuevo: necesitamos abiertos fd[0] y fd2[1] --> el padre no necesita leer nada
	fd[0] = fd2[0];
	fd[1] = fd2[1];
}

static void middle_cmds(char **argv, char **envp, int *fd, int argc)
{
	int		i;

	i = 3;
	while (i < argc - 2)
		middle_exec_2(argv[i++], envp, fd);
}

void pipex_bonus(char **argv, char **envp, int argc)
{
	int		fd[2];

	if (pipe(fd) == 0)
	{
		first_exec(argv, envp, fd);
		middle_cmds(argv, envp, fd, argc);
		last_exec(argv, envp, fd, argc);
	}
}