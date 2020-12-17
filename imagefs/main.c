/*
 * main.c - Main source file for boot sector writer and image creator.
 *
 * Author: Philip R. Simonson
 * Date: 02/28/2020
 *
 *************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_SIZE 512

/* Write sectors to floppy disk.
 */
int write_sectors(int fout, ssize_t skip, const char *filename)
{
	ssize_t nsect = 0, nbytes, count;
	char buf[BLOCK_SIZE];
	off_t off;
	int fd;

	errno = 0;
	if((fd = open(filename, O_RDONLY, 0644)) < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return 1;
	}
	errno = 0;
	off = lseek(fd, 0, SEEK_END);
	if(off < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		close(fd);
		return 1;
	}
	if(lseek(fd, 0, SEEK_SET) < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		close(fd);
		return 1;
	}
	count = off / 512;
	count = (count == 0 ? 1 : count);
	errno = 0;
	off = lseek(fout, BLOCK_SIZE*skip, SEEK_SET);
	if(off < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		close(fd);
		return 1;
	}
	while(nsect < count && (nbytes = read(fd, buf, sizeof(buf))) >= 0) {
		if(write(fout, buf, nbytes) >= 0) {
			++nsect;
		}
	}
	close(fd);
	printf("Total sectors written %ld/%ld at %ld.\n",
		nsect, count, skip);
	return 0;
}
/* Create floppy disk size in sectors.
 */
int create_floppy(const char *filename, size_t count)
{
	size_t nsect = 0;
	char buf[BLOCK_SIZE];
	int fd;

	errno = 0;
	if((fd = open("floppy.img", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return 1;
	}
	errno = 0;
	memset(buf, 0, sizeof(buf));
	while(nsect < count && write(fd, buf, BLOCK_SIZE) > 0) {
		nsect++;
	}
	close(fd);
	if(errno != 0) {
		fprintf(stderr, "Error: Total sectors written %lu/%lu\n",
			nsect, count);
		return 1;
	}
	printf("Total sectors written %lu/%lu\n", nsect, count);
	return 0;
}
/* Program to create a floppy disk.
 */
int main(int argc, char **argv)
{
	char mode = 0;

	if(argc < 4 || argc > 5) {
		fprintf(stderr, "Usage: %s <mode> <image> <file> [skip-count]\n",
			argv[0]);
		return 1;
	}
	switch(argv[1][0]) {
	case 'c':
		create_floppy(argv[2], atoi(argv[3]));
	break;
	case 'w':
		if(argc == 4) {
			mode = 1;
		} else if(argc == 5) {
			mode = 2;
		} else {
			printf("Unknown write mode.\n");
			return 1;
		}
	break;
	default:
		printf("Unknown option '%c'.\n", argv[1][0]);
		return 1;
	}
	if(mode == 1) {
		int fd;

		errno = 0;
		if((fd = open(argv[2], O_RDWR, 0644)) < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			return 1;
		}
		if(write_sectors(fd, 0, argv[3])) {
			close(fd);
			return 1;
		}
		close(fd);
	} else if(mode == 2) {
		int fd;

		/* open output file for writing/reading */
		errno = 0;
		if((fd = open(argv[2], O_RDWR, 0644)) < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			return 1;
		}
		if(write_sectors(fd, atoi(argv[4]), argv[3])) {
			close(fd);
			return 1;
		}
		close(fd);
	}
	return 0;
}
