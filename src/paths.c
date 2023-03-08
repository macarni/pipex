/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:24:49 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/08 18:17:07 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//1. Encontrar PATH
//2. Cortar a  partir de PATH
//3. Split 
//4. Probar en cual está el comando

static char	**cut_path(char *envp)
{
	char	**path;

	path = ft_split(envp, ':');
	return (path);
}

char	**ft_find_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = 0;
	while (envp[i])
	{
		//Significa que lo ha encontrado
		if (ft_memcmp(envp[i], "PATH=/", 6) == 0)
		{
			path = ft_strdup(envp[i]); //devuelve una copia del str desde PATH
			path+=5;
			break;
		}
		i++;
	}
	return (cut_path(path));
}

char	*check_cmd(char *argv, char **envp)
{
	char	*aux;
	char	**path_from_envp;
	int		res;
	int		i;
	char 	*correct_path;

	i = 0;
	path_from_envp = ft_find_path(envp);
	aux = ft_strjoin("/", ft_split(argv, ' ')[0]);
	while(path_from_envp[i])
	{
		correct_path = ft_strjoin(path_from_envp[i], aux);
		res = access(correct_path, X_OK);
		if (res == 0) 
			return (correct_path);
		free(correct_path);
		i++;
	}
	free(aux);
	return (0);
}

