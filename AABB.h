#pragma once

class AABB
{
public:
	// Constructors
	AABB(void);
	AABB(int x, int y, int w, int h);
	~AABB(void);

	// Functions
	bool AABBIntersect(AABB* box);
	static bool* AABBwhichSideIntersected(AABB* prevBox, AABB* currBox, AABB* box2);

	// Variables
	int x, y, w, h;
};

