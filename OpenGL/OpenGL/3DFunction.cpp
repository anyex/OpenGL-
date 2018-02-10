#include "3DFunction.h"
float move_s = 0.0f;
float route_angle = 0;
void SetupMatrices(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除当前缓冲区的值

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 2.0f,
		0.0f, -0.0f, 1.0f,
		0.0f, -1.0f, 0.0f);//改变观察变换，这里将会得到一个倒立的图像

	
	glPushMatrix();//使用矩阵堆栈就只对下面的一个点进行了平移
	//glTranslatef(0.5f, 0, 0);
	//绘制点
	glPointSize(15.0f);//设置点的大小
	glBegin(GL_POINTS);//打开要绘制点的功能
	glColor3f(1.0f, 0.0f, 0.0f);//设定颜色
	glVertex3f(0.0f, 1.0f, -5.0f);//设置点的位置
	
	glEnd();//绘制点结束
	glPopMatrix();
	if (!glIsEnabled(GL_POINT_SMOOTH))//检测是否打开抗锯齿性能
	
		glEnable(GL_POINT_SMOOTH);

		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f,1.0f,-5.0f);

		glEnd();
	
	//绘制线
		if (!glIsEnabled(GL_LINE_SMOOTH))
		{
			glEnable(GL_LINE_SMOOTH);//开启抗锯齿
		}

		glLineWidth(16.0f);//设置线宽
		glBegin(GL_LINES);//开启线宽

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(2.0f, 1.5f, -5.0f);
		glVertex3f(-1.0f, 1.5f, -5.0f);

		glEnd();

	//画虚线
		glEnable(GL_LINE_STIPPLE);
		int stipplePattern = 0xAAAA;
		glLineStipple(10, stipplePattern);

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-6.0f+ move_s, -1.5f, -5.0f);//动态平移虚线
		glVertex3f(-4.0f+ move_s, -1.5f, -5.0f);
		glEnd();
		glDisable(GL_LINE_STIPPLE);


		//绘制三角形

		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(route_angle, 0.0f, 0.0f, 1.0f);//旋转三角形
		if (!glIsEnabled(GL_POLYGON_SMOOTH))
		{
			glEnable(GL_POLYGON_SMOOTH);
		}
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);

		glEnd();
		move_s += 0.04f;
		route_angle += 0.1f;
		if (move_s >=8)
		{
			move_s = 0;
		}
}
