/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnihei <rnihei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 04:27:09 by rnihei            #+#    #+#             */
/*   Updated: 2025/07/16 04:27:10 by rnihei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *saved)
{
	int		i;
	char	*line;

	if (saved == 0)
		return (NULL);
	i = 0;
	if (saved[i] == 0)
		return (NULL);
	while (saved[i] != 0 && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (line == 0)
		return (NULL);
	i = 0;
	while (saved[i] != 0 && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_save_remainder(char *saved)
{
	int		i;
	int		j;
	char	*remainder;

	if (saved == 0)
		return (NULL);
	i = 0;
	while (saved[i] != 0 && saved[i] != '\n')
		i++;
	if (saved[i] == 0)
	{
		free(saved);
		return (NULL);
	}
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (remainder == 0)
		return (NULL);
	i++;
	j = 0;
	while (saved[i] != 0)
	{
		remainder[j] = saved[i];
		j++;
		i++;
	}
	remainder[j] = '\0';
	free(saved);
	return (remainder);
}

char	*ft_read_file(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == 0)
		return (NULL);
	bytes_read = 1;
	while ((saved == 0 || ft_strchr(saved, '\n') == 0) && bytes_read != 0)
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
	if (saved == 0)
		return (NULL);
	line = ft_extract_line(saved);
	saved = ft_save_remainder(saved);
	return (line);
}
