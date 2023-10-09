#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;

class BmpLoader
{
public:
    unsigned char* textureData;
    int iWidth, iHeight;

    BmpLoader(const char*);
    ~BmpLoader();

private:
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
};

BmpLoader::BmpLoader(const char* filename)
{
    FILE *file=0;
    file=fopen(filename, "rb");
    if(!file)
        cout<<"File not found"<<endl;
    fread(&bfh, sizeof(BITMAPFILEHEADER),1,file);
    if(bfh.bfType != 0x4D42)
        cout<<"Not a valid bitmap"<<endl;
    fread(&bih, sizeof(BITMAPINFOHEADER),1,file);
    if(bih.biSizeImage==0)
        bih.biSizeImage=bih.biHeight*bih.biWidth*3;
    textureData = new unsigned char[bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(textureData, 1, bih.biSizeImage, file);
    unsigned char temp;
    for(int i=0; i<bih.biSizeImage; i+=3)
    {
        temp = textureData[i];
        textureData[i] = textureData[i+2];
        textureData[i+2] = temp;

    }

    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(file);
}

BmpLoader::~BmpLoader()
{
    delete [] textureData;
}

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1280, windowWidth=800;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false, pRotate=false;

float  car1InitialX=200.0;
float  car2InitialX=-200.0;
float  car3InitialX=220.0;

float person1InitialX = 40.0, person2InitialX = 60.0, person3InitialX = 100.0, person4InitialX = -40.0, person5InitialX = -60.0, person6InitialX = -100.0;
float person7InitialZ = 4.0, person8InitialZ = -4.5;

unsigned int ID[] = {};

GLfloat spin = -0.60;
GLboolean light1=true, light2=true;

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

static GLubyte quadIndices[6][4] =
{
    {0, 3, 2, 1},
    {2, 6, 7, 3},
    {0, 4, 7, 3},
    {1, 5, 6, 2},
    {4, 7, 6, 5},
    {0, 1, 5, 4}
};

static GLfloat colors1[6][3] =
{
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 1}, //front
    {0, 1, 0},
    {1, 1, 0},
    {0, 1, 1}
};

static GLfloat colors2[6][3] =
{
    {0, 0, 1},
    {1, 0, 1},
    {0, 0, 1}, //front
    {1, 1, 0},
    {0, 1, 0},
    {1, 0, 0}
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void materialProperties(GLfloat mat_ambient[4], GLfloat mat_diffuse[4], GLfloat mat_specular[4], GLfloat mat_shininess[1])
{
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}

void drawcube()
{
    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&clrs[i][0]);
        //glColor3f(1, 1, 1);
        getNormal3p(v_rectangle[quadIndices[i][0]][0], v_rectangle[quadIndices[i][0]][1], v_rectangle[quadIndices[i][0]][2],
                    v_rectangle[quadIndices[i][1]][0], v_rectangle[quadIndices[i][1]][1], v_rectangle[quadIndices[i][1]][2],
                    v_rectangle[quadIndices[i][2]][0], v_rectangle[quadIndices[i][2]][1], v_rectangle[quadIndices[i][2]][2]);
        glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        //glColor3fv(&colors[quadIndices[i][3]][0]);
        glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
    }
    glEnd();
}

void drawcube2()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&clrs[i][0]);
        //glColor3f(1, 1, 1);
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

void mainBuilding()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[4]);

    glPushMatrix();
    glScaled(3.0, 0.05, 0.8);
    glTranslatef(-1.0, -100.0, -1.55);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[7]);

    glPushMatrix();
    glScaled(3.0, 2.05, 0.05);
    glTranslatef(-1.0, -2.4, -26.0);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[0]);

    glPushMatrix();
    glScaled(3.0, 0.5, 0.8);
    glTranslatef(-1.0, -2.5, -1.55);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    GLfloat mat_ambient[] = {0.184, 0.310, 0.310, 1.0};
    GLfloat mat_diffuse[] = {0.184, 0.310, 0.310, 1.0};
    GLfloat mat_specular[] = {0.184, 0.310, 0.310, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glScaled(1.5, 1.5, 0.05);
    glTranslatef(-0.5, -3.3, -5.0);
    drawcube2();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[6]);

    glPushMatrix();
    glScaled(5.0, 3.7, 1.0);
    glTranslatef(-1.2, -1.35, -4.27);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[5]);

    glPushMatrix();
    glScaled(2.0, 3.7, 3.0);
    glTranslatef(4.5, -1.35, -1.423);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[5]);

    glPushMatrix();
    glScaled(2.0, 3.7, 3.0);
    glTranslatef(-6.0, -1.35, -1.423);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[9]);

    glPushMatrix();
    glScaled(2.0, 0.2, 3.0);
    glTranslatef(4.5, 30.35, -1.423);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(2.0, 0.2, 3.0);
    glTranslatef(-6.0, 30.35, -1.423);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(5.0, 0.2, 1.0);
    glTranslatef(-1.2, 30.35, -4.27);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void ground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[1]);

    glPushMatrix();
    glScaled(40.0, 0.05, 20.8);
    glTranslatef(-1.5, -109.0, -2.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void footpath()
{
    GLfloat mat_ambient[] = {0.824, 0.412, 0.118, 1.0};
    GLfloat mat_diffuse[] = {0.824, 0.412, 0.118, 1.0};
    GLfloat mat_specular[] = {0.824, 0.412, 0.118, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glPushMatrix();
    glScaled(40.0, 0.05, 1.1);
    glTranslatef(-1.5, -108.0, 6.5);
    glColor3f(0.545, 0.271, 0.075);
    drawcube2();
    glPopMatrix();
}

void road()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[3]);

    glPushMatrix();
    glScaled(40.0, 0.05, 1.8);
    glTranslatef(-1.5, -109.0, 5.75);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void sky()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[2]);

    glPushMatrix();
    glScaled(40.0, 14.05, 0.05);
    glTranslatef(-1.5, -0.375, -400.0);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void sun()
{
    GLfloat mat_ambient[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glPushMatrix();
    glScaled(0.8, 1, 0.5);
    glTranslatef(-40.0, 20.0, -40.0);
    glutSolidSphere(2.0, 20, 30);
    glPopMatrix();
}

void windmillBlades()
{
    glBegin(GL_POLYGON);

    glVertex3f(-0.3, 0.3, 0);
    glVertex3f(0.3, 0.3, 0);
    glVertex3f(0.3, 3.3, 0);
    glVertex3f(0, 4.3, 0);
    glVertex3f(-0.3, 3.3, 0);

    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(0.3, 0.3, 0);
    glVertex3f(0.3, -0.3, 0);
    glVertex3f(3.3, -0.3, 0);
    glVertex3f(4.3, 0.0, 0);
    glVertex3f(3.3, 0.3, 0);

    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(-0.3, 0.3, 0);
    glVertex3f(-3.3, 0.3, 0);
    glVertex3f(-4.3, 0.0, 0);
    glVertex3f(-3.3, -0.3, 0);
    glVertex3f(-0.3, -0.3, 0);

    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(-0.3, -0.3, 0);
    glVertex3f(-0.3, -3.3, 0);
    glVertex3f(0, -4.3, 0);
    glVertex3f(0.3, -3.3, 0);
    glVertex3f(0.3, -0.3, 0);

    glEnd();
}

void windmillPole()
{
    glBegin(GL_POLYGON);

    glVertex3f(-0.4, 0.5, 0);
    glVertex3f(-0.4, -6.0, 0);
    glVertex3f(0.4, -6.0, 0);
    glVertex3f(0.4, 0.5, 0);

    glEnd();
}

void treeStructure()
{
    GLfloat mat_ambient[] = {0.000, 0.392, 0.000, 1.0};
    GLfloat mat_diffuse[] = {0.000, 0.392, 0.000, 1.0};
    GLfloat mat_specular[] = {0.000, 0.392, 0.000, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0.5);

    glVertex3f(0, 5.5, 0);
    glVertex3f(-1.0, 0, 0);
    glVertex3f(1.0, 0, 0);

    glVertex3f(0, 5.5, 0);
    glVertex3f(-1.0, 1.0, 0);
    glVertex3f(1.0, 1.0, 0);

    glVertex3f(0, 5.5, 0);
    glVertex3f(-1.0, 2.0, 0);
    glVertex3f(1.0, 2.0, 0);

    glEnd();

    GLfloat mat_ambient1[] = {0.545, 0.271, 0.075, 1.0};
    GLfloat mat_diffuse1[] = {0.545, 0.271, 0.075, 1.0};
    GLfloat mat_specular1[] = {0.545, 0.271, 0.075, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glBegin(GL_QUADS);

    glColor3f(0, 0, 1);

    glVertex3f(-0.15, 0.0, 0);
    glVertex3f(-0.15, -1.0, 0);
    glVertex3f(0.15, -1.0, 0);
    glVertex3f(0.15, 0.0, 0);

    glEnd();
}

void tree1()
{
    glPushMatrix();
    glTranslatef(-9.0, -4.4, 6.00);
    treeStructure();
    glPopMatrix();
}

void tree2()
{
    glPushMatrix();
    glTranslatef(12.0, -4.4, 6.00);
    treeStructure();
    glPopMatrix();
}

void tree3()
{
    glPushMatrix();
    glTranslatef(-15.0, -4.4, 6.00);
    treeStructure();
    glPopMatrix();
}

void carStructure()
{
    GLfloat mat_ambient[] = {0.647, 0.165, 0.165, 1.0};
    GLfloat mat_diffuse[] = {0.647, 0.165, 0.165, 1.0};
    GLfloat mat_specular[] = {0.647, 0.165, 0.165, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0.5);

    glVertex3f(-5, 0, 0.9);
    glVertex3f(5, 0, 0.9);
    glVertex3f(4.0, 1.8, 0.9);
    glVertex3f(-4.0, 1.8, 0.9);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0.5);

    glVertex3f(-5, 0, -1.1);
    glVertex3f(5, 0, -1.1);
    glVertex3f(4.0, 1.8, -1.1);
    glVertex3f(-4.0, 1.8, -1.1);

    glEnd();

    GLfloat mat_ambient1[] = {0.502, 0.000, 0.000, 1.0};
    GLfloat mat_diffuse1[] = {0.502, 0.000, 0.000, 1.0};
    GLfloat mat_specular1[] = {0.502, 0.000, 0.000, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glBegin(GL_POLYGON);

    glColor3f(0, 0, 0.5);

    glVertex3f(-4.0, 1.8, 0.9);
    glVertex3f(4.0, 1.8, 0.9);
    glVertex3f(4.0, 1.8, -1.1);
    glVertex3f(-4.0, 1.8, -1.1);

    glEnd();

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);
    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0);

    glVertex3f(-7.0, 0, 0.9);
    glVertex3f(-7.0, -2.5, 0.9);
    glVertex3f(7.0, -2.5, 0.9);
    glVertex3f(7.0, 0, 0.9);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(1, 0, 1);

    glVertex3f(-7.0, 0, -1.1);
    glVertex3f(-7.0, -2.5, -1.1);
    glVertex3f(7.0, -2.5, -1.1);
    glVertex3f(7.0, 0, -1.1);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(1, 1, 0);

    glVertex3f(-7.0, -2.5, 0.9);
    glVertex3f(7.0, -2.5, 0.9);
    glVertex3f(7.0, -2.5, -1.1);
    glVertex3f(-7.0, -2.5, -1.1);

    glEnd();

    GLfloat mat_ambient2[] = {0.184, 0.310, 0.310, 1.0};
    GLfloat mat_diffuse2[] = {0.184, 0.310, 0.310, 1.0};
    GLfloat mat_specular2[] = {0.184, 0.310, 0.310, 1.0};
    GLfloat mat_shininess2[] = {60};

    materialProperties(mat_ambient2, mat_diffuse2, mat_specular2, mat_shininess2);

    glBegin(GL_POLYGON);

    glColor3f(0, 0, 1);

    glVertex3f(-7.0, 0, -1.1);
    glVertex3f(-7.0, -2.5, -1.1);
    glVertex3f(-7.0, -2.5, 0.9);
    glVertex3f(-7.0, 0, 0.9);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 0, 1);

    glVertex3f(7.0, 0, -1.1);
    glVertex3f(7.0, -2.5, -1.1);
    glVertex3f(7.0, -2.5, 0.9);
    glVertex3f(7.0, 0, 0.9);

    glEnd();

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);

    glVertex3f(-7.0, 0, -1.1);
    glVertex3f(-7.0, 0, 0.9);
    glVertex3f(-5.0, 0, 0.9);
    glVertex3f(-5.0, 0, -1.1);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);

    glVertex3f(5.0, 0, -1.1);
    glVertex3f(5.0, 0, 0.9);
    glVertex3f(7.0, 0, 0.9);
    glVertex3f(7.0, 0, -1.1);

    glEnd();

    GLfloat mat_ambient3[] = {0.412, 0.412, 0.412, 1.0};
    GLfloat mat_diffuse3[] = {0.412, 0.412, 0.412, 1.0};
    GLfloat mat_specular3[] = {0.412, 0.412, 0.412, 1.0};
    GLfloat mat_shininess3[] = {60};

    materialProperties(mat_ambient3, mat_diffuse3, mat_specular3, mat_shininess3);

    glBegin(GL_POLYGON);

    glColor3f(0, 0, 1);

    glVertex3f(-5.0, 0, -1.1);
    glVertex3f(-5.0, 0, 0.9);
    glVertex3f(-4.0, 1.8, 0.9);
    glVertex3f(-4.0, 1.8, -1.1);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 0, 1);

    glVertex3f(4.0, 1.8, -1.1);
    glVertex3f(4.0, 1.8, 0.9);
    glVertex3f(5.0, 0, 0.9);
    glVertex3f(5.0, 0, -1.1);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0.5);

    glVertex3f(-4.5, 0.3, 1.0);
    glVertex3f(-0.1, 0.3, 1.0);
    glVertex3f(-0.1, 1.5, 1.0);
    glVertex3f(-3.8, 1.5, 1.0);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0.5);

    glVertex3f(0.1, 0.3, 1.0);
    glVertex3f(4.5, 0.3, 1.0);
    glVertex3f(3.8, 1.5, 1.0);
    glVertex3f(0.1, 1.5, 1.0);

    glEnd();

    GLfloat mat_ambient4[] = {0, 0, 0, 1.0};
    GLfloat mat_diffuse4[] = {0, 0, 0, 1.0};
    GLfloat mat_specular4[] = {0, 0, 0, 1.0};
    GLfloat mat_shininess4[] = {60};

    materialProperties(mat_ambient4, mat_diffuse4, mat_specular4, mat_shininess4);

    //wheels
    int triangleAmount = 20;
    GLfloat twicePi = 2.0 * 3.14159;

    glTranslatef(0, 0, 0.95);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-4.0, -2.5); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            -4.0 + (1 * cos(i *  twicePi / triangleAmount)),
            -2.5 + (1 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(4.0, -2.5); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            4.0 + (1 * cos(i *  twicePi / triangleAmount)),
            -2.5 + (1 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glTranslatef(0, 0, -1.9);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-4.0, -2.5); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            -4.0 + (1 * cos(i *  twicePi / triangleAmount)),
            -2.5 + (1 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(4.0, -2.5); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            4.0 + (1 * cos(i *  twicePi / triangleAmount)),
            -2.5 + (1 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void car1()
{
    car1InitialX-=0.1;
    if(car1InitialX<-200.0)
        car1InitialX=200.0;

    glPushMatrix();
    glScaled(0.3, 0.5, 0.5);
    glTranslated(car1InitialX, -7.15, 24.00);
    carStructure();
    glPopMatrix();
}

void car2()
{
    car2InitialX+=0.1;
    if(car2InitialX>200.0)
        car2InitialX=-200.0;

    glPushMatrix();
    glScaled(0.3, 0.5, 0.5);
    glTranslated(car2InitialX, -7.15, 29.00);
    carStructure();
    glPopMatrix();
}

void car3()
{
    car3InitialX-=0.1;
    if(car3InitialX<-220.0)
        car3InitialX=220.0;

    glPushMatrix();
    glScaled(0.3, 0.5, 0.5);
    glTranslated(car3InitialX, -7.15, 24.00);
    carStructure();
    glPopMatrix();
}

void personStructure()
{
    GLfloat mat_ambient[] = {1.000, 0.271, 0.000, 1.0};
    GLfloat mat_diffuse[] = {1.000, 0.271, 0.000, 1.0};
    GLfloat mat_specular[] = {1.000, 0.271, 0.000, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0);
    glVertex3f(-0.3, 1.2, 3);
    glVertex3f(-0.3, 0, 3);
    glVertex3f(0.3, 0, 3);
    glVertex3f(0.3, 1.2, 3);

    glEnd();

    GLfloat mat_ambient1[] = {0.282, 0.239, 0.545, 1.0};
    GLfloat mat_diffuse1[] = {0.282, 0.239, 0.545, 1.0};
    GLfloat mat_specular1[] = {0.282, 0.239, 0.545, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(-0.2, 0, 3);
    glVertex3f(-0.2, -1.5, 3);
    glVertex3f(0.2, -1.5, 3);
    glVertex3f(0.2, 0, 3);

    glEnd();

    GLfloat mat_ambient2[] = {1.000, 0.871, 0.678, 1.0};
    GLfloat mat_diffuse2[] = {1.000, 0.871, 0.678, 1.0};
    GLfloat mat_specular2[] = {1.000, 0.871, 0.678, 1.0};
    GLfloat mat_shininess2[] = {60};

    materialProperties(mat_ambient2, mat_diffuse2, mat_specular2, mat_shininess2);

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(-0.3, 1.2, 3);
    glVertex3f(-0.5, 0.2, 3);
    glVertex3f(-0.3, 0.2, 3);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(0.3, 1.2, 3);
    glVertex3f(0.3, 0.2, 3);
    glVertex3f(0.5, 0.2, 3);

    glEnd();

    int triangleAmount = 20;
    GLfloat twicePi = 2.0 * 3.14159;

    glTranslatef(0, 0, 3.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 1.6); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            0.0 + (0.4 * cos(i *  twicePi / triangleAmount)),
            1.6 + (0.4 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void person1()
{
    person1InitialX-=0.007;
    if(person1InitialX<-40.0)
        person1InitialX=40.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(person1InitialX, -6.2, 5.0);
    personStructure();
    glPopMatrix();
}

void person2()
{
    person2InitialX-=0.007;
    if(person2InitialX<-60.0)
        person2InitialX=60.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(person2InitialX, -6.2, 5.0);
    personStructure();
    glPopMatrix();
}

void person3()
{
    person3InitialX-=0.007;
    if(person3InitialX<-100.0)
        person3InitialX=100.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(person3InitialX, -6.2, 5.0);
    personStructure();
    glPopMatrix();
}

void person4()
{
    person4InitialX+=0.007;
    if(person4InitialX>40.0)
        person4InitialX=-40.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(person4InitialX, -6.2, 6.0);
    personStructure();
    glPopMatrix();
}

void person5()
{
    person5InitialX+=0.007;
    if(person5InitialX>60.0)
        person5InitialX=-60.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(person5InitialX, -6.2, 6.0);
    personStructure();
    glPopMatrix();
}

void person6()
{
    person6InitialX+=0.007;
    if(person6InitialX>100.0)
        person6InitialX=-100.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(person6InitialX, -6.2, 6.0);
    personStructure();
    glPopMatrix();
}

void person7()
{
    person7InitialZ-=0.004;
    if(person7InitialZ<-5.0)
        person7InitialZ=4.0;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(-2.8, -5.5, person7InitialZ);
    personStructure();
    glPopMatrix();
}

void person8()
{
    person8InitialZ+=0.004;
    if(person8InitialZ>3.9)
        person8InitialZ=-4.5;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(6.75, -5.5, person8InitialZ);
    personStructure();
    glPopMatrix();
}

void windmill1()
{
    GLfloat mat_ambient[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_diffuse[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_specular[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glPushMatrix();
    glTranslatef(-30.0, 1.0, -18.0);
    windmillPole();
    glPopMatrix();

    GLfloat mat_ambient1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glPushMatrix();
    glTranslatef(-30.0, 1.0, -17.9);
    glRotatef(theta, 0, 0, 1);
    windmillBlades();
    glColor3f(1, 0, 0);
    glutSolidTorus(0.15, 0.3, 10, 100);
    glPopMatrix();
}

void windmill2()
{
    GLfloat mat_ambient[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_diffuse[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_specular[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glPushMatrix();
    glTranslatef(-40.0, 1.0, -18.0);
    windmillPole();
    glPopMatrix();

    GLfloat mat_ambient1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glPushMatrix();
    glTranslatef(-40.0, 1.0, -17.9);
    glRotatef(theta, 0, 0, 1);
    windmillBlades();
    glColor3f(1, 0, 0);
    glutSolidTorus(0.15, 0.3, 10, 100);
    glPopMatrix();
}

void windmill3()
{
    GLfloat mat_ambient[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_diffuse[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_specular[] = {0.502, 0.502, 0.502, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glPushMatrix();
    glTranslatef(-50.0, 1.0, -18.0);
    windmillPole();
    glPopMatrix();

    GLfloat mat_ambient1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glPushMatrix();
    glTranslatef(-50.0, 1.0, -17.9);
    glRotatef(theta, 0, 0, 1);
    windmillBlades();
    glColor3f(1, 0, 0);
    glutSolidTorus(0.15, 0.3, 10, 100);
    glPopMatrix();
}

void building2()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[10]);

    glPushMatrix();
    glScaled(4.0, 8.5, 3.0);
    glTranslatef(4.0, -0.6, -1.8);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[11]);

    glPushMatrix();
    glScaled(4.0, 0.2, 3.0);
    glTranslatef(4.0, 102.0, -1.8);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawScene()
{
    sky();
    //sun();

    windmill1();
    windmill2();
    windmill3();

    ground();
    footpath();
    road();

    mainBuilding();
    building2();

    tree1();
    tree2();
    tree3();

    car1();
    car2();
    car3();

    person1();
    person2();
    person3();
    person4();
    person5();
    person6();
    person7();
    person8();
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
    gluLookAt(0,5.5,25, 0,0,0, 0,1,0);

    glViewport(0, 0, windowHeight, windowWidth);
    glPushMatrix();
    //glTranslatef(0,0,Tzval);
    glTranslatef(Txval,Tyval,Tzval);
    glRotatef( alpha, 0.0, axis_y, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 1.0 );
    drawScene();

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

int rotationVar = 0;

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        //uRotate = false;

        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        //bRotate = false;
        axis_y=1.0;

        break;

    case 'p':
        pRotate = !pRotate;
        //bRotate = false;
        //uRotate = false;
        axis_y=1.0;

        break;

    case '=':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:	// Escape key
        exit(1);
    }

    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_position[] = { 20.0, 30.0, 10.0, 1.0 };
    GLfloat light_position1[] = { 0.0, 0.0, 20.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

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
}

void spe_key(int key, int x, int y)
{

    switch (key)
    {

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
        alpha += 0.05;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (pRotate == true)
    {
        alpha -= 0.05;
        if(alpha < -360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    glutPostRedisplay();

}

void LoadTexture(const char*filename,int num)
{
    glGenTextures(1, &ID[num]);
    glBindTexture(GL_TEXTURE_2D,  ID[num]);
    glPixelStorei(GL_UNPACK_ALIGNMENT,  ID[num]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1607101_Project");

    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\brick.bmp",0);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\grass.bmp",1);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\day_sky.bmp",2);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\road.bmp",3);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\building_basement.bmp",4);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\main_building.bmp",5);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\main_building_middle.bmp",6);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\glass_door.bmp",7);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\top_of_gate.bmp",8);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\roof.bmp",9);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\building2.bmp",10);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\roof2.bmp",11);

    glClearColor(0,0,0,1);

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
