#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void removefile(const char *fila)
{
  if (remove(fila) == 0) printf("Fisierul %s a fost sters\n", fila);
  else
  {
    perror("Eroare la incercarea de a sterge fisierul\n");
    return;
  }
}


//vom face nested file tree walk, care porneste de la files si le removeaza, asigurand ca 
//directorul principal pe care vrem sa il stergem va fi ultimul sters

static int removedirector(const char *path, const struct stat *st, int typeflag, struct FTW *buff)
{
  if (typeflag == FTW_F) //FTW_f este file walk tree pentru fila
  {
    if (unlink(path) == 0) printf("Fila %s a fost stearsa.\n", path);
    else perror("Eroare la stergerea filei\n");
  }
  else if (typeflag == FTW_D) //FTW_D este ftw pt director
  {
    if (rmdir(path) == 0) printf("Directorul cu path %s a fost sters.\n", path);
    else perror("Eroare la stergerea directorului\n");
  }
  return 0; //nftw a mers corect pana acum, asa ca continua
}



void rm(const char *path)
{
  struct stat st;
  if (stat(path, &st) == -1)
  {
    perror("Eroare la obtinerea informatiilor despre obiect\n");
    return;
  }
  if (S_ISREG(st.st_mode)) removefile(path);
  else if (S_ISDIR(st.st_mode))
  {
    if (nftw(path, removedirector, 64, FTW_DEPTH) == -1)
    {
      perror("Eroare la stergerea directorului\n");
      return;
    }
    if (rmdir(path) == -1) perror("Nu s-a putut sterge directorul.\n");
    else printf("Directorul %s a fost sters.\n", path);
  }
  else 
  {
    perror("Obiectul nu este nici fila, nici director\n");
    return;
  }
}
