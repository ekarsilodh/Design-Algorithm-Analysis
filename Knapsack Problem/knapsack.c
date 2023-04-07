//Fractional Knapsack Probelm

#include<stdio.h>
#include<stdlib.h>

typedef struct itemdetails{
	int num;
	float weight,value,vw;
}itemdetails;

typedef struct Item{
	int no,knpwt;
	itemdetails items[9999];
}Item;

float max(float a, float b){ 
	return (a > b) ? a : b; 
}

void details(Item item){
	int i,u,n=item.no;
	float v,w,x;
	printf("\nTotal no. of items = %d", n);
	printf("\nThe weight of the knapsack = %d", item.knpwt);
	printf("\n---------------------------------");
	printf("\nItem\tWeight\tValue\tV/W");
	printf("\n---------------------------------\n");
	for(i=0;i<n;i++){
		u=item.items[i].num;
		v=item.items[i].value;
		w=item.items[i].weight;
		x=item.items[i].vw;
		printf("%d\t%.0f\t%.0f\t%.2f\t",u,w,v,x);
		printf("\n");
	}
}

void vector(int n, float arr[]){
	int i;
	printf("<");
	for(i=0;i<n;i++){
		printf("%.2f", arr[i]);
		if(i!=n-1){
			printf(", ");
		}
	}
	printf(">\n");
}

void vectorzo(int n, int arr[]){
	int i;
	printf("<");
	for(i=0;i<n;i++){
		printf("%d", arr[i]);
		if(i!=n-1){
			printf(", ");
		}
	}
	printf(">\n");
}

void vwinit(Item item, float VW[]){
	int i,n=item.no;
	for(i=0;i<n;i++){
		VW[i]=item.items[i].vw;
	}
}

void winit(Item item, int W[]){
	int i,n=item.no;
	for(i=0;i<n;i++){
		W[i]=item.items[i].weight;
	}
}

void vinit(Item item, int V[]){
	int i,n=item.no;
	for(i=0;i<n;i++){
		V[i]=item.items[i].value;
	}
}

void svzoinit(Item item, int SVzo[]){
	int i,n=item.no;
	for(i=0;i<n;i++){
		SVzo[i]=0;
	}
}

void merge(float arr[], int lb, int ub, int mid) {
	int i=lb;
	int j=mid+1;
	float newArr[ub+1];
	int k=lb;
	
	while(i<=mid && j<=ub) {
		if(arr[i]>=arr[j]) 
			newArr[k++]=arr[i++];
		else
			newArr[k++]=arr[j++];
	}
	
	for(; i<=mid; i++)
		newArr[k++]=arr[i];
	for(; j<=ub; j++)
		newArr[k++]=arr[j];
	
	for(k=lb; k<=ub; k++)
		arr[k]=newArr[k];
}


void mergesort(float arr[], int lb, int ub) {
	if(lb<ub){
		int mid=(lb+ub)/2;
		mergesort(arr, lb, mid);
		mergesort(arr, mid+1, ub);
		merge(arr, lb, ub, mid);
	}
}

		
float fracknap(Item item, float VW[], float SV[]){
	int i,j,k,kwt,wt,n=item.no;
	float x,profit = 0.0;
	mergesort(VW,0,n-1);
	//display(VW, n);
	
	kwt=item.knpwt;
	i=0;
	wt=0;
	
	while(wt<kwt && i<n){
		for(j=0;j<n;j++){
			if(VW[i]==item.items[j].vw){
				if(wt + item.items[j].weight<=kwt){
					profit += item.items[j].value;
					wt += item.items[j].weight;
					SV[j]=1.0;
					printf("\nItem %d, having weight %.0f is completely added. Space left = %d",j+1,item.items[j].weight,(kwt-wt));
					if(wt==kwt){
						printf("\nThe knapsack is full. So no further items will be added.");
					}
					i++;
				}
				else if(wt<kwt && wt + item.items[j].weight>kwt){
					x=(kwt-wt)/item.items[j].weight;
					wt += (x*item.items[j].weight);
					profit += x*item.items[j].value;
					SV[j]=x;
					k = x*100;
					printf("\n%d%% of item %d, having total weight %.0f is added. Space left = %d",k,j+1,item.items[j].weight,(kwt-wt));
					if(wt==kwt){
						printf("\n\nThe knapsack is full. So no further items will be added.");
					}
					i++;
				}
			}
		}
	}
	return profit;
}


float zoknap(Item item, int n, int Wt, int V[], int W[], int SVzo[], int ZO[n+1][Wt+1]){
	int i,j,w,res,it,x=item.knpwt;
	
	for(i=0;i<n+1;i++){
		for(w=0;w<Wt+1;w++){
			if(i==0 || w==0){
				ZO[i][w]=0;
			}
			else if(W[i-1]<=w){
				ZO[i][w]=max(V[i-1]+ZO[i-1][w-W[i-1]],ZO[i-1][w]);
			}
			else{
				ZO[i][w]=ZO[i-1][w];
			}
		}
	}
	//display(n,Wt,ZO);
	res=ZO[n][Wt];
	w=Wt;
	for(i=n;i>0 && res>0;i--){
		if(res==ZO[i-1][w]){
			continue;
		}
		else{
			for(j=0;j<n;j++){
				if(W[i-1]==item.items[j].weight){
					it=item.items[j].num;
					x-=W[i-1];
					printf("\nAdded item %d, having weight %d. Space left = %d",it,W[i-1],x);
					SVzo[j]=1;
					break;
				}
			}
			res=res-V[i-1];
			w=w-W[i-1];
		}
	}
	return ZO[n][Wt];
}
			

int main(){
	int n,wt,i,u,choice;
	float v,w,fracprofit,zoprofit;

	char x[200];
	printf("Enter the input filename with extension:");
	scanf("%s",x);
	
	FILE *file = fopen(x,"r");
	if(file==NULL){
		printf("File doesn't exist!!");
	}
	
	fscanf(file,"%d",&n)!=EOF;
	fscanf(file,"%d",&wt)!=EOF;
	
	Item item;
	
	item.no=n;
	item.knpwt=wt;
	
	for(i=0;i<n;i++){
		(fscanf(file, "%d%f%f", &u, &w, &v)!=EOF);
		item.items[i].num=u;
		item.items[i].value=v;
		item.items[i].weight=w;
		item.items[i].vw=v/w;
	}
	fclose(file);
	
	printf("-------------------------------------");
	printf("\nThe given details are:");
	printf("\n---------------------------------");
	details(item);
	
	float VW[n],SV[n];
	int V[n],W[n],SVzo[n],ZO[n+1][wt+1];
	vwinit(item,VW);
	vinit(item,V);
	winit(item,W);
	svzoinit(item,SVzo);
	
	while(1){
		printf("\n--------------------------------------");
		printf("\n\033[1mSelect the type of knapsack:\033[0m\n1.Fractional Knapsack\n2.0/1 Knapsack\n3.Exit");
		printf("\n--------------------------------------");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		printf("--------------------------------------\n");
		switch(choice){
			case 1:
				printf("\n\033[1mFractional Knapsack Problem\033[0m");
				printf("\n------------------------------");
				fracprofit=fracknap(item,VW,SV);
	
				printf("\n\nThe solution vector is: ");
				vector(n,SV);
				printf("\nThe maximum profit is = %.2f\n",fracprofit);
								
				break;
				
			case 2:
				printf("\n\033[1m0/1 Knapsack Problem\033[0m");
				printf("\n------------------------------");
				zoprofit=zoknap(item,n,wt,V,W,SVzo,ZO);
	
				printf("\n\nThe solution vector is: ");
				vectorzo(n,SVzo);
				printf("\nThe maximum profit is = %.2f\n",zoprofit);
								
				break;
				
			case 3:
				exit(1);
				
			default:
				printf("\nPlease enter a valid choice!!");
		}
	}
	
	return 0;
				
	
}
		
	
	
