#pragma once

#include "general.h"
#include "vector.h"

class Camera
{
public:
	explicit Camera();
	virtual ~Camera();

public:
	Vector m_eye;
	Vector m_rotation;
};