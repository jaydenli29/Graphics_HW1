/******************************************
*
* Official Name: Jayden Li
*
* E-mail: jli371@syr.edu
*
* Assignment:  Assignment 1
*
* Environment/Compiler:  XCode
*
* Date submitted:  February 8, 2023
*
* References: book, website for the UP or DOWN key
*
* Interactions:   Press the escape key to quit.
*                  Press O or P to toggle parallel or perspective view.
*                  Press t to change daytime
         Press UP and DOWN key to change robot's head
*
*
*******************************************/
#include <cmath>
//for sin, cos
#include <iostream>
#include <random>
#define PI 3.14159
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif



using namespace std;

//Global Varibles
static int view = 1;
static int robotSize = 1;





// Vertex array for color vectors
static float colors[] =
{
    0.0, 0.0, 0.0, // black
    0.0, 0.0, 1.0, // blue
    0.0, 1.0, 0.0, // green
    0.0, 1.0, 1.0, // cyan
    1.0, 0.0, 0.0, // red
    1.0, 0.0, 1.0, // purple
    1.0, 1.0, 0.0, // yellow
    0.5, 0.5, 0.5  // gray
    
};

// Array of vertices for co-ordinate vectors
static float vertices[8][3] =
{
      {22.5, 10.0, -3.0},
      {22.5, 20.0, -3.0},
      {32.5, 20.0, -3.0},
      {32.5, 10.0, -3.0},
    
      {20.0, 10.0, -3.0},
      {20.0, 20.0, -3.0},
      {35.0, 20.0, -3.0},
      {35.0, 10.0, -3.0}
      
};

static float vertices1 [] =
{
      5.0, 10.0, 0.0,
      5.0, 15.0, 0.0,
      3.0, 15.0, 0.0,
      35.0, 10.0, 0.0
      
};



void projection(); // Set Ortho or Frustum

// Circle drawing function
void circle(float radius, float center [], int nv)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3fv(center);
    for (int j = 0; j <= nv; j++)
    {
        glVertex3f(radius * cos((float)(j) / nv * 2 * PI) + center[0], radius * sin((float)(j) / nv * 2 * PI) + center[1], center[2]);
    }
    glEnd();
}

// Cone drawing function
void cone(float x, float y, float r, float h, float z)
{
    int nv = 20;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i <= nv; i++)
    {
        glVertex3f(x, y, z);
        glVertex3f(r * cos((float)(i) / nv * 2 * PI) + x, (y - h),r * sin((float)(i) / nv * 2 * PI) + z);
    }
    glEnd();
}

// Cylinder drawing function
void cylinder(float R, float x1, double top, double bottom, double z_ValCenter, int nv)
{
    int i;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= nv; i++)
    {
        glArrayElement(i%8);
        glVertex3f(x1 + R * cos((float)(i) / 20 * 2 * PI), top,
            R * sin((float)(i) / 20 * 2 * PI) + z_ValCenter);
        glVertex3f(x1 + R * cos((float)(i) / 20 * 2 * PI), bottom,
            R * sin((float)(i) / 20 * 2 * PI) + z_ValCenter);
    }
    glEnd();
}

// Polygon drawing function
// the right robot drawing starts here

// robot small head
void smallHead()
{
    int i;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    for (i = 0; i < 4; i++)
    {
        glArrayElement(i%4);
        
        glVertex3fv(vertices[i]);
        

    }
    glEnd();
}

// robot big head
void bigHead()
{
    int i;
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    for (i = 4; i < 8; i++)
    {
        glArrayElement(i%6);
        glVertex3fv(vertices[i]);
        
        
    }
    glEnd();
}

void robot_R()
{
    // robot body
    float center[] = {27.5, 4, -3};
    circle(3, center, 20);
    
    glLineWidth(3.0);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    // left hand
    glVertex3f(25,4,-3);
    glVertex3f(23,4,-3);
    glVertex3f(23,4,-3);
    glVertex3f(21,2,-3);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(20,1.5,-3);
    glVertex3f(21,3.5,-3);
    glVertex3f(22,1.5,-3);
    glEnd();
    
    // right hand
    glBegin(GL_LINES);
    glVertex3f(30,4,-3);
    glVertex3f(32,4,-3);
    glVertex3f(32,4,-3);
    glVertex3f(34,6,-3);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(33,6,-3);
    glVertex3f(34,8,-3);
    glVertex3f(35,6,-3);
    glEnd();
    
    // neck for right robot
    //cylinder(1.0, 27.5, 10.0, 7.0, 0, 10);
    glBegin(GL_POLYGON);
    glVertex3f(26,6,-3);
    glVertex3f(26,10,-3);
    glVertex3f(29,10,-3);
    glVertex3f(29,6,-3);
    glEnd();
}
    void robot_R_foot()
{
        // left feet
        glBegin(GL_LINES);
        for (int i = 0; i < 4; i++)
        {
            glArrayElement(i%4);
            glVertex3f(27,2,-3);
            glVertex3f(25,-2,-3);
            glVertex3f(25,-2,-3);
            glVertex3f(25,-4,-3);
        }
        
        glEnd();
        float center_L[] = {25, -5, -3};
        circle(1, center_L, 20);
        
        // right feet
        glBegin(GL_LINES);
        glVertex3f(28,2,-3);
        glVertex3f(30,-2,-3);
        glVertex3f(30,-2,-3);
        glVertex3f(30,-4,-3);
        glEnd();
        float center_R[] = {30, -5, -3};
        circle(1, center_R, 20);
        
    
}

// drawing the left robot
void robot_L()
{
    float x = -30;
    float y = -15;
    float center_Robot_L[] = {x,y,-2};
    
    cylinder(2, -30, -18, -25, -1, 20);
    glColor3ub(rand()%256, rand()%256, rand()%256);
    circle(3 , center_Robot_L, 20);
    
    // right hand
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex3f(-28,-19.5,-2);
    glVertex3f(-24,-19.5,-2);
    glVertex3f(-24,-21.5,-2);
    glVertex3f(-28,-21.5,-2);
    glEnd();
    
    // left hand
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex3f(-32,-19.5,-2);
    glVertex3f(-36,-19.5,-2);
    glVertex3f(-36,-21.5,-2);
    glVertex3f(-32,-21.5,-2);
    glEnd();
}
void robot_L_foot()
{
        //left foot
        glLineWidth(3.0);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(-31,-25,-2);
        glVertex3f(-33,-30,-2);
        glEnd();
        float centerL[] = {-33, -30, -2};
        circle(1, centerL, 20);
    
        // right foot
        glLineWidth(3.0);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(-29,-25,-2);
        glVertex3f(-27,-30,-2);
        glEnd();
        float centerR[] = {-27, -30, -2};
        circle(1, centerR, 20);
        
}
    
    

// Two sides green glass area
void lawn()
{
    glLineWidth(1.0);
    glColor3f(0.6,0.9,0.6); //lawn color
    glBegin(GL_POLYGON);
    
    //Left side lawn
    glVertex3f(-40,-10,-4);
    glVertex3f(-40,-40,-4);
    glVertex3f(-5,-10,-4);
    glEnd();
    //Right side lawn
    
    glBegin(GL_POLYGON);
    glVertex3f(40,-10,-4);
    glVertex3f(40,-40,-4);
    glVertex3f(5,-10,-4);
    glEnd();
}

// the rectangle with brown color
void TopRoad()
{
    glLineWidth(1.0);
    glColor3f(0.7,0.6,0.6); //brown color
    glBegin(GL_POLYGON);
    glVertex3f(-40,-10,-5);
    glVertex3f(-40,-5,-5);
    glVertex3f(40,-5,-5);
    glVertex3f(40,-10,-5);
    glEnd();
}

// the polygon road in the middle of the screen
void PedRoad()
{
    glLineWidth(1.0);
    glColor3f(0.8,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex3f(-10,-10,-4);
    glVertex3f(10,-10,-4);
    glVertex3f(40,-40,-4);
    glVertex3f(-40,-40,-4);
    glEnd();
}

// the house frame
void HouseBase()
{
    glLineWidth(3.0);
    glColor3f(0.82,0.7,0.55); //black
    glBegin(GL_POLYGON);
    glVertex3f(-10,-5,-6);
    glVertex3f(-10,5,-6);
    glVertex3f(10,5,-6);
    glVertex3f(10,-5,-6);
    glEnd();
}

void windows()
{
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-8, 2, -6);
    glVertex3f(-8, 4, -6);
    glVertex3f(-6, 4, -6);
    glVertex3f(-6, 2, -6);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(8, 2, -6);
    glVertex3f(8, 4, -6);
    glVertex3f(6, 4, -6);
    glVertex3f(6, 2, -6);
    glEnd();
}

void HouseRoof()
{
    glLineWidth(1.0);
    glColor3f(0.858824, 0.576471, 0.439216);
    glBegin(GL_POLYGON);
    glVertex3f(-15,5,-6);
    glVertex3f(-5,15,-6);
    glVertex3f(5,15,-6);
    glVertex3f(15,5,-6);
    glEnd();
    
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glColor3f(1, 1, 1);
    glPointSize(3.0);
    glBegin(GL_POLYGON);
    float x = -10,y = 10;
        for (int i = 0; i <= 30; i++)
        {
            glVertex3f(x, y, -6);
            x = x + 1;
        }
    glEnd();
}

void Chimney()
{
    glLineWidth(1.0);
    glColor3f(0.5, 0.5, 0.9);
    glBegin(GL_POLYGON);
    glVertex3f(2, 15, -6);
    glVertex3f(2, 20, -6);
    glVertex3f(5, 20, -6);
    glVertex3f(5, 15, -6);
    glEnd();
}

// Using the circle to draw the smoke from the chimney
void smoke()
{
    float c1[] = {5.5, 21.0, -6.0};
    float c2[] = {6.0, 22.0, -6.0};
    float c3[] = {7.5, 22.5, -6.0};
    glColor3f(0.5, 0.5, 0.5); // grey color
    circle(0.7, c1, 20);
    circle(0.8, c2, 20);
    circle(0.9, c3, 20);
}

// draw a door by using GL_LINE to draw the frame
void door()
{
    glLineWidth(3.0);
    glColor3f(0.0,0.0,0.0); //black
    glBegin(GL_LINES);
    glVertex3f(-2,-5,-6);
    glVertex3f(-2,0,-6);
    glVertex3f(2,-5,-6);
    glVertex3f(2,0,-6);
    glVertex3f(-2.1, 0, -6);
    glVertex3f(2.1, 0, -6);
    glEnd();

    float c[] = {-1, -3, -6};
    circle(0.3, c, 20);
}

// Draw a tree tunk on left side
void treeTunk()
{
    glLineWidth(1.0);
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-25.5, -5, -5);
    glVertex3f(-25.5, 0, -5);
    glVertex3f(-28.5, 0, -5);
    glVertex3f(-28.5, -5, -5);
    glEnd();
}

// Routine to draw a bitmap character string
void writeBitmapString(void* font, const char* string)
{
    const char* c;
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawScene(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    projection();
    
    //glMatrixMode(GL_MODELVIEW);
   // glLoadIdentity();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    float center[] = {-40,40,-5};
    if (daylight)
    {
        glColor3f(1.0, 0.0, 0.0);  // red
        circle(15, center, 50); // Draw sun
    }
    else
    {
        glColor3f(1.0, 1.0, 0.0);  // yellow
        circle(15, center, 50);  // Draw moon
    }
    PedRoad();
    TopRoad();
    lawn();
    HouseBase();
    Chimney();
    HouseRoof();
    smoke();
    windows();
    door();
    treeTunk();
    cone(-27.0, 10.0, 3.0, 10, -5);
    robot_R();
    robot_L();
    robot_R_foot();
    robot_L_foot();
    //Display the text
    if (daylight)
    {
        glColor3f(0.0, 0.0, 0.0);
    }
    else
    {
        glColor3f(1.0, 1.0, 1.0);
    }

    char place[] = "My home";
    char trees[] = "Christmas Tree";
    char road[] = "Pedestrian Road";
    char rightRobot[] = " Press UP or DOWN key to change his head";

    glRasterPos3f(-2.0, 30.0, -2);
    writeBitmapString(GLUT_BITMAP_8_BY_13, place);
    glRasterPos3f(-32.5, 12.0, -2);
    writeBitmapString(GLUT_BITMAP_9_BY_15, trees);
    glRasterPos3f(-5.0, -7.0, 0);
    writeBitmapString(GLUT_BITMAP_8_BY_13, road);
    glRasterPos3f(10.0, 22.0, -2);
    writeBitmapString(GLUT_BITMAP_8_BY_13, rightRobot);

    if (robotSize)
    {
        smallHead();
    }
    else
    {
        bigHead();
    }
    
    glutSwapBuffers(); //instead of glFlush, double buffer
}



// Initialization routine.
void setup(void)
{
    //white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    // Enable two vertex arrays: co-ordinates and color.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    // Specify locations for the co-ordinates and color arrays
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(-40, 40.0, -40.0, 40.0, -1.0,20.0);
    //glMatrixMode(GL_MODELVIEW);
    projection();
}

void projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (view)
    {
        glOrtho(-40, 40, -40, 40, -10.0, 20.0);
    }
    else
    {
        glFrustum(-40/2, 40/2, -40/2, 40/2, 1.0, 8.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
       // change the background color when pressed 't' key
        case 't':
            cout << "You changed the background color" << endl;
            if (daylight)
            {
                glClearColor(0.098,0.098,0.44,0.0);
                daylight = !daylight;
                glutPostRedisplay();
            }
            else
            {
                glClearColor(0.83, 0.68, 0.38, 0.0);
                daylight = !daylight;
                glutPostRedisplay();
            }
            break;
            
        case 'o':
            cout << "You changed the view" << endl;
            view = true;
            glutPostRedisplay();
            break;
        case 'p':
            cout << "You changed the view" << endl;
            view = false;
            glutPostRedisplay();
            break;
            
        default:
            break;
    }
}


// Non-ASCII key input processing routine.
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        if (robotSize)
        {
            bigHead();
            robotSize = !robotSize;
        }
        cout << "You changed a bigger head robot" << endl;
    }
    
    if (key == GLUT_KEY_DOWN)
    {
        if (!robotSize)
        {
            
            smallHead();
            robotSize = !robotSize;
        }
        cout << "You changed a smaller head robot" << endl;
    }

    glutPostRedisplay();
}



// Print the instruction on the console window
void Interaction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press ESC key to quit." << endl;
    cout << "Press 'o' or 'p' to change the view." << endl;
    cout << "Press t to change daytime" << endl;
    cout << "Press UP or DOWN key to change right robot's head" << endl;
}

// Main routine.
int main(int argc, char **argv)
{
    Interaction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Home");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();
    
    return 0;
}

