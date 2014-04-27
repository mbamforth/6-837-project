#include "SetDesign.h"

#include <FL/Fl.H>

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

void SetDesign::load(int argcc, char* argvv[]) {
    argc = argcc;
    argv = argvv;

    glutInit( &argc, argv);
}

// Changed the num of parameters in this
void SetDesign::draw(Matrix4f cameraMatrix)
{
    // draw() gets called whenever a redraw is required
    // (after an update() occurs, when the camera moves, the window is resized, etc)
    m_matrixStack.clear();
    m_matrixStack.push(cameraMatrix);

    // Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
    glLoadMatrixf(m_matrixStack.top());

    // Draws the set, resets the matrix stack
    drawSet();
    m_matrixStack.pop();
}

// draws the Young Frankenstein set with floor and curtains
// colors could be tweaked, same with shininess (?)
void SetDesign::drawSet()
{
    // flattened cube for ground
    // either 3x or 7x flattened cube for curtains
    // either 3x or 6x transformed cube for set

    // this makes sure that the cubes render correctly
    glBegin(GL_POLYGON);
    glEnd();

    GLfloat floorColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    
    //floor
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(0.0f,-5.0f,0.0f);
    glScaled(30.0f,0.01f,20.0f);
    glutSolidCube(1);
    glPopMatrix();

    //GLfloat curtainColor[] = {1.5f, 1.5f, 1.5f, 1.0f};

    // big curtain
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-10.0f);
    glScaled(30.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();

    // back small curtains
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(12.0f,0.0f,-6.0f);
    glScaled(6.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(-12.0f,0.0f,-6.0f);
    glScaled(6.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();

    // mid small curtains
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(12.0f,0.0f,-2.0f);
    glScaled(6.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(-12.0f,0.0f,-2.0f);
    glScaled(6.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();

    // front small curtains
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(12.0f,0.0f,2.0f);
    glScaled(6.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(-12.0f,0.0f,2.0f);
    glScaled(6.0f,10.0f,0.01f);
    glutSolidCube(1);
    glPopMatrix();

    GLfloat platColor[] = {0.55f, 0.27f, 0.07f, 1.0f};

    // tall platform
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, platColor);
    glPushMatrix();
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-4.5f,-3.5f,-2.0f);
    glScaled(7.0f,3.0f,6.0f);
    glutSolidCube(1);
    glPopMatrix();

    // mid platform
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(0.0f,-4.0f,-1.0f);
    glScaled(7.0f,2.0f,6.0f);
    glutSolidCube(1);
    glPopMatrix();

    // short platform
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(5.5f,-4.5f,-1.0f);
    glScaled(7.0f,1.0f,4.0f);
    glutSolidCube(1);
    glPopMatrix();
}

