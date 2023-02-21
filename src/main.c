/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/02/21 15:23:57 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * 1. find local path -> look for "PATH" in envp
 * 2. find command in local path with access() -> if access() == 0, then command exists
 *  int execve(const char *pathname, char *const argv[],
                  char *const envp[]);
 */

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	char	*path_name;
	
	if (argc > 1 && argv)
		printf("");
	path = ft_find_path(envp);
	printf("Comando: %s\n", argv[1]);
	//significa que tenemos permiso para usar el cmd
	//averiguar el path en el que está el cmd
	if (access(path_name, F_OK) != -1)
	{
		
		if (execve(path_name, &argv[1], envp) < 0)
			printf("Error\n");
		else
			printf("Done\n");
	}
	// while (*path){
	// 	printf("%s\n", *path);
	// 	path++;
	// }
    
	return (0);
}


// if (argc != 5)
// 		perror("pipex needs 4 arguments");
// if (argc > 1 && argv)
// 		printf("");
// 	while (*envp){
// 		printf("envp: %s", *envp);
// 		envp++;
// 	}
    	
		
