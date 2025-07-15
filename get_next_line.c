/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnihei <rnihei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 04:27:09 by rnihei            #+#    #+#             */
/*   Updated: 2025/07/16 05:40:17 by rnihei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *saved)
{
	int		i;
	int		j;
	char	*line;

	if (!saved || !saved[0])
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + (saved[i] == '\n') + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = saved[j];
		j++;
	}
	if (saved[i] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_save_remainder(char *saved)
{
	int		i;
	int		j;
	char	*remainder;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		remainder[j++] = saved[i++];
	remainder[j] = '\0';
	free(saved);
	return (remainder);
}

char	*ft_read_file(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while ((!saved || !ft_strchr(saved, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = ft_read_file(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_extract_line(saved);
	saved = ft_save_remainder(saved);
	return (line);
}
