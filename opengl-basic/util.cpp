#include "util.h"

using namespace std;

void update_fps_counter(GLFWwindow* window) {
    double curr_second = glfwGetTime();
    static double prev_second = 0.0f;
    static int frame_count = 0;
    double period = curr_second - prev_second;
    if (period > 0.25f) {
        string tmp("OpenGL @ fps: ");
        double fps = frame_count / period;
        tmp += to_string(fps);

        const char* title_cstr = tmp.c_str();
        glfwSetWindowTitle(window, title_cstr);

        prev_second = curr_second;
        frame_count = 0;
    }

    frame_count++;
}