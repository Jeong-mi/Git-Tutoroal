#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> 
#include <gl/GLAUX.H>

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "glaux.lib")

unsigned int MyTextureObject[1];
AUX_RGBImageRec* pTextureImage[1]; //�ؽ��� ���� ������ ����Ű�� ������

//glRotatef�Լ��� �ʿ��� �Ķ����
GLfloat rx = 0.0; GLfloat ry = 0.0; GLfloat rz = 0.0;
int radius = 0;

//glulookat�Լ� �����ÿ� �ʿ��� �Ķ����
GLfloat ex = 0.0; GLfloat ey = 2.0; GLfloat ez = 2.0; //����(ī�޶�) ��ġ
GLfloat cx = 0.0; GLfloat cy = 0.0; GLfloat cz = 0.0; //������ ��ġ
GLfloat ux = 0.0; GLfloat uy = 1.0; GLfloat uz = 0.0; //���⺤��, �����

int iType = 0;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };

	//0�� ���� Ư��
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };//��ġ�� ����
	GLfloat light_diffuse0[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient0[] = { 0.3, 0.3, 0.3, 1.0 };

	//1�� ���� Ư��
	GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };//���⼺ ����
	GLfloat light_diffuse1[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient1[] = { 0.3, 0.3, 0.3, 1.0 };

	//2�� ���� Ư��
	GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0 };//����Ʈ����Ʈ
	GLfloat light_diffuse2[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light_ambient2[] = { 0.5, 0.4, 0.3, 1.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0); //��ġ�� ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	
	glEnable(GL_LIGHT1);//���⼺ ����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	
	glEnable(GL_LIGHT2);//����Ʈ����Ʈ
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyDisplay() {
	GLfloat light_position0[] = { 1.0, 1.0, 0, 1.0 }; //��ġ�� ���� ��ġ
	GLfloat light_position1[] = { -1.0, 1.0, 0.0, 0.0 }; //���⼺ ���� ��ġ
	GLfloat light_position2[] = { 1.0, 1.0, 1.0, 1.0 }; //����Ʈ����Ʈ ��ġ
	GLfloat light_direction2[] = { -0.5, -0.5, -0.5 }; //����Ʈ����Ʈ ����
	GLfloat SpotAngle[] = { 20.0 }; //����Ʈ����Ʈ ����

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //glulookat�� ���� ���� �𵨺� ��ĸ��(����Ŀ� ������� ���� ��)�� ����
	glLoadIdentity(); //������ǥ��=������ǥ��=����ǥ��, �𵨺������ �ʱ�ȭ
	gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz); //������ǥ��κ��� ������ǥ�谡 �и�, �亯ȯ
	glRotatef(radius, rx, ry, rz); //������ǥ��κ��� ����ǥ�谡 �и�, �𵨺�ȯ
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //��ġ�� ����
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1); //���⼺ ����
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2); //����Ʈ����Ʈ
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction2);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, SpotAngle);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);
	
	glutSolidTeapot(0.5); //����ǥ
	glFlush();
}

AUX_RGBImageRec* LoadBMP()
{

	return auxDIBImageLoad("sample2.bmp");

}

int LoadGLTextures() //������ �ε��ϰ� �ؽ��ķ� ��ȯ
{

	int Status = FALSE;

	glClearColor(0.0, 0.0, 0.0, 0.5);

	memset(pTextureImage, 0, sizeof(void*) * 1); //�����͸� �η�

	if (pTextureImage[0] = LoadBMP()) //��Ʈ���� �ε��ϰ� ����Ȯ��
	{

		Status = TRUE;	//���� �÷��� True��
		glGenTextures(1, &MyTextureObject[0]); //�ؽ��� ����
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);

	}

	if (pTextureImage[0]) //�ؽ��İ� �����ϸ�
	{

		if (pTextureImage[0]->data)	//�ؽ��� ������ �����ϸ�
		{
			free(pTextureImage[0]->data); //�ؽ��� ������� �ݳ�
		}

		free(pTextureImage[0]);	//�ؽ��� �ݳ�

	}

	return Status;

}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		//ī�޶��� x�� �̵�
	case 'a':
	case 's':
		ex += 0.1; //����(ī�޶�)�� ��ǥ�� x��������� 0.1 �����϶�
		cx += 0.1; //���� ��ǥ�� x������ ���� ũ�⸸ŭ(0.1) �����̸�
		//����ǥ�� ������ ���� ������ ī�޶��� ������ �׻� ������ �Ǿ �̵��Ѵ�.
		glutPostRedisplay();
		break;

		//ī�޶��� y�� �̵�
	case 'd':
	case 'f':
		ey += 0.1;
		cy += 0.1; 
		glutPostRedisplay(); //��ȯ�� �������� �ٷ� �ݿ��ؼ� �������ϴ� �Լ�
		break;

		//ī�޶��� z�� �̵�
	case 'z':
	case 'x':
		ez += 0.1;
		cz += 0.1;
		glutPostRedisplay();
		break;

		//���� x��ȸ��
	case 'g':
	case 'h':
		rx = 1.0;	ry = 0.0;   rz = 0.0; //glRotatef �Լ����� x�����θ� 1�� �����ϸ� ���� x�� ȸ���� �ȴ�.
		radius = (radius + 10) % 360; 
		//�ѹ� ȸ���ϰ� ���� �ƴ϶� Ű���带 ��� ������ ��� ȸ���� �ǰԲ� �ڵ带 ����� ����
		//������ 360�� �ȿ��� �����ǰ� ������ ������ ��������ν� ���� ������ ��� ���ϰ� ����
		glutPostRedisplay();
		break;

		//���� y��ȸ��
	case 'j':
	case 'k':
		rx = 0.0;	ry = 1.0;   rz = 0.0;
		radius = (radius + 10) % 360;
		glutPostRedisplay();
		break;

		//���� z��ȸ��
	case 'l':
	case 'm':
		rx = 0.0;	ry = 0.0;   rz = 1.0;
		radius = (radius + 10) % 360;
		glutPostRedisplay();
		break;
	};
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //������ ũ�Ⱑ �ٲ�� ����Ʈ�� ���� �ٲ��
	glMatrixMode(GL_PROJECTION); //��ĸ�带 ������ķ� ���ƾ� �Ѵ�
	glLoadIdentity(); //����������� �׵���ķ� �ʱ�ȭ
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	gluPerspective(45, (GLdouble)w / (GLdouble)h, 0.1, 30.0); 
	//��������(������)�� ������������ ��ȯ��Ŵ
	//�ְ��� �����ϱ� ���� ��Ⱦ��� ������ ũ�⿡ ���󰡵��� ��
	//������ ��ü�κ��� ������ �Ÿ��� �ִٰ� ����, ��缱 ������� ������ ���� ����
	//60���� ������ ���� �Ͱ� 45�� ������ ���� ���� �и��� ���̰� �ִ�.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH); 
	//������ ��带 ���Ϲ��۷�, �÷���带 RGBA�� ����, ���̹��۸� ���� â���� ����
	
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0); 
	//�������� �»���� ȭ����ǥ���� ������ ��ġ��Ŵ
	
	glutCreateWindow("OPENGL Sample Drawing");
	
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	if (LoadGLTextures())
	{
		glClearColor(1, 1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glutMainLoop();

	}
	glutMainLoop();
	return 0;
}