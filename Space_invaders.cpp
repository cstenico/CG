#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max_enemies_x 5
#define max_enemies_y 5

typedef struct{
	int alive;
	int type;
}enemy_t;


// Declara��o de vari�veis globais
GLfloat missel1_y = 0, missel2_y = 0;
GLfloat aviao_x = 0, aviao_ant = 0, aux = 0, missel1_tx = 0, missel2_tx = 0;

bool missel1_moving = false, missel2_moving = false;

int msec_missel1 = 0, msec_missel2 = 0;

int points = 0, lifes = 3;

float start_x = -3.0, start_y = 5.0;

char userPoints[] = {'P', 'O', 'I', 'N', 'T', 'S', ':', ' ', '0', '\0'};

char userLifes[] = {'L', 'I', 'F', 'E', 'S', ':', ' ', '3', '\0'};

enemy_t enemies[max_enemies_x][max_enemies_y];

float distance_between_enemies_x = 1.2f, distance_between_enemies_y = 0.6f;

float time_offset_x = 0, time_offset_y = 0;

void init_enemies() {
	int i, j;
	for(i = 0; i < max_enemies_x; i++) {
		int aux = (/*rand()*/ i % 3) + 1;
		for(j = 0; j < max_enemies_y; j++) {
			enemies[i][j].alive = 1;
			enemies[i][j].type = aux;
		}
	}
}

void timer(int count) {
	if(count == 50) {
		// jogo termina, n�mero 50 � arbitr�rio, ainda deve ser determinado
	}
	if(count % 5 == 0 && count != 0) {
		time_offset_y += 0.1f;
	} else {
		if((count / 5) % 2 == 0) {
			time_offset_x += 0.1f;
		} else {
			time_offset_x -= 0.1f;
		}
	}

	glutTimerFunc(1000, timer, count + 1);
}

/*void move_missel1(int passo){

	missel1_y += (1.0*passo)/100;
	glutPostRedisplay();

	glutTimerFunc(10, move_missel1, passo);
}*/
void move_missel2(int passo){

	missel2_y += (1.0*passo)/100;
	glutPostRedisplay();

	glutTimerFunc(10, move_missel2, passo);
}

// Fun��o para desenhar a base do objeto
void DesenhaNave()
{
  glColor3f(0.0f,1.0f,0.0f);
	glLineWidth(2);
	glBegin(GL_QUADS);
      glVertex2f(-0.3f,-1.0f );
      glVertex2f(0.3f , -1.0f );
      glVertex2f(0.15f , -0.7f);
      glVertex2f(-0.15f, -0.7f);
    glEnd();
		glBegin(GL_QUADS);
	      glVertex2f(-0.05f,-0.7f );
	      glVertex2f(0.05f , -0.7f );
	      glVertex2f(0.05f , -0.65f);
	      glVertex2f(-0.05f, -0.65f);
	    glEnd();
}

void DesenhaInimigo(float offset_x, float offset_y, int type) {

	glPointSize(5.0f);
	glColor3f(1.0f,0.0f,0.0f);

	if(type == 1) {	//inimigo tipo 1
		glBegin(GL_POINTS);
			glVertex2f(offset_x + start_x, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.25f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.25f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.3f);
		glEnd();
	} else if(type == 2) {	//inimigo tipo 2
		glBegin(GL_POINTS);
			glVertex2f(offset_x + start_x, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.55f,offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.25f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.25f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.3f);
		glEnd();
	} else if(type == 3) {	//inimigo tipo 3
		glBegin(GL_POINTS);
			glVertex2f(offset_x + start_x, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.05f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.2f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.25f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.25f);
			glVertex2f(offset_x + start_x, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.05f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.1f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.15f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.25f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.35f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.45f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.5f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.55f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.6f, offset_y + start_y - 0.3f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.2f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.1f);
			glVertex2f(offset_x + start_x + 0.4f, offset_y + start_y - 0.15f);
			glVertex2f(offset_x + start_x + 0.3f, offset_y + start_y - 0.2f);
		glEnd();
	}
}

void DesenhaMatrizInimigos() {
	int i, j;
	for(i = 0; i < max_enemies_x; i++) {
		int aux = enemies[i][0].type;
		for(j = 0; j < max_enemies_y; j++) {
			if(enemies[i][j].alive == 1) {
				float aux_i = (float) i, aux_j = (float) j;
				DesenhaInimigo(distance_between_enemies_x * aux_j + time_offset_x, -(distance_between_enemies_y * aux_i) - time_offset_y, aux);
			}
		}
	}

}

void DesenhaMissel()
{
  glColor3f(1.0f,0.0f,0.0f);
	glLineWidth(2);
	glBegin(GL_QUADS);
      glVertex2f(-0.05f,-1.0f );
      glVertex2f(0.05f , -1.0f );
      glVertex2f(0.05f , -0.8f);
      glVertex2f(-0.05f, -0.8f);
    glEnd();
}

void DesenhaMisseis(){

	glColor3f(1.0f,0.0f,0.0f);
	glLineWidth(2);
	glBegin(GL_POLYGON);
		glVertex2f(-1.0f,-1.0f);
		glVertex2f(-1.0f,-0.7f);
		glVertex2f(-0.9f,-0.6f);
		glVertex2f(-0.8f,-0.7f);
		glVertex2f(-0.8f,-1.0f);
	glEnd();
}

void move_missel1(int passo){

	missel1_y += (1.0*passo)/100;
	glutPostRedisplay();
	if(missel1_y < 5 && missel1_moving)
		glutTimerFunc(100, move_missel1, passo);
  else{
		missel1_moving = false;
		missel1_y = 0;
		DesenhaMissel();
	}
}

void print(float x, float y, char *string){
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x,y);
	//get the length of the string to display
	int len = (int) strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

// Funcao callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transforma��o corrente
	glLoadIdentity();

	// Limpa a janela de visualizacao com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(-aviao_ant,0.0f,0.0f);
	glTranslatef(aviao_x,0.0f,0.0f);
	glTranslatef(0.0f,-0.7f,0.0f);
	glScalef(0.3f,0.3f,0.0f);
	glPushMatrix();

	if(missel2_moving){
		glTranslatef(-aviao_x,0.0f,0.0f);
		glTranslatef(missel2_tx,0.0f,0.0f);
	}

	//M�ssel 2;
	//glTranslatef(0.0f,missel2_y,0.0f);
	//glTranslatef(1.8f,0.0f,0.0f);
	//DesenhaMissel();

	glPopMatrix(); // Carrega a identidade = Limpa a matrix de transforma��es.
	glPushMatrix();

	if(missel1_moving){
		glTranslatef(-aviao_x,0.0f,0.0f);
		glTranslatef(missel1_tx,0.0f,0.0f);
	}
	//M�ssel 1.
	glTranslatef(0.0f,missel1_y,0.0f);
	DesenhaMissel();

	glPopMatrix(); //Pro jatinho nao sair junto com o missel 1.
	// Desenha o jatinho.
	DesenhaNave();
	glPopMatrix();
	glPopMatrix();
	//DesenhaInimigo(1, -1, 1);
	//DesenhaInimigo(2, -2, 2);
	//DesenhaInimigo(3, -3, 3);
	DesenhaMatrizInimigos();

	print(2, 5.3f, userLifes);
	print(-3, 5.3f, userPoints);
	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura)
	{
		gluOrtho2D (-1.0f, 1.0f, -1.0f*altura/largura, 1.0f*altura/largura);
		//win = 1.0f;
	}
	else
	{
		gluOrtho2D (-1.0f*largura/altura, 1.0f*largura/altura, -1.0f, 1.0f);
	//	win = 1.0f*largura/altura;
	}
}

// Fun��o callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT){
		aviao_ant = aviao_x;
		aviao_x-=0.05;
		if ( aviao_x < -1.0f )
			aviao_x = -1.0f;
	}
	if(key == GLUT_KEY_RIGHT){
		aviao_ant = aviao_x;
		aviao_x += 0.05;
		if (aviao_x > 1.0f)
			aviao_x = 1.0f;
	}
	if(key == GLUT_KEY_UP){
		missel1_moving = true;
		missel1_tx = aviao_x;
		glutTimerFunc(10, move_missel1, 1);
	}
	if(key == GLUT_KEY_DOWN){
		missel2_moving = true;
		missel2_tx = aviao_x;
		glutTimerFunc(10, move_missel2, 1);
	}


	glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
    if (key == 32)
    {
        missel1_moving = true;
		//missel1_tx = aviao_x;
		glutTimerFunc(10, move_missel1, 10);
    }
    //glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(0.0f, 0.003f, 0.0823f, 0.0f);
	gluOrtho2D (-1.0f, 1.0f, -1.0f, 1.0f);
	glViewport(0, 0, 720, 720);
	init_enemies();
}



// Programa Principal
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Inicia uma inst�ncia da glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(720,720);
	glutCreateWindow("Space Invaders!");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
	glutTimerFunc(1000, timer, 0);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	glutTimerFunc(0, move_missel1, 0); // Timer para mover o missel 1
	glutTimerFunc(0, move_missel2, 0); // ..........................2

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
