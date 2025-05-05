#include "ft_utils.h"

int	ft_get_pid(void)
{
	int		fd;
	char	buf[32];
	int		i = 0;
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (-1);
	read(fd, buf, 31);
	close(fd);
	buf[31] = '\0';

	while (buf[i] >= '0' && buf[i] <= '9')
		i++;
	buf[i] = '\0';
	pid = ft_atoi(buf);
	return (pid);
}
