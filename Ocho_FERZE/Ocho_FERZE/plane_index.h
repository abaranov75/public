#pragma once

class plane_index
{
	int index = 0;
public:
	plane_index(){}
	plane_index(int i):index(i){}

	operator int() const { return index; }
};