#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void display(int n, int D[n][n], int a){
	int i,j;
	printf("D[%d]=w",a);
	printf("\n");
	for(i=1;i<n;i++){
		for(j=1;j<n;j++){
			printf("\t%d", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void graphinit(int n, int graph[n][n]){
	int i,j;
	for(i=1;i<n;i++){
		for(j=1;j<n;j++){
			graph[i][j]=0;
		}
	}
}

void distminit(int n, int graph[n][n], int D[n][n]){
	int i,j,k;
	
	for(i=1;i<n;i++){
		for(j=1;j<n;j++){
			if(i!=j && graph[i][j]==0){
				graph[i][j]=9999;
			}
			D[i][j]=graph[i][j];
		}
	}
}
	

void floyd(int n, int D[n][n]){
	
	int i,j,k;
		
	display(n,D,0);
	
	for(k=1;k<n;k++){
		for(i=1;i<n;i++){
			for(j=1;j<n;j++){
				if(D[i][j]>(D[i][k]+D[k][j])){
					D[i][j] = D[i][k]+D[k][j];
				}
			}
		}
		display(n,D,k);
	}
}

void apsp(int n, int D[n][n]){
	int i,j;
	printf("Source --> Destination => Path-length");
	printf("\n");
	for(i=1;i<n;i++){
		for(j=1;j<n;j++){
			printf("%d --> %d => %d", i,j,D[i][j]);
			printf("\n");
		}
	}
}
	


int main(){
	int n,row,col,u,v,z,k,i=0;
	
	char x[200];
	printf("Enter the input filename with extension: ");
	scanf("%s",x);
	FILE *file = fopen(x,"r");
	if(file==NULL){
		printf("File doesn't exist!!");
	}
	
	fscanf(file,"%d",&n)!=EOF;
	
	z=n+1;
	
	int graph[z][z];
	graphinit(z,graph);
	
	
	while(fscanf(file, "%d %d %d", &u, &v, &k)!=EOF){
		graph[u][v]=k;
	}
	
	
	fclose(file);
	
	printf("\n");
	
	int D[z][z];
	distminit(z,graph,D);
	
	floyd(z,D);
	printf("The required All Pair Shortest Paths are: \n\n");
	apsp(z,D);
	//printf("\n");
	
	
}
