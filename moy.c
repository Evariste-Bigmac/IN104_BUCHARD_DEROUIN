#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "moy.h"

// LONGUEUR : NOMBRE D'ECHANTILLONS PAR PISTE
// LARGEUR : NOMBRE DE PISTES

double moyenne(double* data, int longueur) {
	double M = 0;
	for(int i = 0; i < longueur; i++) {
		M += data[i];
	}
	M = M / longueur;
	return(M);
}

double ecart(double* data, int longueur) {
	double S = 0;
	double M = moyenne(data, longueur);
	for(int i = 0; i < longueur; i ++) {
		S += (data[i] - M) * (data[i] - M);
	}
	S = S / longueur;
	S = sqrt(S);
	return(S);
}

double* mvect (double* matrice, int longueur_ech, int nb_ech) {
	printf("mvect : debut\n");

	double* res = malloc(sizeof(double) * nb_ech);

	printf("mvect : alloc OK\n");

	double intermedivecteur[longueur_ech];

	for(int i = 0; i < nb_ech; i++) {		// ligne
		for(int j = 0; j < longueur_ech; j++) {		// colonne
			intermedivecteur[j] = matrice[j*nb_ech + i];
			//intermedivecteur[i] = matrice[i + k*nb_ech];
			//printf("i,k : %d %d\n", i, k);
		}

		res[i] = moyenne(intermedivecteur, longueur_ech);
	}

	printf("mvect OK\n");
	return (res);
}

double* ecvect (double* matrice, int longueur_ech, int nb_ech) {
	double* resu = malloc(nb_ech * sizeof(double));
	for(int i = 0; i < nb_ech; i++) {
		double intermedivecteur[longueur_ech];
		for(int j = 0; j < longueur_ech; j++) {
			intermedivecteur[j] = matrice[j*nb_ech + i];
		}
		//printf("ecvect : avant ecart\n");
		double M = ecart(intermedivecteur, longueur_ech);
		resu[i] = M;
}
	return (resu);
}

/*
int main() {
	double matrice [20];
	for(int i = 0; i < 20; i++) {
		matrice[i] = i;
	}
	double *moyvect =  mvect(matrice, 4, 5);
	printf("%f\n %f\n %f\n %f\n %f\n", moyvect[0], moyvect[1], moyvect[2], moyvect[3], moyvect[4]);
	free(moyvect);

	double *vectecart = ecvect(matrice, 4, 5);
	printf("%f\n %f\n %f\n %f\n %f\n", vectecart[0], vectecart[1], vectecart[2], vectecart[3], vectecart[4]);
	free(vectecart);
}*/