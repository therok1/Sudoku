#pragma once
class Vector2D
{
public:

	Vector2D();

	// Setter Functions

	void SetX(float X);
	void SetY(float Y);

	// Getter Functions

	float GetX() const;
	float GetY() const;

private:

	float m_X, m_Y;
};

