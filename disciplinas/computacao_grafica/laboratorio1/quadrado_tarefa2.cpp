#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

float gX = 0;
float gY = 0;
int keyStatus[256];

void display(void)
{
   /* Limpar todos os pixels  */
   glClear(GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 1.0, 1.0);
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (gX + 0.25, gY + 0.25, 0.0);
      glVertex3f (gX + 0.75, gY + 0.25, 0.0);
      glVertex3f (gX + 0.75, gY + 0.75, 0.0);
      glVertex3f (gX + 0.25, gY + 0.75, 0.0);
   glEnd();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init(void) 
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de visualizacao */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void setValue(unsigned char key, int value)
{
    keyStatus[(int)key] = value;
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

void keyPress(unsigned char key, int x, int y)
{
    keyEvent(key, 1);
}

void keyUp(unsigned char key, int x, int y)
{
    keyEvent(key, 0);
    glutPostRedisplay();
}

void idle(void)
{
    if (keyStatus[(int)'w'] || keyStatus[(int)'W'])
        gY += 0.001;
    if (keyStatus[(int)'s'] || keyStatus[(int)'S'])
        gY -= 0.001;
    if (keyStatus[(int)'a'] || keyStatus[(int)'A'])
        gX -= 0.001;
    if (keyStatus[(int)'d'] || keyStatus[(int)'D'])
        gX += 0.001;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello world");
    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);

    glutMainLoop();

    return 0;
}