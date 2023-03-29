/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:24:49 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/29 18:36:13 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**cut_path(char *path)
{
	char	**clean_path;

	clean_path = ft_split(path, ':');
	free(path);
	return (clean_path);
}

char	**ft_find_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = 0;
	while (envp && envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=/", 6) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	return (cut_path(path));
}

/**
 * It takes the command and the path from the environment 
 * variable PATH, and checks if the command is
 * in the path. If it is, it returns the correct 
 * path to the command, if not, it prints an error
 * message and returns 0
 * 
 * @param argv the command line arguments
 * @param path_from_envp is the path from the environment variable PATH
 * 
 * @return The correct path to the command.
 */
char	*check_cmd(char **argv, char **path_from_envp)
{
	char	*aux;
	int		i;
	char	*correct_path;
	char	*cmd;

	i = 0;
	cmd = argv[0];
	aux = ft_strjoin("/", cmd);
	while (path_from_envp && path_from_envp[i])
	{
		correct_path = ft_strjoin(path_from_envp[i++], aux);
		if (!access(correct_path, X_OK))
		{
			free_matrix(path_from_envp);
			free(aux);
			return (correct_path);
		}
		free(correct_path);
	}
	free(aux);
	free_matrix(path_from_envp);
	cmd_not_foud(cmd);
	return (0);
}

void	free_matrix(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
