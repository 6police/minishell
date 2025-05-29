#include "ft_utils.h"

// function to get the process ID of the current process
int	ft_get_pid(void)
{
	int		fd;
	char	buf[32];
	int		i;
	int		pid;

	i = 0;
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
