#include "audio_capture.h"
#include <cstdint>

int main() {
	auto ac = AudioCapture();
	while (true) {
		uint64_t num_frames = ac.fill_buffer();
		UINT32 count = 0;
		for (UINT32 i = 0; i < num_frames; i++) {
			float sample = ac.get_data()[i];
			if (sample > 0.0001 || sample < -0.0001) {
				count++;
			}
		}
		if(count != 0) printf("Waves %d\n", count);
	}
	return 0;
}
