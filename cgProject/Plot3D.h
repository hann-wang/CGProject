#pragma once
#include <gl/freeglut.h>
#include <math.h>
#include "cgProjectDlg.h"

//‘≤÷‹¬ ∫Í
#define GL_PI 3.1415f

struct Point3
{
	float x, y, z;
	Point3() :x(0.0f), y(0.0f), z(0.0f) {}
	Point3(float x, float y, float z) :x(x), y(y), z(z) {}
};

enum MODELS {
	TEAPOT = 0,
	TEXT,
	TEXTURE
};

void plot3d();
void change_model(CcgProjectDlg* phandle, GLint model = TEAPOT, bool manual = true);

void CalcBezierCurve(float points[][3], int n, int m, Point3 *v);
void CalcBezierCurve(float points[][2], int n, int m, Point3 *v);

bool power_of_two(int n);
GLuint load_texture(const char* file_name);
