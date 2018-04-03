#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

template <typename T>
inline void Clamp(T& value, T min, T max) {
	if(value < min)
		value = min;

	if(value > max)
		value = max;
}

template <typename T>
inline T Min(T value, T other) {
	if (value > other)
		value = other;

	return value;
}

template <typename T>
inline T Max(T value, T other) {
	if (value < other)
		value = other;

	return value;
}

inline float WrapAngle(float angle) {
	angle = fmod(angle, 360.0f);
    if (angle < 0.0f)
        angle += 360.0f;

	return angle;
}

inline bool HasZeroMagnitude(const glm::vec2& vector) {
	return vector.x <= 0.0f && vector.y <= 0.0f;
}

inline float Distance(const glm::vec2& a, const glm::vec2& b) {
	glm::vec2 delta = a - b;
	float length = std::sqrt(pow(delta.x, 2) + (pow(delta.y, 2)));
	return length;
}