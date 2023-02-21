/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pippex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:00:08 by adrperez          #+#    #+#             */
/*   Updated: 2023/02/13 12:12:41 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

int		main(int argc, char **argv, char **envp);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	**ft_find_path(char **envp);
size_t	ft_strlen(const char *s);

#endif