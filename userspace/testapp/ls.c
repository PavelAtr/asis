#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <tiny.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv)
{
	char* path;
	if (argc < 2)
		path = "";
	else
		path = argv[1];

	char* dirname = path;
	DIR* dir = opendir(dirname);
	if (!dir)
	{
		puts(strerror(errno));
		puts("\n");
		return -1;
	}
	struct dirent* dent;
	struct stat st;
	chdir(dirname);
	while((dent = readdir(dir)) != NULL)
	{
		stat(fullpath(get_current_dir_name(), dent->d_name), &st);
		switch (st.st_mode & S_IFMT) {
			case S_IFBLK:
				puts("<BLK>");
				break;
			case S_IFCHR:
				puts("<CHR>");			
				break;
			case S_IFDIR:
				puts("<DIR>");			
				break;
			case S_IFIFO:
				puts("<FIFO>");			
				break;
			case S_IFLNK:
				puts("<LNK>");			
				break;
			case S_IFREG:
				puts("<REG>");			
				break;
			case S_IFSOCK:
				puts("<SOCK>");			
				break;
			default:
				break;
		}
		puts(dent->d_name);
		puts("\n");
	}
    return 0;
}
