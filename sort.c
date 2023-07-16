#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void percolate(int index0, int index1) {
	int temp = index0;
	index0 = index1;
	index1 = temp;
}

void heapify(int arr[], int n, int i) {
	int root = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	/* Establish if the children are larger than the
	   parent or not. */ 
	if ((left < n) && (arr[left] > arr[root])) {
		root = left;
	}
	if ((right < n) && (arr[right] > arr[root])) {
		root = right;
	}
	/* If the root greatest value isn't already the root
	(index 0) the it will be percolated.*/
	if (root != i) {
		percolate(&arr[i], &arr[root]);
		heapify(arr, n, root);
	}
	
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	int i;
	for (i = (n / 2) - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	for (i = n - 1; i >= 0; i--) {
		percolate(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Allocate memory for arrays

	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	// Populate the lower and upper ends of the array.
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	

	/* Populate the third array until one of the
	original arrays reaches an end. */
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

	/* Continue populating arrays while if one of the
	arrays were larger than the other. */

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
	free(L);
	free(R);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	int m;
	m = (l + r) / 2;
	if (r < l) {
		mergeSort(pData, r, m);
		mergeSort(pData, m+1, l);
		
	}
	else {
		mergeSort(pData, l,m);
		mergeSort(pData, m+1, r);
	}
	merge(pData, l, m, r);
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}