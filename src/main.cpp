#include "audio_capture.h"
#include "renderer.h"
#include "ringbuf.h"
#include <cstdint>

int main() {
    auto ac = AudioCapture();
    Renderer renderer = Renderer();
    RingBuf rb = RingBuf(15000);
    while (!glfwWindowShouldClose(renderer.window)) {
        glfwPollEvents();
        if (glfwGetKey(renderer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(renderer.window, true);
        }
        if (glfwGetKey(renderer.window, GLFW_KEY_R) == GLFW_PRESS) {
            renderer.LoadShader();
            printf("Reloaded shader\n");
        }
        renderer.Begin();
        uint64_t num_frames = ac.fill_buffer();
        rb.Cat(ac.get_data(), num_frames);
        rb.fft_analyze(1.0f / 44100.0f);
        for (UINT32 i = 0; i < rb.fft_size; i++) {
            float sample = rb.get_fft(i);
            float x = ((float)i / (float)rb.fft_size) * 2.0f - 1.0f;
            float y = -0.99f;
            float w = 1.0f / (float)rb.fft_size;
            Rect rect = {x, y, w, 2 * sample, 0.0f};
            Color bcolor = {0.0f, 1.0f, 1.0f, 1.0f};
            Color tcolor = {1.0f, 0.0f, 1.0f, 1.0f};
            renderer.DrawRect(rect, bcolor, tcolor);
        }
        renderer.End();
    }
    return 0;
}
