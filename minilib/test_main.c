
#include <fcntl.h>
#include <stdio.h>
#include "minilib.h"


int		main(int ac, char **av)
{
	int		ret;
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	
	while ((ret = ft_gnl(&line, fd)) > 0)
	{

		printf("--- Line: %s", line);

		ft_scott_free(&line, 0);
	}
	ft_scott_free(&line, 0);
	while (1)
	{

	}
	return (0);
}
