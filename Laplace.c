/*
   ###############################
	Laplace equation solver in C 
   ###############################
specific initial conditions set,
Iterating until reaching the error<tolerance,
finally giving two txt with the initial values of the matrix and the final values
matrix with a space nxm

Oriol Fernández Serracanta
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#define n 100
#define m 100
/*two iteration indexs i,j and the A1 A2 for each step, also Ain the initial values*/
int i;
int j;
float A1[n][m];
float Ain[n][m];
float A2[n][m];
void Jacobi(i,j){
	/*iteration step*/
	A2[i][j]=0.25*(A1[i+1][j]+A1[i-1][j]+A1[i][j-1]+A1[i][j+1]);
}
float Sinecont(i){
	/*sine function and some checks for the dtype*/
	float k=(i*M_PI/(n-1));
	return sin(k);
}
float totalerror(){
	/*error value after each step, also some checkings commented*/
	/*(it takes the difference between two same places in different time steps and gets the sum of all of them in the matrix)*/
	float error=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			error=error+sqrt(pow(A1[i][j]-A2[i][j],2));
			/*printf("%f",error);
			printf("\t");*/
		}
	}
	printf("%f",error);
	printf("\n");
	return error;
}
void Initial(){
	/*whole initial conditions set in a function*/
	/* (take in account is very important to set the initial conditions in A2, if not the error wont converge)*/
	for( i=0;i<n;i++){
		float s=Sinecont(i);
		A1[0][i]=0;
		A1[n-1][i]=0;
		A1[i][0]=s;
		A1[i][n-1]=s*exp(-M_PI);
		A2[0][i]=0;
		A2[n-1][i]=0;
		A2[i][0]=s;
		A2[i][n-1]=s*exp(-M_PI);
		
	}
}
int main(){
	/*defining variables, error will compute the error for each step and toler how small we want the error to be*/
	float err;
	float toler=0.01;
	
	
	/*###################################
	/*setting initial matrix A1 and Ain
	####################################*/
	for( i=0; i<n;i++){
		for( j=0;j<m;j++){
			A1[i][j]=0;	
		};
	};
	Initial();
	/*setting matrix Ain for data output*/
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			Ain[i][j]=A1[i][j];
		}
	}
	
	
	/*########################################################################
	algorithm itself, do the loop until the error is lower than the tolerance
	##########################################################################*/
	do{
		for(i=1;i<n-1;i++){
			for(j=1;j<m-1;j++){
				Jacobi(i,j);
			}
		}
		err=totalerror();
		for(i=1;i<n-1;i++){
			for(j=1;j<m-1;j++){
				A1[i][j]=A2[i][j];
			}
		}
	
	}while(err>toler);
	
	/*################################################################
	/*file stuff, first the final matrix A2 and then the Ain in a txt
	##################################################################*/
	FILE * fp;
	/*opening file*/
	fp=fopen("data.txt","w");
	if(fp==NULL){
		printf("error opening file\n");
		exit(1);
	}
	/*writing*/
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			fprintf(fp,"%f",A1[i][j]);
			fprintf(fp,"\t");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);	
	
	
	/*initial matrix writing*/
	FILE * fp1;
	fp1=fopen("datainit.txt","w");
	if(fp1==NULL){
		printf("error opening file\n");
		exit(1);
	}
	/*writing*/
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			fprintf(fp1,"%f",Ain[i][j]);
			fprintf(fp1,"\t");
		}
		fprintf(fp1,"\n");
	}
	fclose(fp1);	
	
}





































