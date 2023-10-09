#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

const double PI = 3.14159265389;


/* GLUT callback Handlers */


int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;
int wired=0;
int shcpt=0;
int animat = 0;
const int L=15;
const int L2=11;
const int L3=10;
const int dgre=3;
int ncpt=L+1;
int ncpt2=L2+1;
int ncpt3=L3+1;
int clikd=0;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;

void *currentfont;

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);

	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void helpscreen()
{
setFont(GLUT_BITMAP_TIMES_ROMAN_24);
//glClearColor(0,0,0,0);/*background for cover page*/
//glClear(GL_COLOR_BUFFER_BIT);
drawstring(0.0,35.0,-15.0,"ROLL: 1607101");
drawstring(0.0,31.0,-15.0,"Left / Right: '<-' / '->'");
drawstring(0.0,27.0,-15.0,"Zoom IN / OUT: '=' / '-'");
drawstring(0.0,23.0,-15.0,"Traffic (ON / OFF): 'g'");
drawstring(0.0,19.0,-15.0,"Rotation: 'r' / 'p'");

drawstring(-40.0,31.0,-15.0,"Windmill blades: 's'");
drawstring(-40.0,27.0,-15.0,"Supershop gate: 'h' / 'j'");
drawstring(-40.0,23.0,-15.0,"Day Light: '1'");

drawstring(40.0,23.0,-15.0,"Mobileshop gate: 'k' / 'l'");
drawstring(40.0,19.0,-15.0,"Night Light: '2'");
drawstring(40.0,15.0,-15.0,"Lamp Light: '3'");
}

GLfloat ctrlpoints[L+1][3] =
{
    {4.725, 0.099, 0}, {4.675, 0.049, 0},
    {4.625, -0.075, 0}, {4.55, -0.2, 0},
    {4.575, -0.325, 0}, {4.375, -0.525, 0},
    {4.125, -0.65, 0}, {3.9, -0.725, 0},
    {3.675, -0.875, 0}, {3.55, -1.075, 0},
    {3.4, -1.475, 0}, {3.3, -1.7, 0},
    {3.2, -1.975, 0}, {3.05, -1.925, 0},
    {2.95, -1.725, 0}, {2.875, -1.475, 0},
};

GLfloat ctrlpoints2[L2+1][3] =
{
    {2.775, -1.45, 0.0}, {2.575, -1.45, 0.0},
    {2.275, -1.45, 0.0}, {1.975, -1.4, 0.0},
    {1.725, -1.4, 0.0}, {1.45, -1.35, 0.0},
    {1.125, -1.275, 0.0}, {0.775, -1.125, 0.0},
    {0.55, -0.85, 0.0}, {0.375, -0.6, 0.0},
    {0.2, -0.325, 0.0}, {0,0,0}

};

GLfloat ctrlpoints3[L3+1][3] =
{
    {0.0, 0.0, 0.0}, {0.125, -0.55, 0.0},
    {0.3, -1.3, 0.0}, {0.55, -1.95, 0.0},
    {0.85, -2.675, 0.0}, {1.15, -3.1, 0.0},
    {1.475, -3.6, 0.0}, {1.85, -4.075, 0.0},
    {2.4, -4.625, 0.0}, {2.6, -4.95, 0.0},
    {2.825, -5.125, 0.0}
};

double ex=0, ey=0, ez=15, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

float wcsClkDn[3],wcsClkUp[3];
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];
int flag=0;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info

//////////////////////////
void scsToWcs(float sx,float sy, float wcsv[3] );

void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;
}

//control points
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

void BezierCurve2 ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L2; i++)
    {
        int ncr=nCr(L2,i);
        double oneMinusTpow=pow(1-t,double(L2-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints2[i][0];
        y+=coef*ctrlpoints2[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

void BezierCurve3 ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L3; i++)
    {
        int ncr=nCr(L3,i);
        double oneMinusTpow=pow(1-t,double(L3-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints3[i][0];
        y+=coef*ctrlpoints3[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

///////////////////////
void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
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

    glNormal3f(-Nx,-Ny,-Nz);
}

void lightBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void lightHolderBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints2[L2][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve2( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve2( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void antennaBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints3[L3][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve3( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve3( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i
}

void showControlPoints()
{
    glPointSize(5.0);
    //glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}

void showControlPoints2()
{
    glPointSize(5.0);
    //glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L2; i++)
        glVertex3fv(&ctrlpoints2[i][0]);
    glEnd();
}

void draw_cylinder(GLfloat radius,
                   GLfloat height)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    //glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    //glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

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
float  car4InitialX=-240.0;

float person1InitialX = 40.0, person2InitialX = 60.0, person3InitialX = 100.0,
person4InitialX = -40.0, person5InitialX = -60.0, person6InitialX = -100.0, person9InitialX=80.0,
person10InitialX=50.0;
float person7InitialZ = 4.0, person8InitialZ = -4.5, person11InitialZ=-5.0,
person12InitialZ=-1.7, person14InitialZ=-1.7, person15InitialZ=-5.0;

float gate1L=-21.65, gate1R=-18.6, gate2L=26.75, gate2R=29.8;

unsigned int ID[] = {};

GLfloat spin = -0.60;
GLboolean light1=true, light2=true, light3=true, carControl=true, gate1=false, gate1C=false, gate2=false, gate2C=false;

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

void drawcube3()
{
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&clrs[i][0]);
        //glColor3f(0, 0, 0);
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

void superShop()
{
    //base
    glPushMatrix();
    glScaled(9.0, 0.05, 3.0);
    glTranslatef(-4.5, -106.0, -1.55);
    drawcube();
    glPopMatrix();

    //back
    glPushMatrix();
    glScaled(9.0, 3.0, 0.05);
    glTranslatef(-4.5, -1.8, -95.55);
    drawcube();
    glPopMatrix();

    //left
    glPushMatrix();
    glScaled(0.05, 3.0, 3.0);
    glTranslatef(-810.0, -1.8, -1.55);
    drawcube();
    glPopMatrix();

    //right
    glPushMatrix();
    glScaled(0.05, 3.0, 3.0);
    glTranslatef(-273.0, -1.8, -1.55);
    drawcube();
    glPopMatrix();

    //roof
    glPushMatrix();
    glScaled(9.0, 0.05, 3.0);
    glTranslatef(-4.5, 70.0, -1.55);
    drawcube();
    glPopMatrix();

    //counter
    glPushMatrix();
    glScaled(1.0, 1.0, 0.2);
    glTranslatef(-16.7, -5.0, -17.5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2, 1.0, 0.5);
    glTranslatef(-83.5, -5.0, -9.0);
    drawcube();
    glPopMatrix();

    //shelf1
    glPushMatrix();
    glScaled(6.0, 2.0, 0.2);
    glTranslatef(-6.75, -2.56, -23.5);
    drawcube();
    glPopMatrix();

    //shelf1sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[13]);

    glPushMatrix();
    glScaled(6.0, 2.0, 0.03);
    glTranslatef(-6.75, -2.56, -136.0);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //shelf2
    glPushMatrix();
    glScaled(0.4, 2.0, 1.5);
    glTranslatef(-101.25, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf2sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[13]);

    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-1310.0, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //shelf3
    glPushMatrix();
    glScaled(0.4, 2.0, 1.5);
    glTranslatef(-85.25, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf3sub1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[13]);

    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-1096.7, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf3sub2
    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-1139.6, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //shelf4
    glPushMatrix();
    glScaled(0.4, 2.0, 1.5);
    glTranslatef(-69.25, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf4sub1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[13]);

    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-883.4, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf4sub2
    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-926.3, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //shelf5
    glPushMatrix();
    glScaled(0.4, 2.0, 1.5);
    glTranslatef(-53.25, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf5sub1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[13]);

    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-670.1, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    //shelf5sub2
    glPushMatrix();
    glScaled(0.03, 2.0, 1.5);
    glTranslatef(-713.0, -2.56, -1.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //upper gate wall
    glPushMatrix();
    glScaled(9.0, 1.5, 0.05);
    glTranslatef(-4.5, -0.6, 84.0);
    drawcube();
    glPopMatrix();

    //right gate
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[12]);

    if(gate1) gate1R+=0.003;
    if(gate1R>-15.8) gate1=false;

    if(gate1C) gate1R-=0.003;
    if(gate1R<-18.61) gate1C=false;

    glPushMatrix();
    glScaled(1.45, 1.5, 0.05);
    glTranslatef(gate1R, -3.5, 82.0);
    drawcube();
    glPopMatrix();

    //left gate
    if(gate1) gate1L-=0.003;
    if(gate1L<-24.45) gate1=false;

    if(gate1C) gate1L+=0.003;
    if(gate1L>-21.66) gate1C=false;

    glPushMatrix();
    glScaled(1.45, 1.5, 0.05);
    glTranslatef(gate1L, -3.5, 82.0);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //right gate wall
    glPushMatrix();
    glScaled(3.0, 1.5, 0.05);
    glTranslatef(-7.5, -3.5, 84.0);
    drawcube();
    glPopMatrix();

    //left gate wall
    glPushMatrix();
    glScaled(3.0, 1.5, 0.05);
    glTranslatef(-13.5, -3.5, 84.0);
    drawcube();
    glPopMatrix();
}

void phoneLeft()
{
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, 1.5);
    glVertex3f(0, -1, 1.5);
    glVertex3f(4, 3, 1.5);
    glVertex3f(3, 4, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, -1.5);
    glVertex3f(0, -1, -1.5);
    glVertex3f(4, 3, -1.5);
    glVertex3f(3, 4, -1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, -1.5);
    glVertex3f(-1, 0, 1.5);
    glVertex3f(3, 4, 1.5);
    glVertex3f(3, 4, -1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, -1, -1.5);
    glVertex3f(0, -1, 1.5);
    glVertex3f(4, 3, 1.5);
    glVertex3f(4, 3, -1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, -1.5);
    glVertex3f(0, -1, -1.5);
    glVertex3f(0, -1, 1.5);
    glVertex3f(-1, 0, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(3, 4, -1.5);
    glVertex3f(4, 3, -1.5);
    glVertex3f(4, 3, 1.5);
    glVertex3f(3, 4, 1.5);
    glEnd();
}

void phoneRight()
{
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_shininess[] = {60};

    materialProperties(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

    glBegin(GL_POLYGON);
    glVertex3f(-4, 3, 1.5);
    glVertex3f(0, -1, 1.5);
    glVertex3f(1, 0, 1.5);
    glVertex3f(-3, 4, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-4, 3, -1.5);
    glVertex3f(0, -1, -1.5);
    glVertex3f(1, 0, -1.5);
    glVertex3f(-3, 4, -1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-4, 3, -1.5);
    glVertex3f(0, -1, -1.5);
    glVertex3f(0, -1, 1.5);
    glVertex3f(-4, 3, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-3, 4, 1.5);
    glVertex3f(1, 0, 1.5);
    glVertex3f(1, 0, -1.5);
    glVertex3f(-3, 4, -1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-3, 4, -1.5);
    glVertex3f(-4, 3, -1.5);
    glVertex3f(-4, 3, 1.5);
    glVertex3f(-3, 4, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, 0, -1.5);
    glVertex3f(0, -1, -1.5);
    glVertex3f(0, -1, 1.5);
    glVertex3f(1, 0, 1.5);
    glEnd();
}

void tvShop()
{
    //base
    glPushMatrix();
    glScaled(9.0, 0.05, 3.0);
    glTranslatef(3.3, -106.0, -1.55);
    drawcube();
    glPopMatrix();

    //back
    glPushMatrix();
    glScaled(9.0, 3.0, 0.05);
    glTranslatef(3.3, -1.8, -95.55);
    drawcube();
    glPopMatrix();

    //left
    glPushMatrix();
    glScaled(0.05, 3.0, 3.0);
    glTranslatef(594.0, -1.8, -1.55);
    drawcube();
    glPopMatrix();

    //right
    glPushMatrix();
    glScaled(0.05, 3.0, 3.0);
    glTranslatef(1131.0, -1.8, -1.55);
    drawcube();
    glPopMatrix();

    //roof
    glPushMatrix();
    glScaled(9.0, 0.05, 3.0);
    glTranslatef(3.3, 70.0, -1.55);
    drawcube();
    glPopMatrix();

    //counter
    glPushMatrix();
    glScaled(1.0, 1.0, 0.2);
    glTranslatef(53.55, -5.0, -17.5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2, 1.0, 0.5);
    glTranslatef(267.75, -5.0, -9.0);
    drawcube();
    glPopMatrix();

    //back tv1
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(31.0, 0.0, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv1 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(31.0, 0.0, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv2
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(36.0, 0.0, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv2 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(36.0, 0.0, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv3
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(41.0, 0.0, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv3 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(41.0, 0.0, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv4
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(46.0, 0.0, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv4 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(46.0, 0.0, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv5
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(46.0, -4.5, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv5 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(46.0, -4.5, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv6
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(41.0, -4.5, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv6 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(41.0, -4.5, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv7
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(36.0, -4.5, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv7 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(36.0, -4.5, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //back tv8
    glPushMatrix();
    glScaled(1.0, 0.7, 0.05);
    glTranslatef(31.0, -4.5, -90.55);
    drawcube3();
    glPopMatrix();

    //back tv8 sub
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[17]);

    glPushMatrix();
    glScaled(1.0, 0.7, 0.02);
    glTranslatef(31.0, -4.5, -221.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glScaled(1.0, 1.0, 0.5);
    glTranslatef(33.0, -5.0, -2.0);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(337.0, -19.0, 2.0);
    phoneLeft();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(337.0, -19.0, -10.0);
    phoneLeft();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(352.0, -19.0, 2.0);
    phoneRight();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(352.0, -19.0, -10.0);
    phoneRight();
    glPopMatrix();

    glPushMatrix();
    glScaled(1.0, 1.0, 0.5);
    glTranslatef(40.0, -5.0, -2.0);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(407.0, -19.0, 2.0);
    phoneLeft();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(407.0, -19.0, -10.0);
    phoneLeft();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(422.0, -19.0, 2.0);
    phoneRight();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(422.0, -19.0, -10.0);
    phoneRight();
    glPopMatrix();

    glPushMatrix();
    glScaled(1.0, 1.0, 0.5);
    glTranslatef(47.0, -5.0, -2.0);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(477.0, -19.0, 2.0);
    phoneLeft();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(477.0, -19.0, -10.0);
    phoneLeft();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(492.0, -19.0, 2.0);
    phoneRight();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.1, 0.1, 0.05);
    glTranslatef(492.0, -19.0, -10.0);
    phoneRight();
    glPopMatrix();

    //upper gate wall
    glPushMatrix();
    glScaled(9.0, 1.5, 0.05);
    glTranslatef(3.3, -0.6, 84.0);
    drawcube();
    glPopMatrix();

    //right gate
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[12]);

    if(gate2) gate2R+=0.003;
    if(gate2R>32.6) gate1=false;

    if(gate2C) gate2R-=0.003;
    if(gate2R<29.81) gate2C=false;

    glPushMatrix();
    glScaled(1.45, 1.5, 0.05);
    glTranslatef(gate2R, -3.5, 82.5);
    drawcube();
    glPopMatrix();

    //left gate
    if(gate2) gate2L-=0.003;
    if(gate2L<23.95) gate2=false;

    if(gate2C) gate2L+=0.003;
    if(gate2L>26.76) gate2C=false;

    glPushMatrix();
    glScaled(1.45, 1.5, 0.05);
    glTranslatef(gate2L, -3.5, 82.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //right gate wall
    glPushMatrix();
    glScaled(3.0, 1.5, 0.05);
    glTranslatef(9.9, -3.5, 84.0);
    drawcube();
    glPopMatrix();

    //left gate wall
    glPushMatrix();
    glScaled(3.0, 1.5, 0.05);
    glTranslatef(15.9, -3.5, 84.0);
    drawcube();
    glPopMatrix();
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
    /*glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID[1]);*/

    glPushMatrix();
    glScaled(40.0, 0.05, 20.8);
    glTranslatef(-1.5, -109.0, -2.5);
    drawcube();
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
}

void footpath()
{
    GLfloat mat_ambient[] = {0.980, 0.980, 0.824, 1.0};
    GLfloat mat_diffuse[] = {0.980, 0.980, 0.824, 1.0};
    GLfloat mat_specular[] = {0.980, 0.980, 0.824, 1.0};
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
    if(carControl)
    {
        car1InitialX-=0.3;
    }
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
    if(carControl)
    {
        car2InitialX+=0.3;
    }
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
    if(carControl)
    {
        car3InitialX-=0.3;
    }
    if(car3InitialX<-220.0)
        car3InitialX=220.0;

    glPushMatrix();
    glScaled(0.3, 0.5, 0.5);
    glTranslated(car3InitialX, -7.15, 24.00);
    carStructure();
    glPopMatrix();
}

void car4()
{
    if(carControl)
    {
        car4InitialX+=0.3;
    }
    if(car4InitialX>240.0)
        car4InitialX=-240.0;

    glPushMatrix();
    glScaled(0.3, 0.5, 0.5);
    glTranslated(car4InitialX, -7.15, 29.00);
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

    glBegin(GL_POLYGON);

    glVertex3f(-0.3, 1.2, 2.9);
    glVertex3f(-0.3, 0, 2.9);
    glVertex3f(0.3, 0, 2.9);
    glVertex3f(0.3, 1.2, 2.9);

    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(-0.3, 1.2, 2.9);
    glVertex3f(-0.3, 0, 2.9);
    glVertex3f(-0.3, 0, 3);
    glVertex3f(-0.3, 1.2, 3);

    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(0.3, 1.2, 3);
    glVertex3f(0.3, 0, 3);
    glVertex3f(0.3, 0, 2.9);
    glVertex3f(0.3, 1.2, 2.9);

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

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(-0.2, 0, 2.9);
    glVertex3f(-0.2, -1.5, 2.9);
    glVertex3f(0.2, -1.5, 2.9);
    glVertex3f(0.2, 0, 2.9);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(-0.2, 0, 2.9);
    glVertex3f(-0.2, -1.5, 2.9);
    glVertex3f(0.2, -1.5, 3);
    glVertex3f(0.2, 0, 3);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(0.2, 0, 3);
    glVertex3f(0.2, -1.5, 3);
    glVertex3f(0.2, -1.5, 2.9);
    glVertex3f(0.2, 0, 2.9);

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
    glVertex3f(-0.3, 1.2, 2.9);
    glVertex3f(-0.5, 0.2, 2.9);
    glVertex3f(-0.3, 0.2, 2.9);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(-0.3, 1.2, 2.9);
    glVertex3f(-0.5, 0.2, 2.9);
    glVertex3f(-0.5, 0.2, 3);
    glVertex3f(-0.3, 1.2, 3);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(0.3, 1.2, 3);
    glVertex3f(0.3, 0.2, 3);
    glVertex3f(0.5, 0.2, 3);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(0.3, 1.2, 2.9);
    glVertex3f(0.3, 0.2, 2.9);
    glVertex3f(0.5, 0.2, 2.9);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0, 1, 0);
    glVertex3f(0.3, 1.2, 3);
    glVertex3f(0.5, 0.2, 3);
    glVertex3f(0.5, 0.2, 2.9);
    glVertex3f(0.3, 1.2, 2.9);

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
    person1InitialX-=0.01;
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
    person2InitialX-=0.01;
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
    person3InitialX-=0.01;
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
    person4InitialX+=0.01;
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
    person5InitialX+=0.01;
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
    person6InitialX+=0.01;
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
    person7InitialZ-=0.008;
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
    person8InitialZ+=0.008;
    if(person8InitialZ>3.9)
        person8InitialZ=-4.5;

    glPushMatrix();
    glScaled(0.7, 0.7, 1);
    glTranslated(6.75, -5.5, person8InitialZ);
    personStructure();
    glPopMatrix();
}

void person9()
{
    person9InitialX-=0.009;
    if(person9InitialX<50.0)
        person9InitialX=70.0;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(person9InitialX, -3.0, -2.0);
    personStructure();
    glPopMatrix();
}

void person10()
{
    person10InitialX+=0.009;
    if(person10InitialX>70.0)
        person10InitialX=50.0;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(person10InitialX, -3.0, -5.0);
    personStructure();
    glPopMatrix();
}

void person11()
{
    person11InitialZ+=0.007;
    if(person11InitialZ>-1.7)
        person11InitialZ=-5.0;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(53.0, -3.0, person11InitialZ);
    personStructure();
    glPopMatrix();
}

void person12()
{
    person12InitialZ-=0.007;
    if(person12InitialZ<-4.9)
        person12InitialZ=-1.7;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(72.5, -3.0, person12InitialZ);
    personStructure();
    glPopMatrix();
}

void person13()
{
    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(79.0, -2.5, -7.0);
    personStructure();
    glPopMatrix();
}

void person14()
{
    person14InitialZ-=0.006;
    if(person14InitialZ<-4.9)
        person14InitialZ=-1.7;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-50.0, -3.0, person14InitialZ);
    personStructure();
    glPopMatrix();
}

void person15()
{
    person15InitialZ+=0.006;
    if(person15InitialZ>-1.7)
        person15InitialZ=-5.0;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-55.0, -3.0, person15InitialZ);
    personStructure();
    glPopMatrix();
}

void person16()
{
    person14InitialZ-=0.006;
    if(person14InitialZ<-4.9)
        person14InitialZ=-1.7;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-41.0, -3.0, person14InitialZ);
    personStructure();
    glPopMatrix();
}

void person17()
{
    person15InitialZ+=0.006;
    if(person15InitialZ>-1.7)
        person15InitialZ=-5.0;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-46.0, -3.0, person15InitialZ);
    personStructure();
    glPopMatrix();
}

void person18()
{
    person14InitialZ-=0.006;
    if(person14InitialZ<-4.9)
        person14InitialZ=-1.7;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-32.0, -3.0, person14InitialZ);
    personStructure();
    glPopMatrix();
}

void person19()
{
    person15InitialZ+=0.006;
    if(person15InitialZ>-1.7)
        person15InitialZ=-5.0;

    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-37.0, -3.0, person15InitialZ);
    personStructure();
    glPopMatrix();
}

void person20()
{
    glPushMatrix();
    glScaled(0.7, 1.2, 1);
    glTranslated(-21.0, -2.5, -7.0);
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
    glScaled(1, 2.0, 1);
    glTranslatef(-30.0, 3.4, -18.0);
    windmillPole();
    glPopMatrix();

    GLfloat mat_ambient1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glPushMatrix();
    glTranslatef(-30.0, 7.0, -17.9);
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
    glScaled(1, 2.0, 1);
    glTranslatef(-40.0, 3.4, -18.0);
    windmillPole();
    glPopMatrix();

    GLfloat mat_ambient1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glPushMatrix();
    glTranslatef(-40.0, 7.0, -17.9);
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
    glScaled(1, 2.0, 1);
    glTranslatef(-50.0, 3.4, -18.0);
    windmillPole();
    glPopMatrix();

    GLfloat mat_ambient1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess1[] = {60};

    materialProperties(mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);

    glPushMatrix();
    glTranslatef(-50.0, 7.0, -17.9);
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

void lightCurvePortion()
{
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glScaled(0.22, 0.18, 0.1);
    glTranslatef(-5.2, 2.5, 100);
    lightBezier();
    lightHolderBezier();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glScaled(0.22, 0.18, 0.1);
    glTranslatef(-5.2, -13.5, 100);
    lightBezier();
    lightHolderBezier();
    glPopMatrix();
}

void streetLight()
{
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(1.0, 10, -0.8);
    draw_cylinder(0.12, 6.0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-10.0, 0, -0.5);
    draw_cylinder(0.12, 3.0);
    glPopMatrix();

    lightCurvePortion();
}

void antenna()
{
    glPushMatrix();
    glRotatef(135, 0, 0, 1);
    glRotatef(-30, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    glTranslatef(-13, -46, 0);
    antennaBezier();
    glPopMatrix();

    glPushMatrix();
    glRotatef(45, 0, 0, 1);
    glScaled(0.3, 0.3, 0.3);
    glTranslatef(-5, 39, 0);
    antennaBezier();
    glPopMatrix();
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

    superShop();
    mainBuilding();
    building2();
    tvShop();

    tree1();
    tree2();
    tree3();

    car1();
    car2();
    car3();
    car4();

    person1();
    person2();
    person3();
    person4();
    person5();
    person6();
    person7();
    person8();
    person9();
    person10();
    person11();
    person12();
    person13();
    person14();
    person15();
    person16();
    person17();
    person18();
    person19();
    person20();

    antenna();
    streetLight();

    helpscreen();
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
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
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

    case 'g':
        carControl=!carControl;
        break;

    case 'h':
        gate1=true;
        break;

    case 'j':
        gate1C=true;
        break;

    case 'k':
        gate2=true;
        break;

    case 'l':
        gate2C=true;
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
    GLfloat light_position2[] = { 0.0, -20.0, 8.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

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
        if(light3)
        {
            glEnable(GL_LIGHT2);
            GLfloat spot_direction[] = { 0.0, 1.0, 0.0 };
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10.0);
            light3=!light3;
        }
        else
        {
            glDisable(GL_LIGHT2);
            light3=!light3;
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
    glutPostRedisplay();

    if (pRotate == true)
    {
        alpha -= 0.05;
        if(alpha < -360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
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
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\door.bmp",12);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\shelf2.bmp",13);
    LoadTexture("C:\\Users\\Dell\\Desktop\\Graphics\\textures\\tv.bmp",17);

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

