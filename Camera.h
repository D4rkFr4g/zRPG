#pragma once
#include "AABB.h"

class Camera
{
public:
	Camera(void);
	Camera(int x, int y, int minX, int maxX, int minY, int maxY);
	Camera(int x, int y);
	~Camera(void);
	
	// Functions
	void initialize(int x, int y, int minX, int maxX, int minY, int maxY);
	void updateX(int value);
	void updateY(int value);
	void updateResolution(int width, int height);
	void follow(int x, int y, int width, int height);

	// Variables
	int x, y, width, height;
	int minX, maxX;
	int minY, maxY;
	int overrage;
	AABB collider;
	bool isFollowing;

private:
	void lockCameraToBoundary();
	void updateCollider(int x, int y);
};

