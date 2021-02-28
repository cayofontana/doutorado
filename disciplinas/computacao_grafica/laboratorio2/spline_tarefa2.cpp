#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <cstdio>
#include <GL/glut.h>
#include <math.h>

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

#define TAMANHO_JANELA 500

float size = 5.0;

//Pontos de controle da Spline
GLfloat ctrlpoints[4][3] = {
	{.1, .1, 0.0}, {.3, .8, 0.0}, 
	{.7, .1, 0.0}, {.9, .9, 0.0}
};

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

t_point convertToGLCoordenates(int x, int y);
void movePoints(t_point point);
void addPoints(float x, float y);

void initialization(void);

float calculateEuclidianDistance(t_point p1, t_point p2);
bool isOnRectangle(t_point p1, t_point p2, t_point pc);

void setValue(unsigned char key, int value);
void keyEvent(unsigned char key, int value);
void executeKeyAction(void);

void move(int x, int y);
bool checkClickArea(t_point mouseMovePoint);

t_vectorPoints* vectorPoints;
t_keyboardControl* keyboardControl;
t_mouseControl* mouseControl;

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

	ctrlpoints[1][0] = vectorPoints->points[1].x;
	ctrlpoints[1][1] = vectorPoints->points[1].y;
	ctrlpoints[2][0] = vectorPoints->points[2].x;
	ctrlpoints[2][1] = vectorPoints->points[2].y;
}

void initialization(void)
{
	vectorPoints = (t_vectorPoints*) calloc(1, sizeof(t_vectorPoints));
	vectorPoints->points = (t_point*) malloc(sizeof(t_point));
	vectorPoints->move = NULL;
	vectorPoints->add = &addPoints;

	keyboardControl = (t_keyboardControl*) calloc(1, sizeof(t_keyboardControl));
	mouseControl = (t_mouseControl*) calloc(1, sizeof(t_mouseControl));

	vectorPoints->add(.1, .1);
	vectorPoints->add(.3, .8);
	vectorPoints->add(.7, .1);
	vectorPoints->add(.9, .9);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);

	//Definicao do polinomio com os pontos de controle
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlpoints); 

	//Muda para a matriz de projecao (aulas futuras)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-size, size, -size, size, -size, size);
	glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
}

void display(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	/* Desenha a curva aproximada por n+1 pontos. */
	int n = 30;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= n; i++)
		//Avaliacao do polinomio, retorna um vertice (equivalente a um glVertex3fv) 
		glEvalCoord1f((GLfloat) i/(GLfloat)n);
	glEnd();
	/* Desenha os pontos de controle. */
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();

	glutSwapBuffers();
}

// void reshape(int w, int h)
// {
// 	//Define a porcao visivel da janela
// 	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

// 	//Muda para a matriz de projecao (aulas futuras)
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();

// 	//Controla o redimensionamento da janela mantendo o aspect ration do objeto
// 	if (w <= h)
// 		glOrtho(-size, size, -size*(GLfloat)h/(GLfloat)w, size*(GLfloat)h/(GLfloat)w, -size, size);
// 	else
// 		glOrtho(-size*(GLfloat)w/(GLfloat)h, size*(GLfloat)w/(GLfloat)h, -size, size, -size, size);

// 	//Muda para a matriz de trasformacoes (aulas futuras)
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// }

void mouse(int button, int state, int x, int y)
{
	if (!keyboardControl->keyPressed)
	{
		mouseControl->point = convertToGLCoordenates(x, y);
		printf("(%2f, %2f)\n", mouseControl->point.x, mouseControl->point.y);

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
		printf("(%2f, %2f)\n", mouseControl->point.x, mouseControl->point.y);
		if (mouseControl->isLeftClicked && checkClickArea(mouseMovePoint))
			move(x, y);
		mouseControl->point = mouseMovePoint;
	}
}

int main(int argc, char** argv)
{
	initialization();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	// glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutMainLoop();
	return 0;
}

t_point convertToGLCoordenates(int x, int y)
{
	t_point point;
	
	point.x = (float)x / (float)TAMANHO_JANELA;
	point.y = 1 - (float)y / (float)TAMANHO_JANELA;

	return (point);
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