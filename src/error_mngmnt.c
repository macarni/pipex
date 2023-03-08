/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngmnt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:10:02 by adrperez          #+#    #+#             */
/*   Updated: 2023/03/08 18:14:29 by adrperez         ###   ########.fr       */
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