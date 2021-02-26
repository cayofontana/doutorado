#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	Color(float, float, float);

	float getRed(void);
	float getGreen(void);
	float getBlue(void);
	void setRed(float);
	void setGreen(float);
	void setBlue(float);

private:
	float red;
	float green;
	float blue;
};

#endif