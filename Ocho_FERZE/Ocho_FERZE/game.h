#pragma once
#include <utility>
#include <map>
#include <vector>
#include "plane_index.h"

class game
{
	std::map<int, plane_index> placed_ferz;
	std::map<int, std::vector<plane_index>> attaked_fields;
	std::map<int, std::vector<plane_index>> forbidden_fields;

public:
	bool is_under_attack(const plane_index& pos) const
	{
		for (const auto& f : attaked_fields)
		{
			if (find(f.second.begin(), f.second.end(), pos) != f.second.end())
				return true;
		}
		return false;
	}

	bool is_field_occuped(const plane_index& pos) const
	{
		for (const auto& f : placed_ferz)
		{
			if (f.second == pos )
				return true;
		}
		return false;
	}

	bool is_field_forbidden(int ferz_number, const plane_index& pos)
	{
		auto it = forbidden_fields.find(ferz_number);
		if (it == forbidden_fields.end())
			return false;
		
		if (find(it->second.begin(), it->second.end(), pos) != it->second.end())
			return true;

		return false;
	}

	std::pair<bool, plane_index> get_next_accepted_field(int ferz_number)
	{
		for (int i = 0; i < 64; i++)
		{
			if (is_field_occuped(i))
				continue;

			if (is_under_attack(i))
				continue;

			if (is_field_forbidden(ferz_number, i))
				continue;

			return { true, i };
		}

		return { false, 0 };
	}

	void place_frez(int ferz_number, plane_index i)
	{
		placed_ferz[ferz_number] = i;
	}

	void remove_ferz(int ferz_number)
	{
		auto it = placed_ferz.find(ferz_number);
		if (it != placed_ferz.end())
			placed_ferz.erase(it);
	}

	std::vector<plane_index> calculate_atteked_fields( const plane_index& from ) const
	{
		std::vector<plane_index> retval;
		
		{ // left-top
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true) 
			{
				--x;
				--z;
				if (x < 0 || z < 0)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		{// top
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true) 
			{
				--z;
				if (z < 0)
					break;
				retval.push_back(double_index(x, z));
			}
		}
		
		{ // right-top
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true)
			{
				++x;
				--z;
				if (x > 7 || z < 0)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		{// right
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true) // top
			{
				++x;
				if (x > 7)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		{ // right-bottom
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true)
			{
				++x;
				++z;
				if (x > 7 || z > 7)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		{ // bottom
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true)
			{
				++z;
				if (z > 7)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		{ // left-bottom
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true)
			{
				--x;
				++z;
				if (x < 0 || z > 7)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		{ // left
			double_index di = from;
			int x = di.X();
			int z = di.Z();
			while (true)
			{
				--x;
				if (x < 0)
					break;
				retval.push_back(double_index(x, z));
			}
		}

		return retval;
	}

	void add_attaked_fields(int ferz_number, const std::vector<plane_index>& fields)
	{
		attaked_fields[ferz_number] = fields;
	}

	void remove_from_attaked_fields(int ferz_number)
	{
		auto it = attaked_fields.find(ferz_number);
		if (it != attaked_fields.end())
			attaked_fields.erase(it);
	}

	void remove_from_forbidden_fields(int ferz_number)
	{
		auto it = forbidden_fields.find(ferz_number);
		if (it != forbidden_fields.end())
			forbidden_fields.erase(it);
	}

	void add_to_forbidden_fields(int ferz_number, plane_index pos)
	{
		auto it = forbidden_fields.find(ferz_number);
		if (it != forbidden_fields.end())
			it->second.push_back(pos);
		else
			forbidden_fields[ferz_number] = {pos};
	}

	plane_index get_position(int ferz_number)
	{
		return placed_ferz[ferz_number];
	}

};