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
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

int		main(int argc, char **argv, char **envp);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char 	**ft_find_path(char **envp);
size_t 	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_bzero(void *s, size_t n);
char 	*check_cmd(char **argv, char **path_from_envp);
void 	pipex(char **argv, char **envp, char **path);
void 	ft_putstr_fd(char *s, int fd);
void	check_args(int argc);
void 	free_matrix(char **path);
void 	cmd_not_foud(char *cmd);
void	write_error(char	*str);
void 	get_input_file(char *argv, int *infile);
void 	get_output_file(char *argv, int *outfile);
void	pipex_bonus(char **argv, char **envp, char **path, int *files, int argc);
int 	main_bonus(int argc, char **argv, char **envp);

#endif