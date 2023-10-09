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

//bed
void drawcube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glColor3fv(&colors[quadIndices[i][0]][0]);
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
        glColor3fv(&colors2[quadIndices[i][0]][0]);
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
        glColor3fv(&colors3[quadIndices[i][0]][0]);
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
        glColor3fv(&colors3[quadIndices[i][0]][0]);
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
        glColor3fv(&colors3[quadIndices[i][0]][0]);
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
        glColor3fv(&colors[quadIndices[i][0]][0]);
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
        glColor3fv(&colors[quadIndices[i][0]][0]);
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
        glColor3f(1,1,1);
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
        glColor3f(0,0,0);
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
        glColor3fv(&colors4[quadIndices[i][0]][0]);
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
        glColor3fv(&colors5[quadIndices[i][0]][0]);
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
        glColor3fv(&colors5[quadIndices[i][0]][0]);
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
        glColor3fv(&colors6[quadIndices[i][0]][0]);
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
        glColor3fv(&colors7[quadIndices[i][0]][0]);
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
        glColor3fv(&colors8[quadIndices[i][0]][0]);
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
        glColor3fv(&colors9[quadIndices[i][0]][0]);
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
        glColor3fv(&colors10[quadIndices[i][0]][0]);
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
        glColor3fv(&colors11[quadIndices[i][0]][0]);
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
    /*glPushMatrix();
    glScaled(1.5, 0.2, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 0, -.5);
    glRotatef( theta, axis_x, axis_y, 0.0);
    drawcube();
    glPopMatrix();*/

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

    //left wall
    glPushMatrix();
    glScaled(.1, 1.9, 2.75);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-60.0, 0, -.5);
    drawcube11();
    glPopMatrix();

    //right wall
    glPushMatrix();
    glScaled(3.4, 1.9, .1);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-1.75, 0, -16.8);
    drawcube12();
    glPopMatrix();

    //fan
    glPushMatrix();
    glScaled(0.05, 0.2, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-25.0, 25.5, 40.0);
    v_fan2();
    glPopMatrix();

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

    //ac
    glPushMatrix();
    glScaled(0.24, 0.3, 0.7);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-24.0, 13.0, 1.0);
    v_ac();
    glPopMatrix();

    //bed leg
    glPushMatrix();
    glScaled(1.5, 0.2, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 0, -.5);
    drawcube();
    glPopMatrix();

    //bed sheet
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube2();
    glPopMatrix();

    //blanket
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube3();
    glPopMatrix();

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

    //carpet
    glPushMatrix();
    glScaled(0.8, 0.1, 4.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(0.5, -0.9, 0);
    carpet();
    glPopMatrix();

    //bed head
    glPushMatrix();
    glScaled(1.5, 0.1, 2.5);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-2.0, 5.05, -.5);
    drawcube6();
    glPopMatrix();

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

    //almirah
    glPushMatrix();
    glScaled(0.25, 1.7, 0.8);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-20.0, 0, 4.7);
    drawcube10();
    glPopMatrix();

    //picture
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -30.0);
    v_window();
    glPopMatrix();

    //picture2
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -29.999);
    glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 1);
        glVertex3f(3, 3, 3);
        glVertex3f(0, 0, 3);
        glVertex3f(3, 0, 3);
    glEnd();
    glPopMatrix();

    //picture3
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -29.999);
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(1.5, 1.5, 3);
        glVertex3f(3, 3, 3);
        glVertex3f(0, 3, 3);
    glEnd();
    glPopMatrix();

    //picture4
    glPushMatrix();
    glScaled(0.4, 0.5, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-3.3, 6.0, -29.999);
    glBegin(GL_TRIANGLES);
        glColor3f(1.000, 0.843, 0.000);
        glVertex3f(1.5, 1.5, 3);
        glVertex3f(0, 3, 3);
        glVertex3f(0, 0, 3);
    glEnd();
    glPopMatrix();

    //window
    glPushMatrix();
    glScaled(0.8, 0.7, 0.05);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(2.0, 4.0, -30.0);
    v_window();
    glPopMatrix();

    //wardrobe2
    glPushMatrix();
    glScaled(1.0, 0.9, 0.2);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-6.0, 0, -4.0);
    drawcube();
    glPopMatrix();

    //rig
    glPushMatrix();
    glScaled(0.1, 5.2, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(-43.6, -0.02, 16.5);
    drawcube9();
    glPopMatrix();

    //rig2
    glPushMatrix();
    glScaled(0.015, 2.2, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(188.6, 1.25, -4.52);
    drawcube9();
    glPopMatrix();

    //rig3
    glPushMatrix();
    glScaled(0.011, 2.2, 0.3);
    //glRotatef(180, 0, 0, 1);
    glTranslatef(230.6, -0.08, -2.5);
    drawcube9();
    glPopMatrix();

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

    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(spe_key);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
