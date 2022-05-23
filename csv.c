#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moy.h"
#include "csv.h"
#include "wave.h"

/*
0 : blues
1 : classical
2 : country
3 : disco
4 : hiphop
5 : jazz
6 : metal
7 : pop
8 : reggae
9 : rock
*/

void dump_csv(char* index, double *magnitude, int nbCol, int nbLig){

	printf("Entree dump_csv\n");

	
	double *moyvect =  mvect(magnitude, nbCol, nbLig);
	double *vectecart = ecvect(magnitude, nbCol, nbLig);

	//printf("Moy et sigma calcules\n");

	char filename[80];

	strcpy(filename, "fichier_test");
	//strcat(filename, index);
	strcat(filename, ".csv");

	FILE *f;
	f = fopen(filename, "w");

	if (f == NULL){
		printf("ENT\n");
		return;
	}

	//printf("dump_csv : debut dump\n");

	//fprintf(f, "10;");				// Ah, attention

	for (int i = 0; i < nbLig; i++){
		char buf1[50];
		char buf2[20];

		//printf("moyvect[%d] : %f\n", i, moyvect[i]);
		//printf("vectecart[%d] : %f\n", i, vectecart[i]);

		sprintf(buf1, "%f;", moyvect[i]);
		sprintf(buf2, "%f;", vectecart[i]);

		//printf("buf1.0 : %s\n", buf1);
		//printf("buf2.0 : %s\n", buf2);

		char *str1 = strcat(buf1, buf2);

		//printf("buf1.1 : %s\n", buf1);

		fprintf(f, buf1);
	}

	free(moyvect);
	free(vectecart);

	fprintf(f, "\n");

	fclose(f);
	
	/*
	char filename[80];

	strcpy(filename, "blues");
	strcat(filename, index);
	strcat(filename, ".csv");

	FILE *f;
	f = fopen(filename, "w");

	if (f == NULL){
		printf("ENT\n");
		return;
	}

	//printf("dump_csv : debut dump\n");

	fprintf(f, "0;");

	for (int i = 0; i < nbLig; i++){

		double *vec = mu_sigma(magnitude, nbCol, i);


		char buf1[50];
		char buf2[20];

		sprintf(buf1, "%f;", vec[0]);
		sprintf(buf2, "%f;", vec[1]);

		char *str1 = strcat(buf1, buf2);

		//printf("buf1.1 : %s\n", buf1);

		fprintf(f, buf1);


		free(vec);
	}*/

	printf("dump_csv : fin dump\n");	
}

void double_to_char(double d, char* str){
	sprintf(str, "%f", d);

	printf("%s\n", str);
}