#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cp.h"

void comenzi(){
	printf("\nComenzi valabile:\n");
	printf("cp\n");
	
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
