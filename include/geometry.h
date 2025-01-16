#pragma once

#include "matrix.h"

inline vec3 vec_cross(const vec3 v1, const vec3 v2){
  return vec3(v1[1] * v2[2] - v1[2] * v2[1],
              v1[2] * v2[0] - v1[0] * v2[2],
              v1[0] * v2[1] - v1[1] * v2[0]);
}

inline float radians(const float angle){
  return angle * M_PI / 180.0f;
}

inline mat4 ortho(float x_min, float x_max, float y_min, float y_max, float zNear, float zFar){
  mat4 orthographicMatrix(1.0f);
  orthographicMatrix(0, 0) = 2 / (x_max - x_min);
  orthographicMatrix(0, 3) = -(x_max + x_min) / (x_max - x_min);
  orthographicMatrix(1, 1) = 2 / (y_max - y_min);
  orthographicMatrix(1, 3) = -(y_max + y_min) / (y_max - y_min);
  orthographicMatrix(2, 2) = -2 / (zFar - zNear);
  orthographicMatrix(2, 3) = -(zFar + zNear) / (zFar - zNear);

  return orthographicMatrix;
}
