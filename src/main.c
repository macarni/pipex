/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/07 16:24:49 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int 	outfile;
	char	**paths_cmd;
	char	**cmd1;
	char	**cmd2;

	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	if (argc != 5)
	{
		printf("Error argv \n");
		return (-1);
	}
	infile = open(argv[1], O_RDONLY); //queremos que este infile sea el stdin del comando y que el fd[WRITE_END] sea el stdout --> escribir en fd[WRITE_END] el resultado del cmd1 --> dup2 lo que hace es intercambiar los fds a los stdin/stout
	
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644); //queremos que el fd[READ_END] sea el stdin del comando2 (fd[READ_END] lee del fd[WRITE_END], el output del cmd1) y que el outfile sea nuestro stdout (queremos escribirle el output del cmd2) --> las flags son: Open destination file with write only flag, if it is doesnt exist, create it with permission 666*/

	//En definitiva, infile y outfile tienen que ser los stdin y stdout del pipe

	if (infile < 0 || outfile < 0)
	{     
		printf("Error abriendo archivos \n");
		return (-1);
	}
	paths_cmd = ft_calloc(sizeof(char *), 2);
	if (check_cmd(&paths_cmd[0], cmd1, envp) == -1) 
	{
		printf("Error check_cmd1 \n");
		return (-1);
	}
	else if (check_cmd(&paths_cmd[1], cmd2, envp) == -1)
	{
		printf("Error check_cmd2 \n");
		return (-1);
	}
	printf("Comando 1 %s\n", cmd1[0]);
	printf("Comando 2 %s\n", cmd2[0]);
	pipex(infile, outfile, argv, envp, paths_cmd);
	return (0);
}		
