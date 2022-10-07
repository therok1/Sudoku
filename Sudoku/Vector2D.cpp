#include "Vector2D.h"

Vector2D::Vector2D()
{
	m_X = 0.0f;
	m_Y = 0.0f;
}

void Vector2D::SetX(float X)
{
	m_X = X;
}

void Vector2D::SetY(float Y)
{
	m_Y = Y;
}

float Vector2D::GetX() const
{
	return m_X;
}

float Vector2D::GetY() const
{
	return m_Y;
}
