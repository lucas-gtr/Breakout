#pragma once

#include <cmath>
#include <iostream>
#include <array>

template <size_t N>
class vec {
public:
  std::array<float, N> values;

  vec(float value = 0.0f) {
    values.fill(value);
  }
  
  vec(const vec& other) {
    values = other.values;
  }
  
  vec& operator=(const vec& other) {
    if (this != &other) {
      values = other.values;
    }
    return *this;
  }
  
  template <typename... Args>
  vec(Args... args) : values{ static_cast<float>(args)... } {
    static_assert(sizeof...(Args) == N, "Nombre d'arguments incorrect");
  }
  
  vec operator+(const vec& other) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] + other.values[i];
    }
    return result;
  }
  
  vec operator+(const float scalar) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] + scalar;
    }
    return result;
  }
  
  vec operator-() const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = -values[i];
    }
    return result;
  }
  
  vec operator-(const vec& other) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] - other.values[i];
    }
    return result;
  }
  
  vec operator-(const float scalar) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] - scalar;
    }
    return result;
  }
  
  vec operator*(const vec& other) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] * other.values[i];
    }
    return result;
  }
  
  vec operator*(const float scalar) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] * scalar;
    }
    return result;
  }
  
  vec operator/(const float scalar) const {
    vec result;
    for (size_t i = 0; i < N; ++i) {
      result.values[i] = values[i] / scalar;
    }
    return result;
  }
  
  vec& operator+=(const vec& other) {
    for (size_t i = 0; i < N; ++i) {
      values[i] += other.values[i];
    }
    return *this;
  }
  
  vec& operator+=(const float scalar) {
    for (size_t i = 0; i < N; ++i) {
      values[i] += scalar;
    }
    return *this;
  }
  
  vec& operator-=(const vec& other) {
    for (size_t i = 0; i < N; ++i) {
      values[i] -= other.values[i];
    }
    return *this;
  }
  
  vec& operator-=(const float scalar) {
    for (size_t i = 0; i < N; ++i) {
      values[i] -= scalar;
    }
    return *this;
  }
  
  vec& operator*=(const vec& other) {
    for (size_t i = 0; i < N; ++i) {
      values[i] *= other.values[i];
    }
    return *this;
  }
  
  vec& operator*=(const float scalar) {
    for (size_t i = 0; i < N; ++i) {
      values[i] *= scalar;
    }
    return *this;
  }
  
  vec& operator/=(const float scalar) {
    for (size_t i = 0; i < N; ++i) {
      values[i] /= scalar;
    }
    return *this;
  }
  
  vec& clamp(const float valueMin, const float valueMax){
    for (size_t i = 0; i < N; ++i) {
      values[i] = std::max(valueMin, std::min(values[i], valueMax));
    }
    return *this;
  }
  
  vec& clamp(const vec& vecMin, const vec& vecMax){
    for (size_t i = 0; i < N; ++i) {
      values[i] = std::max(vecMin[i], std::min(values[i], vecMax[i]));
    }
    return *this;
  }
  
  float dot(const vec& other){
    float dot_product = 0.f;
    for (size_t i = 0; i < N; ++i) {
      dot_product += values[i] * other.values[i];
    }
    return dot_product;
  }
  
  bool operator==(const vec& other) {
    for (size_t i = 0; i < N; ++i)
      if(values[i] != other.values[i]) return false;
    return true;
  }
  
  template <size_t M>
  vec(const vec<M>& other, float fillValue = 1.0f) {
    for (size_t i = 0; i < std::min(N, M); ++i) {
      values[i] = other.values[i];
    }
    for (size_t i = M; i < N; ++i) {
      values[i] = fillValue;
    }
  }
  
  float length() const {
    float sum = 0.0f;
    for (size_t i = 0; i < N; ++i) {
      sum += values[i] * values[i];
    }
    return std::sqrt(sum);
  }
  
  vec unit() const {
    float len = length();
    return (len > 0) ? *this * (1.0f / len) : vec(0.0f);
  }
  
  float& operator[](size_t i) { return values[i]; }
  const float& operator[](size_t i) const { return values[i]; }
};

template <size_t N>
std::ostream& operator<<(std::ostream& os, const vec<N>& vec) {
  os << "vec" << N << "(";
  for (size_t i = 0; i < N; ++i) {
    os << vec.values[i];
    if (i < N - 1) os << ", ";
  }
  return os << ")";
}

using vec2 = vec<2>;
using vec3 = vec<3>;
using vec4 = vec<4>;
