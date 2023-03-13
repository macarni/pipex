/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:23:35 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/13 16:32:30 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void get_files(char *argv1, int *infile, char *argv2, int *outfile)
{
	*infile = open(argv1, O_RDONLY);
	if (*infile < 0)
		write_error(argv1);
	*outfile = open(argv2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile < 0)
		write_error(argv2);
}