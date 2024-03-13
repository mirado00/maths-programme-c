#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *allocation1D(int dim);
double **allocation2D(int dim1, int dim2);
void getData(int *dim, double ***A, double **b, double **x, double **y);
void displayResult(double **A , double *b ,double *x ,int dim,double *y);
void cholesky(double **A,double *b ,double*x ,int dim,double *y);
void resolution(int dim, double **A, double *b, double *result);
void problem(char *chaine);
void cleanUp(double **A , double *b,double *x, double* y);


int main(){
    printf("Resolution de système d'équation linéaire en utilisant le méthode de Cholesky\n");
    //entrer de donner
    int dim=0;
    double **A=NULL;        //adresse de la matrice du problème
    double *b=NULL;         //adresse du vecteur second membre
    double *x=NULL;         //adresse du vecteur solution
    double *y=NULL;    
    getData(&dim, &A, &b, &x, &y);

    //resolution
    cholesky(A, b, x, dim, y);

    //afficher le résultat
    displayResult( A, b, x,dim, y);

    //liberer le mémoire
    cleanUp(A, b, x, y);
   
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
void getData(int *dim, double ***A, double **b, double **x, double **y){
    FILE *file=NULL;
    double **M=NULL;
    double *s=NULL;
    double *R=NULL;
    double *Y=NULL;

    file=fopen("./file_sys_lineaire.txt", "r");     //ouvrir le fichier
    if(file==NULL)problem("impossible d'ouvrir le fichier file_sys_lineaire");
    else{
        fscanf(file, "%d", dim);
        M=allocation2D(*dim, *dim);
        s=allocation1D(*dim);
        R=allocation1D(*dim);
        Y=allocation1D(*dim);


        for(int i=0;i<*dim;i++){
            for (int j=0;j<*dim;j++){
                fscanf(file, "%lf ", &M[i][j]);
            }
        }

        for (int i=0;i<*dim;i++){
            fscanf(file, "%lf", &s[i]);
        }
    }
    *A=M;
    *b=s;
    *x=R;
    *y=Y;

}
void displayResult(double **A , double *b ,double *x ,int dim,double *y){
    printf("affichage \n");
    printf("%d \n",dim);
    for(int i=0;i<dim;i++){
        printf("b[%d] = %lf \n",i,b[i]);

    }
    for(int i=0;i<dim;i++){
        for(int j=0 ; j<dim;j++){
            printf("%lf\t ",A[i][j]);
        }
        printf("=  %lf\t",b[i]);
        printf("\n");
    }

		for(int i=0;i<dim;i++){
		printf("x[%d]=%lf \n",i,x[i]);
		}


}
void cholesky(double **A,double *b ,double*x ,int dim,double *y){
/// triangularisation
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            double somme=0;
            if(j <i){
                for(int k=0;k<=j-1;k++){
                    somme+=(A[i][k]*A[j][k]);
                }
                A[i][j]=((A[i][j] - somme)/(A[j][j]));
            }
            else if(j>i){
                A[i][j]=0;
            }
            
            else if(i==j){
                double somme2=0;
                for(int k=0;k<=i-1;k++){
                    somme2 +=(A[i][k]*A[i][k]);
                }
                A[i][i]=sqrt(A[i][i] - (somme2));
            }
        }
    }

	/// resilution de l equation B.y=b
    for(int i=0;i<dim;i++){
        double somme3=0;
        for(int j=0 ; j<dim;j++){
            somme3 += (A[i][j]*y[j]);
        }
        y[i]=((b[i]-somme3)/((A[i][i])));
      
    }
    // resolution de l equation Bt.x=y
    for(int i=dim-1;i>=0;i--){
		double somme4=0;
        for(int j=0 ; j<dim;j++){
              somme4 += (A[j][i]*x[j]);
        }
		x[i]=((y[i]-somme4)/((A[i][i])));
      
    }
}


void resolution(int dim, double **A, double *b, double *result){
    int N=dim;
    double tmp=0.0;
    for (int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            tmp+=A[N-i-1][j]*result[j];
        }
        result[N-i-1]=(b[N-i-1]-tmp)/A[N-i-1][N-i-1];
    }
}

void problem(char *chaine){
    printf("%s", chaine);
    exit(1);
}

void cleanUp(double **A , double *b,double *x, double* y){
    if(A!=NULL){
        free(A);
        printf("\n\nliberation de A \n");
    }
    if(x!=NULL){
        free(x);
        printf("liberation de x \n");

    }
    if(b!=NULL){
        free(b);
        printf("liberation de b \n");

    }
    if(y!=NULL){
        free(y);
        printf("liberation de p \n");

    }

}


