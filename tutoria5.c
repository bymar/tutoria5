#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *sumLine(void *arrayElem);
int count = 0;
int finalSum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void main(void)
{	
	int matrizSize = 0;
	scanf("%d", &matrizSize);
	int matriz[matrizSize][matrizSize];

	for (int x = 0; x < matrizSize; x++) {
		for (int y = 0; y < matrizSize; y++)
			scanf("%d", &matriz[x][y]);
	}

	pthread_t threads[matrizSize]; 
	for (int i = 0; i < matrizSize; i++) { 

		int *line = malloc(matrizSize * sizeof(int));
		if (pthread_create(&(threads[i]), NULL, sumLine, (void*)line))
			printf("error creating thread %d", i);

		for (int j = 0; j < matrizSize; j++)
			line[j] = matriz[i][j];
	}

	for (int index = 0; index < matrizSize; index++)
		pthread_join(threads[index], NULL);

	printf("%d\n", finalSum);

}

void *sumLine(void *arrayLine)
{	

	int *arrLine = (int *)arrayLine; 
	int size = sizeof(*arrLine);
	int totalLine = 0;

	for (int line = 0; line < size; line++)
		totalLine += arrLine[line];

	pthread_mutex_lock(&mutex);
	count += 1;
	finalSum += totalLine;
	pthread_mutex_unlock(&mutex);
}