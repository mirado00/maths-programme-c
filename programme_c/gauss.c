#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *allocation1D(int dim);
double **allocation2D(int dim1, int dim2);
void getData(int *dim, double ***A, double **b, double **result, int **p);
void displayResult(int dim, double **A, double *b, double *result, int *p);
void triangulaire(int dim, double **a, double *b, int *p);
void resolution(int dim, double **A, double *b, double *result, int *p);
void gauss(int dim, double **A, double *b, double *result, int *p);
void problem(char *chaine);
void cleanUp(double **A , double *b,double *result, int *p);

int main(){
    printf("Resolution de système d'équation linéaire en utilisant le méthode de Gauss\n");
    //entrer de donner
    int dim=0;
    double **A=NULL;        //adresse de la matrice du problème
    double *b=NULL;         //adresse du vecteur second membre
    double *result=NULL;        //adresse du vecteur solution
    int *p=NULL;          //index pivot
    getData(&dim, &A, &b, &result, &p);
    //resolution, 
    displayResult(dim, A, b, result, p);
    gauss(dim, A, b, result, p);
    
    //afficher le résultat
    displayResult(dim, A, b, result, p);

    //liberer le mémoire
    cleanUp(A, b, result, p);
   
    return 0;
}

double *allocation1D(int dim){
    double *v=NULL;
    v=(double*)malloc(sizeof(double)*dim);
    if(v==NULL)problem("problème d'allocation\n");
    return v;
}
double **allocation2D(int dim1, int dim2){
    double **v=(double**)malloc(sizeof(double*)*dim1);
    for (int i=0;i<dim1;i++){
        v[i]==NULL;
        v[i]=(double*)malloc(sizeof(double)*dim2);
        if(v[i]==NULL)problem("problème d'allocation\n");
    }
    return v;
}
void getData(int *dim, double ***A, double **b, double **result, int **p){
    FILE *file=NULL;
    double **M=NULL;
    double *s=NULL;
    double *x=NULL;
    int *pt=NULL;
    file=fopen("./file_sys_lineaire.txt", "r");     //ouvrir le fichier
    if(file==NULL)problem("impossible d'ouvrir le fichier file_sys_lineaire");
    else{
        fscanf(file, "%d", dim);
        M=allocation2D(*dim, *dim);
        s=allocation1D(*dim);
        x=allocation1D(*dim);
        pt = malloc(sizeof(int)**dim);
        for(int i=0;i<*dim;i++){
            for (int j=0;j<*dim;j++){
                fscanf(file, "%lf ", &M[i][j]);
            }
        }

        for (int i=0;i<*dim;i++){
            fscanf(file, "%lf", &s[i]);
        }
    }
    for (int i=0;i<*dim;i++){
        pt[i]=i;
    }
    *A=M;
    *b=s;
    *result=x;
    *p=pt;

}
void displayResult(int dim, double **A, double *b, double *result, int *p){
    //printf("-----------------------resultat-----------------------------\n");
    printf("Element du matrice:\n");
    for (int i=0;i<dim;i++){
        for (int j=0;j<dim;j++){
            printf("\t%g",  A[p[i]][j]);
        }
        printf("\n");
    }
    printf("valeur du second membre\n");
    for (int i=0;i<dim;i++){
        printf("b[%d]:%g", i , b[p[i]]);
        printf("\n");
    }
    printf("\nsolution=(");
    for (int i=0;i<dim;i++){
        printf("%g   ", result[i]);
    }
    printf(")\n");
    
}

void triangulaire(int dim, double **a, double *b, int *p){
    int i=0, j=0, k=0, tmp=0;
    for (k=0; k<dim; k++){
        //find pivot
        
        for (int line=k+1;line<dim;line++){
            if(fabs(a[p[line]][k])>fabs(a[p[k]][k])){
               tmp=p[line];
               p[line]=p[k];
               p[k]=tmp;
            }
        }
        
        for (i=k+1; i<dim;i++){
            for (j=k+1;j<dim;j++){
                a[p[i]][j] = a[p[i]][j] - ((a[p[i]][k] / a[p[k]][k]) * a[p[k]][j]);
            }
            b[p[i]] = b[p[i]] - ((a[p[i]][k] / a[p[k]][k]) * b[p[k]]);
            a[p[i]][k]=0;
        }
    }
}

void resolution(int dim, double **A, double *b, double *result, int *p){
    int N=dim;
    double tmp=0.0;
    for (int i=N-1;i>=0;i--){
        tmp=0;
        for(int j=i+1;j<N;j++){
            tmp+=A[p[i]][j]*result[j];
        }
        result[i]=(b[p[i]]-tmp)/A[p[i]][i];
    }
}
void gauss(int dim, double **A, double *b, double *result, int *p){
    triangulaire(dim, A, b, p);
    resolution(dim, A, b, result, p);
}
void problem(char *chaine){
    printf("%s", chaine);
    exit(1);
}
void cleanUp(double **A , double *b,double *result, int* p){
        if(A!=NULL){
            free(A);
            printf("liberation de A \n");
        }
        if(result!=NULL){
            free(result);
            printf("liberation de result \n");

        }
        if(b!=NULL){
            free(b);
            printf("liberation de b \n");

        }
        if(p!=NULL){
            free(p);
            printf("liberation de p \n");

        }

}
