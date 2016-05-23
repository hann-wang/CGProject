#include "stdafx.h"
#include "Plot3D.h"
#include "teapot.h"

float bodyctrl[10][2] = { { 1.4000,2.25000 },{ 1.3375,2.38125 },{ 1.4375,2.38125 },{ 1.5000,2.25000 },{ 1.7500,1.72500 },{ 2.0000,1.20000 },{ 2.0000,0.75000 },{ 2.0000,0.30000 },{ 1.5000,0.07500 },{ 1.5000,0.00000 } };
float lidctrl[7][2] = { { 0.0000,3.0000 },{ 0.8000,3.0000 },{ 0.0000,2.7000 },{ 0.2000,2.5500 },{ 0.4000,2.4000 },{ 1.3000,2.4000 },{ 1.3000,2.2500 } };
float handlectrl[14][2] = { { -1.6,1.875 },{ -2.3,1.875 },{ -2.7,1.875 },{ -2.7,1.65 },{ -2.7,1.425 },{ -2.5,0.975 },{ -2,0.75 },{ -1.5,2.1 },{ -2.5,2.1 },{ -3,2.1 },{ -3,1.65 },{ -3,1.2 },{ -2.65,0.7875 },{ -1.9,0.45 } };
float spoutctrl[14][3] = { { 1.7,1.275,0.66 },{ 2.6,1.275,0.66 },{ 2.3,1.95,0.25 },{ 2.7,2.25,0.25 },{ 2.8,2.325,0.25 },{ 2.9,2.325,0.15 },{ 2.8,2.25,0.15 },{ 1.7,0.45,0.66 },{ 3.1,0.675,0.66 },{ 2.4,1.875,0.25 },{ 3.3,2.25,0.25 },{ 3.525,2.34375,0.25 },{ 3.45,2.3625,0.15 },{ 3.2,2.25,0.15 } };

void DrawBody()
{
	int angle, m, i;
	Point3 *v;

	m = 5;
	v = new Point3[m + 1];
	CalcBezierCurve(&bodyctrl[0], 4, m, v);
	for (angle = 0;angle < 360;angle += 5)
	{
		for (i = 0; i < m; i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(v[i].x * cos(angle * PI / 180), v[i].y, v[i].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos(angle * PI / 180), v[i + 1].y, v[i + 1].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos((angle + 5) *PI / 180), v[i + 1].y, v[i + 1].x * sin((angle + 5) * PI / 180));
			glVertex3f(v[i].x * cos((angle + 5) *PI / 180), v[i].y, v[i].x * sin((angle + 5) * PI / 180));
			glEnd();
		}
	}
	delete[]v;

	m = 8;
	v = new Point3[m + 1];
	CalcBezierCurve(&bodyctrl[3], 4, m, v);
	for (angle = 0;angle < 360;angle += 5)
	{
		for (i = 0; i < m; i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(v[i].x * cos(angle * PI / 180), v[i].y, v[i].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos(angle * PI / 180), v[i + 1].y, v[i + 1].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos((angle + 5) *PI / 180), v[i + 1].y, v[i + 1].x * sin((angle + 5) * PI / 180));
			glVertex3f(v[i].x * cos((angle + 5) *PI / 180), v[i].y, v[i].x * sin((angle + 5) * PI / 180));
			glEnd();
		}
	}
	delete[]v;

	m = 5;
	v = new Point3[m + 1];
	CalcBezierCurve(&bodyctrl[6], 4, m, v);
	for (angle = 0;angle < 360;angle += 5)
	{
		for (i = 0; i < m; i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(v[i].x * cos(angle * PI / 180), v[i].y, v[i].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos(angle * PI / 180), v[i + 1].y, v[i + 1].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos((angle + 5) *PI / 180), v[i + 1].y, v[i + 1].x * sin((angle + 5) * PI / 180));
			glVertex3f(v[i].x * cos((angle + 5) *PI / 180), v[i].y, v[i].x * sin((angle + 5) * PI / 180));
			glEnd();
		}
	}
	delete[]v;
}

void DrawLid()
{
	int angle, m, i;
	Point3 *v;

	m = 8;
	v = new Point3[m + 1];
	CalcBezierCurve(lidctrl, 7, m, v);
	for (angle = 0;angle < 360;angle += 5)
	{
		for (i = 0; i < m; i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(v[i].x * cos(angle * PI / 180), v[i].y, v[i].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos(angle * PI / 180), v[i + 1].y, v[i + 1].x * sin(angle * PI / 180));
			glVertex3f(v[i + 1].x * cos((angle + 5) *PI / 180), v[i + 1].y, v[i + 1].x * sin((angle + 5) * PI / 180));
			glVertex3f(v[i].x * cos((angle + 5) *PI / 180), v[i].y, v[i].x * sin((angle + 5) * PI / 180));
			glEnd();
		}
	}
	delete[]v;
}

void DrawHandle()
{
	int m0 = 12, m = 8, i, j;
	Point3 *inner, *outer, *v1 = NULL, *v2;
	float horizonctrl[4][3];

	//上半部分
	inner = new Point3[m0 + 1];
	CalcBezierCurve(&handlectrl[0], 4, m0, inner);
	outer = new Point3[m0 + 1];
	CalcBezierCurve(&handlectrl[7], 4, m0, outer);
	
	for (i = 0; i < m0; i++)
	{
		//z=0平面纵向线条
		glBegin(GL_LINES);
		glVertex3f(inner[i].x, inner[i].y, 0.0f);
		glVertex3f(inner[i + 1].x, inner[i + 1].y, 0.0f);
		glVertex3f(outer[i].x, outer[i].y, 0.0f);
		glVertex3f(outer[i + 1].x, outer[i + 1].y, 0.0f);
		glEnd();
		
		//横向线条
		if (v1 == NULL)
		{
			horizonctrl[0][0] = inner[i].x; horizonctrl[0][1] = inner[i].y; horizonctrl[0][2] = 0.0f;
			horizonctrl[1][0] = inner[i].x; horizonctrl[1][1] = inner[i].y; horizonctrl[1][2] = 0.3f;
			horizonctrl[2][0] = outer[i].x; horizonctrl[2][1] = outer[i].y; horizonctrl[2][2] = 0.3f;
			horizonctrl[3][0] = outer[i].x; horizonctrl[3][1] = outer[i].y; horizonctrl[3][2] = 0.0f;
			v1 = new Point3[m + 1];
			CalcBezierCurve(horizonctrl, 4, m, v1);
			for (j = 0; j < m; j++)
			{
				glBegin(GL_LINES);
				glVertex3f(v1[j].x, v1[j].y, v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
				//z<0对称
				glVertex3f(v1[j].x, v1[j].y, -v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
				glEnd();
			}
		}

		horizonctrl[0][0] = inner[i + 1].x; horizonctrl[0][1] = inner[i + 1].y; horizonctrl[0][2] = 0.0f;
		horizonctrl[1][0] = inner[i + 1].x; horizonctrl[1][1] = inner[i + 1].y; horizonctrl[1][2] = 0.3f;
		horizonctrl[2][0] = outer[i + 1].x; horizonctrl[2][1] = outer[i + 1].y; horizonctrl[2][2] = 0.3f;
		horizonctrl[3][0] = outer[i + 1].x; horizonctrl[3][1] = outer[i + 1].y; horizonctrl[3][2] = 0.0f;
		v2 = new Point3[m + 1];
		CalcBezierCurve(horizonctrl, 4, m, v2);
		for (j = 0; j < m; j++)
		{
			glBegin(GL_LINES);
			glVertex3f(v2[j].x, v2[j].y, v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			//横向线条之间的纵向连接线
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
			//z<0对称
			glVertex3f(v2[j].x, v2[j].y, -v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
			glEnd();
		}
		delete[]v1;
		v1 = v2;
	}
	delete[]v1;
	delete[]inner;
	delete[]outer;

	//下半部分
	v1 = NULL;
	inner = new Point3[m0 + 1];
	CalcBezierCurve(&handlectrl[3], 4, m0, inner);
	outer = new Point3[m0 + 1];
	CalcBezierCurve(&handlectrl[10], 4, m0, outer);

	for (i = 0; i < m0; i++)
	{
		//z=0平面纵向线条
		glBegin(GL_LINES);
		glVertex3f(inner[i].x, inner[i].y, 0.0f);
		glVertex3f(inner[i + 1].x, inner[i + 1].y, 0.0f);
		glVertex3f(outer[i].x, outer[i].y, 0.0f);
		glVertex3f(outer[i + 1].x, outer[i + 1].y, 0.0f);
		glEnd();

		//横向线条
		if (v1 == NULL)
		{
			horizonctrl[0][0] = inner[i].x; horizonctrl[0][1] = inner[i].y; horizonctrl[0][2] = 0.0f;
			horizonctrl[1][0] = inner[i].x; horizonctrl[1][1] = inner[i].y; horizonctrl[1][2] = 0.3f;
			horizonctrl[2][0] = outer[i].x; horizonctrl[2][1] = outer[i].y; horizonctrl[2][2] = 0.3f;
			horizonctrl[3][0] = outer[i].x; horizonctrl[3][1] = outer[i].y; horizonctrl[3][2] = 0.0f;
			v1 = new Point3[m + 1];
			CalcBezierCurve(horizonctrl, 4, m, v1);
			for (j = 0; j < m; j++)
			{
				glBegin(GL_LINES);
				glVertex3f(v1[j].x, v1[j].y, v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
				//z<0对称
				glVertex3f(v1[j].x, v1[j].y, -v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
				glEnd();
			}
		}

		horizonctrl[0][0] = inner[i + 1].x; horizonctrl[0][1] = inner[i + 1].y; horizonctrl[0][2] = 0.0f;
		horizonctrl[1][0] = inner[i + 1].x; horizonctrl[1][1] = inner[i + 1].y; horizonctrl[1][2] = 0.3f;
		horizonctrl[2][0] = outer[i + 1].x; horizonctrl[2][1] = outer[i + 1].y; horizonctrl[2][2] = 0.3f;
		horizonctrl[3][0] = outer[i + 1].x; horizonctrl[3][1] = outer[i + 1].y; horizonctrl[3][2] = 0.0f;
		v2 = new Point3[m + 1];
		CalcBezierCurve(horizonctrl, 4, m, v2);
		for (j = 0; j < m; j++)
		{
			glBegin(GL_LINES);
			glVertex3f(v2[j].x, v2[j].y, v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			//横向线条之间的纵向连接线
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
			//z<0对称
			glVertex3f(v2[j].x, v2[j].y, -v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
			glEnd();
		}
		delete[]v1;
		v1 = v2;
	}
	delete[]v1;
	delete[]inner;
	delete[]outer;
}


void DrawSpout()
{
	int m0 = 15, m, i, j;
	Point3 *inner, *outer, *v1 = NULL, *v2;
	float horizonctrl[4][3];

	//主体部分
	inner = new Point3[m0 + 1];
	CalcBezierCurve(&spoutctrl[0], 4, m0, inner);
	outer = new Point3[m0 + 1];
	CalcBezierCurve(&spoutctrl[7], 4, m0, outer);

	m = 10;
	for (i = 0; i < m0; i++)
	{
		//横向线条
		if (v1 == NULL)
		{
			horizonctrl[0][0] = inner[i].x; horizonctrl[0][1] = inner[i].y; horizonctrl[0][2] = 0.0f;
			horizonctrl[1][0] = inner[i].x; horizonctrl[1][1] = inner[i].y; horizonctrl[1][2] = inner[i].z;
			horizonctrl[2][0] = outer[i].x; horizonctrl[2][1] = outer[i].y; horizonctrl[2][2] = outer[i].z;
			horizonctrl[3][0] = outer[i].x; horizonctrl[3][1] = outer[i].y; horizonctrl[3][2] = 0.0f;
			v1 = new Point3[m + 1];
			CalcBezierCurve(horizonctrl, 4, m, v1);
			for (j = 0; j < m; j++)
			{
				glBegin(GL_LINES);
				glVertex3f(v1[j].x, v1[j].y, v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
				//z<0对称
				glVertex3f(v1[j].x, v1[j].y, -v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
				glEnd();
			}
		}

		horizonctrl[0][0] = inner[i + 1].x; horizonctrl[0][1] = inner[i + 1].y; horizonctrl[0][2] = 0.0f;
		horizonctrl[1][0] = inner[i + 1].x; horizonctrl[1][1] = inner[i + 1].y; horizonctrl[1][2] = inner[i + 1].z;
		horizonctrl[2][0] = outer[i + 1].x; horizonctrl[2][1] = outer[i + 1].y; horizonctrl[2][2] = outer[i + 1].z;
		horizonctrl[3][0] = outer[i + 1].x; horizonctrl[3][1] = outer[i + 1].y; horizonctrl[3][2] = 0.0f;
		v2 = new Point3[m + 1];
		CalcBezierCurve(horizonctrl, 4, m, v2);
		for (j = 0; j < m; j++)
		{
			glBegin(GL_LINES);
			glVertex3f(v2[j].x, v2[j].y, v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			//横向线条之间的纵向连接线
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
			//z<0对称
			glVertex3f(v2[j].x, v2[j].y, -v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
			glEnd();
		}
		delete[]v1;
		v1 = v2;
	}
	delete[]v1;
	delete[]inner;
	delete[]outer;

	//壶口部分
	inner = new Point3[m0 + 1];
	CalcBezierCurve(&spoutctrl[3], 4, m0, inner);
	outer = new Point3[m0 + 1];
	CalcBezierCurve(&spoutctrl[10], 4, m0, outer);

	v1 = NULL;
	for (i = 0; i < m0; i++)
	{
		//横向线条
		if (v1 == NULL)
		{
			horizonctrl[0][0] = inner[i].x; horizonctrl[0][1] = inner[i].y; horizonctrl[0][2] = 0.0f;
			horizonctrl[1][0] = inner[i].x; horizonctrl[1][1] = inner[i].y; horizonctrl[1][2] = inner[i].z;
			horizonctrl[2][0] = outer[i].x; horizonctrl[2][1] = outer[i].y; horizonctrl[2][2] = outer[i].z;
			horizonctrl[3][0] = outer[i].x; horizonctrl[3][1] = outer[i].y; horizonctrl[3][2] = 0.0f;
			v1 = new Point3[m + 1];
			CalcBezierCurve(horizonctrl, 4, m, v1);
			for (j = 0; j < m; j++)
			{
				glBegin(GL_LINES);
				glVertex3f(v1[j].x, v1[j].y, v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
				//z<0对称
				glVertex3f(v1[j].x, v1[j].y, -v1[j].z);
				glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
				glEnd();
			}
		}

		horizonctrl[0][0] = inner[i + 1].x; horizonctrl[0][1] = inner[i + 1].y; horizonctrl[0][2] = 0.0f;
		horizonctrl[1][0] = inner[i + 1].x; horizonctrl[1][1] = inner[i + 1].y; horizonctrl[1][2] = inner[i + 1].z;
		horizonctrl[2][0] = outer[i + 1].x; horizonctrl[2][1] = outer[i + 1].y; horizonctrl[2][2] = outer[i + 1].z;
		horizonctrl[3][0] = outer[i + 1].x; horizonctrl[3][1] = outer[i + 1].y; horizonctrl[3][2] = 0.0f;
		v2 = new Point3[m + 1];
		CalcBezierCurve(horizonctrl, 4, m, v2);
		for (j = 0; j < m; j++)
		{
			glBegin(GL_LINES);
			glVertex3f(v2[j].x, v2[j].y, v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			//横向线条之间的纵向连接线
			glVertex3f(v2[j + 1].x, v2[j + 1].y, v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, v1[j + 1].z);
			//z<0对称
			glVertex3f(v2[j].x, v2[j].y, -v2[j].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v2[j + 1].x, v2[j + 1].y, -v2[j + 1].z);
			glVertex3f(v1[j + 1].x, v1[j + 1].y, -v1[j + 1].z);
			glEnd();
		}
		delete[]v1;
		v1 = v2;
	}
	delete[]v1;
	delete[]inner;
	delete[]outer;
}

void DrawTeapot()
{
	DrawBody();
	DrawLid();
	DrawHandle();
	DrawSpout();
}

