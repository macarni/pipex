/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/16 13:08:49 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// queremos que este infile sea el stdin del comando y que el fd[WRITE_END] sea el stdout --> escribir en fd[WRITE_END] el resultado del cmd1 --> dup2 lo que hace es intercambiar los fds a los stdin/stout
// queremos que el fd[READ_END] sea el stdin del comando2(fd[READ_END] lee del fd[WRITE_END], el output del cmd1) y que el outfile sea nuestro stdout(queremos escribirle el output del cmd2)-- > las flags son : Open destination file with write only flag, if it is doesnt exist, create it with permission 666
// En definitiva, infile y outfile tienen que ser los stdin y stdout del pipe

void leaks(void){	
	system("leaks pipex");
}

int main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("Argument error. Example usage: ./pipex infile \"ls -l\" [...] \"wc -l\" outfile\n", 2);
		exit(1);
	}
	pipex_bonus(argv, envp, argc);
	//atexit(leaks);
	return (0);
}		
	
