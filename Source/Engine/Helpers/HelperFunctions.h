#pragma once

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