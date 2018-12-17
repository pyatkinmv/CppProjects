//
// File "circumcircle.cpp"
// Draw a circumcircle curve
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <X11/cursorfont.h>
#include "gwindow.h"

static const int MAX_POINTS = 3;
static const double CATCH_DIST = 0.1;

//--------------------------------------------------
// Definition of our main class "MyWindow"
//
class MyWindow: public GWindow {    // Our main class
    R2Point p[MAX_POINTS];          // Points
    int n;                          // Number of points
    Cursor indicateCursor;
    Cursor catchCursor;
    bool nodeIndicated;
    bool nodeCatched;
    int catchedNodeIdx;

    // Offscreen buffer
    bool initialUpdate;
public:
    bool offscreenDrawing;

public:
    MyWindow():                     // Constructor
        n(0),
        indicateCursor(0),
        catchCursor(0),
        nodeIndicated(false),
        nodeCatched(false),
        catchedNodeIdx(-1),
        initialUpdate(true),
        offscreenDrawing(false)
    {}

    void drawTriangle (const R2Point *q);

    void drawCircumcircle (const R2Point *q);

    void drawInOffscreen();

    virtual void onExpose(XEvent& event);
    virtual void onKeyPress(XEvent& event);
    virtual void onButtonPress(XEvent& event);
    virtual void onButtonRelease(XEvent& event);
    virtual void onMotionNotify(XEvent& event);
    virtual void onResize(XEvent& event);

    int nearestNode(const R2Point& t, double& dist) const;
    void dragNode(const R2Point& t);
};

//----------------------------------------------------------
// Implementation of class "MyWindow"

//
// Process the Expose event: draw in the window
//
void MyWindow::onExpose(XEvent& /* event */) {
    if (initialUpdate) {
        initialUpdate = false;

        // Try to create the offscreen buffer
        if (!offscreenDrawing) {
            offscreenDrawing = createOffscreenBuffer();
        }
        if (offscreenDrawing)
            drawInOffscreen();
    }

    if (offscreenDrawing) {
        swapBuffers();
        return;
    }

    //??? LDraw: ;

    // Erase a window
    setForeground(getBackground());
    fillRectangle(m_RWinRect);

    setLineWidth(1);

    // Draw the coordinate axes
    drawAxes("black", true, "gray");

    // Draw a graph of function
    if (n == 3) {
        setForeground("red");
        setLineWidth(3);
        drawTriangle(p);
        drawCircumcircle(p);
    }

    // Draw a cross on mouse clicks
    setForeground("blue");
    setLineWidth(2);
    R2Vector dx(0.4, 0.);
    R2Vector dy(0., 0.4);
    for (int i = 0; i < n; ++i) {
        drawLine(p[i]-dx, p[i]+dx);
        drawLine(p[i]-dy, p[i]+dy);
    }
}

void MyWindow::drawInOffscreen() {
    /*...
    printf(
        "drawInOffscreen: m_IWinRect=(%d, %d, %d, %d)\n",
        m_IWinRect.left(), m_IWinRect.top(),
        m_IWinRect.width(), m_IWinRect.height()
    );
    ...*/

    // Erase a window

    setForeground(getBackground());
    fillRectangle(m_RWinRect, true);

    setLineWidth(1);

    // Draw the coordinate axes
    drawAxes("black", true, "gray", true);

    // Draw a graph of function
    if (n == 3) {
        setLineWidth(2);
        setForeground("orange");
        drawTriangle(p);
        setForeground("green");
        drawCircumcircle(p);
    }

    // Draw a cross on mouse clicks
    setForeground("blue");
    setLineWidth(2);
    R2Vector dx(0.4, 0.);
    R2Vector dy(0., 0.4);
    for (int i = 0; i < n; ++i) {
        drawLine(p[i]-dx, p[i]+dx, true);
        drawLine(p[i]-dy, p[i]+dy, true);
    }
}


void MyWindow::drawTriangle(const R2Point *q){
    drawLine(q[0],q[1], offscreenDrawing);
    drawLine(q[1],q[2], offscreenDrawing);
    drawLine(q[0],q[2], offscreenDrawing);
}

void MyWindow::drawCircumcircle(const R2Point *q){
    R2Point A = q[0];
    R2Point B = q[1];
    R2Point C = q[2];

    double a = B.distance(C);
    double b = A.distance(C);
    double c = A.distance(B);

    double p = (a+b+c)/2;

    double radius = (a*b*c)/(4*sqrt(p*(p-a)*(p-b)*(p-c)));

    double ox = ((pow(A.x, 2) + pow(A.y,2))*(B.y-C.y) +
                (pow(B.x, 2)+pow(B.y, 2)) * (C.y-A.y) +
                (pow(C.x,2)+pow(C.y,2))*(A.y-B.y)
                )/(2*(A.x * (B.y-C.y)+B.x*(C.y-A.y)+C.x*(A.y-B.y)));

    double oy = ((pow(A.x, 2) + pow(A.y,2))*(C.x-B.x) +
                (pow(B.x, 2)+pow(B.y, 2)) * (A.x-C.x) +
                (pow(C.x,2)+pow(C.y,2))*(B.x-A.x)
                )/(2*(A.x * (B.y-C.y)+B.x*(C.y-A.y)+C.x*(A.y-B.y)));

    R2Point centre(ox,oy);
    drawCircle(centre, radius, offscreenDrawing);
}

// Process the KeyPress event:
// if "q" is pressed, then close the window
//
void MyWindow::onKeyPress(XEvent& event) {
    KeySym key;
    char keyName[256];
    int nameLen = XLookupString(&(event.xkey), keyName, 255, &key, 0);
    printf("KeyPress: keycode=0x%x, state=0x%x, KeySym=0x%x\n",
        event.xkey.keycode, event.xkey.state, (int) key);
    if (nameLen > 0) {
        keyName[nameLen] = 0;
        printf("\"%s\" button pressed.\n", keyName);
        if (keyName[0] == 'q') { // quit => close window
            destroyWindow();
        }
    }
}

void MyWindow::onButtonPress(XEvent& event) {
    int x = event.xbutton.x;
    int y = event.xbutton.y;
    R2Point t = invMap(I2Point(x, y));
    int mouseButton = event.xbutton.button;

    printf("Mouse click: x=%d, y=%d, button=%d\n", x, y, mouseButton);

    if (mouseButton != Button1) {
        n = 0;
        if (!offscreenDrawing) {
            redraw();
        } else {
            drawInOffscreen();
            swapBuffers();
        }
    } else {
        double dist;
        int node;
        node = nearestNode(t, dist);
        if (node >= 0 && dist <= CATCH_DIST) {
            printf("Node is catched.\n");
            nodeCatched = true;
            nodeIndicated = false;
            catchedNodeIdx = node;
            if (catchCursor == 0) {
                catchCursor = XCreateFontCursor(
                    m_Display, XC_cross
                );
            }
            XDefineCursor(m_Display, m_Window, catchCursor);
        }
    }
}

void MyWindow::onButtonRelease(XEvent& event) {
    int x = event.xbutton.x;
    int y = event.xbutton.y;
    R2Point t = invMap(I2Point(x, y));
    int mouseButton = event.xbutton.button;

    printf("Mouse button release: x=%d, y=%d, button=%d\n", x, y, mouseButton);

    if (mouseButton != Button1)
        return;

    if (nodeCatched) {
        printf("Node is release.\n");
        nodeCatched = false;
        XUndefineCursor(m_Display, m_Window);
        p[catchedNodeIdx] = t;
        catchedNodeIdx = (-1);
    } else {
        if (n >= MAX_POINTS)
            n = 0;
        p[n] = t;
        ++n;
    }
    if (!offscreenDrawing) {
        redraw();
    } else {
        drawInOffscreen();
        swapBuffers();
    }
}

// Process mouse moving
void MyWindow::onMotionNotify(XEvent& event) {
    int x = event.xmotion.x;
    int y = event.xmotion.y;
    R2Point t = invMap(I2Point(x, y));

    double dist;
    int node;
    if (nodeIndicated) {
        node = nearestNode(t, dist);
        if (node < 0 || dist > CATCH_DIST) {
            printf("Stopped node indication.\n");
            nodeIndicated = false;
            XUndefineCursor(m_Display, m_Window);
        }
    } else if (nodeCatched) {
        dragNode(t);
    } else {
        node = nearestNode(t, dist);
        if (node >= 0 && dist <= CATCH_DIST) {
            printf("Started node indication.\n");
            nodeIndicated = true;
            catchedNodeIdx = node;
            if (indicateCursor == 0) {
                indicateCursor = XCreateFontCursor(
                    m_Display, XC_hand1
                );
            }
            XDefineCursor(m_Display, m_Window, indicateCursor);
        }
    }
}

int MyWindow::nearestNode(const R2Point& t, double& dist) const {
    int nodeIdx = (-1);
    double nodeDist = 1e+30;    // Infinity
    for (int i = 0; i < n; ++i) {
        double d = p[i].distance(t);
        if (d < nodeDist) {
            nodeDist = d;
            nodeIdx = i;
        }
    }
    if (nodeIdx >= 0) {
        dist = nodeDist;
        return nodeIdx;
    }
    return (-1);
}

void MyWindow::dragNode(const R2Point& t) {
    if (!nodeCatched || catchedNodeIdx < 0)
        return;
    p[catchedNodeIdx] = t;
    if (!offscreenDrawing) {
        redraw();
    } else {
        drawInOffscreen();
        swapBuffers();
    }
}

void MyWindow::onResize(XEvent& /* event */) {
    if (offscreenDrawing) {
        drawInOffscreen();
        swapBuffers();
    }
}

//
// End of class MyWindow implementation
//----------------------------------------------------------

/////////////////////////////////////////////////////////////
// Main: initialize X, create an instance of MyWindow class,
//       and start the message loop
int main() {
    // Initialize X stuff
    if (!GWindow::initX()) {
        printf("Could not connect to X-server.\n");
        exit(1);
    }

    MyWindow w;
    double aspect = (double) GWindow::screenMaxY() /
        (double) GWindow::screenMaxX();
    double width = 30.;
    double height = aspect * width;
    w.createWindow(
        I2Rectangle(                    // Window frame rectangle:
            I2Point(10, 10),            //     left-top corner
            GWindow::screenMaxX()/2,    //     width
            GWindow::screenMaxY()/2     //     height
        ),
        R2Rectangle(                    // Coordinate rectangle:
            R2Point(-width/2., -height/2.), // bottom-right corner
            width, height                   // width, height
        ),
        "Circumcircle"                  // Window title
    );
    w.setBackground("lightGray");

    if (w.createOffscreenBuffer()) {
        w.offscreenDrawing = true;
        w.drawInOffscreen();
    }

    GWindow::messageLoop();

    GWindow::closeX();
    return 0;
}
