/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/08 16:13:56 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void pipex(int infile, int outfile, char **argv, char **envp, char **paths)
{
	int		fd[2];
	pid_t 	pid;
	int		status;
	char 	**cmd;

	(void)outfile;

	pipe(fd); // Si no devuelve un 0 es que ha habido un error

	pid = fork();
	printf("pid %d\n", pid);
	if (pid == -1) // error
		perror("Fork: ");
	else if (pid == 0) //hijo
	{
		cmd = ft_calloc(sizeof(char *), 2);
		cmd = ft_split(argv[2], ' ');
		printf("cmd1 %s\n", cmd[0]);
		close(fd[0]);	// vamos ESCRIBIR en el pipe, asi que se cierra el de lectura
		dup2(infile, STDIN_FILENO); // cierra el STDIN estandar y redirecciona el archivo al STDIN -> esto hará que infile sea el input de execve
		close(infile);
		dup2(fd[1], STDOUT_FILENO); // redirecciona la salida del comando a fd[0] en vez de STDOUT
		close(fd[1]);
		execve(paths[0], cmd, envp); // del primer comando
		free(cmd);
	}
	else 
	{
		cmd = ft_calloc(sizeof(char *), 2);
		cmd = ft_split(argv[3], ' ');
		printf("cmd2 %s\n", cmd[0]);
		pid = fork(); // segundo hijo
		close(fd[1]); // padre lee, así que cerramos el de escritura
		if (pid == 0)
		{
			dup2(outfile, STDOUT_FILENO); // redirecciona el STDOUT al outfile
			dup2(fd[0], STDIN_FILENO);	  // redirecciona el STDIN al fd[1] --> queremos que lea del extremo de lectura del pipe (el que el padre tiene abierto)
			close(fd[0]);
			execve(paths[1], cmd, envp);  // del segundo comando
			free(cmd);
		}
		else if (pid == -1) // error
			perror("Fork: ");
		else
		{
			close(fd[0]); // para que se cierre el extremo cuando ya no es necesario
		}
	}
	// un wait para cada hijo
	waitpid(pid, &status, WNOHANG);
	waitpid(pid, &status, WNOHANG);
	// wait(&status);
	// wait(&status);
	// while (1)
	// 	;
	// padre
	// lsof -c pipex -> para ver file descriptors abiertos

}