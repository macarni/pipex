/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:14:24 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/07 17:15:09 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child1_process(int *fd, int infile, char **argv, char **envp, char *path)
{
	close(fd[1]);
	dup2(infile, STDIN_FILENO); //cierra el STDIN estandar y redirecciona el fd al STDIN -> esto hará que fd[0] sea el input de execve
	dup2(fd[0], STDOUT_FILENO); //redirecciona la salida del comando fd[0] al STDOUT 
	close(fd[0]);
	close(infile);
	execve(path, &argv[2], envp); //del primer comando
}
// **comandos 
	//argv[2];
	//0;

// static void	child2_process(int fd, int outfile, char **argv, char **envp, char *path)
	// {
	// 	dup2(outfile, STDOUT_FILENO); //redirecciona el STDOUT al outfile
	// 	dup2(fd, STDIN_FILENO); //redirecciona el STDIN al fd[1]
	// 	execve(path, &argv[3], envp); //del segundo comando
	// }

	void pipex(int infile, int outfile, char **argv, char **envp, char **paths)
	{
	int		fd[2];
	int		pid;

	(void)outfile;
	pipe(fd); // Si no devuelve un 0 es que ha habido un error

	pid = fork(); 
	if (pid == 0) //hijo
		child1_process(fd, infile, argv, envp, paths[0]);
	if (pid == -1) //error
		perror("Fork: ");
	wait(NULL);
	// padre
	//lsof -c pipex -> para ver file descriptors abiertos
	//child2_process(fd[0], outfile, argv, envp, paths[1]);
	close(fd[0]);
	close(fd[1]);
	while (1)
		;
}