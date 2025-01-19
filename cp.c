#include <stdio.h>
#include <unistd.h> //read, write, close
#include <errno.h>
#include <string.h>
#include <fcntl.h> //open, flags
#include <stdlib.h>

void cp(const char *src, char *dst)
{
  int src_fd = open(src, O_RDONLY);
  if (src_fd == -1)
  {
    perror("Eroare la deschiderea fisierului sursa");
    return;
  }
  int dst_fd = open(dst, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  if (dst_fd == -1)
  {
    perror("Eroare la deschiderea fisierului destinatie");
    close(src_fd);
    return;
  }
  char buff[2048];
  ssize_t rdbytes, wrbytes;
  while ((rdbytes = read(src_fd, buff, sizeof(buff))) > 0)
  {
    wrbytes = write(dst_fd, buff, rdbytes);
    if (rdbytes != wrbytes)
    {
      perror("Nu s-a putut scrie corect in fisierul destinatie");
      close(src_fd);
      close(dst_fd);
      return;
    }
  }
  close(src_fd);
  close(dst_fd);
  printf("Fisierul a fost copiat.");
}

