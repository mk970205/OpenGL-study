#include "quaternion.h"

using namespace glm;

vec4 make_versor(GLfloat radian, const vec3& axis) {
    return vec4(
        cos(radian / 2),
        sin(radian / 2) * axis.x,
        sin(radian / 2) * axis.y,
        sin(radian / 2) * axis.z
    );
}

vec4 multiply_versor(const vec4& lhs, const vec4& rhs) {
    return vec4(
        rhs[0] * lhs[0] - rhs[1] * lhs[1] - rhs[2] * lhs[2] - rhs[3] * lhs[3],
        rhs[0] * lhs[1] + rhs[1] * lhs[0] - rhs[2] * lhs[3] + rhs[3] * lhs[2],
        rhs[0] * lhs[2] + rhs[1] * lhs[3] + rhs[2] * lhs[0] - rhs[3] * lhs[1],
        rhs[0] * lhs[3] - rhs[1] * lhs[2] + rhs[2] * lhs[1] + rhs[3] * lhs[0]
    );
}
mat4 quat_to_mat(const vec4& versor) {
    float w = versor[0], x = versor[1], y = versor[2], z = versor[3];
    return mat4(
        1 - 2*y*y - 2*z*z,   2*x*y + 2*w*z,      2*x*z - 2*w*y, 0.0f,
        2*x*y - 2*w*z,       1 - 2*x*x - 2*z*z,  2*y*z + 2*w*x, 0.0f,
        2*x*z + 2*w*y,       2*y*z - 2*w*x,  1 - 2*x*x - 2*y*y, 0.0f,
        0.0f,                0.0f,               0.0f,          1.0f
    );
}

vec4 slerp_versor(const vec4& v0, const vec4& v1, float t) {
    float dv = dot(v0, v1);
    
    if (fabs(dv) < 0.0f) {
        return slerp_versor(v0, -v1, t);
    }

    if (fabs(dv) >= 1.0f) {
        return v0;
    }

    float sin_omega = sqrtf(1 - dv * dv);
    if (sin_omega < 0.001f) {
        return vec4((1 - t) * v0 + t * v1);
    }

    float omega = acosf(dv);
    float coeff0 = sinf((1 - t) * omega) / sinf(omega);
    float coeff1 = sinf(t * omega) / sinf(omega);

    return vec4(coeff0 * v0 + coeff1 * v1);
}