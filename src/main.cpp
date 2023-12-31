#include "audio_capture.h"
#include "renderer.h"
#include "ringbuf.h"
#include <GLFW/glfw3.h>
#include <cstdint>

#define FPS 120

int main() {
    auto ac = AudioCapture();
    Renderer renderer = Renderer();
    RingBuf rb = RingBuf(15000);
    float dt = 0.0f;
    float monitor_width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    float monitor_height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
    float center_x = 0.0f;
    float center_y = 580.0f;
    float radius = 400.0f;
    float volume;
    while (!glfwWindowShouldClose(renderer.window)) {
        float time = glfwGetTime();
        volume = ac.volume;
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
        rb.fft_analyze(40, dt);
        for (UINT32 i = 0; i < rb.fft_size; i++) {
            float sample = rb.get_fft(rb.fft_size - i - 1);
            float sample_angle = (((float)i / (float)rb.fft_size) * 2.0f * PI) + PI;
            float x = (center_x + radius * cos(sample_angle/2))/monitor_height ;
            float y = (center_y + radius * sin(sample_angle/2))/monitor_height;
            float w = 1.0f / (float)rb.fft_size;
            float angular_width = 2 * PI / (float)rb.fft_size;
            float rect_angle = sample_angle/2 - PI/2 - angular_width/2;
            float h = volume * radius * sample/sqrt(monitor_width * monitor_width);
            Rect rect = {x, y, w, h, rect_angle};
            Rect rect2 = {-x, y, w, h, -(rect_angle)};
            Color bcolor = {0.0f, 1.0f, 1.0f, 1.0f};
            Color tcolor = {1.0f, 0.0f, 1.0f, 1.0f};
            renderer.DrawRect(rect, bcolor, tcolor);
            renderer.DrawRect(rect2, bcolor, tcolor);
        }
        renderer.End();
        dt = glfwGetTime() - time;
    }
    return 0;
}
