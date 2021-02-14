#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

#define TAMANHO_JANELA 500

struct point
{
	float x;
	float y;
};
typedef struct point t_point;

struct vectorPoints
{
	t_point* points;
	int total;
	void (*add)(float x, float y);
	void (*move)(t_point);
};
typedef struct vectorPoints t_vectorPoints;

struct keyboardControl
{
	int keyStatus[256];
	bool keyPressed;
};
typedef struct keyboardControl t_keyboardControl;

struct mouseControl
{
	t_point point;
	bool isLeftClicked;
};
typedef struct mouseControl t_mouseControl;

t_vectorPoints* vectorPoints;
t_keyboardControl* keyboardControl;
t_mouseControl* mouseControl;

void movePoints(t_point point);
t_point convertToGLCoordenates(int x, int y);
void addPoints(float x, float y);

void initialization(void);

float calculateEuclidianDistance(t_point p1, t_point p2);
bool isOnRectangle(t_point p1, t_point p2, t_point pc);

void setValue(unsigned char key, int value);
void keyEvent(unsigned char key, int value);
void executeKeyAction(void);

void move(int x, int y);
bool checkClickArea(t_point mouseMovePoint);

void init(void);
void display(void);
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void idle(void);
void onExit(void);

int main(int argc, char** argv)
{
	initialization();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello world");
	init();	
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyPress);
	glutIgnoreKeyRepeat(true);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(idle);
	atexit(onExit);
	glutMainLoop();

	return (0);
}

void init(void)
{
	/* selecionar cor de fundo (preto) */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/* inicializar sistema de visualizacao */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void display(void)
{
	int i;

	/* Limpar todos os pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
	glColor3f(1.0, 1.0, 1.0);
	/* Desenhar um polígono branco (retângulo) */
	
	if (vectorPoints->total > 0)
	{
		glBegin(GL_POLYGON);
		glVertex3f(vectorPoints->points[0].x, vectorPoints->points[0].y, 0.0);
		for (i = 1; i < vectorPoints->total; i++)
			glVertex3f(vectorPoints->points[i - 1].x + (vectorPoints->points[i].x - vectorPoints->points[i - 1].x), vectorPoints->points[i - 1].y + (vectorPoints->points[i].y - vectorPoints->points[i - 1].y), 0.0);
		glEnd();
	}

	/* Desenhar no frame buffer! */
	glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void keyPress(unsigned char key, int x, int y)
{
	if (!mouseControl->isLeftClicked)
	{
		mouseControl->point.x = mouseControl->point.y = 0.0f;
		keyboardControl->keyPressed = true;
		vectorPoints->move = &movePoints;
		keyEvent(key, 1);
	}
}

void keyUp(unsigned char key, int x, int y)
{
	if (!mouseControl->isLeftClicked)
	{
		keyEvent(key, 0);
		vectorPoints->move = NULL;
		keyboardControl->keyPressed = false;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (!keyboardControl->keyPressed)
	{
		mouseControl->point = convertToGLCoordenates(x, y);

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			mouseControl->isLeftClicked = state == GLUT_DOWN;
		else
			mouseControl->isLeftClicked = false;
	}
}	

void mouseMotion(int x, int y)
{
	t_point mouseMovePoint;

	if (!keyboardControl->keyPressed)
	{
		mouseMovePoint = convertToGLCoordenates(x, y);
		if (mouseControl->isLeftClicked && checkClickArea(mouseMovePoint))
			move(x, y);
		mouseControl->point = mouseMovePoint;
	}
}

void idle(void)
{
	if (keyboardControl->keyPressed)
		executeKeyAction();
	
	glutPostRedisplay();
}

void onExit(void)
{
	free(vectorPoints->points);
	free(vectorPoints);
}

t_point convertToGLCoordenates(int x, int y)
{
	t_point point;
	
	point.x = (float)x / (float)TAMANHO_JANELA;
	point.y = 1 - (float)y / (float)TAMANHO_JANELA;

	return (point);
}

void addPoints(float x, float y)
{
	vectorPoints->points = (t_point*) realloc(vectorPoints->points, ++vectorPoints->total * sizeof(t_point));
	vectorPoints->points[vectorPoints->total - 1].x = x;
	vectorPoints->points[vectorPoints->total - 1].y = y;
}

void movePoints(t_point point)
{
	int i;

	for (i = 0; i < vectorPoints->total; i++)
	{
		vectorPoints->points[i].x += (point.x - mouseControl->point.x);
		vectorPoints->points[i].y += (point.y - mouseControl->point.y);
	}
}

void initialization(void)
{
	vectorPoints = (t_vectorPoints*) calloc(1, sizeof(t_vectorPoints));
	vectorPoints->points = (t_point*) malloc(sizeof(t_point));
	vectorPoints->move = NULL;
	vectorPoints->add = &addPoints;

	keyboardControl = (t_keyboardControl*) calloc(1, sizeof(t_keyboardControl));
	mouseControl = (t_mouseControl*) calloc(1, sizeof(t_mouseControl));;

	vectorPoints->add(0.25, 0.25);
	vectorPoints->add(0.50, 0.25);
	vectorPoints->add(0.50, 0.50);
	vectorPoints->add(0.25, 0.50);
}

void setValue(unsigned char key, int value)
{
	keyboardControl->keyStatus[(int)key] = value;
}

void keyEvent(unsigned char key, int value)
{
	switch (key)
	{
		case 'w':
		case 's':
		case 'a':
		case 'd':
			setValue(key, value);
			setValue(key & 0x5f, value);
			break;
		case 'W':
		case 'S':
		case 'A':
		case 'D':
			setValue(key, value);
			setValue(key ^ 0x20, value);
			break;
	}
}

void executeKeyAction(void)
{
	t_point point;

	point.x = point.y = 0.0f;

	if (keyboardControl->keyStatus[(int)'w'] || keyboardControl->keyStatus[(int)'W'])
		point.y += 0.01f;
	if (keyboardControl->keyStatus[(int)'s'] || keyboardControl->keyStatus[(int)'S'])
		point.y -= 0.01f;
	if (keyboardControl->keyStatus[(int)'a'] || keyboardControl->keyStatus[(int)'A'])
		point.x -= 0.01f;
	if (keyboardControl->keyStatus[(int)'d'] || keyboardControl->keyStatus[(int)'D'])
		point.x += 0.01f;

	if (vectorPoints->move)
		vectorPoints->move(point);
}

void move(int x, int y)
{
	t_point point;

	vectorPoints->move = &movePoints;
	point = convertToGLCoordenates(x, y);
	vectorPoints->move(point);
}

float calculateEuclidianDistance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

void findOpositeVertices(t_point *v1, t_point *v2)
{
	float euclidianDistanceTemp, euclidianDistanceMax = 0.0f;
	int i;

	*v1 = vectorPoints->points[0];

	for (i = 1; i < vectorPoints->total; i++)
	{
		euclidianDistanceTemp = calculateEuclidianDistance(*v1, vectorPoints->points[i]);
		if (euclidianDistanceTemp > euclidianDistanceMax)
		{
			euclidianDistanceMax = euclidianDistanceTemp;
			*v2 = vectorPoints->points[i];
		}
	}
}

bool isOnRectangle(t_point p1, t_point p2, t_point pc)
{
    return ((pc.x <= max(p1.x, p2.x)) && (pc.x >= min(p1.x, p2.x)) && (pc.y <= max(p1.y, p2.y)) && (pc.y >= min(p1.y, p2.y)));
}

bool checkClickArea(t_point mouseMovePoint)
{
	t_point vertex1, vertex2;

	findOpositeVertices(&vertex1, &vertex2);

	return (isOnRectangle(vertex1, vertex2, mouseMovePoint));
}