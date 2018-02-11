#include "3DFunction.h"


float move_s = 0.0f;
float route_angle = 0;
float armAngle[2] = { 0 };
float legAngle[2] = { 0 };
float angle = 0;
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
	gluLookAt(0.0f, .0f, 2.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 3.0f);//改变观察变换，这里将会得到一个倒立的图像

	
	/*glPushMatrix();//使用矩阵堆栈就只对下面的一个点进行了平移
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

		glEnd();*/
		
	//绘制机器人
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -30.f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	RenderRobert(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	angle = angle + 0.05f;

	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}
}

//画一个机器人
void RenderRobert(float xPos,float yPos,float zPos)
{
	static bool leg1 = true;
	static bool leg2 = false;

	static bool arm1 = true;
	static bool arm2 = false;

	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		DrawHead(1.0f, 2.0f, 0.0f);
		DrawTorso(1.5f, 0.0f, 0.0f);
	glPushMatrix();
		if (arm1)
		
			armAngle[0] = armAngle[0] + 0.1f;
		else
			armAngle[0] = armAngle[0] - 0.1f;

		//如果胳膊达到其最大的角度则改变其状态
		if (armAngle[0]>=15.0f)
		{
			arm1 = false;
		}
		if (armAngle[0]<=-15.0f)
		{
			arm1 = true;
		}

		//平移并旋转后绘制胳膊
		glTranslatef(0.0f, -0.5f, 0.0f);
		glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);
		DrawArm(2.5f, 0.0f, -0.5f);
	glPopMatrix();
		

	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	DrawHead(1.0f, 2.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);
	glPushMatrix();
	if (arm2)

		armAngle[1] = armAngle[1] + 0.1f;
	else
		armAngle[1] = armAngle[1] - 0.1f;

	//如果胳膊达到其最大的角度则改变其状态
	if (armAngle[1] >= 15.0f)
	{
		arm2 = false;
	}
	if (armAngle[1] <= -15.0f)
	{
		arm2 = true;
	}

	//平移并旋转后绘制胳膊
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);
	DrawArm(-1.5f, 0.0f, -0.5f);
	glPopMatrix();

	//绘制腿部

	glPushMatrix();
	if (leg1)
	{
		legAngle[0] = legAngle[0] + 0.1f;
	}
	else
		legAngle[0] = legAngle[0] - 0.1f;

	if (legAngle[0]>=15.0f)
	{
		leg1 = false;
	}
	if (legAngle[0]<=-15.0f)
	{
		leg1 = true;
	}

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);
	DrawLeg(-0.5f, -0.5f, -0.5f);

	glPopMatrix();

	glPushMatrix();
	if (leg2)
	{
		legAngle[1] = legAngle[1] + 0.1f;
	}
	else
		legAngle[1] = legAngle[1] - 0.1f;

	if (legAngle[1]>=15.0f)
	{
		leg2 = false;
	}
	
	if (legAngle[1]<=-15.0f)
	{
		leg2 = true;
	}

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);
	DrawLeg(1.5f, -5.0f, -0.5f);

	glPopMatrix();



}
//绘制立方体
void DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	glBegin(GL_POLYGON);
	//顶面
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	//前面
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	//右面
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	//左面
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	//底面
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	//后面
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);

	

	glEnd();


}

void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);
		DrawCube(0.0f, 0.0f, 0.f);
	glPushMatrix();
}

void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPushMatrix();
}

void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 5.0f, 1.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}


