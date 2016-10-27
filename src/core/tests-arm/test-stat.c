#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void
main(void)
{
  struct stat sbuf;

  printf("sizeof(struct stat) = %d...\n", sizeof(struct stat));
  if (stat("test-stat", &sbuf))
    {
      printf("cannot stat file...\n");
      exit(1);
    }

  printf("st_dev     = %Ld\n", sbuf.st_dev);
  printf("st_ino     = %d\n", sbuf.st_ino);
  printf("st_mode    = %d\n", sbuf.st_mode);
  printf("st_nlink   = %d\n", sbuf.st_nlink);
  printf("st_uid     = %d\n", sbuf.st_uid);
  printf("st_gid     = %d\n", sbuf.st_gid);
  printf("st_rdev    = %Ld\n", sbuf.st_rdev);
  printf("st_size    = %d\n", sbuf.st_size);
  printf("st_blksize = %d\n", sbuf.st_blksize);
  printf("st_blocks  = %d\n", sbuf.st_blocks);
  printf("st_atime   = %d\n", sbuf.st_atime);
  printf("st_mtime   = %d\n", sbuf.st_mtime);
  printf("st_ctime   = %d\n", sbuf.st_ctime);
}

