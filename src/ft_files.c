/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:23:35 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/08 17:46:00 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int get_infile(char *argv)
{
	int file;

	file = open(argv, O_RDONLY);
	if (file < 0)
	{
		ft_putstr_fd("Error infile. ", 2);
		ft_putstr_fd(strerror(errno), 2); // returns a pointer to a string that describes the error code passed in the argument errnum
		exit(errno); // number of last error
	}

	return (file);
}

int get_outfile(char *argv)
{
	int file;

	file = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file < 0)
	{
		ft_putstr_fd("Error outfile. ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}

	return (file);
}