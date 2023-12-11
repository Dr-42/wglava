#include "audio_capture.h"
#include "renderer.h"
#include <cstdint>

int main() {
    auto ac = AudioCapture();
    Renderer renderer = Renderer();
    while (!glfwWindowShouldClose(renderer.window)) {
        renderer.Begin();
        uint64_t num_frames = ac.fill_buffer();
        if (num_frames > 0) {
            for (UINT32 i = 0; i < num_frames; i++) {
                float sample = ac.get_data()[i];
                float x = ((float)i / (float)num_frames) * 2.0f - 1.0f;
                float y = -1.0f;
                float w = 1.0f / (float)num_frames;
                Rect rect = {x, y, w, sample, 0.0f};
                Color color = {1.0f, 0.0f, 1.0f, 1.0f};
                renderer.DrawRect(rect, color);
            }
        }
    }
    return 0;
}
