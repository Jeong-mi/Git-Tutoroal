#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> 
#include <gl/GLAUX.H>

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "glaux.lib")

unsigned int MyTextureObject[1];
AUX_RGBImageRec* pTextureImage[1]; //텍스쳐 저장 공간을 가리키는 포인터

//glRotatef함수에 필요한 파라미터
GLfloat rx = 0.0; GLfloat ry = 0.0; GLfloat rz = 0.0;
int radius = 0;

//glulookat함수 구현시에 필요한 파라미터
GLfloat ex = 0.0; GLfloat ey = 2.0; GLfloat ez = 2.0; //시점(카메라) 위치
GLfloat cx = 0.0; GLfloat cy = 0.0; GLfloat cz = 0.0; //초점의 위치
GLfloat ux = 0.0; GLfloat uy = 1.0; GLfloat uz = 0.0; //상향벡터, 기울임

int iType = 0;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };

	//0번 광원 특성
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };//위치성 광원
	GLfloat light_diffuse0[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient0[] = { 0.3, 0.3, 0.3, 1.0 };

	//1번 광원 특성
	GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };//방향성 광원
	GLfloat light_diffuse1[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient1[] = { 0.3, 0.3, 0.3, 1.0 };

	//2번 광원 특성
	GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0 };//스포트라이트
	GLfloat light_diffuse2[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light_ambient2[] = { 0.5, 0.4, 0.3, 1.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0); //위치성 광원
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	
	glEnable(GL_LIGHT1);//방향성 광원
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	
	glEnable(GL_LIGHT2);//스포트라이트
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyDisplay() {
	GLfloat light_position0[] = { 1.0, 1.0, 0, 1.0 }; //위치성 광원 위치
	GLfloat light_position1[] = { -1.0, 1.0, 0.0, 0.0 }; //방향성 광원 위치
	GLfloat light_position2[] = { 1.0, 1.0, 1.0, 1.0 }; //스포트라이트 위치
	GLfloat light_direction2[] = { -0.5, -0.5, -0.5 }; //스포트라이트 방향
	GLfloat SpotAngle[] = { 20.0 }; //스포트라이트 각도

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //glulookat을 쓰기 위해 모델뷰 행렬모드(뷰행렬에 모델행렬을 곱한 것)로 설정
	glLoadIdentity(); //전역좌표계=시점좌표계=모델좌표계, 모델뷰행렬을 초기화
	gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz); //전역좌표계로부터 시점좌표계가 분리, 뷰변환
	glRotatef(radius, rx, ry, rz); //시점좌표계로부터 모델좌표계가 분리, 모델변환
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //위치성 광원
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1); //방향성 광원
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2); //스포트라이트
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction2);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, SpotAngle);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);
	
	glutSolidTeapot(0.5); //모델좌표
	glFlush();
}

AUX_RGBImageRec* LoadBMP()
{

	return auxDIBImageLoad("sample2.bmp");

}

int LoadGLTextures() //파일을 로드하고 텍스쳐로 변환
{

	int Status = FALSE;

	glClearColor(0.0, 0.0, 0.0, 0.5);

	memset(pTextureImage, 0, sizeof(void*) * 1); //포인터를 널로

	if (pTextureImage[0] = LoadBMP()) //비트맵을 로드하고 오류확인
	{

		Status = TRUE;	//상태 플랙을 True로
		glGenTextures(1, &MyTextureObject[0]); //텍스쳐 생성
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);

	}

	if (pTextureImage[0]) //텍스쳐가 존재하면
	{

		if (pTextureImage[0]->data)	//텍스쳐 영상이 존재하면
		{
			free(pTextureImage[0]->data); //텍스쳐 영상공간 반납
		}

		free(pTextureImage[0]);	//텍스쳐 반납

	}

	return Status;

}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		//카메라의 x축 이동
	case 'a':
	case 's':
		ex += 0.1; //시점(카메라)의 좌표가 x축방향으로 0.1 움직일때
		cx += 0.1; //모델의 좌표도 x축으로 같은 크기만큼(0.1) 움직이면
		//극좌표계 시점이 되지 않으며 카메라의 방향은 항상 수평이 되어서 이동한다.
		glutPostRedisplay();
		break;

		//카메라의 y축 이동
	case 'd':
	case 'f':
		ey += 0.1;
		cy += 0.1; 
		glutPostRedisplay(); //변환된 변수값을 바로 반영해서 렌더링하는 함수
		break;

		//카메라의 z축 이동
	case 'z':
	case 'x':
		ez += 0.1;
		cz += 0.1;
		glutPostRedisplay();
		break;

		//모델의 x축회전
	case 'g':
	case 'h':
		rx = 1.0;	ry = 0.0;   rz = 0.0; //glRotatef 함수에서 x축으로만 1로 설정하면 모델의 x축 회전이 된다.
		radius = (radius + 10) % 360; 
		//한번 회전하고 끝이 아니라 키보드를 계속 누르면 계속 회전이 되게끔 코드를 만들기 위해
		//각도를 360도 안에서 유지되게 나머지 연산을 사용함으로써 누를 때마다 계속 변하게 만듬
		glutPostRedisplay();
		break;

		//모델의 y축회전
	case 'j':
	case 'k':
		rx = 0.0;	ry = 1.0;   rz = 0.0;
		radius = (radius + 10) % 360;
		glutPostRedisplay();
		break;

		//모델의 z축회전
	case 'l':
	case 'm':
		rx = 0.0;	ry = 0.0;   rz = 1.0;
		radius = (radius + 10) % 360;
		glutPostRedisplay();
		break;
	};
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //윈도우 크기가 바뀌면 뷰포트도 따라서 바뀐다
	glMatrixMode(GL_PROJECTION); //행렬모드를 투상행렬로 놓아야 한다
	glLoadIdentity(); //현투상행렬을 항등행렬로 초기화
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	gluPerspective(45, (GLdouble)w / (GLdouble)h, 0.1, 30.0); 
	//평행투상(정투상)을 원근투상으로 변환시킴
	//왜곡을 방지하기 위해 종횡비는 윈도우 크기에 따라가도록 함
	//시점이 물체로부터 유한한 거리에 있다고 간주, 방사선 모양으로 투상선이 퍼져 나감
	//60도의 각으로 보는 것과 45의 각으로 보는 것은 분명한 차이가 있다.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH); 
	//프레임 모드를 단일버퍼로, 컬러모드를 RGBA로 지정, 깊이버퍼를 가진 창으로 지정
	
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0); 
	//윈도우의 좌상단을 화면좌표계의 원점에 위치시킴
	
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