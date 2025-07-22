#include "./get_next_line.h"
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		flag;

	fd = open("./test.txt", O_RDONLY);
	flag = 1;
	while (flag)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		printf("%s", line);
		free(line);
	}
	while ((line = get_next_line(fd)) != NULL)
		free(line);
	return (0);
}
