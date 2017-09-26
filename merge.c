#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
 
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 

void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
 

int main(int argc, char *argv[])
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Programa feito para vetores com tamanho par
    int arr[] = {12, 11, 13, 5, 6, 7, 3, 10, 4, 1, 8, 15};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    
    int *v1 = (int *)malloc(arr_size * sizeof(int));
    int *v2 = (int *)malloc((arr_size/2) * sizeof(int));
    
    
    //Separando o vetor original em duas partes
    for(int i = 0; i <= ((arr_size/2)-1); i++){
		v1[i] = arr[i];
		v2[i] = arr[i+(arr_size/2)];		
	}
    
    
    
    if(rank == 0){
		
		//Ordenando a primeira parte
		mergeSort(v1, 0, ((arr_size/2)-1));
		
		//Recebendo a segunda parte ordenada pelo processo dois
		MPI_Recv(v2, (arr_size/2), MPI_INT, 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		
		//Juntando a primeira com a segunda parte
		for(int i = 0; i <= ((arr_size/2)-1); i++){
			v1[i + (arr_size/2)] = v2[i];
		}
		
		//Ordenando o novo vetor 
		mergeSort(v1, 0, arr_size-1);
		
		//Imprimindo o vetor geral ordenado
		printArray(v1, arr_size);
	
	
	}else if(rank == 1){
		
		//Ordenando a segunda parte
		mergeSort(v2, 0, ((arr_size/2)-1));
		
		//Eviando a segunda parte ordenada para o processo um
		MPI_Send(v2, (arr_size/2), MPI_INT, 0, 0, MPI_COMM_WORLD);
	
	}		   
    
    MPI_Finalize();
    
    return 0;
}
