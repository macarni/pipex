/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:27 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/29 20:54:02 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// system("leaks pipex");

int	main(int argc, char **argv, char **envp)
{
	char	**path_from_envp;

	if (argc != 5)
	{
		ft_putstr_fd("Argument error. Example usage: ", 2);
		ft_putstr_fd("./pipex infile \"ls -l\" \"wc -l\" outfile\n", 2);
		exit(1);
	}
	path_from_envp = ft_find_path(envp);
	pipex(argv, envp, path_from_envp);
	free_matrix(path_from_envp);
	return (0);
}
