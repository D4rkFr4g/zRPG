#include "Camera.h"


Camera::Camera(void)
{
}
/*-----------------------------------------------*/
Camera::Camera(int x, int y, int minX, int maxX, int minY, int maxY)
{
	initialize(x, y, minX, maxX, minY, maxY);
}
/*-----------------------------------------------*/
Camera::Camera(int x, int y)
{
	initialize(x, y, 0, sizeof(int), 0, sizeof(int));
}
/*-----------------------------------------------*/
Camera::~Camera(void)
{
}
/*-----------------------------------------------*/
void Camera::initialize(int x, int y, int minX, int maxX, int minY, int maxY)
{
	/* PURPOSE:		Initializer for constructors to setup all variables 
		RECEIVES:	x - Horizontal screen position
						y - Vertical screen position
						minX - Minimum horizontal screen position
						maxX - Maximum horizontal screen position
						minY - Minimum vertical screen position
						maxY - Maximum vertical screen position
		RETURNS:		 
		REMARKS:		 
	*/

	this->x = x;
	this->y = y;
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
	collider.x = x - overrage;
	collider.y = y - overrage;
	overrage = 64;
	isFollowing = false;
}
/*-----------------------------------------------*/
void Camera::updateResolution(int width, int height)
{
	/* PURPOSE:		Sets collider and screen dimension variables to new resolution 
		RECEIVES:	width - New horizontal resolution
						height - New vertical resolution
		RETURNS:		 
		REMARKS:		 
	*/

	this->width = width;
	this->height = height;

	collider.w = width + overrage;
	collider.h = height + overrage;
}
/*-----------------------------------------------*/
void Camera::updateX(int value)
{
	/* PURPOSE:		Moves the camera within defined boundaries 
		RECEIVES:	value - Amount to move in x direction 
		RETURNS:		 
		REMARKS:		 
	*/

	x = x + value;
	lockCameraToBoundary();
	updateCollider(this->x, this->y);
}
/*-----------------------------------------------*/
void Camera::updateY(int value)
{
	/* PURPOSE:		Moves the camera within defined boundaries 
		RECEIVES:	value - Amount to move in y direction 
		RETURNS:		 
		REMARKS:		 
	*/

	y = y + value;
	lockCameraToBoundary();
	updateCollider(this->x, this->y);
}
/*-----------------------------------------------*/
void Camera::follow(int x, int y, int width, int height)
{
	/* PURPOSE:		Camera tracks object by keeping it in the center of the screen 
		RECEIVES:	x - horizontal screen position of object to be followed
						y - vertical screen position of object to be followed
						width - Width of object to be followed
						height - Height of object to be followed
		RETURNS:		 
		REMARKS:		 
	*/

	if (isFollowing)
	{
		// Put in center of screen
		this->x = (x + (width/2)) - (this->width / 2); 
		this->y = (y + (height/2)) - (this->height / 2);

		lockCameraToBoundary();
		updateCollider(this->x, this->y);
	}
}
/*-----------------------------------------------*/
void Camera::lockCameraToBoundary()
{
	/* PURPOSE:		Keeps camera within pre-defined boundary 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	if (x < minX)
		x = minX;
	else if (x > maxX)
		x = maxX;

	if (y < minY)
		y = minY;
	else if (y > maxY)
		y = maxY;
}
/*-----------------------------------------------*/
void Camera::updateCollider(int x, int y)
{
	/* PURPOSE:		Move the position of the objects collider 
		RECEIVES:	x - horizontal position of collider
						y - vertical position of collider
		RETURNS:		 
		REMARKS:		 
	*/

	collider.x = x - overrage;
	collider.y = y - overrage;
}
/*-----------------------------------------------*/