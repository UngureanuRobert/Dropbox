#include <stdio.h>
#include <unistd.h> //read, write, close
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void mkdr(const char *path)
{
  struct stat st;
  if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
  {
    printf("Directorul %s deja existent!\n", path);
    return;
  }
  else
  {
    if (mkdir(path, S_IRWXU) == -1)
    {
      perror("Eroare la crearea directtorului.\n");
      return;
    }
  }
  printf("Directorul %s a fost creat.\n", path);
}

