
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

static void first_exec(char **argv, char **envp, int *fd)
{
	char 	*path;
	char	**cmd;
	int 	infile;
	pid_t 	pid;
	int		status;

	infile = 0;
	pid = fork();
	//close(fd[1]); //POR QUE ESTE CUANDO SE CIERRA NO FUNCIONA?
	if (pid == -1) // error
		perror("Fork: ");
	else if (pid == 0)
	{
		get_input_file(argv[1], &infile);
		cmd = ft_split(argv[2], ' ');
		path = check_cmd_bonus(cmd, envp);
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

static void last_exec(char **argv, char **envp, int *fd, int argc)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		outfile;
	int		status;

	outfile = 0;
	get_output_file(argv[argc - 1], &outfile);
	cmd = ft_split(argv[argc - 2], ' ');
	path = check_cmd_bonus(cmd, envp);
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
	waitpid(pid, &status, WNOHANG);
	close(fd[0]); // para que se cierre el extremo cuando ya no es necesario
	close(outfile);
	free_matrix(cmd);
	free(path);
}

//fd[0] -> read / fd[1] -> write

static void middle_exec(char **argv, char **envp, int *fd, int argc)
{
	char 	*path;
	char	**cmd;
	pid_t	pid;
	int		i;
	int		fd2[2];
	//int		status;

	i = 3;
	while (i < argc - 2)
	{	
		cmd = ft_split(argv[i], ' ');
		i++;
		path = check_cmd_bonus(cmd, envp);
		pipe(fd2);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd2[1], STDOUT_FILENO); //escribimos en el nuevo fd del pipe
			close(fd2[1]);
			close(fd2[0]);
			dup2(fd[0], STDIN_FILENO); //leemos del pipe anterior
			close(fd[0]);
			if (execve(path, cmd, envp) < 0) 
				exit(errno);
		}
		else if (pid == -1)
			perror("Fork: ");
		waitpid(pid, &i, WNOHANG);
		close(fd[0]); //el padre no necesita leer nada al terminar el pipe
		close(fd2[1]); //necesitamos leer del padre (del pipe anterior) y escribir en el pipe nuevo: necesitamos abiertos fd[0] y fd2[1] --> el padre no necesita leer nada
		fd[0] = fd2[0];
		fd[1] = fd2[1];
		free_matrix(cmd);
		free(path);
	}
	
}

void pipex_bonus(char **argv, char **envp, int argc)
{
	int		fd[2];

	if (pipe(fd) == 0)
	{
		first_exec(argv, envp, fd);
		middle_exec(argv, envp, fd, argc);
		last_exec(argv, envp, fd, argc);
	}
	// while (1)
	// 	;
}