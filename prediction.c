#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// --------------------------------------------------

double *read_array(char filename[],  int m, int n);
double* prod_matrice_vect(double* mat, double* vec,
	int nbLig, int nbCol);
double* addition_vect(double* vec1, double* vec2, int size);
int argmax(double* vec, int size);

// --------------------------------------------------

int main(int argc, char* argv[]){
	/*int nbLig = 2;
	int nbCol = 2;
	double matrice[] = {1, 2, 3, 4};
	double vect[] = {1, 3};
	double vect2[] = {3, 4};

	double* res1 = prod_matrice_vect(matrice, vect, nbLig, nbCol);
	double* res2 = addition_vect(res1, vect2, nbLig);

	for (int i = 0; i < nbLig; i++){
		printf("res2[%d] : %f\n", i, res2[i]);
	}

	free(res1);

	int maxindex = argmax(res2, nbLig);
	printf("max : %d\n", maxindex);


	free(res2);*/


	double* W = read_array("matrice_w.txt", 10, 514);
	double* b = read_array("vecteur_b.txt", 10, 1);
	double* vec = read_array("fichier_test.csv", 514, 1);

	double* res1 = prod_matrice_vect(W, vec, 10, 514);
	double* res2 = addition_vect(res1, b, 10);

	for(int i = 0; i < 10; i++) {
		printf("%f\n", res2[i]);
	}

	int indice = argmax(res2, 10);

	printf("argmax : %d\n", indice);

	free(res1);
	free(res2);
	free(W);
	free(b);
	free(vec);

	return 0;
}


// ------------------------------------------------


double *read_array(char filename[],  int m, int n){
	// m : nb lignes
	// n : nb colonnes

    FILE* fp = fopen(filename, "r");
    //double arr[10][514];
    if (!fp)
        printf("Can't open file\n");
 
    else {
    	double* arr = malloc(sizeof(double)*(m*n));

        char buffer[4096];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,
                     4096, fp)) {
            column = 0;
            char* value = strtok(buffer, ", ");
            while (value) {
                arr[column + row*n] = atof(value);
                value = strtok(NULL, ", ");
                column++;
            }
            row++;
        }

        printf("row * column = %d\n", (row*column));
        printf("%d, %d\n", row, column);

        fclose(fp);

        return arr;
    }
}

double* prod_matrice_vect(double* mat, double* vec,
	int nbLig, int nbCol){
	/* Effectue le produit mat . vec, où la matrice est codée ligne par ligne
	(a11, a12, ..., a1n, a21, ...) et le vecteur de façon classique, de la composante
	0 à la n-ème.
	nbLig, nbCol : pour la matrice. Le nombre de lignes du vecteur est nécessairement
	égal à nbCol*/

	double *res = malloc(sizeof(double) * nbLig);

	for (int i = 0; i < nbLig; i++){	// Ligne par ligne
		for (int j = 0; j < nbCol; j++){	// Ligne fixée, col par col
			res[i] += vec[j]*(mat[(i * nbLig) + j]);
		}
	}

	return res;
}

double* addition_vect(double* vec1, double* vec2, int size){
	double* res = malloc(sizeof(double) * size);

	for (int i = 0; i < size; i++){
		res[i] = vec1[i] + vec2[i];
	}

	return res;
}

int argmax(double* vec, int size){
	int indice = 0;

	for (int i = 0; i < size; i++){
		if (fabs(vec[i]) > fabs(vec[indice])){
			indice = i;
		}
	}
	return indice;
}


