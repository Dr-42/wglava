#include "audio_capture.h"
#include "renderer.h"
#include "ringbuf.h"
#include <cstdint>

int main() {
    auto ac = AudioCapture();
    Renderer renderer = Renderer();
    RingBuf rb = RingBuf(20000);
    while (!glfwWindowShouldClose(renderer.window)) {
        renderer.Begin();
        uint64_t num_frames = ac.fill_buffer();
        rb.Cat(ac.get_data(), num_frames);
        rb.fft_analyze(1.0f / 44100.0f);
        for (UINT32 i = 0; i < rb.fft_size; i++) {
            float sample = rb.get_fft(i);
            float x = ((float)i / (float)rb.fft_size) * 2.0f - 1.0f;
            float y = -0.5f;
            float w = 1.0f / (float)rb.fft_size;
            Rect rect = {x, y, w, sample, 0.0f};
            Color color = {1.0f, 0.0f, 1.0f, 1.0f};
            renderer.DrawRect(rect, color);
        }
    }
    return 0;
}
