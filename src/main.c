/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/02/15 15:47:56 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * 1. find local path -> look for "PATH" in envp
 * 2. find command in local path with access() -> if access() == 0, then command exists
 */

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	
	if (argc > 1 && argv)
		printf("");
	path = ft_find_path(envp);
	
	//significa que tenemos permiso para usar el cmd
	if (access(argv[1], F_OK) != -1)
	{
		
	}
	while (*path){
		printf("%s\n", *path);
		path++;
	}
    
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
    	
		
