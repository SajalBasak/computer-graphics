#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
GLboolean a_bool=true, d_bool=true, s_bool=true;
GLboolean light1=true, light2=true, spotLight=true;

static GLfloat v_rectangle[8][3] =
{
    {0, 0, 0},
    {3, 0, 0},
    {3, 0, 3},
    {0, 0, 3},
    {0, 3, 0},
    {3, 3, 0},
    {3, 3, 3},
    {0, 3, 3}
};

static GLfloat v_blanket[8][3] =
{
    {0, 3, 2.3},
    {3, 3, 2.3},
    {3, 3, 3},
    {0, 3, 3},
    {0, 3.1, 2.3},
    {3, 3.1, 2.3},
    {3, 3.1, 3},
    {0, 3.1, 3}
};

static GLfloat v_pillow[8][3] =
{
    {0.3, 3, 0.3},
    {1.4, 3, 0.3},
    {1.4, 3, 0.8},
    {0.3, 3, 0.8},
    {0.3, 3.1, 0.3},
    {1.4, 3.1, 0.3},
    {1.4, 3.1, 0.8},
    {0.3, 3.1, 0.8}
};

static GLfloat v_pillow2[8][3] =
{
    {1.6, 3, 0.3},
    {2.7, 3, 0.3},
    {2.7, 3, 0.8},
    {1.6, 3, 0.8},
    {1.6, 3.1, 0.3},
    {2.7, 3.1, 0.3},
    {2.7, 3.1, 0.8},
    {1.6, 3.1, 0.8}
};

static GLubyte quadIndices[6][4] =
{
    {0, 3, 2, 1},
    {2, 6, 7, 3},
    {0, 4, 7, 3},
    {1, 5, 6, 2},
    {4, 7, 6, 5},
    {0, 1, 5, 4}
};

static GLfloat v_bedhead[8][3] =
{
    {0, 3, 0},
    {3, 3, 0},
    {3, 3, 0.05},
    {0, 3, 0.05},
    {0, 12, 0},
    {3, 12, 0},
    {3, 12, 0.05},
    {0, 12, 0.05}
};

static GLfloat v_wardrobe[8][3] =
{
    {0, 0, 0},
    {1.2, 0, 0},
    {1.2, 0, 0.2},
    {0, 0, 0.2},
    {0, 1, 0},
    {1.2, 1, 0},
    {1.2, 1, 0.2},
    {0, 1, 0.2}
};

/*
//color bed
static GLfloat colors[6][3] =
{
    {0.627, 0.322, 0.176},
    {0.627, 0.322, 0.176},
    {0.545, 0.271, 0.075}, //front
    {0.545, 0.271, 0.075},
    {0.545, 0.271, 0.075},
    {0.545, 0.271, 0.075}
};
//color bed sheet
static GLfloat colors2[6][3] =
{
    {0.576, 0.439, 0.859},
    {0.576, 0.439, 0.859},
    {0.294, 0.000, 0.510},
    {0.416, 0.353, 0.804},
    {0.416, 0.353, 0.804},
    {0.545, 0.000, 0.000}
};
//color blanket
static GLfloat colors3[6][3] =
{
    {0.855, 0.647, 0.125},
    {0.855, 0.647, 0.125},
    {0.855, 0.647, 0.125},
    {0.855, 0.647, 0.125},
    {0.855, 0.647, 0.125},
    {0.855, 0.647, 0.125}
};
//color bed
static GLfloat colors4[6][3] =
{
    {0.275, 0.510, 0.706},
    {0.275, 0.510, 0.706},
    {0.373, 0.620, 0.627}, //front
    {0.545, 0.271, 0.075},
    {0.545, 0.271, 0.075},
    {0.545, 0.271, 0.075}
};
//color left wall
static GLfloat colors5[6][3] =
{
    {0.275, 0.510, 0.706},
    {0.871, 0.722, 0.529},
    {0.804, 0.522, 0.247}, //front
    {0.545, 0.271, 0.075},
    {0.545, 0.271, 0.075},
    {0.545, 0.271, 0.075}
};
//color roof, floor
static GLfloat colors6[6][3] =
{
    {0.439, 0.502, 0.565},
    {0.804, 0.522, 0.247},
    {0.184, 0.310, 0.310}, //front
    {0.663, 0.663, 0.663},
    {0.663, 0.663, 0.663},
    {0.663, 0.663, 0.663}
};
//color fan
static GLfloat colors7[6][3] =
{
    {0.000, 0.000, 0.804},
    {0.000, 0.000, 0.804},
    {0.000, 0.000, 0.804}, //front
    {0.000, 0.000, 0.804},
    {0.000, 0.000, 0.804},
    {0.000, 0.000, 0.804}
};
//color fan2
static GLfloat colors8[6][3] =
{
    {0.294, 0.000, 0.510},
    {0.294, 0.000, 0.510},
    {0.294, 0.000, 0.510}, //front
    {0.294, 0.000, 0.510},
    {0.294, 0.000, 0.510},
    {0.294, 0.000, 0.510}
};
//color ac
static GLfloat colors9[6][3] =
{
    {0.294, 0.000, 0.510},
    {0.502, 0.000, 0.502},
    {0.502, 0.502, 0.502}, //front
    {0.294, 0.000, 0.510},
    {0.294, 0.000, 0.510},
    {0.294, 0.000, 0.510}
};
//color window
static GLfloat colors10[6][3] =
{
    {0.529, 0.808, 0.980},
    {0.529, 0.808, 0.980},
    {0.529, 0.808, 0.980}, //front
    {0.529, 0.808, 0.980},
    {0.529, 0.808, 0.980},
    {0.529, 0.808, 0.980}
};
//carpet
static GLfloat colors11[6][3] =
{
    {0.282, 0.239, 0.545},
    {0.282, 0.239, 0.545},
    {0.282, 0.239, 0.545}, //front
    {0.282, 0.239, 0.545},
    {0.282, 0.239, 0.545},
    {0.282, 0.239, 0.545}
};
*/

//bed
void drawcube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//bed sheet
void drawcube2()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors2[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//blanket
void drawcube3()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors3[quadIndices[i][0]][0]);
        glVertex3fv(&v_blanket[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_blanket[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_blanket[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_blanket[quadIndices[i][3]][0]);
    }
    glEnd();
}
//pillow1
void drawcube4()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors3[quadIndices[i][0]][0]);
        glVertex3fv(&v_pillow[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_pillow[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_pillow[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_pillow[quadIndices[i][3]][0]);
    }
    glEnd();
}
//pillow2
void drawcube5()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors3[quadIndices[i][0]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][3]][0]);
    }
    glEnd();
}
//bed head
void drawcube6()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors[quadIndices[i][0]][0]);
        glVertex3fv(&v_bedhead[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_bedhead[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_bedhead[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_bedhead[quadIndices[i][3]][0]);
    }
    glEnd();
}
//bed head
void drawcube7()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors[quadIndices[i][0]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][3]][0]);
    }
    glEnd();
}
//
void drawcube8()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        //glColor3f(1,1,1);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//rig
void drawcube9()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(0,0,0);
        glVertex3fv(&v_wardrobe[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_wardrobe[quadIndices[i][3]][0]);
    }
    glEnd();
}
//almirah
void drawcube10()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors4[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//left wall
void drawcube11()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors5[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//right wall
void drawcube12()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors5[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
void v_floor()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors6[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//fan
void v_fan()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors7[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//fan
void v_fan2()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors8[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//ac
void v_ac()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors9[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//window
void v_window()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors10[quadIndices[i][0]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
    }
    glEnd();
}
//carpet
void carpet()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors11[quadIndices[i][0]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_pillow2[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawRoom() {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.09, 0.15, 0.15, 1.0 };
    GLfloat mat_diffuse[] = { 0.184, 0.310, 0.310, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    //roof
    glPushMatrix();
    glScaled(3.5, 0.05, 2.8);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-1.78, 112.3, -.55);
    v_floor();
    glPopMatrix();

    //floor
    glPushMatrix();
    glScaled(3.5, 0.05, 2.8);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-1.78, -1.3, -.55);
    v_floor();
    glPopMatrix();

    GLfloat mat_ambient1[] = { 0.27, 0.13, 0.0, 1.0 };
    GLfloat mat_diffuse1[] = { 0.545, 0.271, 0.075, 1.0 };
    GLfloat mat_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular1);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);

    //left wall
    glPushMatrix();
    glScaled(.1, 1.9, 2.75);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-60.0, 0, -.5);
    drawcube11();
    glPopMatrix();

    GLfloat mat_ambient2[] = { 0.4, 0.26, 0.12, 1.0 };
    GLfloat mat_diffuse2[] = { 0.804, 0.522, 0.247, 1.0 };
    GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess2);

    //right wall
    glPushMatrix();
    glScaled(3.4, 1.9, .1);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-1.75, 0, -16.8);
    drawcube12();
    glPopMatrix();

    GLfloat mat_ambient3[] = { 0.0, 0.0, 0.4, 1.0 };
    GLfloat mat_diffuse3[] = { 0.000, 0.000, 0.804, 1.0 };
    GLfloat mat_specular3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess3[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient3);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular3);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess3);

    //fan
    glPushMatrix();
    glScaled(0.05, 0.2, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-25.0, 25.5, 40.0);
    v_fan2();
    glPopMatrix();

    GLfloat mat_ambient4[] = { 0.14, 0.0, 0.25, 1.0 };
    GLfloat mat_diffuse4[] = { 0.294, 0.000, 0.510, 1.0 };
    GLfloat mat_specular4[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess4[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient4);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse4);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular4);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess4);

    //fan blade 1
    glPushMatrix();
    glScaled(0.1, 0.02, 1.2);
    //glScaled(0.5, 0.2, 1.2);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-13.5, 250.5, 0.2);
    //glTranslatef(-2.0, 20.0, -.5);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, 1.5, 1.5, 1.5 );
    v_fan();
    glPopMatrix();

    //fan blade 2
    glPushMatrix();
    glScaled(1.2, 0.02, 0.1);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.5, 250.5, 19.7);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, 1.5, 1.5, 1.5 );
    v_fan();
    glPopMatrix();

    GLfloat mat_ambient5[] = { 0.09, 0.15, 0.15, 1.0 };
    GLfloat mat_diffuse5[] = { 0.184, 0.310, 0.310, 1.0 };
    GLfloat mat_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5);

    //ac
    glPushMatrix();
    glScaled(0.24, 0.3, 0.7);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-24.0, 13.0, 1.0);
    v_ac();
    glPopMatrix();

    GLfloat mat_ambient6[] = { 0.2, 0.1, 0.0, 1.0 };
    GLfloat mat_diffuse6[] = { 0.545, 0.271, 0.075, 1.0 };
    GLfloat mat_specular6[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess6[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular6);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess6);

    //bed leg
    glPushMatrix();
    glScaled(1.5, 0.2, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 0, -.5);
    drawcube();
    glPopMatrix();

    GLfloat mat_ambient7[] = { 0.1, 0.0, 0.25, 1.0 };
    GLfloat mat_diffuse7[] = { 0.294, 0.000, 0.510, 1.0 };
    GLfloat mat_specular7[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess7[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient7);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse7);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular7);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess7);

    //bed sheet
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube2();
    glPopMatrix();

    GLfloat mat_ambient8[] = { 0.4, 0.3, 0.05, 1.0 };
    GLfloat mat_diffuse8[] = { 0.855, 0.647, 0.125, 1.0 };
    GLfloat mat_specular8[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess8[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient8);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse8);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular8);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess8);

    //blanket
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube3();
    glPopMatrix();

    GLfloat mat_ambient9[] = { 0.4, 0.3, 0.05, 1.0 };
    GLfloat mat_diffuse9[] = { 0.855, 0.647, 0.125, 1.0 };
    GLfloat mat_specular9[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess9[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient9);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse9);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular9);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess9);

    //pillow1
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube4();
    glPopMatrix();

    //pillow2
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube5();
    glPopMatrix();

    GLfloat mat_ambient10[] = { 0.14, 0.11, 0.27, 1.0 };
    GLfloat mat_diffuse10[] = { 0.282, 0.239, 0.545, 1.0 };
    GLfloat mat_specular10[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess10[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient10);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse10);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular10);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess10);

    //carpet
    glPushMatrix();
    glScaled(0.8, 0.1, 4.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(0.5, -0.9, 0);
    carpet();
    glPopMatrix();

    GLfloat mat_ambient11[] = { 0.27, 0.135, 0.0, 1.0 };
    GLfloat mat_diffuse11[] = { 0.545, 0.271, 0.075, 1.0 };
    GLfloat mat_specular11[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess11[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient11);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse11);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular11);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess11);

    //bed head
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube6();
    glPopMatrix();

    GLfloat mat_ambient12[] = { 0.2, 0.13, 0.0, 1.0 };
    GLfloat mat_diffuse12[] = { 0.545, 0.271, 0.075, 1.0 };
    GLfloat mat_specular12[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess12[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient12);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse12);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular12);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess12);

    //wardrobe
    glPushMatrix();
    glScaled(1.2, 1.9, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(1.5, 0.05, -.5);
    drawcube7();
    glPopMatrix();

    //wardrobe
    glPushMatrix();
    glScaled(1.2, 1.9, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(1.5, 0.05, -.5);
    drawcube7();
    glPopMatrix();

    GLfloat mat_ambient13[] = { 0.18, 0.31, 0.31, 1.0 };
    GLfloat mat_diffuse13[] = { 0.373, 0.620, 0.627, 1.0 };
    GLfloat mat_specular13[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess13[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient13);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse13);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular13);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess13);

    //almirah
    glPushMatrix();
    glScaled(0.25, 1.7, 0.8);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-20.0, 0, 4.7);
    drawcube10();
    glPopMatrix();

    GLfloat mat_ambient14[] = { 0.0, 0.5, 0.0, 1.0 };
    GLfloat mat_diffuse14[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_specular14[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess14[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient14);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse14);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular14);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess14);

    //picture
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -30.0);
    v_window();
    glPopMatrix();

    GLfloat mat_ambient15[] = { 0.5, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse15[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular15[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess15[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient15);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse15);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular15);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess15);

    //picture2
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -29.999);
    glBegin(GL_TRIANGLES);
        //glColor3f(0, 0, 1);
        glVertex3f(3, 3, 3);
        glVertex3f(0, 0, 3);
        glVertex3f(3, 0, 3);
    glEnd();
    glPopMatrix();

    GLfloat mat_ambient16[] = { 0.0, 0.0, 0.5, 1.0 };
    GLfloat mat_diffuse16[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat mat_specular16[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess16[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient16);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse16);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular16);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess16);

    //picture3
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -29.999);
    glBegin(GL_TRIANGLES);
        //glColor3f(1, 0, 0);
        glVertex3f(1.5, 1.5, 3);
        glVertex3f(3, 3, 3);
        glVertex3f(0, 3, 3);
    glEnd();
    glPopMatrix();

    GLfloat mat_ambient17[] = { 0.0, 0.5, 0.0, 1.0 };
    GLfloat mat_diffuse17[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_specular17[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess17[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient17);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse17);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular17);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess17);

    //picture4
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -29.999);
    glBegin(GL_TRIANGLES);
        //glColor3f(1.000, 0.843, 0.000);
        glVertex3f(1.5, 1.5, 3);
        glVertex3f(0, 3, 3);
        glVertex3f(0, 0, 3);
    glEnd();
    glPopMatrix();

    GLfloat mat_ambient18[] = { 0.26, 0.4, 0.49, 1.0 };
    GLfloat mat_diffuse18[] = { 0.529, 0.808, 0.980, 1.0 };
    GLfloat mat_specular18[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess18[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient18);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse18);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular18);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess18);

    //window
    glPushMatrix();
    glScaled(0.8, 0.7, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(2.0, 4.0, -30.0);
    v_window();
    glPopMatrix();

    GLfloat mat_ambient19[] = { 0.2, 0.13, 0.0, 1.0 };
    GLfloat mat_diffuse19[] = { 0.545, 0.271, 0.075, 1.0 };
    GLfloat mat_specular19[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess19[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient19);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse19);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular19);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess19);

    //wardrobe2
    glPushMatrix();
    glScaled(1.0, 0.9, 0.2);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-6.0, 0, -4.0);
    drawcube();
    glPopMatrix();

    GLfloat mat_ambient20[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse20[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular20[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess20[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient20);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse20);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular20);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess20);

    //rig
    glPushMatrix();
    glScaled(0.1, 5.2, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-43.6, -0.02, 16.5);
    drawcube9();
    glPopMatrix();

    GLfloat mat_ambient21[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse21[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular21[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess21[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient21);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse21);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular21);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess21);

    //rig2
    glPushMatrix();
    glScaled(0.015, 2.2, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(188.6, 1.25, -4.52);
    drawcube9();
    glPopMatrix();

    GLfloat mat_ambient22[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse22[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular22[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess22[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient22);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse22);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular22);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess22);

    //rig3
    glPushMatrix();
    glScaled(0.011, 2.2, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(230.6, -0.08, -2.5);
    drawcube9();
    glPopMatrix();

    GLfloat mat_ambient23[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse23[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular23[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess23[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient23);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse23);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular23);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess23);

    //rig4
    glPushMatrix();
    glScaled(0.011, 2.4, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-400.6, 0.06, -0.65);
    drawcube9();
    glPopMatrix();

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5,-5,5, 4, 50);
    //gluPerspective(60,1,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(5,5.5,10, 0,0,0, 0,1,0);

    glViewport(0, 0, windowHeight, windowWidth);
    glPushMatrix();
    //glTranslatef(0,0,Tzval);
    glTranslatef(Txval,Tyval,Tzval);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawRoom();

    glPopMatrix();

    /*
    glPushMatrix();
        glTranslatef(0,0,Tzval);
        glScalef(2,2,2);
        glutSolidCube(1);
    glPopMatrix();
    */

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:	// Escape key
        exit(1);
    }

    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};

    GLfloat light_diffuse1[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse2[]  = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat light_diffuse3[]  = { 0.58, 0.66, 0.88, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_position1[] = { 0.0, 50.0, 0.0, 1.0 };
    GLfloat light_position2[] = { -10.0, 20.0, 5.0, 0.0 };
    GLfloat light_position3[] = { 0.0, 50.0, 0.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);

    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);

    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);

    glLightfv( GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position3);

    if(key=='1')
    {
        if(light1)
        {
            glEnable(GL_LIGHT0);
            light1=false;
        }
        else
        {
            glDisable(GL_LIGHT0);
            light1=true;
        }
    }

    if(key=='2')
    {
        if(light2)
        {
            glEnable(GL_LIGHT1);
            light2=false;
        }
        else
        {
            glDisable(GL_LIGHT1);
            light2=true;
        }
    }

    if(key=='3')
    {
        if(spotLight)
        {
            glEnable(GL_LIGHT2);
            GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10.0);
            spotLight=false;
        }
        else
        {
            glDisable(GL_LIGHT2);
            spotLight=true;
        }
    }

    if(key=='a')
    {
        if(a_bool)
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);

            glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
            glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);

            glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
            glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);

            a_bool=false;
        }
        else
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
            glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);

            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
            glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);

            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);

            a_bool=true;
        }
    }

    if(key=='d')
    {
        if(d_bool)
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
            glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);

            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
            glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);

            glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
            glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);

            d_bool=false;
        }
        else
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);

            glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
            glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);

            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);

            d_bool=true;
        }
    }

    if(key=='p')
    {
        if(s_bool)
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
            glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);

            glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
            glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);

            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);

            s_bool=false;
        }
        else
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);

            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
            glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);

            glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
            glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);

            s_bool=true;
        }
    }
}

void spe_key(int key, int x, int y)
{

	switch (key) {

        case GLUT_KEY_LEFT:
            Txval +=2;
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            Txval -=2;
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:
            Tyval -=2;
            glutPostRedisplay();
            break;

        case GLUT_KEY_DOWN:
            Tyval +=2;
            glutPostRedisplay();
            break;

        default:
			break;
	}
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1607101_Room");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(spe_key);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
