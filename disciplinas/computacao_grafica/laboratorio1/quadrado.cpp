#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

float gX = 0;
float gY = 0;

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

void keyPress(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'w':
   case 'W':
      gY += 0.01;
      break;
   case 's':
   case 'S':
      gY -= 0.01;
      break;
   case 'a':
   case 'A':
      gX -= 0.01;
      break;
   case 'd':
   case 'D':
      gX += 0.01;
      break;   
   default:
      printf("Opção inválida!");
      break;
   }
   glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'w':
   case 'W':
      gY += 0.01;
      break;
   case 's':
   case 'S':
      gY -= 0.01;
      break;
   case 'a':
   case 'A':
      gX -= 0.01;
      break;
   case 'd':
   case 'D':
      gX += 0.01;
      break;   
   default:
      printf("Opção inválida!");
      break;
   }
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
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);    

    glutMainLoop();

    return 0;
}