#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

// --- GLOBALS ---
float rotation = 0.0f;
float orbit = 45.0f;
float zoom = 38.0f;
float waterShift = 0.0f;
float skyRotation = 0.0f;
float flapAngle = 0.0f;
float fireflyFlicker = 0.0f;
float smokeShift = 0.0f;
float treeSway = 0.0f;

float targetX = 0.0f, targetY = -5.0f, targetZ = 0.0f;

// Material Presets
GLfloat mat_zero[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_soft_spec[] = {0.15f, 0.15f, 0.1f, 1.0f};

const int NUM_CLOUDS = 80;
struct Cloud
{
    float x, y, z, s;
} skyField[NUM_CLOUDS];

// --- FORWARD DECLARATIONS ---
void updateEnvironment();
void drawSimpleBase();
void drawGreatWaterSystem();
void drawBridge();
void drawFireflies();
void drawMountain(float x, float z, float h, float w);
void drawCabin(float x, float z, float rot);
void drawSmoke(float x, float z, float rot);
void drawRock(float x, float z, float s, float rot);
void drawFlowers(float x, float z, int type);
void drawDeer(float x, float z, float rot);
void drawFox(float x, float z, float rot);
void drawSheep(float x, float z, float rot);
void drawBird(float x, float y, float z, float orbitAngle);
void drawTree(float x, float z, float s);
void drawPuffyCloud(float x, float y, float z, float s);
void drawHUD();

// --- ASSET FUNCTIONS ---

void drawMountain(float x, float z, float h, float w)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_soft_spec);
    glPushMatrix();
    glTranslatef(x, 0.45f, z);
    glColor3f(0.42f, 0.42f, 0.45f);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(w, h, 8, 1);
    glTranslatef(0, 0, h * 0.75f);
    glColor3f(1.0f, 1.0f, 1.0f); // Snow cap
    glutSolidCone(w * 0.35f, h * 0.35f, 8, 1);
    glPopMatrix();
}

void drawDeer(float x, float z, float rot)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_zero);
    glPushMatrix();
    glTranslatef(x, 0.75f, z);
    glRotatef(rot, 0, 1, 0);
    glScalef(0.5f, 0.5f, 0.5f);
    glColor3f(0.45f, 0.3f, 0.2f); // Brown body
    glPushMatrix();
    glScalef(1.2f, 0.8f, 0.6f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.7f, 0.5f, 0);
    glRotatef(45, 0, 0, 1);
    glScalef(0.4f, 0.8f, 0.4f);
    glutSolidCube(1.0);
    glPopMatrix();
    glColor3f(0.35f, 0.25f, 0.15f);
    float lp[4][2] = {{0.4, 0.2}, {0.4, -0.2}, {-0.4, 0.2}, {-0.4, -0.2}};
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(lp[i][0], -0.6f, lp[i][1]);
        glScalef(0.15f, 0.6f, 0.15f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawFox(float x, float z, float rot)
{
    glPushMatrix();
    glTranslatef(x, 0.72f, z);
    glRotatef(rot, 0, 1, 0);
    glScalef(0.4f, 0.4f, 0.4f);
    glColor3f(0.8f, 0.35f, 0.0f); // Orange
    glPushMatrix();
    glScalef(1.2f, 0.6f, 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8f, 0, 0);
    glScalef(0.6f, 0.3f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.7f, 0.3f, 0);
    glutSolidSphere(0.4, 6, 6);
    glPopMatrix();
    glPopMatrix();
}

void drawSheep(float x, float z, float rot)
{
    glPushMatrix();
    glTranslatef(x, 0.75f, z);
    glRotatef(rot, 0, 1, 0);
    glScalef(0.45f, 0.45f, 0.45f);
    glColor3f(0.9f, 0.9f, 0.9f);
    glutSolidSphere(0.8, 8, 8); // Wool
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0.7f, 0.2f, 0);
    glutSolidSphere(0.35, 6, 6);
    glPopMatrix();
    glPopMatrix();
}

void drawCabin(float x, float z, float rot)
{
    float sunY = sin(orbit * 0.017f);
    glPushMatrix();
    glTranslatef(x, 0.65f, z);
    glRotatef(rot, 0, 1, 0);
    glColor3f(0.3f, 0.18f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 1.0f, 0);
    glScalef(2.5f, 2.0f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    glColor3f(0.45f, 0.15f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 2.0f, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(45, 0, 0, 1);
    glutSolidCone(2.2, 1.6, 4, 1);
    glPopMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.8f, 2.1f, 0.5f);
    glScalef(0.4f, 1.4f, 0.4f);
    glutSolidCube(1.0);
    glPopMatrix();
    if (sunY < 0.2)
    {
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 0.8f, 0.2f);
    }
    else
    {
        glColor3f(0.1f, 0.05f, 0.0f);
    }
    glPushMatrix();
    glTranslatef(0, 1.2f, 1.01f);
    glScalef(0.4f, 0.4f, 0.02f);
    glutSolidCube(1.0);
    glPopMatrix();
    if (sunY < 0.2)
        glEnable(GL_LIGHTING);
    glPopMatrix();
}

void drawSmoke(float x, float z, float rot)
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glPushMatrix();
    glRotatef(rotation, 0, 1, 0);
    glTranslatef(x, 0.65f, z);
    glRotatef(rot, 0, 1, 0);
    for (int i = 0; i < 4; i++)
    {
        float s = fmod(smokeShift + (i * 1.5f), 4.0f);
        glColor4f(1.0f, 1.0f, 1.0f, 0.6f - (s * 0.15f));
        glPushMatrix();
        glTranslatef(0.8f, 2.9f + s, 0.5f + sin(s * 2.0f) * 0.2f);
        glutSolidSphere(0.2f + (s * 0.1f), 6, 6);
        glPopMatrix();
    }
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void drawGreatWaterSystem()
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.55f, 0.95f, 0.85f);
    glPushMatrix();
    glTranslatef(0.0f, 0.68f, 0.0f);
    glRotatef(90, 1, 0, 0);
    GLUquadric *q1 = gluNewQuadric();
    gluDisk(q1, 0, 10.5, 32, 1);
    gluDeleteQuadric(q1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.68f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0, 5.5f);
    glVertex3f(16.0f, 0, 5.5f);
    glVertex3f(16.0f, 0, -5.5f);
    glVertex3f(0.0f, 0, -5.5f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(16.05f, 0.68f, 0.0f);
    glColor4f(0.2f, 0.65f, 1.0f, 0.7f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0, 5.5f);
    glVertex3f(0.0f, 0, -5.5f);
    glVertex3f(0.0f, -40.0f, -5.5f);
    glVertex3f(0.0f, -40.0f, 5.5f);
    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
    for (int i = 0; i < 4; i++)
    {
        float sPos = fmod(waterShift + (i * 10.0f), 40.0f);
        glBegin(GL_QUADS);
        glVertex3f(0.05f, -sPos, -4.0f + (i * 2.5f) + 0.8f);
        glVertex3f(0.05f, -sPos, -4.0f + (i * 2.5f) - 0.8f);
        glVertex3f(0.05f, -sPos - 4.0f, -4.0f + (i * 2.5f) - 0.8f);
        glVertex3f(0.05f, -sPos - 4.0f, -4.0f + (i * 2.5f) + 0.8f);
        glEnd();
    }
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void drawTree(float x, float z, float s)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_zero);
    glPushMatrix();
    glTranslatef(x, 0.65f, z);
    glScalef(s, s, s);
    glColor3f(0.35f, 0.25f, 0.15f);
    glPushMatrix();
    glScalef(0.2f, 0.7f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    glColor3f(0.12f, 0.45f, 0.18f);
    float sway = sin(treeSway + (x * z)) * 3.0f;
    for (int i = 0; i < 3; i++)
    {
        glPushMatrix();
        glTranslatef(0, 0.4f + (i * 0.35f), 0);
        glRotatef(sway, 1, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.8f - (i * 0.2f), 1.0f, 6, 1);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawBird(float x, float y, float z, float orbitAngle)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glRotatef(orbitAngle, 0, 1, 0);
    glTranslatef(x, y, z);
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(0.4f, 0.2f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    float wf = sin(flapAngle) * 45.0f;
    glPushMatrix();
    glRotatef(wf, 1, 0, 0);
    glTranslatef(0, 0, 0.3f);
    glScalef(0.3f, 0.05f, 0.6f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-wf, 1, 0, 0);
    glTranslatef(0, 0, -0.3f);
    glScalef(0.3f, 0.05f, 0.6f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawSimpleBase()
{
    glColor3f(0.22f, 0.55f, 0.12f);
    glPushMatrix();
    glScalef(3.2f, 0.12f, 3.2f);
    glutSolidSphere(5.0, 12, 8);
    glPopMatrix();
    glColor3f(0.32f, 0.22f, 0.16f);
    glPushMatrix();
    glTranslatef(0, -0.4f, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidCone(10.5, 14.0, 8, 2);
    glPopMatrix();
}

void drawPuffyCloud(float x, float y, float z, float s)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(s, s, s);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glScalef(2.0f, 0.8f, 1.2f);
    glutSolidSphere(1.0, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.8f, 0.3f, 0.2f);
    glutSolidSphere(0.7, 6, 6);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.7f, 0.2f, -0.3f);
    glutSolidSphere(0.6, 6, 6);
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawRock(float x, float z, float s, float rot)
{
    glPushMatrix();
    glTranslatef(x, 0.65f, z);
    glRotatef(rot, 0, 1, 0);
    glScalef(s, s * 0.7f, s);
    glColor3f(0.42f, 0.42f, 0.45f);
    glutSolidIcosahedron();
    glPopMatrix();
}

void drawFlowers(float x, float z, int type)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(x, 0.72f, z);
    if (type == 0)
        glColor3f(1.0f, 0.2f, 0.2f);
    else if (type == 1)
        glColor3f(1.0f, 0.9f, 0.0f);
    else
        glColor3f(0.8f, 0.4f, 1.0f);
    glutSolidSphere(0.12, 4, 4);
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotatef(i * 90, 0, 1, 0);
        glTranslatef(0.12f, 0, 0);
        glScalef(1.5, 0.5, 1);
        glutSolidSphere(0.08, 4, 4);
        glPopMatrix();
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawBridge()
{
    glPushMatrix();
    glTranslatef(8.0f, 0.75f, 0.0f);
    glColor3f(0.35f, 0.22f, 0.1f);
    glPushMatrix();
    glScalef(2.5f, 0.15f, 11.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    for (int i = -1; i <= 1; i += 2)
    {
        glPushMatrix();
        glTranslatef(0, 0.6f, i * 5.6f);
        glScalef(2.5f, 0.1f, 0.2f);
        glutSolidCube(1.0);
        glPopMatrix();
        for (float j = -1.0f; j <= 1.0f; j += 1.0f)
        {
            glPushMatrix();
            glTranslatef(j * 1.0f, 0.3f, i * 5.6f);
            glScalef(0.15f, 0.7f, 0.15f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void drawFireflies()
{
    float sunY = sin(orbit * 0.017f);
    if (sunY < 0.1)
    {
        glDisable(GL_LIGHTING);
        for (int i = 0; i < 15; i++)
        {
            float t = fireflyFlicker + i;
            float fx = sin(t * 0.5f) * 8.0f;
            float fz = cos(t * 0.3f) * 8.0f;
            float fy = 3.0f + sin(t * 1.2f) * 1.5f;
            glPushMatrix();
            glTranslatef(fx, fy, fz);
            glColor4f(1.0f, 1.0f, 0.4f, (sin(t * 4.0f) + 1.0f) * 0.5f);
            glutSolidSphere(0.1, 4, 4);
            glPopMatrix();
        }
        glEnable(GL_LIGHTING);
    }
}

void drawHUD()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 720);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2i(0, 675);
    glVertex2i(1280, 675);
    glVertex2i(1280, 720);
    glVertex2i(0, 720);
    glVertex2i(0, 0);
    glVertex2i(1280, 0);
    glVertex2i(1280, 45);
    glVertex2i(0, 45);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    std::string title = "PROJECT AETHERIA: THE SANCTUARY";
    glRasterPos2i(20, 690);
    for (char c : title)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    std::string keys = "WASD/RF: Move Camera | +/-: Zoom | ESC: Exit";
    glRasterPos2i(20, 15);
    for (char c : keys)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// --- CORE SYSTEM ---

void updateEnvironment()
{
    float sunY = sin(orbit * 3.14159 / 180.0);
    if (sunY > 0.3)
        glClearColor(0.45, 0.8, 1.0, 1.0);
    else if (sunY > -0.1)
        glClearColor(0.85, 0.42, 0.18, 1.0);
    else
        glClearColor(0.01, 0.01, 0.08, 1.0);
    GLfloat lp[] = {80.0f * (float)cos(orbit * 0.017f), 80.0f * (float)sin(orbit * 0.017f), -30.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lp);
}

void display()
{
    updateEnvironment();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(targetX + zoom, targetY + zoom * 0.42f, targetZ + zoom, targetX, targetY, targetZ, 0.0, 1.0, 0.0);

    glPushMatrix();
    float sx = 80.0f * cos(orbit * 0.017f), sy = 80.0f * sin(orbit * 0.017f);
    glDisable(GL_LIGHTING);
    glTranslatef(sx, sy, -30.0f);
    if (sy > 0)
        glColor3f(1.0, 0.98, 0.55);
    else
        glColor3f(0.8, 0.8, 1.0);
    glutSolidSphere(5.0, 12, 12);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
    glRotatef(skyRotation, 0.2, 1, 0.1);
    for (int i = 0; i < NUM_CLOUDS; i++)
    {
        drawPuffyCloud(skyField[i].x, skyField[i].y, skyField[i].z, skyField[i].s);
    }
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotation, 0, 1, 0);
    drawSimpleBase();
    drawGreatWaterSystem();
    drawBridge();
    drawFireflies();
    drawMountain(-9.0f, -7.5f, 13.0f, 5.8f);
    drawMountain(-4.5f, 9.0f, 9.0f, 4.8f);
    drawCabin(-13.0f, 6.0f, 135.0f);

    // Rocks
    drawRock(5.0, 5.0, 1.2, 45);
    drawRock(-6.0, 3.0, 0.8, 12);
    drawRock(3.0, -8.0, 1.5, 90);
    drawRock(-10.0, -5.0, 1.1, 200);
    drawRock(12.0, -2.0, 1.3, 160);
    drawRock(-8.0, 12.0, 1.4, 33);
    drawRock(14.0, 5.0, 0.9, 120);

    // Flowers
    for (int i = 0; i < 3; i++)
    {
        drawFlowers(10.0 + i, 5.0, i % 3);
        drawFlowers(-5.0 - i, -10.0, (i + 1) % 3);
        drawFlowers(3.0, 12.0 + i, (i + 2) % 3);
        drawFlowers(-12.0 + i, 0.0, i % 3);
    }

    // Trees
    drawTree(-10.0, 5.0, 1.8);
    drawTree(-12.0, 8.0, 1.5);
    drawTree(-8.5, 9.5, 1.4);
    drawTree(2.0, 10.0, 1.7);
    drawTree(4.0, 11.5, 1.3);
    drawTree(0.0, 13.0, 1.6);
    drawTree(12.0, 2.0, 1.3);
    drawTree(14.0, 4.0, 1.5);
    drawTree(-5.0, -12.0, 1.7);

    // Wildlife
    drawDeer(12.0f, 3.0f, -45.0f);
    drawFox(8.0f, 12.0f, 90.0f);
    drawSheep(14.0f, 8.0f, 30.0f);
    drawBird(20.0f, 15.0f, 0.0f, rotation * 1.5f);
    drawBird(25.0f, 12.0f, 5.0f, rotation * 1.2f + 50.0f);
    glPopMatrix();

    drawSmoke(-13.0f, 6.0f, 135.0f);
    drawHUD();
    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_FLAT);
    glEnable(GL_MULTISAMPLE);
    GLfloat sd[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sd);
    GLfloat am[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, am);
    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.005f);
    srand(time(0));
    for (int i = 0; i < NUM_CLOUDS; i++)
    {
        float th = (rand() % 360) * 0.017f, ph = (rand() % 180 - 90) * 0.017f, r = 70.0f + (rand() % 30);
        skyField[i].x = r * cos(ph) * cos(th);
        skyField[i].y = r * sin(ph);
        skyField[i].z = r * cos(ph) * sin(th);
        skyField[i].s = 1.0f + (rand() % 200) / 100.0f;
    }
}

void timer(int v)
{
    rotation += 0.15f;
    orbit += 0.22f;
    waterShift += 0.8f;
    skyRotation += 0.04f;
    flapAngle += 0.25f;
    fireflyFlicker += 0.05f;
    smokeShift += 0.05f;
    treeSway += 0.03f;
    if (smokeShift > 4.0f)
        smokeShift = 0.0f;
    if (waterShift > 40.0f)
        waterShift = 0.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '+')
        zoom -= 1.0f;
    if (key == '-')
        zoom += 1.0f;
    if (key == 'w' || key == 'W')
        targetZ -= 1.0f;
    if (key == 's' || key == 'S')
        targetZ += 1.0f;
    if (key == 'a' || key == 'A')
        targetX -= 1.0f;
    if (key == 'd' || key == 'D')
        targetX += 1.0f;
    if (key == 'r' || key == 'R')
        targetY += 1.0f;
    if (key == 'f' || key == 'F')
        targetY -= 1.0f;
    if (key == 27)
        exit(0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Aetheria: Official Final Build");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}