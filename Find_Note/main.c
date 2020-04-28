#include "function.h"

void main() {
	samplenum = 0;
	float note_freq[8] = { 0,0, };
	fopen_s(&fin, "input16k.raw", "rb");

	for (int i = 0; i < 8; i++) {
		note_freq[i] = comp_freq(i);
		printf("Harmonics of %d Note is %.2f Hz \n", i+1, note_freq[i]);
		print_note(note_freq[i]);
	}


	printf("Total length : %.2f s\n", (float)samplenum / 16000);

	fclose(fin);
}
