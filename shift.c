/*
 * Filename: shift.c
 * Owner: Sean Callahan
 * Description: Display an animated replica of the Shift Pale Lager logo
 * Credits: Used some of Vlakkies code for a few various things.
 */

#include "CSCIx229.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


double PI = 3.1415926535897932384626433832795;

// Variables
int th = 0;       //  Azimuth of view angle
int ph = -15;       //  Elevation of view angle
int proj = 1;
int fov = 60;
double asp = 1;
double dim=4.0;

double ambient = 0.19225;
double specular = 0.508273;
double diffuse = 0.50754;
double shine = 0.4;

int win = 0;

// Models
int gear2Int;
int gear3Int;
int gear4Int;
int gear5Int;
// Chain models
int displayChain[4];
int chain;
int chain2;
int chain3;
int chain4;

double dt;
double t;
float chainMove = 0.0;

int ch = 1;



// Textures
unsigned int newBelgTex;

// Gear variables
static float angle = 0.0;


// My Color Vectors
double signBlue[3] = {26.0/255.0, 37.0/255.0, 116.0/255.0};
double signSilver[3] = {178.0/255.0, 184.0/255.0, 196.0/255.0};

// My custom objects / fuctions
//

void drawS(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glNormal3f( 0, 0, 1);
  glVertex2f(0.286, 0.7057);
  glVertex2f(0.44, 0.7057);
  glVertex2f(0.44, 0.757);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.286, 0.7057);
  glVertex2f(0.282, 0.771);
  glVertex2f(0.44, 0.757);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.433, 0.803);
  glVertex2f(0.282, 0.771);
  glVertex2f(0.44, 0.757);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.433, 0.803);
  glVertex2f(0.282, 0.771);
  glVertex2f(0.277, 0.8);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.433, 0.803);
  glVertex2f(0.423, 0.837);
  glVertex2f(0.277, 0.8);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.263, 0.829);
  glVertex2f(0.423, 0.837);
  glVertex2f(0.277, 0.8);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.263, 0.829);
  glVertex2f(0.423, 0.837);
  glVertex2f(0.409, 0.877);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.263, 0.829);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.409, 0.877);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.391, 0.911);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.409, 0.877);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.391, 0.911);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.369, 0.94);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.345, 0.96);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.369, 0.94);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.345, 0.96);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.306, 0.983);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 0.994);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.306, 0.983);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 0.994);
  glVertex2f(0.243, 0.846);
  glVertex2f(0.223, 0.851);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 0.994);
  glVertex2f(0.237, 0.997);
  glVertex2f(0.223, 0.851);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.171, 0.994);
  glVertex2f(0.237, 0.997);
  glVertex2f(0.223, 0.851);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.171, 0.994);
  glVertex2f(0.197, 0.851);
  glVertex2f(0.223, 0.851);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.171, 0.994);
  glVertex2f(0.197, 0.851);
  glVertex2f(0.126, 0.98);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.197, 0.851);
  glVertex2f(0.126, 0.98);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.094, 0.963);
  glVertex2f(0.126, 0.98);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.094, 0.963);
  glVertex2f(0.066, 0.94);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.043, 0.911);
  glVertex2f(0.066, 0.94);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.043, 0.911);
  glVertex2f(0.02, 0.874);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.009, 0.84);
  glVertex2f(0.02, 0.874);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.174, 0.837);
  glVertex2f(0.009, 0.84);
  glVertex2f(0.157, 0.814);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(-0.002, 0.794);
  glVertex2f(0.009, 0.84);
  glVertex2f(0.157, 0.814);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(-0.002, 0.794);
  glVertex2f(0.149, 0.777);
  glVertex2f(0.157, 0.814);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(-0.002, 0.794);
  glVertex2f(0.149, 0.777);
  glVertex2f(-0.006, 0.74);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.677);
  glVertex2f(0.149, 0.777);
  glVertex2f(-0.006, 0.74);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.677);
  glVertex2f(0.149, 0.777);
  glVertex2f(0.157, 0.714);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.677);
  glVertex2f(0.011, 0.629);
  glVertex2f(0.157, 0.714);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.171, 0.689);
  glVertex2f(0.011, 0.629);
  glVertex2f(0.157, 0.714);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.171, 0.689);
  glVertex2f(0.011, 0.629);
  glVertex2f(0.034, 0.58);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.171, 0.689);
  glVertex2f(0.234, 0.62);
  glVertex2f(0.034, 0.58);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.069, 0.529);
  glVertex2f(0.234, 0.62);
  glVertex2f(0.034, 0.58);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.069, 0.529);
  glVertex2f(0.234, 0.62);
  glVertex2f(0.314, 0.551);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.069, 0.529);
  glVertex2f(0.143, 0.457);
  glVertex2f(0.314, 0.551);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.359, 0.5);
  glVertex2f(0.143, 0.457);
  glVertex2f(0.314, 0.551);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.359, 0.5);
  glVertex2f(0.143, 0.457);
  glVertex2f(0.223, 0.386);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.359, 0.5);
  glVertex2f(0.406, 0.454);
  glVertex2f(0.223, 0.386);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.28, 0.334);
  glVertex2f(0.406, 0.454);
  glVertex2f(0.223, 0.386);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.28, 0.334);
  glVertex2f(0.406, 0.454);
  glVertex2f(0.429, 0.417);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.28, 0.334);
  glVertex2f(0.297, 0.303);
  glVertex2f(0.429, 0.417);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.446, 0.38);
  glVertex2f(0.297, 0.303);
  glVertex2f(0.429, 0.417);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.446, 0.38);
  glVertex2f(0.297, 0.303);
  glVertex2f(0.46, 0.331);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.297, 0.303);
  glVertex2f(0.314, 0.269);
  glVertex2f(0.46, 0.331);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.466, 0.28);
  glVertex2f(0.314, 0.269);
  glVertex2f(0.46, 0.331);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.466, 0.28);
  glVertex2f(0.311, 0.214);
  glVertex2f(0.314, 0.269);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.466, 0.28);
  glVertex2f(0.311, 0.214);
  glVertex2f(0.466, 0.24);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.46, 0.197);
  glVertex2f(0.311, 0.214);
  glVertex2f(0.466, 0.24);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.46, 0.197);
  glVertex2f(0.311, 0.214);
  glVertex2f(0.446, 0.149);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.426, 0.106);
  glVertex2f(0.311, 0.214);
  glVertex2f(0.446, 0.149);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.426, 0.106);
  glVertex2f(0.311, 0.214);
  glVertex2f(0.297, 0.186);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.426, 0.106);
  glVertex2f(0.28, 0.163);
  glVertex2f(0.297, 0.186);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.426, 0.106);
  glVertex2f(0.28, 0.163);
  glVertex2f(0.257, 0.151);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.426, 0.106);
  glVertex2f(0.389, 0.06);
  glVertex2f(0.257, 0.151);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.354, 0.034);
  glVertex2f(0.389, 0.06);
  glVertex2f(0.257, 0.151);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.354, 0.034);
  glVertex2f(0.317, 0.017);
  glVertex2f(0.257, 0.151);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.257, 0.151);
  glVertex2f(0.317, 0.017);
  glVertex2f(0.283, 0.009);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.257, 0.151);
  glVertex2f(0.249, 0.003);
  glVertex2f(0.283, 0.009);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.257, 0.151);
  glVertex2f(0.249, 0.003);
  glVertex2f(0.2, 0.003);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.257, 0.151);
  glVertex2f(0.214, 0.149);
  glVertex2f(0.2, 0.003);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.146, 0.014);
  glVertex2f(0.214, 0.149);
  glVertex2f(0.2, 0.003);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.214, 0.149);
  glVertex2f(0.106, 0.034);
  glVertex2f(0.2, 0.003);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.214, 0.149);
  glVertex2f(0.106, 0.034);
  glVertex2f(0.071, 0.063);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.214, 0.149);
  glVertex2f(0.046, 0.097);
  glVertex2f(0.071, 0.063);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.214, 0.149);
  glVertex2f(0.046, 0.097);
  glVertex2f(0.183, 0.168);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.029, 0.131);
  glVertex2f(0.046, 0.097);
  glVertex2f(0.183, 0.168);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.029, 0.131);
  glVertex2f(0.017, 0.169);
  glVertex2f(0.183, 0.168);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.009, 0.203);
  glVertex2f(0.017, 0.169);
  glVertex2f(0.183, 0.168);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.009, 0.203);
  glVertex2f(0.003, 0.246);
  glVertex2f(0.183, 0.168);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.16, 0.22);
  glVertex2f(0.003, 0.246);
  glVertex2f(0.183, 0.168);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.16, 0.22);
  glVertex2f(0.003, 0.246);
  glVertex2f(0.157, 0.246);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.157, 0.297);
  glVertex2f(0.003, 0.246);
  glVertex2f(0.157, 0.246);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.157, 0.297);
  glVertex2f(0.003, 0.297);
  glVertex2f(0.003, 0.246);
  glEnd();

  glPopMatrix();
}

void drawP(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.183, 1.0);
  glVertex2f(0.183, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.183, 1.0);
  glVertex2f(0.183, 0.841);
  glVertex2f(0.268, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 1.0);
  glVertex2f(0.183, 0.841);
  glVertex2f(0.28, 0.829);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 1.0);
  glVertex2f(0.3658, 0.975);
  glVertex2f(0.28, 0.829);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.3658, 0.975);
  glVertex2f(0.28, 0.829);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.3658, 0.975);
  glVertex2f(0.451, 0.89);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.5, 0.78);
  glVertex2f(0.451, 0.89);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.5, 0.78);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.5, 0.67);
  glVertex2f(0.5, 0.78);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.5, 0.67);
  glVertex2f(0.487, 0.57);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.292, 0.585);
  glVertex2f(0.487, 0.57);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.292, 0.585);
  glVertex2f(0.487, 0.57);
  glVertex2f(0.451, 0.487);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.292, 0.585);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.451, 0.487);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.354, 0.415);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.451, 0.487);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.354, 0.415);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.256, 0.390);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.183, 0.548);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.256, 0.390);
  glVertex2f(0.183, 0.390);
  glEnd();

  glPopMatrix();
}

void drawG(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.482, 0.647);
  glVertex2f(0.482, 0.753);
  glVertex2f(0.329, 0.753);
  glVertex2f(0.329, 0.647);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.494, 0.471);
  glVertex2f(0.282, 0.471);
  glVertex2f(0.282, 0.329);
  glVertex2f(0.494, 0.329);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.494, 0.329);
  glVertex2f(0.341, 0.329);
  glVertex2f(0.341, 0.259);
  glVertex2f(0.494, 0.259);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.494, 0.259);
  glVertex2f(0.494, 0.0);
  glVertex2f(0.424, 0.0);
  glVertex2f(0.424, 0.259);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.329, 0.753);
  glVertex2f(0.482, 0.753);
  glVertex2f(0.318, 0.811);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.471, 0.859);
  glVertex2f(0.482, 0.753);
  glVertex2f(0.318, 0.811);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.471, 0.859);
  glVertex2f(0.282, 0.859);
  glVertex2f(0.318, 0.811);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.471, 0.859);
  glVertex2f(0.282, 0.859);
  glVertex2f(0.424, 0.941);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.365, 0.988);
  glVertex2f(0.282, 0.859);
  glVertex2f(0.424, 0.941);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.365, 0.988);
  glVertex2f(0.282, 0.859);
  glVertex2f(0.306, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.212, 1.0);
  glVertex2f(0.282, 0.859);
  glVertex2f(0.306, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.212, 1.0);
  glVertex2f(0.282, 0.859);
  glVertex2f(0.247, 0.859);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.212, 1.0);
  glVertex2f(0.141, 0.976);
  glVertex2f(0.247, 0.859);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.082, 0.918);
  glVertex2f(0.141, 0.976);
  glVertex2f(0.247, 0.859);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.082, 0.918);
  glVertex2f(0.212, 0.824);
  glVertex2f(0.247, 0.859);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.082, 0.918);
  glVertex2f(0.212, 0.824);
  glVertex2f(0.035, 0.824);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.188, 0.706);
  glVertex2f(0.212, 0.824);
  glVertex2f(0.035, 0.824);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.188, 0.706);
  glVertex2f(0.012, 0.659);
  glVertex2f(0.035, 0.824);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.188, 0.706);
  glVertex2f(0.012, 0.659);
  glVertex2f(0.188, 0.306);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.012, 0.306);
  glVertex2f(0.012, 0.659);
  glVertex2f(0.188, 0.306);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.012, 0.306);
  glVertex2f(0.047, 0.141);
  glVertex2f(0.188, 0.306);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.224, 0.176);
  glVertex2f(0.047, 0.141);
  glVertex2f(0.188, 0.306);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.224, 0.176);
  glVertex2f(0.047, 0.141);
  glVertex2f(0.129, 0.024);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.247, 0.153);
  glVertex2f(0.224, 0.176);
  glVertex2f(0.129, 0.024);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.247, 0.153);
  glVertex2f(0.212, 0.0);
  glVertex2f(0.129, 0.024);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.247, 0.153);
  glVertex2f(0.212, 0.0);
  glVertex2f(0.306, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.247, 0.153);
  glVertex2f(0.294, 0.153);
  glVertex2f(0.306, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.365, 0.047);
  glVertex2f(0.294, 0.153);
  glVertex2f(0.306, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.365, 0.047);
  glVertex2f(0.294, 0.153);
  glVertex2f(0.329, 0.212);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.365, 0.047);
  glVertex2f(0.388, 0.082);
  glVertex2f(0.329, 0.212);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.341, 0.259);
  glVertex2f(0.388, 0.082);
  glVertex2f(0.329, 0.212);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.341, 0.259);
  glVertex2f(0.388, 0.082);
  glVertex2f(0.424, 0.259);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.424, 0.0);
  glVertex2f(0.388, 0.082);
  glVertex2f(0.424, 0.259);
  glEnd();

  glPopMatrix();
}

void drawR(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.183, 1.0);
  glVertex2f(0.183, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.183, 1.0);
  glVertex2f(0.183, 0.841);
  glVertex2f(0.268, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 1.0);
  glVertex2f(0.183, 0.841);
  glVertex2f(0.28, 0.829);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.268, 1.0);
  glVertex2f(0.3658, 0.975);
  glVertex2f(0.28, 0.829);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.3658, 0.975);
  glVertex2f(0.28, 0.829);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.3658, 0.975);
  glVertex2f(0.451, 0.89);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.5, 0.78);
  glVertex2f(0.451, 0.89);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.317, 0.768);
  glVertex2f(0.5, 0.78);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.5, 0.67);
  glVertex2f(0.5, 0.78);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.5, 0.67);
  glVertex2f(0.487, 0.57);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.292, 0.585);
  glVertex2f(0.487, 0.57);
  glVertex2f(0.317, 0.671);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.292, 0.585);
  glVertex2f(0.487, 0.57);
  glVertex2f(0.451, 0.487);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.292, 0.585);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.451, 0.487);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.354, 0.415);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.451, 0.487);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.354, 0.415);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.256, 0.390);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.183, 0.548);
  glVertex2f(0.256, 0.548);
  glVertex2f(0.256, 0.390);
  glVertex2f(0.183, 0.390);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.232, 0.439);
  glVertex2f(0.317, 0.0);
  glVertex2f(0.512, 0.0);
  glVertex2f(0.39, 0.476);
  glEnd();

  glPopMatrix();
}

void drawH(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.181, 0.0);
  glVertex2f(0.181, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.18, 0.6);
  glVertex2f(0.18, 0.424);
  glVertex2f(0.2996, 0.424);
  glVertex2f(0.2996, 0.6);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.2996, 0.0);
  glVertex2f(0.4807, 0.0);
  glVertex2f(0.4807, 1.0);
  glVertex2f(0.2996, 1.0);
  glEnd();

  glPopMatrix();
}

void drawI(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.181, 0.0);
  glVertex2f(0.181, 1.0);
  glEnd();

  glPopMatrix();
}

void drawF(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.181, 0.0);
  glVertex2f(0.181, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.181, 0.418);
  glVertex2f(0.347, 0.418);
  glVertex2f(0.347, 0.578);
  glVertex2f(0.181, 0.578);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.181, 0.845);
  glVertex2f(0.392, 0.845);
  glVertex2f(0.392, 1.0);
  glVertex2f(0.181, 1.0);
  glEnd();

  glPopMatrix();
}

void drawT(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.846);
  glVertex2f(0.487, 0.846);
  glVertex2f(0.487, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.154, 0.846);
  glVertex2f(0.154, 0.0);
  glVertex2f(0.329, 0.0);
  glVertex2f(0.329, 0.846);
  glEnd();

  glPopMatrix();
}

void drawM(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.1875, 0.0);
  glVertex2f(0.1875, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.1875, 0.6875);
  glVertex2f(0.375, 0.0);
  glVertex2f(0.469, 0.4375);
  glVertex2f(0.3125, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.375, 0.0);
  glVertex2f(0.469, 0.4375);
  glVertex2f(0.5625, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.1875, 0.6875);
  glVertex2f(0.3125, 1.0);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.6875);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.469, 0.4375);
  glVertex2f(0.625, 1.0);
  glVertex2f(0.75, 0.6875);
  glVertex2f(0.5625, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.9375, 1.0);
  glVertex2f(0.9375, 0.6875);
  glVertex2f(0.75, 0.6875);
  glVertex2f(0.625, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.75, 0.0);
  glVertex2f(0.75, 1.0);
  glVertex2f(0.9375, 1.0);
  glVertex2f(0.9375, 0.0);
  glEnd();

  glPopMatrix();
}

void drawA(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.134, 1.0);
  glVertex2f(0.244, 0.829);
  glVertex2f(0.171, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.134, 1.0);
  glVertex2f(0.244, 0.829);
  glVertex2f(0.253, 0.829);
  glVertex2f(.39, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(.39, 1.0);
  glVertex2f(0.253, 0.829);
  glVertex2f(0.354, 0.0);
  glVertex2f(0.524, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.18, 0.354);
  glVertex2f(0.31, 0.354);
  glVertex2f(0.354, 0.219);
  glVertex2f(0.171, 0.219);
  glEnd();

  glPopMatrix();
}

void drawL(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.195, 0.0);
  glVertex2f(0.195, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.427, 0.0);
  glVertex2f(0.427, 0.146);
  glVertex2f(0.0, 0.146);
  glEnd();

  glPopMatrix();
}

void drawE(double x, double y, double z, double scale)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScaled(scale, scale, scale);

  glBegin(GL_POLYGON);
  glVertex2f(0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.195, 0.0);
  glVertex2f(0.195, 1.0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.195, 0.0);
  glVertex2f(0.439, 0.0);
  glVertex2f(0.439, 0.146);
  glVertex2f(0.195, 0.146);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.195, 0.415);
  glVertex2f(0.366, 0.415);
  glVertex2f(0.366, 0.5853);
  glVertex2f(0.195, 0.5853);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(0.195, 0.841);
  glVertex2f(0.427, 0.841);
  glVertex2f(0.427, 1.0);
  glVertex2f(0.195, 1.0);
  glEnd();


  glPopMatrix();
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

// Based on the implementation at http://slabode.exofire.net/circle_draw.shtml
void drawCircle(float cx, float cy, float cz, double scale,
  float r, int points, int bottom, int half, int logo)
{

  float theta;

  if (half)
  {
    theta = PI / (float)points;
  }
  else
  {
    theta = 2 * PI / (float)points;
  }

  float c = cosf(theta);//precalculate the sine and cosine
  float s = sinf(theta);
  float t;
  int i;

  float x = r;
  float y = 0;

  float tx;
  float ty;

  glPushMatrix();
  glTranslatef(cx, cy, cz);
  glScaled(scale, scale, scale);

  if(bottom == 1)
  {
    glRotatef(180.0, 0.0, 0.0, 1.0);
  }

  if (logo)
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, newBelgTex);
  }

  glBegin(GL_POLYGON);
  //glTexCoord2f(0,0);
  //glVertex2f(0,0);
  glNormal3f( 0, 0, 1);
  for(i = 0; i < points; i++)
  {
    if (logo)
    {
      tx = (x/r + 1)*0.5;
      ty = (y/r + 1)*0.5;
      glTexCoord2f(tx, ty);
    }
    glVertex2f(x, y); //output vertex

    //apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  if (!logo)
  {
    glVertex2f(-r, 0);
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}

// This function handles creating the actual sign without
// the letters or the gears.
// TODO: Make the middle of the sign have an upward curve like the real logo.
// TODO: Lighting, materials, etc.
void drawBackground()
{

  // Small top red circle
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(-1.0f, -1.0f);
  glColor3f(1.0, 1.0, 1.0);
  drawCircle(0.0, 1.8, 0.02, 2.0, 0.25, 150, 0, 0, 1);
  glDisable(GL_POLYGON_OFFSET_FILL);
  // Small top blue cicle
  glColor3dv(signBlue);
  drawCircle(0.0, 1.8, 0.02, 2.0, 0.29, 150, 0, 0, 0);

  // Top gray
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(-1.0f, -1.0f);
  glColor3dv(signSilver);
  drawCircle(0.0, 0.0, 0.0, 2.0, 1.0, 150, 0, 1, 0);
  glDisable(GL_POLYGON_OFFSET_FILL);
  // Top Blue
  glColor3dv(signBlue);
  drawCircle(0.0, 0.0, 0.0, 2.0, 1.04, 150, 0, 1, 0);

  // Bottom blue
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(-1.0f, -1.0f);
  glColor3dv(signBlue);
  drawCircle(0.0, 0.0, 0.0, 2.0, 1.0, 150, 1, 1, 0);
  glDisable(GL_POLYGON_OFFSET_FILL);
  // Bottom gray
  glColor3dv(signSilver);
  drawCircle(0.0, 0.0, 0.0, 2.0, 1.04, 150, 1, 1, 0);
}

// This function handle creating all of the letters on the sign.
// TODO: Lighting, materials, etc.
void drawLetters()
{
  glColor3dv(signBlue);

  // SHIFT
  drawS(-1.13, 0.15, 0.01, 0.96);
  drawH(-0.63, 0.15, 0.01, 0.95);
  drawI(-0.07, 0.15, 0.01, 0.95);
  drawF(0.21, 0.15, 0.01, 0.95);
  drawT(0.62, 0.15, 0.01, 0.95);
  // Trademark
  drawT(0.98, 0.1501, 0.01, 0.0902077);
  drawM(1.03, 0.1501, 0.01, 0.0902077);

  glColor3dv(signSilver);
  // PALE
  drawP(-0.6, -0.3, 0.01, 0.223);
  drawA(-0.47, -0.3, 0.01, 0.223);
  drawL(-0.32, -0.3, 0.01, 0.223);
  drawE(-0.2, -0.3, 0.01, 0.223);

  // LAGER
  drawL(0.0, -0.3, 0.01, 0.223);
  drawA(0.12, -0.3, 0.01, 0.223);
  drawG(0.25, -0.3, 0.01, 0.223);
  drawE(0.39, -0.3, 0.01, 0.223);
  drawR(0.52, -0.3, 0.01, 0.223);
}

static void
gear(float scale,
  GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
  GLint teeth, GLfloat tooth_depth)
{
  GLint i;
  GLfloat r0, r1, r2;
  GLfloat angle, da;
  GLfloat u, v, len;

  r0 = inner_radius;
  r1 = outer_radius - tooth_depth / 2.0;
  r2 = outer_radius + tooth_depth / 2.0;

  da = 2.0 * M_PI / teeth / 4.0;

  glPushMatrix();
  glScaled(scale, scale, scale);

  glShadeModel(GL_FLAT);

  glNormal3f(0.0, 0.0, 1.0);

  /* draw front face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    if (i < teeth) {
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    }
  }
  glEnd();

  /* draw front sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  glNormal3f(0.0, 0.0, -1.0);

  /* draw back face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    if (i < teeth) {
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    }
  }
  glEnd();

  /* draw back sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
  }
  glEnd();

  /* draw outward faces of teeth */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
    glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
    glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glNormal3f(cos(angle), sin(angle), 0.0);
  }

  glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
  glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();

  glShadeModel(GL_SMOOTH);

  /* draw inside radius cylinder */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glNormal3f(-cos(angle), -sin(angle), 0.0);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
  }
  glEnd();

  glPopMatrix();

}

// This function handles creating all of the different gears and their interiors
void drawGears()
{

  glColor3dv(signSilver);

  // Gear 1 (Base Gear)
  glPushMatrix();
  glRotatef(-angle, 0.0, 0.0, 1.0);
  gear(1.0, 0.825, 1.0, 0.2, 33, 0.175);
  glPopMatrix();

  // Gear 2 (Smaller gear inside the chain)
  glPushMatrix();
  glTranslatef(-1.1, 2.2, 0.0);
  glRotatef(-angle, 0.0, 0.0, 1.0);
  gear(0.88, 0.8, 1.0, 0.2, 22, 0.175);
  glPopMatrix();


  // Gear 3 (Larger gear to the left of the base gear)
  glPushMatrix();
  glTranslatef(-2.65, -0.55, 0.0);
  glRotatef(0.5 * angle - 125.0, 0.0, 0.0, 1.0);
  gear(1.633, 0.825, 1.0, 0.2, 26, 0.1);
  glPopMatrix();

  // Gear 4 (Larger gear on the upper right of the base gear)
  glPushMatrix();
  glTranslatef(2.05, 2.25, 0.0);
  glRotatef(angle/2.0 - 9.0, 0.0, 0.0, 1.0);
  gear(1.957, 0.825, 1.0, 0.2, 60, 0.08);
  glPopMatrix();

  // Gear 5 (Large gear inside the chain)
  glPushMatrix();
  glTranslatef(-6.25, 2.25, 0.0);
  glRotatef(0.5 * -angle, 0.0, 0.0, 1.0);
  gear(2.35, 0.825, 1.0, 0.2, 30, 0.08);
  glPopMatrix();

  //glColor3dv(signBlue);

  // Z SCALE MIGHT NEED TO BE FIXED AFTER LIGHTING IS ENTERED!

  // Gear 2 Interior
  glPushMatrix();
  glTranslatef(-1.1, 2.2, 0.0);
  glScaled(1.6,1.6,0.98);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(-angle, 0.0, 1.0, 0.0);
  glCallList(gear2Int);
  glPopMatrix();

  // Gear 3 Interior
  glPushMatrix();
  glTranslatef(-2.65, -0.55, 0.0);
  glScaled(1.35,1.35,0.815);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(0.5 * angle - 125.0, 0.0, 1.0, 0.0);
  glCallList(gear3Int);
  glPopMatrix();

  // Gear 4 Interior
  glPushMatrix();
  glTranslatef(2.05, 2.25, 0.0);
  glScaled(1.55,1.55,0.93);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(angle/2.0 - 9.0, 0.0, 1.0, 0.0);
  glCallList(gear4Int);
  glPopMatrix();

  // Gear 5 Interior
  glPushMatrix();
  glTranslatef(-6.25, 2.25, 0.0);
  glScaled(1.54,1.54,0.929);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(0.5 * -angle, 0.0, 1.0, 0.0);
  glCallList(gear5Int);
  glPopMatrix();


  glPushMatrix();
  if(ch == 0)
  {
    glTranslatef(-2.5, 5.25, 0.0);
  }
  else
  {
    glTranslatef(-2.25, 5.78, 0.0);
  }
  glScaled(1.7, 1.7, 10.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glCallList(displayChain[ch]);
  glPopMatrix();

}


// All of the "main" functions below

static void reProject()
{
  //  Tell OpenGL we want to manipulate the projection matrix
  glMatrixMode(GL_PROJECTION);
  //  Undo previous transformations
  glLoadIdentity();
  if(proj == 0) // Orthogonal Projection
  {

    //  Orthogonal projection
    glOrtho(-asp*dim,+asp*dim, -dim,+dim, -15.0,+15.0);

  }
  else // Perspective Projection
  {
    gluPerspective(fov, asp, 2, 20);
    gluLookAt(0,0,5,0,0,0,0,1,0);
  }
  //  Switch to manipulating the model matrix
  glMatrixMode(GL_MODELVIEW);
  //  Undo previous transformations
  glLoadIdentity();
}

static void
cleanup(void)
{
   glDeleteLists(gear2Int, 1);
   glDeleteLists(gear3Int, 1);
   glDeleteLists(gear4Int, 1);
   glDeleteLists(gear5Int, 1);
   glutDestroyWindow(win);
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  //  Set view angle
  glLoadIdentity();
  glRotatef(ph, 1, 0, 0);
  glRotatef(th, 0, 1, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Lighting
  float Ambient[]   = {ambient ,ambient ,ambient ,1.0};
  float Diffuse[]   = {diffuse ,diffuse ,diffuse ,1.0};
  float Specular[]  = {specular,specular,specular,1.0};
  float Emission[]  = {0.0,0.0,0.0,1.0};
  //  Light direction
  float Position[]  = {0.0,-0.3,5.0,1.0};

  glColor3f(1,1,1);

  //ball(Position[0],Position[1],Position[2] , 0.1);
  //  OpenGL should normalize normal vectors
  glEnable(GL_NORMALIZE);
  //  Enable lighting
  glEnable(GL_LIGHTING);
  //  glColor sets ambient and diffuse color materials
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine * 128.0);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
  glEnable(GL_COLOR_MATERIAL);
  //  Enable light 0
  glEnable(GL_LIGHT0);
  //  Set ambient, diffuse, specular components and position of light 0
  glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
  glLightfv(GL_LIGHT0,GL_POSITION,Position);

  // Draws the sign without letters or gears
  drawBackground();

  // Draws the letters on the sign
  drawLetters();

  // Draws all the gears on the sign
  glPushMatrix();
  glTranslatef(0.5, -1.4, 0.15);
  glScaled(0.22, 0.22, 0.22);
  drawGears();
  glPopMatrix();

  glDisable(GL_LIGHTING);

  glWindowPos2i(5, 5);
  Print("th=%i, ph=%i Projection=%s", th, ph, proj?"Perpective":"Orthogonal");

  ErrCheck("display");
  glFlush();
  glutSwapBuffers();
}

void idle ()
{
  static double t0 = -1.;
  dt, t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  if (t0 < 0.0)
    t0 = t;
  dt = t - t0;
  t0 = t;

  angle += 70.0 * dt;  /* 70 degrees per second */
  chainMove += 15.0 * dt;
  angle = fmod(angle, 360.0); /* prevents eventual overflow */

  if (fmod(chainMove, 4.0) >= 0 && fmod(chainMove, 4.0) < 1)
  {
    ch = 0;
  }
  else if(fmod(chainMove, 4.0) >= 1 && fmod(chainMove, 4.0) < 2)
  {
    ch = 1;
  }
  else if(fmod(chainMove, 4.0) >= 2 && fmod(chainMove, 4.0) < 3)
  {
    ch = 2;
  }
  else if(fmod(chainMove, 4.0) >= 3 && fmod(chainMove, 4.0) < 4)
  {
    ch = 3;
  }

  glutPostRedisplay();
}

void special(int key, int x, int y)
{
  //  Right arrow key - increase angle by 5 degrees
  if (key == GLUT_KEY_RIGHT)
    th += 5;
  //  Left arrow key - decrease angle by 5 degrees
  else if (key == GLUT_KEY_LEFT)
    th -= 5;
  //  Up arrow key - increase elevation by 5 degrees
  else if (key == GLUT_KEY_UP)
    ph += 5;
  //  Down arrow key - decrease elevation by 5 degrees
  else if (key == GLUT_KEY_DOWN)
    ph -= 5;
  //  Keep angles to +/-360 degrees
  th %= 360;
  ph %= 360;
  //  Tell GLUT it is necessary to redisplay the scene
  reProject();
  glutPostRedisplay();
}

void reshape(int width, int height)
{
  //  Set the viewport to the entire window
  glViewport(0,0, width,height);
  reProject();
}

void key(unsigned char k, int x, int y)
{
  switch (k)
  {
    case 27:
      cleanup();
      exit (0);
      break;

    case 'p':
      proj = 1 - proj;
      break;

    case 'c':
      ch += 1;
      ch = ch % 4;

    /*case 'm':
      move = 1 - move;
      break;*/

    /*case 'a':
      zh = zh - 2;
      break;

    case 'd':
      zh = zh + 2;
      break;

    zh %= 360;*/

    default:
    return;
  }

  reProject();
  glutPostRedisplay();

}

int main(int argc, char *argv[])
{
  // Initalize GLUT and process user parameters
  glutInit(&argc, argv);
  // Request double buffered, true color window with Z buffering
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  // Request 600 x 600 pixel window
  glutInitWindowSize(900, 900);
  // Create window
  win = glutCreateWindow("Shift - Sean Callahan");
  // Tell GLUT to call "display" when the scene should be drawn
  glutDisplayFunc(display);
  // Tell GLUT to call "reshape" when the window is resized
  glutReshapeFunc(reshape);
  // Tell GLUT to call "special" when an arrow key is pressed
  glutSpecialFunc(special);
  // Tell GLUT to call "key" when a special key is pressed
  glutKeyboardFunc(key);
  newBelgTex = LoadTexBMP("newBelgTex.bmp");

  gear2Int = LoadOBJ("gear2.obj");
  gear3Int = LoadOBJ("gear3.obj");
  gear4Int = LoadOBJ("gear4.obj");
  gear5Int = LoadOBJ("gear5.obj");

  chain = LoadOBJ("chain.obj");
  chain2 = LoadOBJ("chain2.obj");
  chain3 = LoadOBJ("chain3.obj");
  chain4 = LoadOBJ("chain4.obj");

  displayChain[0] = chain;
  displayChain[1] = chain2;
  displayChain[2] = chain3;
  displayChain[3] = chain4;

  glutIdleFunc(idle);
  // Pass control to GLUT so it can interact with the user
  glutMainLoop();
  return 0;
}