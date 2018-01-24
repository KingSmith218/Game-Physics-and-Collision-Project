#pragma once


class cannon 
{
public:
	cannon(float ix, float iy);
	void show();
	void move(float Aangle);
	void show_cannon();
private:
	float x, y;
	float angle;
};