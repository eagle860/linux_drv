/* Çı¶¯²âÊÔ³ÌĞòdrv_test.c */
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	fd = open("/dev/my_drv_device", O_RDWR);
	printf("%d\n", fd);
	read(fd, 0, 1);

	return 0;
}
