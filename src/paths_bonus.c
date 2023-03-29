/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:24:49 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/29 20:52:07 by adrperez         ###   ########.fr       */
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

static char	**ft_find_path_bonus(char **envp)
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
 * It checks if the command is in the PATH and returns the correct path if it is
 * 
 * @param cmd is the command that the user typed in the shell.
 * @param envp is the environment variables.
 * 
 * @return The correct path to the command.
 */
char	*check_cmd_bonus(char **cmd, char **envp)
{
	char	*aux;
	char	**path_from_envp;
	int		i;
	char	*correct_path;

	i = 0;
	if (!cmd || !(*cmd))
		cmd_not_foud("");
	path_from_envp = ft_find_path_bonus(envp);
	aux = ft_strjoin("/", cmd[0]);
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
	cmd_not_foud(*cmd);
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
