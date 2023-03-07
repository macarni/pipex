/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/07 13:27:05 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child1_process(int fd, char *cmd)
{
	close(fd[READ_END]);
	dup2(infile, STDIN); //cierra el STDIN estandar y redirecciona el fd al STDIN -> esto hará que fd[WRITE_END] sea el input de execve
	dup2(fd[WRITE_END], STDOUT); //redirecciona la salida del comando fd[WRITE_END] al STDOUT 
	close(fd[WRITE_END);
	close(infile);
	execve(correct_path, mycmds, envp); //del primer comando
}

int	child2_process(int fd, char *cmd)
{
	close(fd[WRITE_END]);
	dup2(outfile, STDOUT); //redirecciona el STDOUT al outfile
	dup2(fd[READ_END], STDIN); //redirecciona el STDIN al fd[READ_END]
	execve(correct_path, mycmds, envp); //del segundo comando
}

int	main(int argc, char **argv, char **envp)
{
	char	**mycmds;
	char	*correct_path;
	int		fd[2];
	pid_t	pid;
	int		infile;
	int 	outfile;

	infile = open(argv[1], O_RDONLY); //queremos que este infile sea el stdin del comando y que el fd[WRITE_END] sea el stdout --> escribir en fd[WRITE_END] el resultado del cmd1 --> dup2 lo que hace es intercambiar los fds a los stdin/stout
	
	outfile = open(argv[4], O_RDONLY); //queremos que el fd[READ_END] sea el stdin del comando2 (fd[READ_END] lee del fd[WRITE_END], el output del cmd1) y que el outfile sea nuestro stdout (queremos escribirle el output del cmd2)

	//En definitiva, infile y outfile tienen que ser los stdin y stdout del pipe

	pipe(fd); //Si no devuelve un 0 es que ha habido un error

	pid = fork();

	if (pid == 0) //hijo
		child1_process(file1, cmd1);
	if (pid == -1) //error
		perror("Fork: ");
	else //padre
		child2_process(file2, cmd2);
	
	correct_path = 0;
	if (argc > 1 && argv)
		printf(" ");
	mycmds = ft_split(argv[1], ' ');
	if(check_cmd(&correct_path, mycmds, envp) == -1)
		printf("Error\n");
	else
		printf("Correct \n");
	
	printf("Comando %s\n", mycmds[0]);
	printf("Correct path %s\n", correct_path);
	execve(correct_path, mycmds, envp);
	return (0);
}		
