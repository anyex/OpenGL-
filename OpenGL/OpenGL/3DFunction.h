#pragma once
#include "windows.h"
#include "gl/GL.H"
#include "gl/GLAUX.H"
#include "gl/GLUT.H"

void SetupMatrices(int w, int h);
void InitOpenGL();
void Render();
void DrawCube(float xPos, float yPos, float zPos);
void DrawArm(float xPos, float yPos, float zPos);
void RenderRobert(float xPos, float yPos, float zPos);
void DrawLeg(float xPos, float yPos, float zPos);
void DrawTorso(float xPos, float yPos, float zPos);
void DrawHead(float xPos, float yPos, float zPos);