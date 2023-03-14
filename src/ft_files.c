/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:23:35 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/14 16:37:46 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void get_input_file(char *argv, int *infile)
{
	*infile = open(argv, O_RDONLY);
	if (*infile < 0)
		write_error(argv);
}

void get_output_file(char *argv, int *outfile)
{
	*outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile < 0)
		write_error(argv);
}

// void get_files(char *argv1, int *infile, char *argv2, int *outfile)
// {
// 	*outfile = open(argv2, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (*outfile < 0)
// 		write_error(argv2);
// }