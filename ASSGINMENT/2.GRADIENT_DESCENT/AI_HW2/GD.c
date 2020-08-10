#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define DIM 10
#define RAND_SEED 1
FILE *fin;
FILE *fo;
FILE *fcost;


void weight_order(float *arr);

int main() {
	// initialize input & target
	float input[DIM] = { 0.0, }, target;

	// initialize learning rate
	float lr = 0.001;

	// initialize weight
	srand(RAND_SEED);
	float w[DIM] = { 0.0, };
	for (int i = 0; i < DIM; i++)
		w[i] = ((float)rand() / RAND_MAX) - 0.5;

	// cost & delta & gradient
	float cost = 0.0;
	float delta = 0.0;
	float grad[DIM] = { 0.0, };
	float grad_sum[DIM] = { 0.0, };

	// file stream
	fopen_s(&fin, "trainingDB.dat", "rt");
	fopen_s(&fo, "output.dat", "wt");
	fopen_s(&fcost, "cost.dat", "wt");

	// clock
	clock_t start, end;

	start = clock();
	for (int epoch = 0; epoch < 1; epoch++) {
		for (int i = 0; i < 1000; i++) {
			// initialize prediction y
			float y = 0.0;

			/*		DATA READ		*/
			// x1 ~ x10 read
			for (int k = 0; k < DIM; k++)
				fscanf_s(fin, "%f", input + k);
			// target read
			fscanf_s(fin, "%f", &target);


			/*		OUTPUT COMPUTATION		*/
			for (int k = 0; k < DIM; k++)
				y += input[k] * w[k];
			cost = (float)0.5*pow(target - y, 2);
			delta = (target - y);

			/*		GRADIENT COMPUTATION	*/
			for (int k = 0; k < DIM; k++)
				grad[k] = input[k] * (y - target);
			for (int k = 0; k < DIM; k++)
				grad_sum[k] += grad[k];
		}

		/*		WEIGHT UPDATE		*/
		for (int k = 0; k < DIM; k++)
			w[k] -= lr * grad_sum[k] / (float)1000;

		/*		WEIGHT AND COST WRITE		*/
		for (int k = 0; k < DIM; k++)
			fprintf(fo, "%10.7f ", w[k]);
		if (epoch != 999)
			fprintf(fo, "\n");	// line change

		if (epoch != 999) fprintf(fcost, "%10.7f\n", cost);
		else fprintf(fcost, "%10.7f", cost);

		if (epoch == 499)
			printf("cost of 500th cost : %0.5f\n", cost);
		else if (epoch == 999)
			printf("cost of 1000th cost : %0.7f\n", cost);

		/*		gradient sum initialize		*/	
		for (int k = 0; k < DIM; k++)
			grad_sum[k] = 0.0;
		if((epoch+1) % 100 == 0)
		printf("%d epoch is over\n", epoch+1);
	}
	end = clock();

	// Time
	float time_result = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Time: %.3f\n", time_result);


	// PRINT WEIGHT
	printf("==========================\n");
	float arr[DIM];
	for (int i = 0; i < DIM; i++)
		arr[i] = w[i];
	for (int i = 0; i < DIM; i++)
		printf("WEIGHT[%d]: %f\n", i + 1, w[i]);
	printf("==========================\n");
	weight_order(arr);

	fclose(fin);
	fclose(fo);
	fclose(fcost);
}

void weight_order(float *arr) {	// By Selection Sort
								//	INDEX_ARRAY matched with arr
	int index_order[DIM];
	for (int i = 0; i < DIM; i++)
		index_order[i] = i + 1;

	//	CHANGE INDEX AT THE SAME TIME
	for (int i = 0; i < DIM; i++) {			// Target Index
		float max_temp = arr[i];
		int max_idx = i;
		for (int k = i + 1; k < DIM; k++) {	// Find Max from i+1 ~ DIM
			if (max_temp < arr[k]) {
				max_temp = arr[k];
				max_idx = k;
			}
		}
		// swap value
		arr[max_idx] = arr[i];
		arr[i] = max_temp;

		// swap idx
		int tmp = index_order[max_idx];
		index_order[max_idx] = index_order[i];
		index_order[i] = tmp;
	}

	// print ORDER
	printf("WEIGHT ORDER \n");
	for (int i = 0; i < DIM; i++) {
		if (i != 9)
			printf("w_%d > ", index_order[i]);
		else printf("w_%d\n", index_order[i]);
	}
	printf("\n");
}
