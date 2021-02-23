#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point(float, float);

	float getX(void);
	void setX(float);
	float getY(void);
	void setY(float);
	void increase(float, float);

private:
	float x;
	float y;
};

#endif