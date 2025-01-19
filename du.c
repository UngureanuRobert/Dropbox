#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

long dimensiune_fisier(const char *path){
	int fd = open(path, O_RDONLY);
	if (fd == -1){
		perror("Eroare deschidere fisier");
		return 0;
	}
	
	long size = 0;   	// dimensiunea totala
	ssize_t read_size;  	// dimensiunea citita
	char buffer[1024];  	// bufferul in care se baga ce e citit
	while ((read_size = read(fd, buffer, sizeof(buffer))) > 0){	//citesc din fisier cat timp exista ceva de citit in fisier
		size += read_size;
	}
	
	close(fd);
	return size;
}

void du(const char *path){
	DIR *director = opendir(path);
	long total_size = 0;
	
	struct dirent *curent; 		//va fi fila sau directorul curent care se citeste
	while ((curent = readdir(director)) != NULL){	// cat timp bag in curent fila/directorul pe care il citesc
	
		// Daca este directorul curent sau directorul parinte, se trece mai departe
		if (strcmp(curent->d_name, ".") == 0 || strcmp(curent->d_name, "..") == 0){  // d_name == variabila din structura dirent
			continue;
		}
		
		char full_path[1024];
		// snprintf pentru formatarea lui full_path ca "%s/%s" pentru path-ul complet
		snprintf(full_path, sizeof(full_path), "%s/%s", path, curent->d_name);
		
		if (curent->d_type == DT_DIR){ 		//Directory-Entry, daca tipul(d_type) al obiectului de tip struct dirent este director(DT_DIR)
			du(full_path);			//Apelam recursiv pentru continutul directorului
		}
		else if (curent->d_type == DT_REG){	//Directory-Entry, daca tipul(d_type) al obiectului de tip struct dirent este fisier(DT_REG)
			total_size += dimensiune_fisier(full_path);  		//Apelam pentru fisier
		}
		
	}

	closedir(director);
	printf("Dimensiune %s este de %ld bytes\n", path, total_size);
}
