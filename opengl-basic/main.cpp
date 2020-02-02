#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h"
#include "include/GLM/glm.hpp"
#include "include/GLM/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

#include "callback.h"
#include "log.h"
#include "util.h"
#include "math.h"
#include "quaternion.h"

using namespace std;
using namespace glm;

constexpr int width = 1024;
constexpr int height = 768;

int main()
{

#pragma region 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << '\n';
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(
        width, // width
        height, // height
        "OpenGL Example",
        NULL, NULL
    );

    if (!window)
    {
        std::cerr << "윈도우 생성 실패" << '\n';
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW 초기화 실패 " << glewGetErrorString(err) << '\n';
        glfwTerminate();
        exit(-1);
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#pragma endregion

#pragma region 물체 데이터
    const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };
    const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };
#pragma endregion

#pragma region 움직임 데이터
    vec3 cam_pos = vec3(0.0f, 0.0f, 5.0f);
    vec3 cam_dir = vec3(0.0f, 0.0f, 0.0f) - cam_pos;
    vec3 up = vec3(0.0f, 1.0f, 0.0f);

    GLfloat pitch_angle = 0.0f;
    GLfloat yaw_angle = M_PI;
    GLfloat roll_angle = 0.0f;

    float near = 0.1f;
    float far = 100.0f;
    float fovy = radians(45.0f);
    float aspect = 4.0f / 3.0f;

    mat4 world_mat = mat4(1.0f);
    //world_mat = rotate(world_mat, M_PI / 4, vec3(0.0f, 1.0f, 0.0f));
    //world_mat = rotate(world_mat, M_PI / 4, vec3(1.0f, 0.0f, 0.0f));

    vec4 vs1 = make_versor(M_PI / 4, vec3(1.0f, 0.0f, 0.0f));
    vec4 vs2 = make_versor(M_PI / 4, vec3(0.0f, 1.0f, 0.0f));
    vec4 vs = multiply_versor(vs2, vs1);
    mat4 vs_mat = quat_to_mat(vs);
    world_mat *= vs_mat;

    mat4 view_mat = get_vmat(cam_pos, cam_dir, up);
    mat4 proj_mat = get_pmat(near, far, fovy, aspect);
    mat4 mvp = proj_mat * view_mat * world_mat;

    GLfloat cam_speed = 0.5f;
    GLfloat mouse_speed = 0.005f;
    GLfloat rotate_speed = 1.0f;
#pragma endregion

#pragma region vao & shader
    GLuint vbo_pos = 1;
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint vbo_color = 1;
    glGenBuffers(1, &vbo_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint vao = 1;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    ifstream v_shader_source("shader/basic.vert");
    string v_shader_str((istreambuf_iterator<char>(v_shader_source)),
        istreambuf_iterator<char>());
    const char* v_cstr = v_shader_str.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &v_cstr, NULL);
    glCompileShader(vertex_shader);

    ifstream f_shader_source("shader/basic.frag");
    string f_shader_str((istreambuf_iterator<char>(f_shader_source)),
        istreambuf_iterator<char>());
    const char* f_cstr = f_shader_str.c_str();

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_cstr, NULL);
    glCompileShader(fragment_shader);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int mvp_loc = glGetUniformLocation(shader_program, "mvp");
    glUseProgram(shader_program);
    glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, value_ptr(mvp));

#pragma endregion

    // Loop
    while (!glfwWindowShouldClose(window)) {
        update_fps_counter(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        static GLdouble prev_second = glfwGetTime();
        GLdouble curr_second = glfwGetTime();
        GLfloat delta_time = static_cast<GLfloat>(curr_second - prev_second);
        prev_second = curr_second;

        static GLfloat slerp_t = 0.0f;
        static int angle_gradient = 1;
        slerp_t += angle_gradient * rotate_speed * delta_time;
        if (slerp_t <= 0.0f) {
            angle_gradient = 1;
        }
        if (slerp_t >= 1.0f) {
            angle_gradient = -1;
        }
        world_mat = mat4(1.0f);
        vec4 vs0 = make_versor(M_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
        vec4 vs1 = make_versor(M_PI / 2.0f, vec3(0.0f, 1.0f, 0.0f));
        world_mat *= quat_to_mat(slerp_versor(vs0, vs1, slerp_t));
        
#pragma region control
        GLdouble mouse_xpos, mouse_ypos;
        glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
        glfwSetCursorPos(window, width / 2, height / 2);

        yaw_angle += ((width / 2) - mouse_xpos) * mouse_speed * delta_time;
        pitch_angle += ((height / 2) - mouse_ypos) * mouse_speed * delta_time;

        cam_dir = vec3(
            cos(pitch_angle) * sin(yaw_angle),
            sin(pitch_angle),
            cos(pitch_angle) * cos(yaw_angle)
        );

        vec3 right = vec3(
            sin(yaw_angle - M_PI / 2.0f),
            0.0f,
            cos(yaw_angle - M_PI / 2.0f)
        );

        if (glfwGetKey(window, GLFW_KEY_A)) {
            cam_pos -= right * cam_speed * delta_time;
        }

        if (glfwGetKey(window, GLFW_KEY_D)) {
            cam_pos += right * cam_speed * delta_time;
        }

        if (glfwGetKey(window, GLFW_KEY_W)) {
            cam_pos += cam_dir * cam_speed * delta_time;
        }

        if (glfwGetKey(window, GLFW_KEY_S)) {
            cam_pos -= cam_dir * cam_speed * delta_time;
        }

        if (glfwGetKey(window, GLFW_KEY_Q)) {
            cam_pos += up * cam_speed * delta_time;
        }

        if (glfwGetKey(window, GLFW_KEY_E)) {
            cam_pos -= up * cam_speed * delta_time;
        }
        view_mat = get_vmat(cam_pos, cam_dir, up);
        
#pragma endregion

        mvp = proj_mat * view_mat * world_mat;
        glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, value_ptr(mvp));

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        glfwPollEvents();
        glfwSwapBuffers(window);

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}