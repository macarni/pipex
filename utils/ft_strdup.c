/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:17 by adrperez          #+#    #+#             */
/*   Updated: 2023/02/15 12:43:55 by adrperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
		n--;
	}
	return (dst);
}

/**
 * It copies the string s1 into a new string s2.
 * 
 * @param s1 The string to be copied.
 * 
 * @return A pointer to the first character of the string.
 */
char	*ft_strdup(const char *s1)
{
	int		len;
	char	*s2;

	len = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * len);
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, len);
	return (s2);
}
