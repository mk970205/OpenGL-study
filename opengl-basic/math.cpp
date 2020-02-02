#include "math.h"

using namespace glm;

mat4 look_at(const vec3& eye, const vec3& at, const vec3& up) {
    vec3 n = normalize(eye - at);
    vec3 u = normalize(cross(up, n));
    vec3 v = cross(n, u);

    mat4 T = mat4(1.0f);
    T[3] = vec4(-eye, 1.0f);

    mat4 R = mat4(1.0f);
    R[0] = vec4(u, 0.0f);
    R[1] = vec4(v, 0.0f);
    R[2] = vec4(n, 0.0f);
    R = transpose(R);

    return R * T;
}

mat4 get_pmat(float n, float f, float fovy, float aspect) {
    mat4 ret(0);
    float x = 1.0f / tan(fovy / 2);
    ret[0][0] = x / aspect;
    ret[1][1] = x;
    ret[2][2] = -(f + n) / (f - n);
    ret[2][3] = -1.0f;
    ret[3][2] = -2 * n * f / (f - n);

    return ret;
}

mat4 get_vmat(vec3 pos, vec3 dir, vec3 up) {
    return look_at(
        pos,
        pos + dir,
        up
    );
}