/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnihei <rnihei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:47:05 by rnihei            #+#    #+#             */
/*   Updated: 2025/07/22 14:54:55 by rnihei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i = i + 1;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == uc)
		{
			return ((char *)(s + i));
		}
		i = i + 1;
	}
	if (uc == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
	}
	if (!s1)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}
