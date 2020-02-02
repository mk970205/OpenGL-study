#pragma once
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "include/GLFW/glfw3.h"
#include "include/GLM/glm.hpp"

glm::vec4 make_versor(GLfloat radian, const glm::vec3 &axis);
glm::vec4 multiply_versor(const glm::vec4 &lhs, const glm::vec4 &rhs);
glm::mat4 quat_to_mat(const glm::vec4 &versor);
glm::vec4 slerp_versor(const glm::vec4& v0, const glm::vec4& v1, float t);
#endif // !_QUATERNION_H_