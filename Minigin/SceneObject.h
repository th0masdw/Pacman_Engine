#pragma once

class SceneObject
{
public:
	SceneObject() = default;
	virtual ~SceneObject() = default;

	virtual void Update() = 0;
	virtual void Render() const = 0;

	SceneObject(const SceneObject& other) = delete;
	SceneObject(SceneObject&& other) = delete;
	SceneObject& operator=(const SceneObject& other) = delete;
	SceneObject& operator=(SceneObject&& other) = delete;
};