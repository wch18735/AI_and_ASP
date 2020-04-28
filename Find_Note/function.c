#include "function.h"

float comp_freq(int skip_idx) {
	double signal[N], spec_real[N], spec_imag[N], spec_mag[N], freq;
	short data;
	int max_idx;
	float tmp_X_k = 0.0;

	// initialize skip array
	float start_at[8] = {0.3, 0.8, 1.13, 1.38, 1.57, 1.82, 2.1, 2.3};
	skip_sample_as(start_at);

	// skip to the start
	for (int n = 0; n < skip[skip_idx]; n++) {
		fread(&data, 2, 1, fin);
		samplenum++;
	}

	// start to read datad
	for (int n = 0; n < N; n++) {
		fread(&data, 2, 1, fin);
		signal[n] = (float)data; // input array
		samplenum++;
	}

	// hanning window
	for (int n = 0; n < N; n++) {
		signal[n] = signal[n] * (0.5 - 0.5*cos(2 * PI * n / (float)(N - 1)));
	}

	// N-point DFT
	for (int k = 0; k < N; k++) {

		spec_real[k] = spec_imag[k] = 0.0;

		for (int n = 0; n < N; n++) {
			spec_real[k] = spec_real[k] + signal[n] * cos(2 * PI * k * n / (float)N); // DFT Real
			spec_imag[k] = spec_imag[k] - signal[n] * sin(2 * PI * k * n / (float)N); // DFT Imainary
		}

		spec_mag[k] = sqrt(pow(spec_real[k], 2) + pow(spec_imag[k], 2));		// |spec_mag[k]|^2 = |spec_real[k]|^2 + |spec_imag[k]|^2
	}
	
	// peak magnitude
	for (int k = 1; k < N; k++) {
		if (tmp_X_k < spec_mag[k]) {
			max_idx = k;
			tmp_X_k = spec_mag[k];
		}
		else continue;
	}

	// index to frequency
	freq = detect_freq(N, max_idx, 10.0);

	return freq;
}

float detect_freq(int n_point, int max_idx, float f_resolution) {
	// freq (Hz) Detection
	if (N / 2 < max_idx) {
		return (float)(n_point - max_idx) * f_resolution;
	}
	else
	{
		return (float)max_idx * f_resolution;
	}
}

void skip_sample_as(float *start_at) {
	for (int i = 0; i < 8; i++) {
		if (i == 0) {
			skip[i] = (int)(start_at[i] * 16000);
		}
		else {
			skip[i] = (int)((start_at[i] - (start_at[i - 1] + 0.1)) * 16000);
		}
	}
}

void print_note(float test_frq) {
	float Do = 440 * pow(SEMITONE_INTERVAL_RATIO, -9);
	float note_array[12] = { 0.0, };
	char *note_name[12] = { "C", "C# / Db" ,"D", "D# / Eb", "E","F","F# / Gb","G","G# / Ab","A","A# / Bb","B" };

	// check octave
	int oct = (int)test_frq / Do;

	// initialize octave
	for (int i = 0; i < 12; i++) {
		note_array[i] = 440 * pow(SEMITONE_INTERVAL_RATIO, i - 9) * oct;
	}

	// temp_difference between note_array[i] and test_frq
	float tmpdif;

	// minimum index
	int min_idx = 0;

	// find minimum index
	for (int i = 0; i < 12; i++) {
		if (i == 0) {
			tmpdif = fabsf(test_frq - note_array[i]);
		}
		else {
			if (tmpdif > fabsf(test_frq - note_array[i])) {
				tmpdif = fabsf(test_frq - note_array[i]);
				min_idx = i;
			}
			else continue;
		}
	}
	printf("The %f Hz note is %s \n\n", test_frq, note_name[min_idx]);
}