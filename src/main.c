/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/06 19:47:30 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * 1. find local path -> look for "PATH" in envp
 * 2. find command in local path with access() -> if access() == 0, then command exists
 *  int execve(const char *pathname, char *const argv[], char *const envp[]);
 * 3. //checks whether the calling process can access the file pathname --> para ejecutar el comando execve(correct, mycmds, envp) == -1
 //LEER ESTO averiguar el path en el que está el cmd: https://stackoverflow.com/questions/71333156/pathname-vs-arguments-for-execve-parameters
 */

int	main(int argc, char **argv, char **envp)
{
	char	**mycmds;
	char	*correct_path;

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
