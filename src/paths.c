/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:24:49 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/14 12:23:12 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char **cut_path(char *path)
{
	char **clean_path;

	clean_path = ft_split(path, ':');
	free(path);
	return (clean_path);
}

char **ft_find_path(char **envp)
{
	char *path;
	int i;

	i = 0;
	path = 0;
	while (envp[i])
	{
		// Significa que lo ha encontrado
		if (ft_memcmp(envp[i], "PATH=/", 6) == 0)
		{
			path = ft_strdup(envp[i] + 5); // devuelve una copia del str desde PATH
			break;
		}
		i++;
	}
	return (cut_path(path));
}

char *check_cmd(char **argv, char **path_from_envp)
{
	char *aux;
	int res;
	int i;
	char *correct_path;
	char *cmd;

	i = 0;
	cmd = argv[0];
	aux = ft_strjoin("/", cmd);
	while (path_from_envp[i])
	{
		correct_path = ft_strjoin(path_from_envp[i], aux);
		res = access(correct_path, X_OK);
		if (res == 0)
		{
			free_matrix(path_from_envp);
			free(aux);
			return (correct_path);
		}
		free(correct_path);
		i++;
	}
	cmd_not_foud(cmd);
	free(aux);
	free_matrix(path_from_envp);
	return (0);
}

void free_matrix(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
