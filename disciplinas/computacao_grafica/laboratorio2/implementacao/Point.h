#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point(float, float);
	Point(int, int, int, int);

	float getX(void);
	void setX(float);
	float getY(void);
	void setY(float);
	void increase(float, float);
	void setGLCoordinates(int, int, int, int);

private:
	float x;
	float y;
};

#endif