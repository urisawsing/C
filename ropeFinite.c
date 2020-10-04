#include <stdio.h>
#include <math.h>
#define X 6
#define T 30
#define L 0.345678
float matrix[X+1][T+2];
void initial(){
	int a;
	for(a=0;a<X+1;a++){
		
		matrix[a][0]=sin((a*M_PI)/X);
		matrix[a][1]=sin((a*M_PI)/X)*cos(M_PI/T);	
	} 
}
float recursive(x,t){
	float Ux=2*(1-L)*matrix[x][t-1]+L*matrix[x-1][t-1]+L*matrix[x+1][t-1]-matrix[x][t-2];
	
	return Ux;
}
int main(){
	int i;
	int j;
	for(i=0;i<X+1;i++){
		for(j=0;j<T+2;j++){
			matrix[i][j]=0.0;
		}
	}
	initial();
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
