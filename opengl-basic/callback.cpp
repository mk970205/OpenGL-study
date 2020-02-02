#pragma once

#include "callback.h"

using namespace std;

void glfw_error_callback(int error, const char* desc) {
    gl_log("GLFW ERROR [code: " + to_string(error) + "] " + string(desc));
}