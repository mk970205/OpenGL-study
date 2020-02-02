#pragma once
#ifndef _MATH_H_
#define _MATH_H_

#include"include/GLM/glm.hpp"

constexpr float M_PI = 3.141592f;

glm::mat4 look_at(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
glm::mat4 get_pmat(float n, float f, float fovy, float aspect);
glm::mat4 get_vmat(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);

#endif