#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

/* DEFINE PARAMETER */
#define N 1600
#define PI 3.1415
#define SEMITONE_INTERVAL_RATIO 1.06

int skip[8];
FILE *fin;
int samplenum;


/* DEFINE FUNCTION */
float comp_freq(int);
void skip_sample_as(float* start_at);
float detect_freq(int n_point, int max_idx, float f_resolution);
void print_note(float note_freq);