#include <stdio.h>
#include <unistd.h> //read, write, close
#include <errno.h>
#include <string.h>
#include <fcntl.h> //open, flags
#include <stdlib.h>
#include <dirent.h> //pentru deschiderea directorului

void ls(const char *path)
{
  DIR *director;
  struct dirent *citire_director;
  director = opendir(path);
  if (director == NULL)
  {
    perror("Eroare la deschiderea directorului");
    return;
  }
  while ((citire_director = readdir(director)) != NULL)
  {
    printf("%s\t%d bytes\n", citire_director->d_name, citire_director->d_reclen);
  }
  if (closedir(director) == -1)
  {
    perror("Eroare la inchiderea directorului");
  }
}




