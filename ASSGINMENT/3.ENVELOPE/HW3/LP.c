#include<stdio.h>
#include<math.h>

#define _USE_MATH_DEFINES
#define N 320
#define PI 3.1415

FILE *fin;
FILE *fa;
FILE *fE;
FILE *fenv;
FILE *fc;

void frame_number_count(FILE *fp);
void n_dft(double* signal, double* spec_mag, int N_PT);
void read_data(FILE *fp, double* signal, int N_PT, short *data);
void hamming_window(double *signal, double* window_signal, int N_PT);
void zero_window(double *signal, double* window_signal, int offset, int frame_num, int sample_num);
double auto_correlation(double* signal, int sample_num, int k);
void auto_cor_arr(double* signal, double* acor_arr, int sample_num, int k);
void durbin(double* acor_arr, double* E, double* k_i, double a[][11], int k);
void get_A_z(double* a_z, double a[][11], int sample_num, int k);
void get_envelope(double* dft_a, double* envelope, int sample_num);

int main(void) {

	double signal[N], h_win_signal[N], window_signal[N];
	double acor_arr[11];
	double a_z[N], dft_a[N], envelope[N];
	short data;
	double E[11] = { 0.0, };
	double k_i[11] = { 0,0 };
	double a[11][11] = { 0.0, };
	int file_num;

	// FILE CONNECT //
	FILE *flist[5];
	file_num = 5;
	fopen_s(&fin, "Male.raw", "rb");
	fopen_s(&fa, "a_i.txt", "wb");
	fopen_s(&fE, "E.txt", "wb");
	fopen_s(&fenv,"envelope.txt","wb");
	fopen_s(&fc, "k_i.txt", "wb");

	if (fc == NULL) {
		printf("ERROR!!\n");
		exit(1);
	}
	
	flist[0] = fin; 
	flist[1] = fa;
	flist[2] = fE;
	flist[3] = fenv;
	flist[4] = fc;

	// FILE READ
	read_data(fin, signal, N, &data);

	// Hamming WIndow
	hamming_window(signal, h_win_signal, 320);

	// Window (20ms Frame in 8kHz sampling => 160 sample) & total sample = 320
	zero_window(h_win_signal, window_signal, 0, 160, 320);

	// Auto Correlation
	// printf("acor[10]: %f\n", auto_correlation(window_signal, 320, 10));

	// R array
	auto_cor_arr(window_signal, acor_arr, 320, 10);

	// durbin
	durbin(acor_arr,E,k_i,a,10);

	// Frequency response
	get_A_z(a_z, a, 320, 10);

	// DFT A(z)
	n_dft(a_z, dft_a, 320);

	// 1/A(z)
	get_envelope(dft_a, envelope, 320);

	// get file
	for (int i = 1; i <= 10; i++) fprintf(fa, "%10.7f\n", a[10][i]);
	for (int i = 1; i <= 10; i++) fprintf(fE, "%10.7f\n", E[i]);
	for (int i = 0; i < 320; i++) fprintf(fenv, "%10.7f\n", envelope[i]);
	for (int i = 0; i <= 10; i++) fprintf(fc, "%10.7f\n", k_i[i]);

	// File close
	for (int i = 0; i < file_num; i++) {
		fclose(flist[i]);
	}
}

void frame_number_count(FILE *fp) {
	if (fp == NULL) printf("Error!!\n");

	short fr_data;
	int count = 0;
	while (feof(fp) == 0) {
		fread(&fr_data, 2, 1, fin);
		count++;
	}
	// TEST: printf("sample number: %d\n\n", count); //-> RESULT: 640 samples -> 0.8s
}

void read_data(FILE *fp, double* signal, int N_PT, short *data) {
	for (int i = 0; i < N_PT; i++) {
		fread(data, 2, 1, fin);
		signal[i] = (double)*data; // input array
		// TEST: printf("%f\n", signal[i]);
	}
}

void hamming_window(double *signal, double* window_signal, int N_PT) {
	for (int n = 0; n < N_PT; n++) {
		window_signal[n] = signal[n] * (0.5 - 0.5*cos(2 * PI * n / (float)(N_PT - 1)));
	}
	//TEST: for (int n = 0; n < N_PT; n++) printf("window_signal[%d] = %f\n", n, window_signal[n]);
}

void zero_window(double *signal, double* window_signal,int offset, int frame_num, int sample_num) {
	for (int i = 0; i < sample_num; i++) {
		if (i < offset || offset + frame_num <= i) {
			window_signal[i] = 0.0;
		}
		else {
			window_signal[i] = signal[i];
		}
	}
	// TEST: for (int i = 0; i < sample_num; i++) printf("window_signal[%d]: %f\n", i, window_signal[i]);
}

void n_dft(double* signal, double* spec_mag, int N_PT) {
	double spec_real[N] = { 0.0, };
	double spec_imag[N] = { 0.0, };

	for (int k = 0; k < N_PT; k++) {
		for (int n = 0; n < N_PT; n++) {
			spec_real[k] = spec_real[k] + signal[n] * cos(2 * PI * k * n / (float)N_PT); // DFT Real
			spec_imag[k] = spec_imag[k] - signal[n] * sin(2 * PI * k * n / (float)N_PT); // DFT Imainary
		}

		spec_mag[k] = sqrt(pow(spec_real[k], 2) + pow(spec_imag[k], 2));		// |spec_mag[k]|^2 = |spec_real[k]|^2 + |spec_imag[k]|^2
																				// TEST: printf("spec_mag[%d] = %f\n", k, spec_mag[k]);
	}
}

double auto_correlation(double* signal, int sample_num, int k) {
	double acor = 0;
	for (int i = 0; i < sample_num; i++) {
		if (k <= i){
			acor +=  signal[i-k] * signal[i];
		}
		else continue;
	}
	// TEST: printf("autocorrealtion R[%d] = %f\n", k, acor);
	return acor;
}

void auto_cor_arr(double* signal,double* acor_arr, int sample_num, int k) {
	for (int i = 0; i < k+1; i++) {
		acor_arr[i] = auto_correlation(signal, sample_num, i);
		// TEST: printf("acor_arr[%d] = %f\n", i, acor_arr[i]);
	}
}

void durbin(double* acor_arr, double* E, double* k_i, double a[][11], int k) {
	double sum;
	E[0] = acor_arr[0];

	for (int i = 1; i <= k; i++) { // for(i=1;i<=10;i++)
		sum = 0;
		for (int j = 1; j <= i-1; j++) { // sum(a_j^(i-1)R[i-j])
			sum += a[i-1][j] * acor_arr[i - j];
		}

		k_i[i] = (acor_arr[i] - sum) / E[i - 1];
		a[i][i] = k_i[i];

		for (int j = 1; j <= i - 1; j++) a[i][j] = a[i - 1][j] - k_i[i] * a[i - 1][i - j];
		E[i] = (1-pow(k_i[i], 2))*E[i-1];
		//TEST: printf("sum: %f\n", sum);
		//TEST: printf("k_i[%d]: %f\n",i, k_i[i]);
	}
	//TEST: for (int i = 0; i < k + 1; i++) printf("k_i[%d]: %f\n",i, k_i[i]);
	//TEST: for (int i = 0; i < k + 1; i++) printf("E[%d]: %f\n", i, E[i]);
}

void get_A_z(double* a_z, double a[][11], int sample_num, int k){
	for (int i = 0; i < sample_num; i++) {
		if (i == 0) a_z[0] = 1;
		else if (i < k) {
			a_z[i] = -a[10][i+1];
		}
		else a_z[i] = 0;
	}
	// TEST: for (int i = 0; i < sample_num; i++)printf("a_z[%d] = %f\n", i, a_z[i]);
}

void get_envelope(double* dft_a, double* envelope, int sample_num) {
	for (int i = 0; i < sample_num; i++)  envelope[i] = 1 / dft_a[i];
	// TEST: for (int i = 0; i < sample_num; i++)  printf("envelope[%d] = %f\n",i,envelope[i]);
}