#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ftw.h>
#include "cp.h"
#include "du.h"
#include "ls.h"
#include "rm.h"

void comenzi(){
	printf("\nComenzi valabile:\n");
	printf("cp\n");
	printf("du\n");
	printf("ls\n");
	
	printf("rm\n");
	printf("iesire\n");
}

int main()
{
	char command[350], parametru1[250], parametru2[250];
	do{
		comenzi();
		printf(">>> ");
		scanf("%s", command);
		
		if (strcmp(command, "cp") == 0){
			printf("Introduceti fisierul sursa: ");
			scanf("%s", parametru1);
			FILE *sursa = fopen(parametru1, "r");
			if (sursa == NULL){
				printf("Fila sursa nu exista!\n");
				continue;
			}
			fclose(sursa);
			
			printf("Introduceti fisierul destinatie: ");
			scanf("%s", parametru2);
			FILE *destinatie = fopen(parametru2, "w");
			if (destinatie == NULL){
				printf("Fila destinatie nu exista!\n");
				continue;
			}
			fclose(destinatie);
			
			cp(parametru1, parametru2);
		}
		else if (strcmp(command, "du") == 0){
			printf("introduceti directorul: ");
			scanf("%s", parametru1);
			DIR *director = opendir(parametru1);
			if (director == NULL){
				printf("Nu se poate deschide directorul dat!\n");
				continue;
			}
			closedir(director);
			
			du(parametru1);
		}
		else if (strcmp(command, "ls") == 0)
		{
		  printf("introduceti directorul: ");
		  scanf("%s", parametru1);
		  DIR *director = opendir(parametru1);
		  if (director == NULL)
		  {
		    printf("Nu se poate deschide directorul dat!\n");
		    continue;
		  }
		  closedir(director);
		  
		  ls(parametru1);
		}
		else if (strcmp(command, "rm") == 0)
		{
		  printf("introduceti path-ul obiectului: ");
		  scanf("%s", parametru1);
		  rm(parametru1);
		}
		else if (strcmp(command, "iesire") == 0){
			printf("Parasire shell\n");
		}
		else {
			printf("Comanda invalida! Incercati din nou!\n");
		}
	}
	while (strcmp(command, "iesire") != 0); 
	
	return 0;
}
