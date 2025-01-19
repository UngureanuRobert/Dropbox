#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int mv(const char *src, const char *dst){
	int src_fd, dst_fd;
	ssize_t rdbytes, wrbytes;
	char buffer[1024];
	
	char *nume_fila, aux[1024];
	struct stat x;
	if (stat(dst, &x) == 0 && S_ISDIR(x.st_mode)){
		nume_fila = strrchr(src, '/');
		if (nume_fila != NULL) nume_fila++;
		else nume_fila = (char *)src;
		
		snprintf(aux, sizeof(aux), "%s/%s", dst, nume_fila);
		dst = aux;
	}
	
	src_fd = open(src, O_RDONLY);
	if (src_fd == -1){
		perror("Eroare deschidere fisier sursa\n");
		return errno;
	}
	
	dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (dst_fd == -1){
		perror("Eroare deschidere fisier destinatie\n");
		close(src_fd);
		return errno;
	}
	
	while ((rdbytes = read(src_fd, buffer, sizeof(buffer))) > 0){
		wrbytes = write(dst_fd, buffer, rdbytes);
		if (wrbytes != rdbytes){
			perror("Eroare la scrierea in fisierul destinatie\n");
			close(src_fd);
			close(dst_fd);
			return errno;
		}
	}
	if (rdbytes == -1){
		perror("Eroare la citirea fisierului sursa\n");
		close(src_fd);
		close(dst_fd);
		return errno;
	}
	
	close(src_fd);
	close(dst_fd);
	
	if (unlink(src) == -1){
		perror("Eroare la stergerea sursei\n");
		return errno;
	}
	printf("Fisierul a fost mutat cu succes!\n");
	return 0;
}

