#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point(float x, float y);
	Point(int x, int y, int width, int height);

	float getX(void);
	float getY(void);
	void setX(float x);
	void setY(float y);

private:
	float x;
	float y;
	void convertToGLCoordenates(int x, int y, int width, int height);

};

#endif