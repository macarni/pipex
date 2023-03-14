/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/14 16:44:26 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// queremos que este infile sea el stdin del comando y que el fd[WRITE_END] sea el stdout --> escribir en fd[WRITE_END] el resultado del cmd1 --> dup2 lo que hace es intercambiar los fds a los stdin/stout
// queremos que el fd[READ_END] sea el stdin del comando2(fd[READ_END] lee del fd[WRITE_END], el output del cmd1) y que el outfile sea nuestro stdout(queremos escribirle el output del cmd2)-- > las flags son : Open destination file with write only flag, if it is doesnt exist, create it with permission 666
// En definitiva, infile y outfile tienen que ser los stdin y stdout del pipe
	
int main_bonus(int argc, char **argv, char **envp)
{
	char 	**path_from_envp;
	//int		files[2];

	check_args(argc);
	//get_files(argv[1], &files[0], argv[4], &files[1]);
	path_from_envp = ft_find_path(envp);
	pipex(argv, envp, path_from_envp, argc);
	//system("leaks pipex");
	return (0);
}		
	
