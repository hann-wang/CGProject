#include "stdafx.h"
#include <gl/freeglut.h>
#include <math.h>
#include "Plot3D.h"
#include "teapot.h"
#include "text3d.h"

CcgProjectDlg* handle;

//纹理编号
GLuint texKing;

GLfloat light_position[] = { 600.0,600.0,600.0,0.0 };
GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
GLfloat mat_grey_ambient[] = { 0.5,0.5,0.5,1.0 };
GLfloat mat_green_ambient[] = { 0.0,1.0,0.0,1.0 };
GLfloat mat_diffuse[] = { 0.2,0.2,0.2,1.0 };
GLfloat mat_specular[] = { 0.2,1.0,0.2,1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.2,0.2,0.2,0.0 };

//获取屏幕的宽度
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//设置程序的窗口大小
GLint windowWidth = 800;
GLint windowHeight = 600;
//绕x轴旋转角度
GLfloat xRotAngle = 0.0f;
//绕y轴旋转角度
GLfloat yRotAngle = 0.0f;
//受支持的点大小范围
GLfloat sizes[2];
//受支持的点大小增量
GLfloat step;

GLint iModel = TEAPOT;
bool bManual = true;
bool notquit = true;

void change_model(CcgProjectDlg* phandle, GLint model, bool manual)
{
	handle = phandle;
	iModel = model;
	bManual = manual;
	xRotAngle = 0.0f;
	yRotAngle = 0.0f;
	notquit = true;
}

//显示回调函数
void renderScreen(void) {
	//将窗口颜色清理为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//将模板缓冲区值全部清理为1
	glClearStencil(1);
	//使能模板缓冲区
	glEnable(GL_STENCIL_TEST);
	//把整个窗口清理为当前清理颜色：黑色。清除深度缓冲区、模板缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//将当前Matrix状态入栈
	glPushMatrix();
	//坐标系绕x轴旋转xRotAngle
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//坐标系绕y轴旋转yRotAngle
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//进行平滑处理　
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	if (iModel == TEAPOT)
	{
		//白色绘制坐标系
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-3.0f, 0.0f, 0.0f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -3.0f, 0.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -3.0f);
		glVertex3f(0.0f, 0.0f, 3.0f);
		glEnd();

		glPushMatrix();
		glTranslatef(3.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(0.1, 0.2, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 3.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.1, 0.2, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 3.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCone(0.1, 0.2, 10, 10);
		glPopMatrix();
	}
	else
	{
		//白色绘制坐标系
		glColor3f(1.0f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);

		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);//使材质色跟踪当前颜色

		glBegin(GL_LINES);
		glVertex3f(-500.0f, 0.0f, 0.0f);
		glVertex3f(500.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -500.0f, 0.0f);
		glVertex3f(0.0f, 500.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -500.0f);
		glVertex3f(0.0f, 0.0f, 500.0f);
		glEnd();

		glPushMatrix();
		glTranslatef(500.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(10, 20, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 500.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(10, 20, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 500.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCone(10, 20, 10, 10);
		glPopMatrix();
	}

	//设置绘画颜色为绿色
	glColor3f(0.0f, 1.0f, 0.0f);
	switch (iModel) 
	{
		//茶壶
	case TEAPOT:
		DrawTeapot();
		break;
	case TEXT:
		/*为光照模型指定材质参数*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);//使材质色跟踪当前颜色
		glColor3f(0.0f, 1.0f, 0.0f);
		DrawText3D();
		break;
	case TEXTURE:
		DrawText3DTexture();
		break;
	default:
		break;
	}
	//恢复压入栈的Matrix
	glPopMatrix();
	//交换两个缓冲区的指针
	glutSwapBuffers();
}
//设置Redering State 
void setupRederingState(void) {
	//设置清理颜色为黑色
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	if (iModel != TEAPOT)
	{
		//开启光照
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
	}
	//设置绘画颜色为绿色
	glColor3f(0.0f, 1.0f, 0.0f);
	//使能深度测试
	glEnable(GL_DEPTH_TEST);
	//2D纹理
	if (iModel == TEXTURE)
	{
		glEnable(GL_TEXTURE_2D);
		texKing = load_texture("texture.bmp");
	}
	//获取受支持的点大小范围
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//获取受支持的点大小增量
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
}

//窗口大小变化回调函数
void changSize(GLint w, GLint h) {
	//横宽比率
	GLfloat ratio, coordinatesize;
	//设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
	if (iModel == TEAPOT)
		coordinatesize = 4.0f;
	else
		coordinatesize = 800.0f;
	//窗口宽高为零直接返回
	if ((w == 0) || (h == 0))
		return;
	//设置视口和窗口大小一致
	glViewport(0, 0, w, h);
	//对投影矩阵应用随后的矩阵操作
	glMatrixMode(GL_PROJECTION);
	//重置当前指定的矩阵为单位矩阵　
	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;
	//正交投影
	if (w<h)
		glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
	else
		glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
	//对模型视图矩阵堆栈应用随后的矩阵操作
	glMatrixMode(GL_MODELVIEW);
	//重置当前指定的矩阵为单位矩阵　
	glLoadIdentity();
}

//按键输入处理回调函数
void specialKey(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		xRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_DOWN) {
		xRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_LEFT) {
		yRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT) {
		yRotAngle += 5.0f;
	}
	//重新绘制
	glutPostRedisplay();
}
void OnTimer(int value)
{
	if (notquit)
	{
		xRotAngle += 2.5f;
		yRotAngle += 1.5f;
		glutPostRedisplay();
		glutTimerFunc(50, OnTimer, 1);
	}
}
void OnClose()
{
	notquit = false;
	Sleep(100);
}
void plot3d()
{
	int argc = 0;
	//初始化glut 
	glutInit(&argc, NULL);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//使用双缓冲区、深度缓冲区、模板缓冲区
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//获取系统的宽像素
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	//获取系统的高像素
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	glutCreateWindow("3D Display");
	//设置窗口大小
	glutReshapeWindow(windowWidth, windowHeight);
	//窗口居中显示
	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//窗口大小变化时的处理函数
	glutReshapeFunc(changSize);
	//设置显示回调函数 
	glutDisplayFunc(renderScreen);
	if (bManual)
	{
		//设置按键输入处理回调函数
		glutSpecialFunc(specialKey);
	}
	else
	{
		glutTimerFunc(50, OnTimer, 1);
		glutCloseFunc(OnClose);
	}

	//设置全局渲染参数
	setupRederingState();
	glutMainLoop();
}

double CalcCoeff(int nn, int k)
{
	int i;
	double sum = 1;
	for (i = 1; i <= k; i++)
		sum = sum * (nn - i + 1) / i;
	return sum;
}

//计算Bezier曲线上点的坐标
Point3 CalcBezierPoint(float points[][2], double t, int n)
{
	double Ber;
	int k;
	Point3 p;
	for (k = 0;k < n;k++)
	{
		Ber = CalcCoeff(n - 1, k)*pow(t, k)*pow(1 - t, n - 1 - k);
		p.x += points[k][0] * Ber;
		p.y += points[k][1] * Ber;
	}
	return p;
}
Point3 CalcBezierPoint(float points[][3], double t, int n)
{
	double Ber;
	int k;
	Point3 p;
	for (k = 0;k < n;k++)
	{
		Ber = CalcCoeff(n - 1, k)*pow(t, k)*pow(1 - t, n - 1 - k);
		p.x += points[k][0] * Ber;
		p.y += points[k][1] * Ber;
		p.z += points[k][2] * Ber;
	}
	return p;
}

//根据n个控制点，求曲线上的m+1个点
void CalcBezierCurve(float points[][2], int n, int m, Point3 *v)
{
	int i;
	for (i = 0;i <= m;i++)
		v[i] = CalcBezierPoint(points, (double)i / (double)m, n);
}
void CalcBezierCurve(float points[][3], int n, int m, Point3 *v)
{
	int i;
	for (i = 0;i <= m;i++)
		v[i] = CalcBezierPoint(points, (double)i / (double)m, n);
}

/* 函数power_of_two
* 检查一个整数是否为2的整数次方，如果是，返回1，否则返回0
* 实际上只要查看其二进制位中有多少个，如果正好有1个，返回1，否则返回0
* 在“查看其二进制位中有多少个”时使用了一个小技巧
* 使用n &= (n-1)可以使得n中的减少一个（具体原理大家可以自己思考）
*/
bool power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 在旧版本的OpenGL中
	// 如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
	// 另外，无论是旧版本还是新版本，
	// 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	// 之前为pixels分配的内存可在使用glTexImage2D以后释放
	// 因为此时像素数据已经被OpenGL另行保存了一份（可能被保存到专门的图形硬件中）
	free(pixels);
	return texture_ID;
}
