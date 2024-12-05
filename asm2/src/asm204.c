#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat sb;

    if (argc != 2)
    {
        printf("Argument error\n");
        return 1;
    }

    if (lstat(argv[1], &sb) == -1)
    {
        printf("File doesn't exit");
    }

    printf("File name:                %s\n", argv[1]);

    printf("File type:                ");
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }

    printf("Last file modification:   %s", ctime(&sb.st_mtime));
    printf("File size:                %jd bytes\n", (intmax_t)sb.st_size);

    return 0;
}

