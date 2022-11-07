#include "plane_index.h"
#include <utility>

#pragma once

class double_index
{
	int x = 0; // столбцы слева на право
	int z = 0; // строки сверху вниз
public:
	double_index(int x, int z):x(x), z(z){}
	double_index(const plane_index& pi)
	{
		z = int(pi) / 8;
		x = int(pi) % 8;
	}

	operator std::pair<int, int>() const { return { x,z }; }

	operator plane_index() const
	{
		return z * 8 + x;
	}

	int Z() const { return z; }
	int X() const { return x; }
};