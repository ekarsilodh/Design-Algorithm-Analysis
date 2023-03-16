//Find the minimum number of scalar multiplication needed for chain of matrix whose sequences are < 5, 10, 3, 12, 5, 50, 6 > using the dynamic programming technique.

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


void minitialize(int n, int M[n][n]){
	int row,col;
	for(row=0;row<n;row++){
		for(col=0;col<n;col++){
			if(row<col){
				M[row][col]=INT_MAX;
			}
			else if(row>col){
				M[row][col]='-';
			}
		}
	}	

}

void opmini(int n, int opm[n][n]){
	int row,col;
	for(row=0;row<n;row++){
		for(col=0;col<n;col++){
			if(row<col || row==col){
				opm[row][col]=0;
			}
			else if(row>col){
				opm[row][col]='-';
			}
		}
	}
}

void parenthesis(int i, int j, int n, int opm[n][n])
{
    if (i == j) {
        printf("A%d", i);
        return;
    }
    printf("(");
    parenthesis(i, opm[i][j], n, opm);
    printf("*");
    parenthesis(opm[i][j] + 1, j, n, opm);
    printf(")");
}


	

int findM(int n, int d[], int M[n][n], int opm[n+1][n+1]){
	int i,j,k,x;
	
	
	for(i=n;i>0;i--){
		for(j=i;j<n+1;j++){
			if(i==j){
				M[j-1][j-1]=0;
			}
			else if(i<j){
				int min=INT_MAX;
				for(k=i;k<j;k++){
					x=M[i-1][k-1]+M[k][j-1]+(d[i-1]*d[k]*d[j]);
					if(x<min){
						min=x;
						opm[i][j]=k;
					}
					M[i-1][j-1]=min;
				}
			}
		}	
	}
	
    	
}

		
				


void display(int n, int M[n][n]){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d\t", M[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(){
	int size,i=0,v,min;
	
	char x[200];
	printf("\nEnter the input filename with extension: ");
	scanf("%s",x);
	FILE *file = fopen(x,"r");
	fscanf(file,"%d",&size)!=EOF;
	int arr[size];
	printf("\nThe given array is: ");
	while(fscanf(file,"%d",&arr[i])!=EOF){
		printf("%d ",arr[i]);
		i++;
	}
	fclose(file);
	
	printf("\n\n");
	
	v=size-1;
	
	int M[v][v];
	int opm[size][size];
	minitialize(v,M);
	opmini(size,opm);
	
	findM(v,arr,M,opm);
	display(v,M);
	
	
	printf("\nThe minimum no. of multiplication required: %d\n", M[0][v-1]);
	printf("\nOptimal Parenthesization is: ");
    	parenthesis(1, v, size, opm);
    	printf("\n\n");
	
	
	
}
