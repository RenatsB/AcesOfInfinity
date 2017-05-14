#include "Mesh.h"
#include <iostream>
#include <cmath>

void Mesh::bullet(float _scale)
{
    glBegin(GL_TRIANGLES);
        glNormal3f    ( 0.0f*_scale,      -1.0f*_scale,        0.0f*_scale); //Bottom
        glVertex3f    ( 0.0f*_scale,       0.005f*_scale,      0.25f*_scale); //A
        glVertex3f    (-0.02f*_scale,     -0.02f*_scale,      -0.25f*_scale); //B
        glVertex3f    ( 0.02f*_scale,     -0.02f*_scale,      -0.25f*_scale); //C

        glNormal3f    (-1.0f*_scale,       0.6f*_scale,       0.25f*_scale); //Left
        glVertex3f    ( 0.0f*_scale,       0.005f*_scale,      0.25f*_scale); //A
        glVertex3f    (-0.02f*_scale,     -0.02f*_scale,      -0.25f*_scale); //B
        glVertex3f    ( 0.0f*_scale,       0.025f*_scale,     -0.25f*_scale); //D

        glNormal3f    ( 1.0f*_scale,       0.6f*_scale,       0.25f*_scale); //Right
        glVertex3f    ( 0.0f*_scale,       0.005f*_scale,      0.25f*_scale); //A
        glVertex3f    ( 0.02f*_scale,     -0.02f*_scale,      -0.25f*_scale); //C
        glVertex3f    ( 0.0f*_scale,       0.025f*_scale,     -0.25f*_scale); //D
    glEnd();
}

 void Mesh::shipTest(float _scale)
 {
  glBegin(GL_TRIANGLES);
  glNormal3f    (-1.0f*_scale,       0.6f*_scale,       0.25f*_scale); //LEFT
  glVertex3f    (-0.15f*_scale,     -0.05f*_scale,      0.25f*_scale); //A
  glVertex3f    (-0.2f*_scale,      -0.05f*_scale,     -0.25f*_scale); //B
  glVertex3f    (-0.15f*_scale,      0.15f*_scale,     -0.25f*_scale); //C

  glNormal3f    ( 1.0f*_scale,       0.6f*_scale,       0.25f*_scale); //RIGHT
  glVertex3f    ( 0.2f*_scale,      -0.05f*_scale,     -0.25f*_scale); //D
  glVertex3f    ( 0.15f*_scale,      0.15f*_scale,     -0.25f*_scale); //E
  glVertex3f    ( 0.15f*_scale,     -0.05f*_scale,      0.25f*_scale); //F
  glEnd();
  glBegin(GL_QUADS);
  glNormal3f    ( 0.0f*_scale,       1.0f*_scale,      -0.2f*_scale); //TOP
  glVertex3f    (-0.15f*_scale,     -0.05f*_scale,      0.25f*_scale); //A
  glVertex3f    (-0.15f*_scale,      0.15f*_scale,     -0.25f*_scale); //C
  glVertex3f    ( 0.15f*_scale,      0.15f*_scale,     -0.25f*_scale); //E
  glVertex3f    ( 0.15f*_scale,     -0.05f*_scale,      0.25f*_scale); //F

  glNormal3f    ( 0.0f*_scale,       0.0f*_scale,       1.0f*_scale); //BACK
  glVertex3f    (-0.2f*_scale,      -0.05f*_scale,     -0.25f*_scale); //B
  glVertex3f    (-0.15f*_scale,      0.15f*_scale,     -0.25f*_scale); //C
  glVertex3f    ( 0.15f*_scale,      0.15f*_scale,     -0.25f*_scale); //E
  glVertex3f    ( 0.2f*_scale,      -0.05f*_scale,     -0.25f*_scale); //D

  glNormal3f    ( 0.0f*_scale,      -1.0f*_scale,      -0.0f*_scale); //BOTTOM
  glVertex3f    (-0.15f*_scale,     -0.05f*_scale,      0.25f*_scale); //A
  glVertex3f    (-0.2f*_scale,      -0.05f*_scale,     -0.25f*_scale); //B
  glVertex3f    ( 0.2f*_scale,      -0.05f*_scale,     -0.25f*_scale); //D
  glVertex3f    ( 0.15f*_scale,     -0.05f*_scale,      0.25f*_scale); //F
  glEnd();
 }

 void Mesh::ship1(float _scale)
 {
    //TERRAN INTERCEPTOR
     //ALL VERTS:
     /*
     glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
     glVertex3f    (-0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //B
     glVertex3f    (-0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //C
     glVertex3f    (-0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //D
     glVertex3f    (-0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //E
     glVertex3f    ( 0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //F
     glVertex3f    ( 0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //G
     glVertex3f    ( 0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //H
     glVertex3f    ( 0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //I
     glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
     glVertex3f    (-0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //K
     glVertex3f    ( 0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //L
     glVertex3f    ( 0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //M
     glVertex3f    (-0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //N
     */
     //ALL NORMALS:
     /*
     glNormal3f    ( 0.0f*_scale,       0.6f*_scale,       0.25f*_scale); //1
     glNormal3f    (-1.0f*_scale,       0.5f*_scale,       0.2f*_scale); //2
     glNormal3f    ( 1.0f*_scale,       0.5f*_scale,       0.2f*_scale); //3
     glNormal3f    ( 0.0f*_scale,      -0.6f*_scale,       0.25f*_scale); //4
     glNormal3f    ( 1.0f*_scale,      -0.5f*_scale,       0.2f*_scale); //5
     glNormal3f    (-1.0f*_scale,      -0.5f*_scale,       0.2f*_scale); //6
     glNormal3f    ( 0.0f*_scale,       1.0f*_scale,      -0.02f*_scale); //7
     glNormal3f    ( 0.0f*_scale,      -1.0f*_scale,      -0.02f*_scale); //8
     glNormal3f    (-1.0f*_scale,       0.6f*_scale,       0.25f*_scale); //9
     glNormal3f    ( 1.0f*_scale,       0.6f*_scale,       0.25f*_scale); //10
     glNormal3f    ( 1.0f*_scale,       0.5f*_scale,      -0.05f*_scale); //11
     glNormal3f    (-1.0f*_scale,       0.5f*_scale,      -0.05f*_scale); //12
     glNormal3f    ( 1.0f*_scale,      -0.5f*_scale,       0.0f*_scale); //13
     glNormal3f    (-1.0f*_scale,      -0.5f*_scale,       0.0f*_scale); //14
     glNormal3f    ( 0.0f*_scale,      -1.0f*_scale,      -0.5f*_scale); //15
     */
     glBegin(GL_TRIANGLES);
        glNormal3f    (-1.0f*_scale,       0.5f*_scale,        0.2f*_scale); //2
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    (-0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //B
        glVertex3f    (-0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //K

        glNormal3f    ( 1.0f*_scale,       0.5f*_scale,        0.2f*_scale); //3
        glVertex3f    ( 0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //I
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
        glVertex3f    ( 0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //L

        glNormal3f    ( 1.0f*_scale,      -0.5f*_scale,        0.2f*_scale); //5
        glVertex3f    ( 0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //I
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
        glVertex3f    ( 0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //M

        glNormal3f    (-1.0f*_scale,      -0.5f*_scale,        0.2f*_scale); //6
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    (-0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //B
        glVertex3f    (-0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //N

        glNormal3f    ( 1.0f*_scale,       0.5f*_scale,       -0.05f*_scale); //11
        glVertex3f    (-0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //D
        glVertex3f    (-0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //E
        glVertex3f    (-0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //K

        glNormal3f    (-1.0f*_scale,       0.5f*_scale,       -0.05f*_scale); //12
        glVertex3f    ( 0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //F
        glVertex3f    ( 0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //G
        glVertex3f    ( 0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //L

        glNormal3f    ( 1.0f*_scale,      -0.5f*_scale,        0.0f*_scale); //13
        glVertex3f    ( 0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //H
        glVertex3f    ( 0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //I
        glVertex3f    ( 0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //M

        glVertex3f    ( 0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //F
        glVertex3f    ( 0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //H
        glVertex3f    ( 0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //M

        glNormal3f    (-1.0f*_scale,      -0.5f*_scale,        0.0f*_scale); //14
        glVertex3f    (-0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //B
        glVertex3f    (-0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //C
        glVertex3f    (-0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //N

        glVertex3f    (-0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //C
        glVertex3f    (-0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //E
        glVertex3f    (-0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //N

        glNormal3f    ( 0.0f*_scale,      -1.0f*_scale,       -0.5f*_scale); //15
        glVertex3f    ( 0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //F
        glVertex3f    ( 0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //G
        glVertex3f    ( 0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //H

        glVertex3f    (-0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //C
        glVertex3f    (-0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //D
        glVertex3f    (-0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //E
     glEnd();
     glBegin(GL_QUADS);
        glNormal3f    ( 0.0f*_scale,       0.6f*_scale,        0.25f*_scale); //1
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    (-0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //K
        glVertex3f    ( 0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //L
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J

        glNormal3f    ( 0.0f*_scale,      -0.6f*_scale,        0.25f*_scale); //4
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
        glVertex3f    ( 0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //M
        glVertex3f    (-0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //N
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A

        glNormal3f    ( 0.0f*_scale,       1.0f*_scale,       -0.02f*_scale); //7
        glVertex3f    (-0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //K
        glVertex3f    ( 0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //L
        glVertex3f    ( 0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //F
        glVertex3f    (-0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //E

        glNormal3f    ( 0.0f*_scale,      -1.0f*_scale,       -0.02f*_scale); //8
        glVertex3f    ( 0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //M
        glVertex3f    (-0.05f*_scale,     -0.075f*_scale,     -0.035f*_scale); //N
        glVertex3f    (-0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //E
        glVertex3f    ( 0.05f*_scale,      0.025f*_scale,     -0.32f*_scale); //F

        glNormal3f    (-1.0f*_scale,       0.6f*_scale,        0.25f*_scale); //9
        glVertex3f    (-0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //B
        glVertex3f    (-0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //C
        glVertex3f    (-0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //D
        glVertex3f    (-0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //K

        glNormal3f    ( 1.0f*_scale,       0.6f*_scale,        0.25f*_scale); //10
        glVertex3f    ( 0.1f*_scale,       0.1f*_scale,       -0.35f*_scale); //G
        glVertex3f    ( 0.2f*_scale,       0.0f*_scale,       -0.3f*_scale); //H
        glVertex3f    ( 0.1f*_scale,      -0.025f*_scale,     -0.03f*_scale); //I
        glVertex3f    ( 0.06f*_scale,      0.06f*_scale,      -0.035f*_scale); //L
     glEnd();
 }
 void Mesh::ship2(float _scale)
 {
     //PIRATE INTERCEPTOR
      //ALL VERTS:
      /*
      glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
      glVertex3f    (-0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //B
      glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C
      glVertex3f    (-0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //D
      glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //E
      glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //F
      glVertex3f    ( 0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //G
      glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H
      glVertex3f    ( 0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //I
      glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
      glVertex3f    (-0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //K
      glVertex3f    ( 0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //L
      glVertex3f    ( 0.0f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
      glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N
      */
      //ALL NORMALS:
      /*
      glNormal3f    ( 0.0f*_scale,       0.6f*_scale,        0.25f*_scale); //1
      glNormal3f    ( 0.0f*_scale,       0.5f*_scale,        0.4f*_scale); //2
      glNormal3f    ( 0.0f*_scale,       1.0f*_scale,        0.0f*_scale); //3
      glNormal3f    ( 0.5f*_scale,       0.5f*_scale,        0.1f*_scale); //4
      glNormal3f    (-0.5f*_scale,       0.5f*_scale,        0.1f*_scale); //5
      glNormal3f    ( 0.0f*_scale,      -0.7f*_scale,        0.3f*_scale); //6
      glNormal3f    ( 0.7f*_scale,      -0.45f*_scale,       0.02f*_scale); //7
      glNormal3f    (-0.7f*_scale,      -0.45f*_scale,       0.02f*_scale); //8
      glNormal3f    ( 0.5f*_scale,      -0.7f*_scale,       -0.25f*_scale); //9
      glNormal3f    (-0.5f*_scale,      -0.7f*_scale,       -0.25f*_scale); //10
      glNormal3f    ( 0.0f*_scale,      -0.6f*_scale,       -0.4f*_scale); //11
      glNormal3f    (-0.5f*_scale,       0.8f*_scale,       0.0f*_scale); //12
      glNormal3f    ( 0.5f*_scale,       0.8f*_scale,       0.0f*_scale); //13
      */
      glBegin(GL_TRIANGLES);
        glNormal3f    ( 0.5f*_scale,       0.5f*_scale,        0.1f*_scale); //4
        glVertex3f    ( 0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //I
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
        glVertex3f    ( 0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //L
        glVertex3f    ( 0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //L
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H
        glVertex3f    ( 0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //I

        glNormal3f    (-0.5f*_scale,       0.5f*_scale,        0.1f*_scale); //5
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    (-0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //B
        glVertex3f    (-0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //K
        glVertex3f    (-0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //B
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C
        glVertex3f    (-0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //K

        glNormal3f    ( 0.0f*_scale,      -0.7f*_scale,        0.3f*_scale); //6
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    ( 0.0f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H
        glVertex3f    ( 0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //G
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C
        glVertex3f    (-0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //D
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N

        glNormal3f    ( 0.7f*_scale,      -0.45f*_scale,       0.02f*_scale); //7
        glVertex3f    ( 0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //I
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J
        glVertex3f    ( 0.0f*_scale,      -0.05f*_scale,       0.0f*_scale); //M

        glNormal3f    (-0.7f*_scale,      -0.45f*_scale,       0.02f*_scale); //8
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    (-0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //B
        glVertex3f    ( 0.0f*_scale,      -0.05f*_scale,       0.0f*_scale); //M

        glNormal3f    ( 0.5f*_scale,      -0.7f*_scale,       -0.25f*_scale); //9
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //F
        glVertex3f    ( 0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //G

        glNormal3f    (-0.5f*_scale,      -0.7f*_scale,       -0.25f*_scale); //10
        glVertex3f    (-0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //D
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //E
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N

        glNormal3f    ( 0.0f*_scale,      -0.6f*_scale,       -0.4f*_scale); //11
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //E
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //F
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N

        glNormal3f    (-0.5f*_scale,       0.8f*_scale,       0.0f*_scale); //12
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C
        glVertex3f    (-0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //D
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //E

        glNormal3f    ( 0.5f*_scale,       0.8f*_scale,       0.0f*_scale); //13
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //F
        glVertex3f    ( 0.3f*_scale,      -0.04f*_scale,      -0.05f*_scale); //G
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H
      glEnd();
      glBegin(GL_QUADS);
        glNormal3f    ( 0.0f*_scale,       0.6f*_scale,        0.25f*_scale); //1
        glVertex3f    (-0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //A
        glVertex3f    (-0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //K
        glVertex3f    ( 0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //L
        glVertex3f    ( 0.045f*_scale,    -0.05f*_scale,       0.35f*_scale); //J

        glNormal3f    ( 0.0f*_scale,       0.5f*_scale,        0.4f*_scale); //2
        glVertex3f    ( 0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //L
        glVertex3f    (-0.08f*_scale,      0.06f*_scale,       0.0f*_scale); //K
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H

        glNormal3f    ( 0.0f*_scale,       1.0f*_scale,        0.0f*_scale); //3
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //E
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.35f*_scale); //F
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C

        glNormal3f    ( 0.5f*_scale,      -0.7f*_scale,       -0.25f*_scale); //9
        glVertex3f    ( 0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //H
        glVertex3f    ( 0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //I
        glVertex3f    ( 0.0f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N

        glNormal3f    (-0.5f*_scale,      -0.7f*_scale,       -0.25f*_scale); //10
        glVertex3f    (-0.11f*_scale,      0.0f*_scale,        0.0f*_scale); //B
        glVertex3f    (-0.08f*_scale,      0.025f*_scale,     -0.15f*_scale); //C
        glVertex3f    ( 0.0f*_scale,      -0.04f*_scale,      -0.25f*_scale); //N
        glVertex3f    ( 0.0f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
      glEnd();
 }
 void Mesh::ship3(float _scale)
 {
     //ALIEN INTERCEPTOR
      //ALL VERTS:
      /*
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,        0.4f*_scale); //A
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //B
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,       -0.2f*_scale); //C
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //D
      glVertex3f    ( 0.0f*_scale,       0.1f*_scale,        0.0f*_scale); //E
      glVertex3f    ( 0.0f*_scale,      -0.1f*_scale,        0.0f*_scale); //F

      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //G
      glVertex3f    (-0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //H
      glVertex3f    (-0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //I
      glVertex3f    (-0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //J

      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //K
      glVertex3f    ( 0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //L
      glVertex3f    ( 0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
      glVertex3f    ( 0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //N
      */
      //ALL NORMALS:
      /*
      glNormal3f    ( 0.5f*_scale,       0.5f*_scale,        0.25f*_scale); //1
      glNormal3f    (-0.5f*_scale,       0.5f*_scale,        0.25f*_scale); //2
      glNormal3f    ( 0.5f*_scale,      -0.5f*_scale,        0.25f*_scale); //3
      glNormal3f    (-0.5f*_scale,      -0.5f*_scale,        0.25f*_scale); //4
      glNormal3f    ( 0.5f*_scale,       0.5f*_scale,       -0.1f*_scale); //5
      glNormal3f    (-0.5f*_scale,       0.5f*_scale,       -0.1f*_scale); //6
      glNormal3f    ( 0.5f*_scale,      -0.5f*_scale,       -0.1f*_scale); //7
      glNormal3f    (-0.5f*_scale,      -0.5f*_scale,       -0.1f*_scale); //8

      glNormal3f    ( 0.5f*_scale,       0.0f*_scale,       -0.5f*_scale); //9
      glNormal3f    (-0.5f*_scale,       0.0f*_scale,       -0.5f*_scale); //10

      glNormal3f    ( 1.0f*_scale,       0.0f*_scale,        0.0f*_scale); //11
      glNormal3f    (-1.0f*_scale,       0.0f*_scale,        0.0f*_scale); //12
      */
      glBegin(GL_TRIANGLES);
      //HULL
      glNormal3f    ( 0.5f*_scale,       0.5f*_scale,        0.25f*_scale); //1
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,        0.4f*_scale); //A
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //D
      glVertex3f    ( 0.0f*_scale,       0.1f*_scale,        0.0f*_scale); //E

      glNormal3f    (-0.5f*_scale,       0.5f*_scale,        0.25f*_scale); //2
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,        0.4f*_scale); //A
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //B
      glVertex3f    ( 0.0f*_scale,       0.1f*_scale,        0.0f*_scale); //E

      glNormal3f    ( 0.5f*_scale,      -0.5f*_scale,        0.25f*_scale); //3
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,        0.4f*_scale); //A
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //D
      glVertex3f    ( 0.0f*_scale,      -0.1f*_scale,        0.0f*_scale); //F

      glNormal3f    (-0.5f*_scale,      -0.5f*_scale,        0.25f*_scale); //4
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,        0.4f*_scale); //A
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //B
      glVertex3f    ( 0.0f*_scale,      -0.1f*_scale,        0.0f*_scale); //F

      glNormal3f    ( 0.5f*_scale,       0.5f*_scale,       -0.1f*_scale); //5
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,       -0.2f*_scale); //C
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //D
      glVertex3f    ( 0.0f*_scale,       0.1f*_scale,        0.0f*_scale); //E

      glNormal3f    (-0.5f*_scale,       0.5f*_scale,       -0.1f*_scale); //6
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,       -0.2f*_scale); //C
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //B
      glVertex3f    ( 0.0f*_scale,       0.1f*_scale,        0.0f*_scale); //E

      glNormal3f    ( 0.5f*_scale,      -0.5f*_scale,       -0.1f*_scale); //7
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,       -0.2f*_scale); //C
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //B
      glVertex3f    ( 0.0f*_scale,      -0.1f*_scale,        0.0f*_scale); //F

      glNormal3f    (-0.5f*_scale,      -0.5f*_scale,       -0.1f*_scale); //8
      glVertex3f    ( 0.0f*_scale,       0.0f*_scale,       -0.2f*_scale); //C
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.0f*_scale); //D
      glVertex3f    ( 0.0f*_scale,      -0.1f*_scale,        0.0f*_scale); //F

      //RIGHT WING:
      glNormal3f    (-0.5f*_scale,       0.5f*_scale,        0.25f*_scale); //2
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //G
      glVertex3f    (-0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //H
      glVertex3f    (-0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //J

      glNormal3f    (-0.5f*_scale,      -0.5f*_scale,        0.25f*_scale); //4
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //G
      glVertex3f    (-0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //H
      glVertex3f    (-0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //I

      glNormal3f    ( 0.5f*_scale,       0.0f*_scale,       -0.5f*_scale); //9
      glVertex3f    (-0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //H
      glVertex3f    (-0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //I
      glVertex3f    (-0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //J

      glNormal3f    ( 1.0f*_scale,       0.0f*_scale,        0.0f*_scale); //11
      glVertex3f    (-0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //G
      glVertex3f    (-0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //I
      glVertex3f    (-0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //J
      //LEFT WING:
      glNormal3f    ( 0.5f*_scale,       0.5f*_scale,        0.25f*_scale); //1
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //K
      glVertex3f    ( 0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //L
      glVertex3f    ( 0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //N

      glNormal3f    ( 0.5f*_scale,      -0.5f*_scale,        0.25f*_scale); //3
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //K
      glVertex3f    ( 0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //L
      glVertex3f    ( 0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //M

      glNormal3f    (-0.5f*_scale,       0.0f*_scale,       -0.5f*_scale); //10
      glVertex3f    ( 0.225f*_scale,     0.0f*_scale,       -0.1f*_scale); //L
      glVertex3f    ( 0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
      glVertex3f    ( 0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //N

      glNormal3f    (-1.0f*_scale,       0.0f*_scale,        0.0f*_scale); //12
      glVertex3f    ( 0.1f*_scale,       0.0f*_scale,        0.2f*_scale); //K
      glVertex3f    ( 0.1f*_scale,      -0.05f*_scale,       0.0f*_scale); //M
      glVertex3f    ( 0.1f*_scale,       0.05f*_scale,       0.0f*_scale); //N
      glEnd();
 }

 void Mesh::asteroid(float _scale)
 {
     glBegin(GL_TRIANGLE_STRIP);

       glNormal3f(0.0f*_scale,     1.0f*_scale,       0.5f*_scale);
       glVertex3f(0.0f*_scale,     0.4f*_scale,       0.0f*_scale);
       glVertex3f(-0.25f*_scale,   0.0f*_scale,       0.0f*_scale);
       glVertex3f(0.0f*_scale,     0.0f*_scale,       0.25f*_scale);

       glVertex3f(0.0f*_scale,     -0.4f*_scale,      0.0f*_scale);

       //glNormal3f(0.5f*_scale,     1.0f*_scale,       0.0f*_scale);
       glVertex3f(0.25f*_scale,    0.0f*_scale,       0.0f*_scale);

       //glNormal3f(0.0f*_scale,     0.0f*_scale,     0.25f*_scale);
       glVertex3f(0.0f*_scale,     0.0f*_scale,       -0.25f*_scale);


       glVertex3f(0.0f*_scale,     -0.4f*_scale,       0.0f*_scale);
       glVertex3f(-0.25f*_scale,     0.0f*_scale,      0.0f*_scale);
       glVertex3f(0.0f*_scale,     0.0f*_scale,       -0.25f*_scale);
       glVertex3f(0.0*_scale,     0.4f*_scale,       0.0f*_scale);
       glVertex3f(0.25*_scale,     0.0f*_scale,       0.0f*_scale);

     glEnd();
 }
