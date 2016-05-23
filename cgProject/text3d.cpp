#include "stdafx.h"
#include <math.h>
#include "text3d.h"

extern CcgProjectDlg *handle;
//纹理编号
extern GLuint texKing;

Point3 CalcNormal(Point3 &a, Point3 &b)
{
	Point3 n(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.z);
	return n;
}


void DrawText3D()
{
	const float depth = 40.0f;
	Point3 a, b, c, d(0.0f, 0.0f, 1.0f), n;
	int i, j;
	//前面
	for (i = 0;i < handle->edgecnt;++i)
	{
		glBegin(GL_LINE_LOOP);
		glNormal3f(0.0f, 0.0f, -1.0f);
		for (j = 1;j <= handle->edges[i][0][0];++j)
		{
			glVertex3f(3 * handle->edges[i][j][0], 3 * handle->edges[i][j][1], 0);
		}
		glEnd();
	}

	//后面
	for (i = 0;i < handle->edgecnt;++i)
	{
		glBegin(GL_LINE_LOOP);
		glNormal3f(0.0f, 0.0f, 1.0f);
		for (j = 1;j <= handle->edges[i][0][0];++j)
		{
			glVertex3f(3 * handle->edges[i][j][0], 3 * handle->edges[i][j][1], depth);
		}
		glEnd();
	}

	//侧面
	for (i = 0;i < handle->edgecnt;++i)
	{
		glBegin(GL_QUAD_STRIP);
		a = Point3(3 * handle->edges[i][1][0], 3 * handle->edges[i][1][1], 0);
		glVertex3f(a.x, a.y, 0);
		glVertex3f(a.x, a.y, depth);
		for (j = 2;j <= handle->edges[i][0][0];++j)
		{
			b = Point3(3 * handle->edges[i][j][0], 3 * handle->edges[i][j][1], 0);
			c = Point3(a.x - b.x, a.y - b.y, 0);
			n = CalcNormal(c, d);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(b.x, b.y, 0);
			glVertex3f(b.x, b.y, depth);
			a = b;
		}
		b = Point3(3 * handle->edges[i][1][0], 3 * handle->edges[i][1][1], 0);
		c = Point3(a.x - b.x, a.y - b.y, 0);
		n = CalcNormal(c, d);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(b.x, b.y, 0);
		glVertex3f(b.x, b.y, depth);
		glEnd();
	}

}


void DrawText3DTexture()
{
	const float depth = 200.0f;
	Point3 a, b, c, d(0.0f, 0.0f, 1.0f), n;
	int i, j;
	float k = 0.0f;
	//前面
	for (i = 0;i < handle->edgecnt;++i)
	{
		glBegin(GL_LINE_LOOP);
		glNormal3f(0.0f, 0.0f, -1.0f);
		for (j = 1;j <= handle->edges[i][0][0];++j)
		{
			glVertex3f(3 * handle->edges[i][j][0], 3 * handle->edges[i][j][1], 0);
		}
		glEnd();
	}

	//后面
	for (i = 0;i < handle->edgecnt;++i)
	{
		glBegin(GL_LINE_LOOP);
		glNormal3f(0.0f, 0.0f, 1.0f);
		for (j = 1;j <= handle->edges[i][0][0];++j)
		{
			glVertex3f(3 * handle->edges[i][j][0], 3 * handle->edges[i][j][1], depth);
		}
		glEnd();
	}

	//侧面
	glBindTexture(GL_TEXTURE_2D, texKing);
	for (i = 0;i < handle->edgecnt;++i)
	{
		k = 0.0f;
		glBegin(GL_QUAD_STRIP);
		a = Point3(3 * handle->edges[i][1][0], 3 * handle->edges[i][1][1], 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(a.x, a.y, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(a.x, a.y, depth);
		for (j = 2;j <= handle->edges[i][0][0];++j)
		{
			
			b = Point3(3 * handle->edges[i][j][0], 3 * handle->edges[i][j][1], 0);

			k += sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y)) / 200;

			glTexCoord2f(0.0f, k);
			glVertex3f(b.x, b.y, 0);
			glTexCoord2f(1.0f, k);
			glVertex3f(b.x, b.y, depth);
			a = b;
		}
		b = Point3(3 * handle->edges[i][1][0], 3 * handle->edges[i][1][1], 0);

		k += sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y)) / 200;

		glTexCoord2f(0.0f, k);
		glVertex3f(b.x, b.y, 0);
		glTexCoord2f(1.0f, k);
		glVertex3f(b.x, b.y, depth);
		glEnd();
	}

}
