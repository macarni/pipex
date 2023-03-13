/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngmnt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:10:02 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/13 13:01:11 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void check_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Argument error. Example usage: ./pipex infile \"ls -l\" \"wc -l\" outfile", 2);
		exit(1);
	}
}

void cmd_not_foud(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	exit(errno);
}