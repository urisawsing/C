/*
   ###########################################################
    Rope time evolution with finite differences method  in C 
   ###########################################################
specific initial conditions set,
Iterating T times, 
giving a matrix X+1 times T+2 with every rope state in every T in a txt file

Oriol Fernández Serracanta
*/


#include <stdio.h>
#include <math.h>
/*some constants, X the lenght of the rope and T the time while we will iterate the system, L is a constant needed for the iteration process*/
#define X 6
#define T 30
#define L 0.345678
float matrix[X+1][T+2];
void initial(){
/*initial two states, a sine dispositon and a slightly evolved state in T=1*/
	int a;
	for(a=0;a<X+1;a++){
		matrix[a][0]=sin((a*M_PI)/X);
		matrix[a][1]=sin((a*M_PI)/X)*cos(M_PI/T);	
	} 
}
float recursive(x,t){
/*iteration method of finite differences*/
	float Ux=2*(1-L)*matrix[x][t-1]+L*matrix[x-1][t-1]+L*matrix[x+1][t-1]-matrix[x][t-2];
	
	return Ux;
}
int main(){
	/*declaring index variables and initial conditions of the matrix*/
	int i;
	int j;
	for(i=0;i<X+1;i++){
		for(j=0;j<T+2;j++){
			matrix[i][j]=0.0;
		}
	}
	initial();
	/*evolution loop*/
	for (i=2;i<T+2;i++){
		for(j=1;j<X;j++){
			matrix[j][i]=recursive(j,i);
		}	
	}
	/*################################################################
	/*file stuff, first the final matrix A2 and then the Ain in a txt
	##################################################################*/
	FILE * fp;
	/*opening file*/
	fp=fopen("finitedif.txt","w");
	if(fp==NULL){
		printf("error opening file\n");
	}
	/*writing*/
	
	for(i=0;i<T+2;i++){
		for(j=0;j<X+1;j++){
			fprintf(fp,"%f",matrix[j][i]);
			printf("%f",matrix[j][i]);
			fprintf(fp,"\t");
			printf("\t");
		}
		fprintf(fp,"\n");
		printf("\n");
	}
	fclose(fp);		
	
	
	
	
}
