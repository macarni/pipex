/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:24:49 by adrperez          #+#    #+#             */
/*   Updated: 2023/02/15 15:39:32 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//1. Encontrar PATH
//2. Cortar a  partir de PATH
//3. Split 
//4. Probar en cual está el comando

static char	**cut_path(char **envp)
{
	char	**path;

	path = ft_split(&envp[0][5], ':');
	return (path);
}

char	**ft_find_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	path = malloc(sizeof(char *) * 2);
	while (envp[i])
	{
		//Significa que lo ha encontrado
		if (ft_memcmp(envp[i], "PATH=/", 6) == 0)
		{
			path[0] = ft_strdup(envp[i]); //devuelve una copia del str desde PATH
			path[1] = 0;
			break;
		}
		i++;
	}
	return (cut_path(path));
}

