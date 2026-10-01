/*
    3D Hospital Management System - Graphics Lab Project
    Scene: Hospital Entrance + Emergency Department (ER)

      Section 1 - Entrance
        - Main Gate
        - Parking Area
        - Ambulance Parking (bay + ANIMATED ambulance arrival)
        - Reception (building block)
        - Waiting Area (benches)
        - Security Desk

      Section 2 - Emergency Department (ER)
        - Emergency beds
        - Wheelchairs
        - Medical equipment (IV stand, monitor cart, oxygen tank)
        - Emergency doctor
        - Nurse station (with nurse)
        - Ambulance arrival animation (drives in from the gate, stops
          at the bay with a blinking light, then reverses out and loops)

      Section 3 - Outpatient Department (OPD)
        - Registration desk
        - Patient waiting queue (chairs + seated patients)
        - Doctor chambers (2)
        - Consultation rooms (2, with examination table)

      Section 4 - Patient Cabins (further back, its own open-front wing
                  so every room is clearly visible from the front)
        - Single Cabin   (1 bed, visitor chair, TV, AC, attached bathroom)
        - VIP Cabin      (1 bed, sofa, gold trim, TV, AC, attached bathroom)
        - General Ward   (4 beds with curtain dividers, visitors, shared
                           TV, 2 AC units, attached bathroom)

    Library: freeglut (OpenGL + GLU + GLUT)
    Compile (Linux):
        g++ hospital_entrance.cpp -o hospital -lGL -lGLU -lglut
    Compile (Windows, MinGW + freeglut installed):
        g++ hospital_entrance.cpp -o hospital.exe -lfreeglut -lopengl32 -lglu32
    Run:
        ./hospital

    Controls:
        Arrow Keys  -> move camera forward/back, turn left/right
        W / S       -> move up / down
        R           -> reset camera
        Esc         -> quit
*/

#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ----------------------------------------------------------------------
// Camera state
// ----------------------------------------------------------------------
// Camera state

// Camera state

// Camera state

float camX = 0.0f;
float camY = 8.0f;
float camZ = 52.0f;

float camAngle = 0.0f;

float camHeight = 8.0f;

// ----------------------------------------------------------------------
// Light, simple, "flat" pastel palette (kept as normalized RGB)
// Every new color introduced for the ER stays inside this same light
// family so the whole scene reads as one consistent, simple palette.
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// Realistic Hospital Color Theme
// ----------------------------------------------------------------------

struct Color {
    float r;
    float g;
    float b;
};

void setColor(const Color& c)
{
    glColor3f(c.r, c.g, c.b);
}


// Outdoor environment

const Color COL_GRASS =
{
    0.55f, 0.75f, 0.45f
};

const Color COL_GROUND =
{
    0.72f, 0.78f, 0.68f
};

const Color COL_ROAD =
{
    0.25f, 0.28f, 0.32f
};

const Color COL_ROAD_LINE =
{
    1.0f, 0.9f, 0.45f
};

const Color COL_PARK_LINE =
{
    0.95f,0.95f,0.95f
};


// Hospital exterior

const Color COL_BUILDING =
{
    0.92f,0.95f,0.98f
};


const Color COL_WALL =
{
    0.96f,0.97f,0.98f
};


const Color COL_ROOF =
{
    0.15f,0.45f,0.75f
};


const Color COL_GLASS =
{
    0.35f,0.75f,0.90f
};


const Color COL_DOOR =
{
    0.10f,0.45f,0.65f
};


// Medical signs

const Color COL_MEDICAL_RED =
{
    0.90f,0.10f,0.10f
};


const Color COL_WHITE =
{
    1.0f,1.0f,1.0f
};


const Color COL_MEDICAL_GREEN =
{
    0.20f,0.70f,0.35f
};


// Furniture

const Color COL_WOOD =
{
    0.55f,0.32f,0.15f
};


const Color COL_DESK =
{
    0.65f,0.78f,0.85f
};

const Color COL_LAPTOP =
{
    0.05f,0.05f,0.08f
};


const Color COL_FILE =
{
    0.75f,0.55f,0.20f
};


const Color COL_COUNTER =
{
    0.85f,0.85f,0.90f
};

const Color COL_METAL =
{
    0.75f,0.78f,0.82f
};


// Ambulance

const Color COL_AMBULANCE =
{
    0.96f,0.96f,0.96f
};


const Color COL_AMB_RED =
{
    0.85f,0.05f,0.05f
};


// ER equipment

const Color COL_BED =
{
    0.82f,0.86f,0.90f
};


const Color COL_SHEET =
{
    0.45f,0.75f,0.90f
};


const Color COL_PILLOW =
{
    0.98f,0.98f,0.98f
};


const Color COL_MONITOR =
{
    0.10f,0.80f,0.40f
};


const Color COL_OXYGEN =
{
    0.55f,0.85f,0.60f
};


// Human colors

const Color COL_SKIN =
{
    0.95f,0.75f,0.60f
};


const Color COL_DOCTOR =
{
    1.0f,1.0f,1.0f
};


const Color COL_NURSE =
{
    0.55f,0.75f,0.95f
};


// Cabin section

const Color COL_VIP_GOLD =
{
    0.95f,0.75f,0.25f
};


const Color COL_CURTAIN =
{
    0.75f,0.85f,0.95f
};


const Color COL_TV =
{
    0.05f,0.05f,0.08f
};


const Color COL_AC =
{
    0.95f,0.98f,1.0f
};
// Additional missing colors

const Color COL_SIGN_BG =
{
    1.0f, 1.0f, 0.85f
};

const Color COL_SIGN_CROSS =
{
    0.9f, 0.1f, 0.1f
};


const Color COL_BED_FRAME =
{
    0.65f, 0.68f, 0.72f
};

const Color COL_BED_SHEET =
{
    0.45f, 0.75f, 0.95f
};

const Color COL_BLANKET =
{
    0.3f, 0.55f, 0.85f
};


const Color COL_EQUIP_METAL =
{
    0.7f, 0.72f, 0.75f
};


const Color COL_TV_FRAME =
{
    0.12f, 0.12f, 0.15f
};

const Color COL_TV_SCREEN =
{
    0.05f, 0.25f, 0.55f
};


const Color COL_AC_BODY =
{
    0.95f, 0.97f, 1.0f
};

const Color COL_AC_VENT =
{
    0.55f, 0.8f, 0.95f
};


const Color COL_BATH_WALL =
{
    0.85f, 0.9f, 0.95f
};

const Color COL_BATH_FIXTURE =
{
    0.9f,0.9f,0.9f
};


const Color COL_GATE_PILLAR =
{
    0.8f,0.85f,0.9f
};

const Color COL_GATE_ARCH =
{
    0.2f,0.45f,0.7f
};


const Color COL_WINDOW =
{
    0.35f,0.75f,0.9f
};


const Color COL_BENCH =
{
    0.55f,0.35f,0.2f
};


const Color COL_TREE_TRUNK =
{
    0.45f,0.25f,0.1f
};

const Color COL_TREE_LEAF =
{
    0.2f,0.7f,0.25f
};


const Color COL_ER_WALL =
{
    0.92f,0.95f,0.98f
};


const Color COL_AMB_BODY =
{
    0.95f,0.95f,0.95f
};

const Color COL_AMB_STRIPE =
{
    0.9f,0.05f,0.05f
};


const Color COL_WHEELCHAIR =
{
    0.65f,0.7f,0.75f
};

const Color COL_WHEEL =
{
    0.1f,0.1f,0.1f
};


const Color COL_MONITOR_SCREEN =
{
    0.1f,0.8f,0.4f
};

const Color COL_OXY_TANK =
{
    0.5f,0.85f,0.6f
};


const Color COL_DOCTOR_COAT =
{
    1.0f,1.0f,1.0f
};

const Color COL_NURSE_UNIFORM =
{
    0.55f,0.75f,0.95f
};


const Color COL_VIP_ACCENT =
{
    0.95f,0.75f,0.25f
};
// ----------------------------------------------------------------------
// PATIENT CABIN - HIGH CONTRAST COLORS
// ----------------------------------------------------------------------

const Color COL_CABIN_WALL =
{
    0.72f, 0.82f, 0.90f
};

const Color COL_CABIN_DIVIDER =
{
    0.40f, 0.55f, 0.70f
};

const Color COL_SINGLE_FLOOR =
{
    0.68f, 0.86f, 0.95f
};

const Color COL_VIP_FLOOR =
{
    0.95f, 0.86f, 0.58f
};

const Color COL_WARD_FLOOR =
{
    0.72f, 0.90f, 0.75f
};

const Color COL_CABIN_TRIM =
{
    0.12f, 0.45f, 0.70f
};

const Color COL_PATIENT_GOWN =
{
    0.35f, 0.70f, 0.85f
};

const Color COL_PATIENT_GOWN_2 =
{
    0.55f, 0.80f, 0.70f
};
// ----------------------------------------------------------------------
// Small vector helper for the ambulance path
// ----------------------------------------------------------------------
struct Vec2 { float x, z; };
void drawAmbulanceVehicle(
    float x,
    float y,
    float z,
    float headingDeg,
    bool lightOn
);
// ----------------------------------------------------------------------
// Ambulance arrival animation state
//   Path: start far up the access road -> down the road -> turn into
//   the ambulance bay -> stop inside the bay (pause + blinking light)
//   -> reverse back out the same way -> pause -> loop.
// ----------------------------------------------------------------------
Vec2 ambWaypoints[5] = {

    {0.0f,42.0f},

    {0.0f,25.0f},

    {10.0f,25.0f},

    {22.0f,35.0f},

    {22.0f,35.0f}

};
float ambT = 0.0f; // progress along the path, range 0..3
int   ambDir = 1;    // +1 driving in, -1 reversing out
int   ambPauseTimer = 0;    // frames left to hold position
bool  ambLightOn = false;
int   ambLightTimer = 0;
// Nurse variables
float cabinNurseX = 6.0f;
int cabinNurseDir = 1;
float visitorWalkX = -13.0f;
int visitorDirection = 1;
float nurseWalkZ = -30.0f;
int nurseDirection = 1;


float doctorHandAngle = 0;

Vec2 getAmbulancePos() {
    int seg = (int)ambT;
    if (seg > 2) seg = 2;
    if (seg < 0) seg = 0;
    float frac = ambT - seg;
    Vec2 a = ambWaypoints[seg];
    Vec2 b = ambWaypoints[seg + 1];
    Vec2 pos;
    pos.x = a.x + (b.x - a.x) * frac;
    pos.z = a.z + (b.z - a.z) * frac;
    return pos;
}

float getAmbulanceHeading() {
    int seg = (int)ambT;
    if (seg > 2) seg = 2;
    if (seg < 0) seg = 0;
    Vec2 a = ambWaypoints[seg];
    Vec2 b = ambWaypoints[seg + 1];
    float dx = (b.x - a.x);
    float dz = (b.z - a.z);
    if (ambDir < 0) { dx = -dx; dz = -dz; } // reversing: face the way it is now moving
    if (dx == 0 && dz == 0) return 0.0f;
    return atan2f(dx, -dz) * 180.0f / (float)M_PI;
}

// ----------------------------------------------------------------------
// Helper: axis-aligned box centered at (x,y,z) with given size
// ----------------------------------------------------------------------
void drawBox(float x, float y, float z, float sx, float sy, float sz) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawLaptop(float x, float y, float z)
{

    glPushMatrix();

    glTranslatef(x, y, z);


    // laptop base

    setColor(COL_LAPTOP);

    drawBox(
        0,
        0,
        0,
        0.8f,
        0.05f,
        0.5f
    );


    // laptop screen

    drawBox(
        0,
        0.35f,
        -0.2f,
        0.8f,
        0.5f,
        0.05f
    );


    glPopMatrix();

}
// =====================================
// Reception Counter
// =====================================

void drawReceptionCounter()
{

    float x = 0.0f;
    float z = -1.0f;


    // Counter

    setColor(COL_COUNTER);

    drawBox(
        x,
        0.8f,
        z,
        6.0f,
        1.2f,
        1.0f
    );


    // Laptop

    drawLaptop(
        -1.5f,
        1.45f,
        z
    );


    // Patient files

    setColor(COL_FILE);

    drawBox(
        2.0f,
        1.35f,
        z,
        0.5f,
        0.7f,
        0.4f
    );

}
void drawCylinderAt(float x, float y, float z, float radius, float height) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, radius, radius, height, 20, 4);
    glPushMatrix();
    glTranslatef(0, 0, height);
    gluDisk(q, 0, radius, 20, 4);
    glPopMatrix();
    gluDeleteQuadric(q);
    glPopMatrix();
}

// Wheel drawn as a torus standing upright, for wheelchairs
void drawWheel(float x, float y, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 0, 1, 0);
    glutSolidTorus(radius * 0.3, radius, 8, 16);
    glPopMatrix();
}

// Simple bitmap text label (lighting disabled briefly so it stays crisp)
void drawText(float x, float y, float z, void* font, const char* text) {
    glDisable(GL_LIGHTING);
    setColor(COL_SIGN_CROSS);
    glRasterPos3f(x, y, z);
    for (const char* c = text; *c; c++) glutBitmapCharacter(font, *c);
    glEnable(GL_LIGHTING);
}

// Very simple humanoid figure: legs, torso, arms, head
void drawHuman(float x,float z,float rotY, Color clothes, Color skin, int type)
{

    glPushMatrix();

    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);


    // ----------------
    // LEGS
    // ----------------

    setColor(clothes);


    drawCylinderAt(
        -0.18,
        0.0,
        0,
        0.08,
        0.75
    );


    drawCylinderAt(
        0.18,
        0.0,
        0,
        0.08,
        0.75
    );



    // ----------------
    // BODY
    // ----------------

    drawBox(
        0,
        1.15,
        0,
        0.45,
        0.75,
        0.25
    );


    // ----------------
    // NECK
    // ----------------

    setColor(skin);

    drawCylinderAt(
        0,
        1.55,
        0,
        0.08,
        0.15
    );


    // ----------------
    // HEAD
    // ----------------


    glPushMatrix();

    glTranslatef(
        0,
        1.85,
        0
    );

    glutSolidSphere(
        0.20,
        20,
        20
    );


    glPopMatrix();



    // ----------------
    // HAIR
    // ----------------

    if (type != 1)
    {
        setColor(Color{ 0.05,0.03,0.02 });

        glPushMatrix();

        glTranslatef(
            0,
            2.0,
            -0.05
        );

        glutSolidSphere(
            0.21,
            20,
            20
        );

        glPopMatrix();

    }



    // ----------------
    // ARMS
    // ----------------


    setColor(skin);


    drawCylinderAt(
        -0.35,
        1.25,
        0,
        0.06,
        0.55
    );


    drawCylinderAt(
        0.35,
        1.25,
        0,
        0.06,
        0.55
    );




    // ----------------
    // Nurse Cap
    // ----------------

    if (type == 2)
    {

        setColor(COL_WHITE);

        drawBox(
            0,
            2.05,
            0,
            0.18,
            0.04,
            0.18
        );


    }



    // ----------------
    // Doctor badge
    // ----------------

    if (type == 3)
    {

        setColor(COL_MEDICAL_RED);

        drawBox(
            0,
            1.35,
            -0.15,
            0.08,
            0.08,
            0.03
        );

    }


    glPopMatrix();

}
// =====================================
// Reception Staff
// =====================================

void drawReceptionStaff()
{

    // Receptionist behind desk

    drawHuman(
        0.0f,
        -2.8f,
        180,
        COL_NURSE_UNIFORM,
        COL_SKIN,
        2
    );

}
// Single waiting-room chair (used by the OPD queue and doctor chambers)
void drawChair(float x, float z, float rotY, Color frameColor) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);

    setColor(frameColor);
    drawBox(0, 0.45f, 0, 0.45f, 0.08f, 0.45f);          // seat
    drawBox(0, 0.75f, -0.20f, 0.45f, 0.5f, 0.08f);      // backrest
    drawBox(-0.18f, 0.22f, -0.18f, 0.06f, 0.44f, 0.06f); // 4 legs
    drawBox(0.18f, 0.22f, -0.18f, 0.06f, 0.44f, 0.06f);
    drawBox(-0.18f, 0.22f, 0.18f, 0.06f, 0.44f, 0.06f);
    drawBox(0.18f, 0.22f, 0.18f, 0.06f, 0.44f, 0.06f);

    glPopMatrix();
}

// A person sitting on a 0.45-high chair seat (used for the waiting queue)
void drawSeatedPerson(float x, float z, float rotY, Color outfit, Color skin) {
    const float seatH = 0.45f;
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);

    setColor(outfit);
    drawBox(-0.14f, seatH * 0.5f, 0.0f, 0.16f, seatH, 0.16f); // shins
    drawBox(0.14f, seatH * 0.5f, 0.0f, 0.16f, seatH, 0.16f);
    drawBox(-0.14f, seatH, 0.20f, 0.16f, 0.16f, 0.45f);       // thighs
    drawBox(0.14f, seatH, 0.20f, 0.16f, 0.16f, 0.45f);
    drawBox(0.0f, seatH + 0.35f, 0.0f, 0.5f, 0.55f, 0.26f);  // torso

    setColor(skin);
    drawBox(-0.33f, seatH + 0.32f, 0.05f, 0.13f, 0.45f, 0.13f); // arms
    drawBox(0.33f, seatH + 0.32f, 0.05f, 0.13f, 0.45f, 0.13f);

    glPushMatrix();
    glTranslatef(0, seatH + 0.72f, 0);
    glutSolidSphere(0.2, 14, 14);                              // head
    glPopMatrix();

    glPopMatrix();
}

// Examination table for the consultation rooms
void drawExamTable(float x, float z, float rotY) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);

    setColor(COL_BED_FRAME);
    drawBox(0, 0.55f, 0, 0.8f, 0.12f, 1.9f);            // frame
    drawBox(-0.32f, 0.22f, 0.75f, 0.1f, 0.44f, 0.1f);  // legs
    drawBox(0.32f, 0.22f, 0.75f, 0.1f, 0.44f, 0.1f);
    drawBox(-0.32f, 0.22f, -0.75f, 0.1f, 0.44f, 0.1f);
    drawBox(0.32f, 0.22f, -0.75f, 0.1f, 0.44f, 0.1f);
    drawBox(0, 0.85f, -0.9f, 0.8f, 0.5f, 0.06f);        // headrest support

    setColor(COL_BED_SHEET);
    drawBox(0, 0.65f, 0.0f, 0.75f, 0.06f, 1.7f);        // padded top

    setColor(COL_SIGN_BG);
    drawBox(0, 0.69f, 0.3f, 0.7f, 0.02f, 0.6f);         // paper roll strip

    glPopMatrix();
}

// Small wall-mounted room label (background plaque + red bitmap text)
void drawRoomSign(float x, float y, float z, const char* label) {
    setColor(COL_SIGN_BG);
    drawBox(x, y, z, 2.2f, 0.4f, 0.04f);
    drawText(x - 0.9f, y - 0.08f, z + 0.03f, GLUT_BITMAP_HELVETICA_12, label);
}

// Wall-mounted flat-screen TV (bezel + screen + small mount arm).
// Faces +z by default; scale lets the shared ward TV read as slightly bigger.
void drawTV(float x, float y, float z, float rotY, float scale = 1.0f) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotY, 0, 1, 0);
    glScalef(scale, scale, 1.0f);

    setColor(COL_EQUIP_METAL);
    drawBox(0, 0, -0.06f, 0.08f, 0.08f, 0.12f);   // wall mount arm
    setColor(COL_TV_FRAME);
    drawBox(0, 0, 0, 0.9f, 0.55f, 0.06f);          // bezel
    setColor(COL_TV_SCREEN);
    drawBox(0, 0, 0.03f, 0.78f, 0.44f, 0.03f);     // screen

    glPopMatrix();
}

// Wall-mounted split-AC indoor unit (body + a thin vent slit).
void drawACUnit(float x, float y, float z, float rotY, float scale = 1.0f) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotY, 0, 1, 0);
    glScalef(scale, scale, 1.0f);

    setColor(COL_AC_BODY);
    drawBox(0, 0, 0, 1.2f, 0.32f, 0.28f);
    setColor(COL_AC_VENT);
    drawBox(0, -0.09f, 0.15f, 1.0f, 0.05f, 0.02f);

    glPopMatrix();
}

// Compact attached-bathroom cluster: a short partition wall with a door,
// plus a toilet, a sink counter and a small mirror tucked just inside.
// Placed in a room corner; door faces +z (toward the open front) by default.
void drawBathroomCorner(float x, float z, float rotY) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);

    setColor(COL_BATH_WALL);
    drawBox(-0.55f, 1.1f, 0.0f, 0.08f, 2.2f, 1.6f);    // side partition
    drawBox(0.0f, 1.1f, 0.75f, 1.7f, 2.2f, 0.08f);     // front partition (door sits in it)

    setColor(COL_DOOR);
    drawBox(0.55f, 1.0f, 0.75f, 0.7f, 2.0f, 0.06f);    // door leaf

    setColor(COL_BATH_FIXTURE);
    drawBox(-0.25f, 0.35f, -0.5f, 0.4f, 0.4f, 0.4f);   // toilet
    drawBox(0.35f, 0.5f, -0.55f, 0.5f, 0.08f, 0.35f);  // sink counter

    setColor(COL_AC_VENT); // pale-blue tint doubles as the mirror above the sink
    drawBox(0.35f, 0.95f, -0.58f, 0.45f, 0.4f, 0.03f);

    setColor(COL_SIGN_BG);
    drawBox(0.0f, 2.5f, 0.79f, 0.4f, 0.2f, 0.03f);     // small "WC" plaque
    glPopMatrix();
}

// ----------------------------------------------------------------------
// Ground plaza + access road + driveway connectors
// ----------------------------------------------------------------------
void drawGround() {
    setColor(COL_GROUND);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-45, 0, -45);
    glVertex3f(-45, 0, 45);
    glVertex3f(45, 0, 45);
    glVertex3f(45, 0, -45);
    glEnd();

    // main access road leading in from the gate
    setColor(COL_ROAD);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-4, 0.01f, 8);
    glVertex3f(4, 0.01f, 8);
    glVertex3f(4, 0.01f, 44);
    glVertex3f(-4, 0.01f, 44);
    glEnd();

    // driveway connector strip tying the road to parking / ambulance bay
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-26, 0.01f, 6);
    glVertex3f(26, 0.01f, 6);
    glVertex3f(26, 0.01f, 10);
    glVertex3f(-26, 0.01f, 10);
    glEnd();

    // lane connecting the ambulance bay straight back to the ER entrance
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(16, 0.01f, -6);
    glVertex3f(24, 0.01f, -6);
    glVertex3f(24, 0.01f, 1);
    glVertex3f(16, 0.01f, 1);
    glEnd();

    // short walkway connecting the plaza down to the OPD entrance
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-26, 0.01f, -10);
    glVertex3f(-14, 0.01f, -10);
    glVertex3f(-14, 0.01f, -8);
    glVertex3f(-26, 0.01f, -8);
    glEnd();
}

// ----------------------------------------------------------------------
// Main Gate
// ----------------------------------------------------------------------
void drawMainGate()
{

    float gateZ = 40.0f;


    // Left pillar
    setColor(COL_GATE_PILLAR);

    drawBox(
        -5,
        1.8,
        gateZ,
        0.8,
        3.5,
        0.8
    ); drawBox(
        -6,
        2,
        gateZ,
        1,
        4,
        1
    ); drawBox(
        -6,
        2,
        gateZ,
        1,
        4,
        1
    );


    // Right pillar
    drawBox(
        5,
        1.8,
        gateZ,
        0.8,
        3.5,
        0.8
    );


    // Gate top
    setColor(COL_GATE_ARCH);

    drawBox(
        0,
        4.5,
        gateZ,
        10,
        0.4,
        0.5
    );


    // Hospital sign

    setColor(COL_SIGN_BG);

    drawBox(
        0,
        4.6,
        gateZ - 0.5,
        7,
        1,
        0.1
    );


    drawText(
        -3,
        4.5,
        gateZ - 0.6,
        GLUT_BITMAP_HELVETICA_18,
        "CITY HOSPITAL"
    );


}

// ----------------------------------------------------------------------
// Parking area
// ----------------------------------------------------------------------
void drawParkingArea()
{

    float baseX = -18;
    float baseZ = 25;


    setColor(COL_ROAD);


    drawBox(
        baseX,
        0.02,
        baseZ,
        18,
        0.05,
        15
    );


    // parking lines

    setColor(COL_PARK_LINE);


    for (int i = -3; i <= 3; i++)
    {

        drawBox(
            baseX + i * 2.5,
            0.05,
            baseZ,
            0.05,
            0.02,
            12
        );

    }


    // Cars

    Color car1 = { 0.2,0.5,0.9 };

    setColor(car1);

    drawBox(
        -22,
        0.5,
        25,
        2,
        1,
        4
    );


    Color car2 = { 0.9,0.4,0.2 };

    setColor(car2);

    drawBox(
        -15,
        0.5,
        25,
        2,
        1,
        4
    );

}

// ----------------------------------------------------------------------
// Ambulance bay markings (static) + the animated ambulance vehicle
// ----------------------------------------------------------------------
void drawAmbulanceBay()
{

    float x = 22;
    float z = 35;


    // ==========================
    // Ambulance parking floor
    // ==========================

    setColor(COL_ROAD);

    drawBox(
        x,
        0.02f,
        z,
        12,
        0.05f,
        18
    );


    // ==========================
    // Parking border
    // ==========================

    Color border = { 1.0f,0.85f,0.0f };

    setColor(border);


    drawBox(
        x - 5.5f,
        0.08f,
        z,
        0.1f,
        0.02f,
        17
    );


    drawBox(
        x + 5.5f,
        0.08f,
        z,
        0.1f,
        0.02f,
        17
    );


    drawBox(
        x,
        0.08f,
        z - 8,
        11,
        0.02f,
        0.1f
    );


    drawBox(
        x,
        0.08f,
        z + 8,
        11,
        0.02f,
        0.1f
    );


    // ==========================
    // Ambulance parking roof
    // ==========================

    setColor(COL_GATE_ARCH);


    drawBox(
        x,
        4.5f,
        z,
        12,
        0.3f,
        18
    );


    // Roof pillars

    setColor(COL_GATE_PILLAR);


    drawBox(x - 5, 2, z - 7, 0.5, 4, 0.5);
    drawBox(x + 5, 2, z - 7, 0.5, 4, 0.5);

    drawBox(x - 5, 2, z + 7, 0.5, 4, 0.5);
    drawBox(x + 5, 2, z + 7, 0.5, 4, 0.5);



    // ==========================
    // Ambulance sign board
    // ==========================

    setColor(COL_SIGN_BG);

    drawBox(
        x,
        3.8f,
        z - 8.5f,
        5,
        0.7,
        0.1
    );


    drawText(
        x - 3,
        3.65f,
        z - 8.6f,
        GLUT_BITMAP_HELVETICA_12,
        "AMBULANCE PARKING"
    );


    // ==========================
    // Static parked ambulance
    // ==========================

    drawAmbulanceVehicle(
        x,
        0.9f,
        z,
        0,
        true
    );

}

void drawAmbulanceVehicle(float x, float y, float z, float headingDeg, bool lightOn) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(headingDeg, 0, 1, 0);

    setColor(COL_AMB_BODY);
    drawBox(0, 0, 0, 2.0f, 1.4f, 4.0f);
    setColor(COL_AMB_STRIPE);
    drawBox(0, 0, 0, 2.02f, 0.3f, 4.02f);
    setColor(COL_SIGN_CROSS);
    drawBox(0, 0.7f, 0, 0.3f, 0.05f, 0.9f);
    drawBox(0, 0.7f, 0, 0.9f, 0.05f, 0.3f);

    // roof beacon - blinks between soft and bright red while animating
    Color lightBar = lightOn ? Color{ 0.95f, 0.25f, 0.25f } : Color{ 0.90f, 0.65f, 0.65f };
    setColor(lightBar);
    drawBox(0, 0.85f, -1.2f, 0.8f, 0.15f, 0.3f);

    glPopMatrix();
}

// ----------------------------------------------------------------------
// Reception building
// ----------------------------------------------------------------------
void drawReceptionBuilding()
{

    float bx = 0.0f;
    float bz = -5.0f;


    // Back wall

    setColor(COL_BUILDING);

    drawBox(
        bx,
        2.5f,
        bz - 3.5f,
        10.0f,
        5.0f,
        0.3f
    );


    // Left wall

    drawBox(
        bx - 5,
        2.5f,
        bz,
        0.3f,
        5.0f,
        7.0f
    );


    // Right wall

    drawBox(
        bx + 5,
        2.5f,
        bz,
        0.3f,
        5.0f,
        7.0f
    );


    // Roof

    setColor(COL_ROOF);

    drawBox(
        bx,
        5.2f,
        bz,
        10.6f,
        0.4f,
        8.6f
    );


    // Reception door

    setColor(COL_DOOR);

    drawBox(
        bx,
        1.2f,
        bz + 3.8f,
        1.6f,
        2.4f,
        0.1f
    );


    // Reception counter

    drawReceptionCounter();


    // Reception staff

    drawReceptionStaff();

}

// ----------------------------------------------------------------------
// Waiting area
// ----------------------------------------------------------------------
void drawBench(float x, float z, float rotY) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);
    setColor(COL_BENCH);
    drawBox(0, 0.45f, 0, 2.0f, 0.1f, 0.6f);
    drawBox(0, 0.75f, -0.25f, 2.0f, 0.5f, 0.1f);
    drawBox(-0.9f, 0.2f, 0, 0.1f, 0.4f, 0.6f);
    drawBox(0.9f, 0.2f, 0, 0.1f, 0.4f, 0.6f);
    glPopMatrix();
}

void drawWaitingArea()
{

    drawBench(-8, 12, 0);

    drawBench(-3, 12, 0);

    drawBench(3, 12, 0);

    drawBench(8, 12, 0);

}

// ----------------------------------------------------------------------
// Security desk
// ----------------------------------------------------------------------
void drawSecurityDesk() {
    float sx = -10.0f;
    float sz = 45.0f;

    setColor(COL_DESK);
    drawBox(sx, 1.0f, sz, 1.6f, 1.2f, 1.2f);
    setColor(COL_WINDOW);
    drawBox(sx, 1.4f, sz + 0.61f, 1.2f, 0.5f, 0.05f);
    setColor(COL_ROOF);
    drawBox(sx, 1.75f, sz, 1.9f, 0.15f, 1.5f);
}

// ----------------------------------------------------------------------
// Trees
// ----------------------------------------------------------------------
void drawTree(float x, float z) {
    setColor(COL_TREE_TRUNK);
    drawCylinderAt(x, 0.0f, z, 0.15f, 1.2f);
    setColor(COL_TREE_LEAF);
    glPushMatrix();
    glTranslatef(x, 1.8f, z);
    glutSolidSphere(0.8, 12, 12);
    glPopMatrix();
}

void drawTrees() {
    drawTree(-11.0f, 18.0f);
    drawTree(11.0f, 18.0f);
    drawTree(-9.0f, -6.0f);
    drawTree(9.0f, -6.0f);
    drawTree(-24.0f, -9.0f);
    drawTree(-16.0f, -9.0f);
}
void drawBedsideTable(float x, float z)
{
    setColor(COL_WOOD);

    drawBox(
        x,
        0.5f,
        z,
        0.6f,
        1.0f,
        0.5f
    );

    // drawer handle
    setColor(COL_METAL);

    drawBox(
        x,
        0.55f,
        z + 0.28f,
        0.25f,
        0.05f,
        0.05f
    );
}
void drawWallClock(float x, float y, float z)
{
    glPushMatrix();

    glTranslatef(x, y, z);

    setColor(COL_WHITE);

    glutSolidTorus(
        0.03,
        0.25,
        20,
        20
    );


    setColor(COL_MEDICAL_RED);

    drawBox(
        0,
        0,
        0.05,
        0.02,
        0.3,
        0.02
    );


    glPopMatrix();
}
void drawOxygenOutlet(float x, float z)
{

    setColor(COL_MEDICAL_GREEN);


    drawCylinderAt(
        x,
        0.8f,
        z,
        0.08f,
        0.25f
    );


}
// ----------------------------------------------------------------------
// Patient lying on a hospital bed
// ----------------------------------------------------------------------

void drawPatientOnBed(
    float x,
    float z,
    float rotY,
    Color gownColor
)
{
    glPushMatrix();

    glTranslatef(x, 0.0f, z);
    glRotatef(rotY, 0, 1, 0);


    // --------------------------------------------------
    // BODY / HOSPITAL GOWN
    // --------------------------------------------------

    setColor(gownColor);

    glPushMatrix();

    glTranslatef(0, 0.85, -0.1);

    glutSolidSphere(
        0.35,
        20,
        20
    );

    glPopMatrix();


    // left leg
    drawBox(
        -0.14f,
        0.80f,
        0.58f,
        0.18f,
        0.15f,
        0.78f
    );


    // right leg
    drawBox(
        0.14f,
        0.80f,
        0.58f,
        0.18f,
        0.15f,
        0.78f
    );


    // --------------------------------------------------
    // PATIENT ARMS
    // --------------------------------------------------

    setColor(COL_SKIN);

    drawBox(
        -0.34f,
        0.82f,
        -0.05f,
        0.12f,
        0.12f,
        0.65f
    );

    drawBox(
        0.34f,
        0.82f,
        -0.05f,
        0.12f,
        0.12f,
        0.65f
    );


    // --------------------------------------------------
    // HEAD
    // --------------------------------------------------

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.88f,
        -0.72f
    );

    glutSolidSphere(
        0.22f,
        16,
        16
    );

    glPopMatrix();


    glPopMatrix();
}

// ------------------------------------------------------------------------
// EMERGENCY DEPARTMENT (ER)
// Placed directly behind the ambulance bay so the ambulance "arrives"
// right at its doorstep. Built as an open-front room (back wall + two
// side walls + roof) so beds/staff inside stay visible to the camera.
// Room footprint: x in [14,26], z in [-15,-5], height 5.
// ------------------------------------------------------------------------
void drawERBuilding() {
    float cx = 20.0f;

    // floor
    setColor(COL_ER_WALL);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(14, 0.015f, -15);
    glVertex3f(26, 0.015f, -15);
    glVertex3f(26, 0.015f, -5);
    glVertex3f(14, 0.015f, -5);
    glEnd();

    // back wall
    setColor(COL_ER_WALL);
    drawBox(cx, 2.5f, -15.0f, 12.0f, 5.0f, 0.3f);
    // side walls
    drawBox(14.0f, 2.5f, -10.0f, 0.3f, 5.0f, 10.0f);
    drawBox(26.0f, 2.5f, -10.0f, 0.3f, 5.0f, 10.0f);
    // roof
    setColor(COL_ROOF);
    drawBox(cx, 5.2f, -10.0f, 12.6f, 0.4f, 10.6f);

    // "EMERGENCY" sign above the open entrance + cross
    setColor(COL_SIGN_BG);
    drawBox(cx, 4.6f, -5.05f, 5.0f, 0.7f, 0.08f);
    setColor(COL_SIGN_CROSS);
    drawBox(cx - 2.1f, 4.6f, -5.02f, 0.35f, 0.35f, 0.03f);
    drawText(cx - 1.5f, 4.45f, -5.0f, GLUT_BITMAP_HELVETICA_18, "EMERGENCY");
}

void drawBed(float x, float z, float rotY) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);

    setColor(COL_BED_FRAME);
    drawBox(0, 0.5f, 0, 1.0f, 0.15f, 2.2f);       // frame/mattress base
    drawBox(-0.42f, 0.2f, 0.9f, 0.12f, 0.4f, 0.12f); // legs
    drawBox(0.42f, 0.2f, 0.9f, 0.12f, 0.4f, 0.12f);
    drawBox(-0.42f, 0.2f, -0.9f, 0.12f, 0.4f, 0.12f);
    drawBox(0.42f, 0.2f, -0.9f, 0.12f, 0.4f, 0.12f);
    drawBox(0, 0.85f, -1.05f, 1.0f, 0.6f, 0.08f);  // headboard

    setColor(COL_PILLOW);
    drawBox(0, 0.62f, -0.8f, 0.6f, 0.15f, 0.35f);

    setColor(COL_BED_SHEET);
    drawBox(0, 0.6f, 0.15f, 0.95f, 0.05f, 1.7f);

    setColor(COL_BLANKET);
    drawBox(0, 0.63f, 0.55f, 0.98f, 0.06f, 0.35f);

    glPopMatrix();
}

void drawEmergencyBeds() {
    drawBed(17.0f, -13.2f, 0);
    drawBed(20.0f, -13.2f, 0);
    drawBed(23.0f, -13.2f, 0);
}

void drawWheelchair(float x, float z, float rotY) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotY, 0, 1, 0);

    setColor(COL_WHEELCHAIR);
    drawBox(0, 0.5f, 0, 0.5f, 0.08f, 0.5f);        // seat
    drawBox(0, 0.85f, -0.22f, 0.5f, 0.6f, 0.08f);  // backrest
    drawBox(-0.27f, 0.65f, 0, 0.06f, 0.3f, 0.5f);  // armrests
    drawBox(0.27f, 0.65f, 0, 0.06f, 0.3f, 0.5f);

    setColor(COL_WHEEL);
    drawWheel(-0.30f, 0.35f, 0.05f, 0.32f); // large rear wheels
    drawWheel(0.30f, 0.35f, 0.05f, 0.32f);
    drawWheel(-0.28f, 0.13f, 0.35f, 0.12f); // small front casters
    drawWheel(0.28f, 0.13f, 0.35f, 0.12f);

    glPopMatrix();
}

void drawWheelchairsER() {
    drawWheelchair(16.0f, -7.0f, 20.0f);
    drawWheelchair(24.0f, -7.0f, -20.0f);
}

void drawIVStand(float x, float z) {
    setColor(COL_EQUIP_METAL);
    drawCylinderAt(x, 0.0f, z, 0.03f, 1.6f);       // pole
    drawBox(x, 1.65f, z, 0.35f, 0.03f, 0.03f);     // hook bar
    setColor(COL_WINDOW);
    drawBox(x - 0.12f, 1.45f, z, 0.14f, 0.22f, 0.1f); // drip bag
}

void drawMonitorCart(float x, float z) {
    setColor(COL_EQUIP_METAL);
    drawBox(x, 0.9f, z, 0.5f, 0.06f, 0.4f);        // cart top
    drawCylinderAt(x - 0.18f, 0.0f, z - 0.15f, 0.03f, 0.9f);
    drawCylinderAt(x + 0.18f, 0.0f, z - 0.15f, 0.03f, 0.9f);
    drawCylinderAt(x - 0.18f, 0.0f, z + 0.15f, 0.03f, 0.9f);
    drawCylinderAt(x + 0.18f, 0.0f, z + 0.15f, 0.03f, 0.9f);
    setColor(COL_MONITOR_SCREEN);
    drawBox(x, 1.25f, z, 0.35f, 0.3f, 0.05f);      // screen
}

void drawOxygenTank(float x, float z) {
    setColor(COL_OXY_TANK);
    drawCylinderAt(x, 0.0f, z, 0.14f, 0.9f);
    setColor(COL_EQUIP_METAL);
    drawBox(x, 1.0f, z, 0.12f, 0.15f, 0.12f);      // valve
}

void drawMedicalEquipment() {
    drawIVStand(17.8f, -12.5f);
    drawMonitorCart(20.8f, -12.3f);
    drawOxygenTank(23.7f, -12.5f);
}

void drawERStaff() {
    // emergency doctor near the middle bed, facing the beds
    drawHuman(
        20.0f,
        -11.2f,
        180,
        COL_DOCTOR_COAT,
        COL_SKIN,
        3
    );
    setColor(COL_SIGN_CROSS);
    drawBox(20.0f, 1.25f, -11.35f, 0.14f, 0.14f, 0.03f); // small badge/cross on coat
}

void drawNurseStation() {
    float nx = 24.6f, nz = -8.5f;

    setColor(COL_DESK);
    drawBox(nx, 0.55f, nz, 0.3f, 1.1f, 3.0f);      // long counter
    setColor(COL_WINDOW);
    drawBox(nx - 0.16f, 0.85f, nz, 0.05f, 0.4f, 2.6f); // glass panel on counter

    setColor(COL_MONITOR_SCREEN);
    drawBox(nx - 0.2f, 1.25f, nz - 0.9f, 0.05f, 0.35f, 0.4f); // small monitor

    drawHuman(
        nx - 0.5f,
        nz,
        -90,
        COL_NURSE_UNIFORM,
        COL_SKIN,
        2
    );
}

// ------------------------------------------------------------------------
// OUTPATIENT DEPARTMENT (OPD)
// Mirrors the ER on the opposite side of the plaza (left of parking).
// Open-front room, footprint x in [-26,-14], z in [-20,-10], height 5.
// Laid out entrance-to-back as: registration desk -> waiting queue ->
// 2 doctor chambers + 2 consultation rooms along the back wall.
// ------------------------------------------------------------------------
void drawOPDBuilding() {
    float cx = -20.0f;

    setColor(COL_ER_WALL); // reuse the same light wall tone as the ER
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-26, 0.015f, -20);
    glVertex3f(-14, 0.015f, -20);
    glVertex3f(-14, 0.015f, -10);
    glVertex3f(-26, 0.015f, -10);
    glEnd();

    drawBox(cx, 2.5f, -20.0f, 12.0f, 5.0f, 0.3f);     // back wall
    drawBox(-26.0f, 2.5f, -15.0f, 0.3f, 5.0f, 10.0f); // left wall
    drawBox(-14.0f, 2.5f, -15.0f, 0.3f, 5.0f, 10.0f); // right wall

    setColor(COL_ROOF);
    drawBox(cx, 5.2f, -15.0f, 12.6f, 0.4f, 10.6f);

    setColor(COL_SIGN_BG);
    drawBox(cx, 4.6f, -10.05f, 5.6f, 0.7f, 0.08f);
    setColor(COL_SIGN_CROSS);
    drawBox(cx - 2.5f, 4.6f, -10.02f, 0.3f, 0.3f, 0.03f);
    drawText(cx - 1.9f, 4.45f, -10.0f, GLUT_BITMAP_HELVETICA_18, "OPD - OUTPATIENT");
}

void drawRegistrationDesk() {
    float x = -20.0f, z = -11.3f;

    setColor(COL_DESK);
    drawBox(x, 0.55f, z, 3.4f, 1.1f, 0.4f);        // counter
    setColor(COL_WINDOW);
    drawBox(x, 0.95f, z - 0.22f, 3.0f, 0.35f, 0.05f); // glass panel
    setColor(COL_MONITOR_SCREEN);
    drawBox(x - 1.1f, 1.15f, z - 0.05f, 0.3f, 0.3f, 0.05f); // small monitor

    drawHuman(
        x,
        z - 0.55f,
        180.0f,
        COL_NURSE_UNIFORM,
        COL_SKIN,
        2
    ); // staff

    setColor(COL_SIGN_BG);
    drawBox(x, 1.7f, z - 0.02f, 2.2f, 0.4f, 0.05f);
    drawText(x - 0.95f, 1.6f, z + 0.02f, GLUT_BITMAP_HELVETICA_12, "REGISTRATION");
}

void drawWaitingQueueOPD() {
    float z = -13.4f;
    float xs[4] = { -23.5f, -21.5f, -19.5f, -17.5f };
    Color outfits[4] = { COL_BENCH, COL_TREE_LEAF, COL_GATE_PILLAR, COL_NURSE_UNIFORM };

    for (int i = 0; i < 4; i++) {
        drawChair(xs[i], z, 0.0f, COL_DESK);
        drawSeatedPerson(xs[i], z, 0.0f, outfits[i], COL_SKIN);
    }
}

void drawDoctorChamber(float x) {
    float zDesk = -18.3f;

    setColor(COL_DESK);
    drawBox(x, 0.55f, zDesk, 1.6f, 1.0f, 0.6f);              // desk
    drawHuman(
        x,
        zDesk - 0.55f,
        180.0f,
        COL_DOCTOR_COAT,
        COL_SKIN,
        3
    ); // doctor
    drawChair(x, zDesk + 1.0f, 180.0f, COL_DESK);            // patient chair
}

void drawDoctorChambers() {
    setColor(COL_ER_WALL);
    drawBox(-23.0f, 1.1f, -18.0f, 0.15f, 2.2f, 4.0f); // divider between the 2 chambers

    drawDoctorChamber(-24.5f);
    drawDoctorChamber(-21.5f);

    drawRoomSign(-24.5f, 4.0f, -19.8f, "DR. CHAMBER 1");
    drawRoomSign(-21.5f, 4.0f, -19.8f, "DR. CHAMBER 2");
}

void drawConsultationRoom(float x) {
    float zTable = -18.3f;
    drawExamTable(x, zTable, 0.0f);
    drawHuman(
        x - 0.9f,
        zTable - 0.3f,
        90.0f,
        COL_DOCTOR_COAT,
        COL_SKIN,
        3
    );
}

void drawConsultationRooms() {
    setColor(COL_ER_WALL);
    drawBox(-20.0f, 1.1f, -18.0f, 0.15f, 2.2f, 4.0f); // divider: chambers <-> consultation zone
    drawBox(-17.0f, 1.1f, -18.0f, 0.15f, 2.2f, 4.0f); // divider between the 2 consultation rooms

    drawConsultationRoom(-18.5f);
    drawConsultationRoom(-15.5f);

    drawRoomSign(-18.5f, 4.0f, -19.8f, "CONSULT ROOM 1");
    drawRoomSign(-15.5f, 4.0f, -19.8f, "CONSULT ROOM 2");
}

// ------------------------------------------------------------------------
// SECTION 4 - PATIENT CABINS
//
// Layout from LEFT to RIGHT:
// [ SINGLE CABIN ] [ VIP CABIN ] [ GENERAL WARD ]
//
// Every room remains OPEN from the front so that:
// Bed, Visitor, TV, AC and Attached Bathroom are clearly visible.
// ------------------------------------------------------------------------

const float PC_X_LEFT = -16.0f;
const float PC_X_RIGHT = 16.0f;

const float PC_Z_BACK = -37.0f;
const float PC_Z_FRONT = -24.5f;

// Room division:
// Single Cabin = -16 to -6
// VIP Cabin    =  -6 to  4
// General Ward =   4 to 16
const float PC_DIV1_X = -6.0f;
const float PC_DIV2_X = 4.0f;


// ========================================================================
// Slightly enlarged bed for the cabin section
// Makes beds easier to see from the front camera.
// ========================================================================

void drawCabinBed(float x, float z, float rotY = 0.0f)
{
    glPushMatrix();

    glTranslatef(x, 0.0f, z);
    glRotatef(rotY, 0, 1, 0);

    // slightly larger than ER beds
    glScalef(1.15f, 1.10f, 1.15f);

    drawBed(0.0f, 0.0f, 0.0f);

    glPopMatrix();
}


// ========================================================================
// VIP sofa
// ========================================================================

void drawVIPCabinSofa(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    // Main sofa seat
    setColor(COL_DESK);
    drawBox(
        0.0f, 0.48f, 0.0f,
        2.5f, 0.30f, 0.90f
    );

    // Backrest
    drawBox(
        0.0f, 0.95f, -0.35f,
        2.5f, 0.75f, 0.20f
    );

    // Left arm rest
    setColor(COL_VIP_ACCENT);
    drawBox(
        -1.15f, 0.70f, 0.0f,
        0.20f, 0.55f, 0.90f
    );

    // Right arm rest
    drawBox(
        1.15f, 0.70f, 0.0f,
        0.20f, 0.55f, 0.90f
    );

    // Gold decorative strip
    drawBox(
        0.0f, 0.30f, 0.46f,
        2.3f, 0.08f, 0.05f
    );

    glPopMatrix();
}


// ========================================================================
// MAIN PATIENT CABIN BUILDING
// ========================================================================

void drawPatientCabinsBuilding()
{
    float cx = 0.0f;

    float cz =
        (PC_Z_BACK + PC_Z_FRONT) * 0.5f;

    float depth =
        PC_Z_FRONT - PC_Z_BACK;


    // ==============================================================
    // CALCULATE ROOM CENTERS AND WIDTHS
    // ==============================================================

    float singleCenterX =
        (PC_X_LEFT + PC_DIV1_X) * 0.5f;

    float singleWidth =
        PC_DIV1_X - PC_X_LEFT;


    float vipCenterX =
        (PC_DIV1_X + PC_DIV2_X) * 0.5f;

    float vipWidth =
        PC_DIV2_X - PC_DIV1_X;


    float wardCenterX =
        (PC_DIV2_X + PC_X_RIGHT) * 0.5f;

    float wardWidth =
        PC_X_RIGHT - PC_DIV2_X;



    // ==============================================================
    // SINGLE CABIN FLOOR - BLUE
    // ==============================================================

    setColor(COL_SINGLE_FLOOR);

    drawBox(
        singleCenterX,
        0.04f,
        cz,
        singleWidth - 0.15f,
        0.08f,
        depth - 0.20f
    );


    // ==============================================================
    // VIP CABIN FLOOR - GOLD
    // ==============================================================

    setColor(COL_VIP_FLOOR);

    drawBox(
        vipCenterX,
        0.04f,
        cz,
        vipWidth - 0.15f,
        0.08f,
        depth - 0.20f
    );


    // ==============================================================
    // GENERAL WARD FLOOR - GREEN
    // ==============================================================

    setColor(COL_WARD_FLOOR);

    drawBox(
        wardCenterX,
        0.04f,
        cz,
        wardWidth - 0.15f,
        0.08f,
        depth - 0.20f
    );



    // ==============================================================
    // BACK WALL
    // ==============================================================

    setColor(COL_CABIN_WALL);

    drawBox(
        cx,
        2.5f,
        PC_Z_BACK,
        PC_X_RIGHT - PC_X_LEFT,
        5.0f,
        0.30f
    );


    // ==============================================================
    // LEFT WALL
    // ==============================================================

    drawBox(
        PC_X_LEFT,
        2.5f,
        cz,
        0.30f,
        5.0f,
        depth
    );


    // ==============================================================
    // RIGHT WALL
    // ==============================================================

    drawBox(
        PC_X_RIGHT,
        2.5f,
        cz,
        0.30f,
        5.0f,
        depth
    );


    // ==============================================================
    // DARKER ROOM DIVIDERS
    // ==============================================================

    setColor(COL_CABIN_DIVIDER);


    drawBox(
        PC_DIV1_X,
        2.5f,
        cz,
        0.35f,
        5.0f,
        depth
    );


    drawBox(
        PC_DIV2_X,
        2.5f,
        cz,
        0.35f,
        5.0f,
        depth
    );



    // ==============================================================
    // FRONT FLOOR BORDER / THRESHOLD
    // ==============================================================

    setColor(COL_CABIN_TRIM);


    // Single cabin front border
    drawBox(
        singleCenterX,
        0.10f,
        PC_Z_FRONT,
        singleWidth,
        0.15f,
        0.18f
    );


    // VIP front border
    setColor(COL_VIP_ACCENT);

    drawBox(
        vipCenterX,
        0.10f,
        PC_Z_FRONT,
        vipWidth,
        0.15f,
        0.18f
    );


    // General ward front border
    setColor(COL_MEDICAL_GREEN);

    drawBox(
        wardCenterX,
        0.10f,
        PC_Z_FRONT,
        wardWidth,
        0.15f,
        0.18f
    );



    // ==============================================================
    // ROOF
    // ==============================================================

    setColor(COL_ROOF);

    drawBox(
        cx,
        5.2f,
        cz,
        (PC_X_RIGHT - PC_X_LEFT) + 0.6f,
        0.40f,
        depth + 0.6f
    );



    // ==============================================================
    // MAIN PATIENT CABINS SIGN
    // ==============================================================

    setColor(COL_SIGN_BG);

    drawBox(
        0.0f,
        4.65f,
        PC_Z_FRONT - 0.05f,
        7.0f,
        0.75f,
        0.08f
    );


    setColor(COL_SIGN_CROSS);

    // cross vertical
    drawBox(
        -3.20f,
        4.65f,
        PC_Z_FRONT - 0.01f,
        0.22f,
        0.48f,
        0.04f
    );

    // cross horizontal
    drawBox(
        -3.20f,
        4.65f,
        PC_Z_FRONT - 0.01f,
        0.48f,
        0.22f,
        0.04f
    );


    drawText(
        -2.60f,
        4.48f,
        PC_Z_FRONT,
        GLUT_BITMAP_HELVETICA_18,
        "PATIENT CABINS"
    );



    // ==============================================================
    // INDIVIDUAL ROOM LABELS
    // ==============================================================

    drawRoomSign(
        singleCenterX,
        3.85f,
        PC_Z_FRONT + 0.04f,
        "SINGLE CABIN"
    );


    drawRoomSign(
        vipCenterX,
        3.85f,
        PC_Z_FRONT + 0.04f,
        "VIP CABIN"
    );


    drawRoomSign(
        wardCenterX,
        3.85f,
        PC_Z_FRONT + 0.04f,
        "GENERAL WARD"
    );
}

// ========================================================================
// 1. SINGLE CABIN
//
// Contains:
// - Single bed
// - Visitor
// - TV
// - AC
// - Attached bathroom
// ========================================================================

void drawSingleCabin()
{
    const float bedX = -11.0f;
    const float bedZ = -31.6f;


    // --------------------------------------------------------------------
    // SINGLE PATIENT BED
    // --------------------------------------------------------------------

    drawCabinBed(
        bedX,
        bedZ,
        0.0f
    );
    // Patient lying on Single Cabin bed
    drawPatientOnBed(
        bedX,
        bedZ,
        0.0f,
        COL_PATIENT_GOWN
    );

    // --------------------------------------------------------------------
    // VISITOR CHAIR
    // --------------------------------------------------------------------

    drawChair(
        -13.3f,
        -29.0f,
        180.0f,
        COL_DESK
    );


    // Visitor sitting on chair
    drawSeatedPerson(
        -13.3f,
        -29.0f,
        180.0f,
        COL_NURSE_UNIFORM,
        COL_SKIN
    );
    // Standing family member / attendant
    drawHuman(
        visitorWalkX,
        -28.8f,
        -20,
        COL_GATE_PILLAR,
        COL_SKIN,
        1
    );

    // --------------------------------------------------------------------
    // TV
    // Back wall
    // --------------------------------------------------------------------

    drawTV(
        -8.2f,
        2.65f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.20f
    );


    // --------------------------------------------------------------------
    // AIR CONDITIONER
    // --------------------------------------------------------------------

    drawACUnit(
        -11.5f,
        4.05f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.10f
    );


    // --------------------------------------------------------------------
    // ATTACHED BATHROOM
    //
    // Placed in BACK-LEFT corner.
    // It no longer blocks the front view.
    // --------------------------------------------------------------------

    drawBathroomCorner(
        -14.5f,
        -35.4f,
        0.0f
    );


    // --------------------------------------------------------------------
    // ROOM SIGN
    // --------------------------------------------------------------------

    drawRoomSign(
        -11.0f,
        4.35f,
        PC_Z_BACK + 0.20f,
        "SINGLE CABIN"
    );
    drawBedsideTable(
        -9.5f,
        -31.5f
    );


    drawWallClock(
        -11,
        3.2,
        PC_Z_BACK + 0.1
    );


    drawOxygenOutlet(
        -10,
        -30
    );
}


// ========================================================================
// 2. VIP CABIN
//
// Contains:
// - VIP patient bed
// - Sofa
// - Visitor
// - TV
// - AC
// - Attached bathroom
// - Gold VIP decoration
// ========================================================================

void drawVIPCabin()
{
    const float bedX = -1.0f;
    const float bedZ = -31.6f;


    // --------------------------------------------------------------------
    // VIP PATIENT BED
    // --------------------------------------------------------------------

    drawCabinBed(
        bedX,
        bedZ,
        0.0f
    );
    // VIP Cabin Patient
    drawPatientOnBed(
        bedX,
        bedZ,
        0.0f,
        COL_PATIENT_GOWN_2
    );
    drawHuman(
        0.5f,
        nurseWalkZ,
        -90,
        COL_NURSE_UNIFORM,
        COL_SKIN,
        2
    );
    // --------------------------------------------------------------------
    // GOLD DECORATIVE STRIP ON BED
    // --------------------------------------------------------------------

    setColor(COL_VIP_ACCENT);

    drawBox(
        bedX,
        0.72f,
        bedZ + 0.85f,
        1.20f,
        0.05f,
        0.22f
    );


    // --------------------------------------------------------------------
    // VIP VISITOR SOFA
    // --------------------------------------------------------------------

    drawVIPCabinSofa(
        -1.5f,
        -28.5f
    );


    // Visitor sitting on sofa
    drawSeatedPerson(
        -1.5f,
        -28.5f,
        0.0f,
        COL_GATE_PILLAR,
        COL_SKIN
    );


    // --------------------------------------------------------------------
    // TV
    // --------------------------------------------------------------------

    drawTV(
        2.0f,
        2.65f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.25f
    );


    // --------------------------------------------------------------------
    // AIR CONDITIONER
    // --------------------------------------------------------------------

    drawACUnit(
        -1.0f,
        4.05f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.15f
    );


    // --------------------------------------------------------------------
    // ATTACHED BATHROOM
    // Back-right corner of VIP cabin
    // --------------------------------------------------------------------

    drawBathroomCorner(
        2.4f,
        -35.4f,
        0.0f
    );


    // --------------------------------------------------------------------
    // VIP CABIN SIGN
    // --------------------------------------------------------------------

    drawRoomSign(
        -1.0f,
        4.35f,
        PC_Z_BACK + 0.20f,
        "VIP CABIN"
    );
    drawBedsideTable(
        0.5f,
        -31.5f
    );


    drawWallClock(
        -1,
        3.2,
        PC_Z_BACK + 0.1
    );
}


// ========================================================================
// 3. GENERAL WARD
//
// Contains:
// - 4 patient beds
// - Curtain dividers
// - Multiple visitors
// - Shared TV
// - 2 AC units
// - Attached bathroom
// ========================================================================

void drawGeneralWard()
{
    const float bedZ = -31.8f;


    // --------------------------------------------------------------------
    // FOUR PATIENT BEDS
    // --------------------------------------------------------------------

    float bedXs[4] =
    {
        5.5f,
        8.5f,
        11.5f,
        14.5f
    };


    for (int i = 0; i < 4; i++)
    {
        drawCabinBed(
            bedXs[i],
            bedZ,
            0.0f
        );


        // Every bed now contains a patient
        drawPatientOnBed(
            bedXs[i],
            bedZ,
            0.0f,
            (i % 2 == 0)
            ? COL_PATIENT_GOWN
            : COL_PATIENT_GOWN_2
        );
    }


    // --------------------------------------------------------------------
    // PRIVACY CURTAINS
    // --------------------------------------------------------------------

    float curtainXs[3] =
    {
        7.0f,
        10.0f,
        13.0f
    };


    setColor(COL_CURTAIN);


    for (int i = 0; i < 3; i++)
    {
        drawBox(
            curtainXs[i],
            1.25f,
            bedZ,
            0.05f,
            2.50f,
            2.40f
        );
    }


    // --------------------------------------------------------------------
    // VISITOR 1
    // Sitting beside first bed
    // --------------------------------------------------------------------

    drawChair(
        5.5f,
        -28.8f,
        180.0f,
        COL_DESK
    );


    drawSeatedPerson(
        5.5f,
        -28.8f,
        180.0f,
        COL_TREE_LEAF,
        COL_SKIN
    );


    // --------------------------------------------------------------------
    // VISITOR 2
    // Standing beside third bed
    // --------------------------------------------------------------------

    drawHuman(
        cabinNurseX,
        -29.1f,
        190.0f,
        COL_NURSE_UNIFORM,
        COL_SKIN,
        2
    );


    // --------------------------------------------------------------------
    // SHARED TV
    // Larger than cabin TVs
    // --------------------------------------------------------------------

    drawTV(
        10.0f,
        2.70f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.45f
    );


    // --------------------------------------------------------------------
    // AIR CONDITIONER 1
    // --------------------------------------------------------------------

    drawACUnit(
        6.0f,
        4.10f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.10f
    );


    // --------------------------------------------------------------------
    // AIR CONDITIONER 2
    // --------------------------------------------------------------------

    drawACUnit(
        14.0f,
        4.10f,
        PC_Z_BACK + 0.20f,
        0.0f,
        1.10f
    );


    // --------------------------------------------------------------------
    // ATTACHED BATHROOM
    // Back-right corner
    // --------------------------------------------------------------------

    drawBathroomCorner(
        14.6f,
        -35.4f,
        0.0f
    );


    // --------------------------------------------------------------------
    // GENERAL WARD SIGN
    // --------------------------------------------------------------------

    drawRoomSign(
        10.0f,
        4.35f,
        PC_Z_BACK + 0.20f,
        "GENERAL WARD"
    );
    for (int i = 0; i < 4; i++)
    {
        drawBedsideTable(
            bedXs[i] + 0.7f,
            bedZ
        );
    }
}

// ----------------------------------------------------------------------
// Lighting setup
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// Realistic Hospital Lighting
// ----------------------------------------------------------------------

void setupLighting()
{

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);


    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );


    GLfloat lightPosition[] =
    {
        15.0f,
        30.0f,
        20.0f,
        1.0f
    };


    GLfloat ambient[] =
    {
    0.25f,
    0.25f,
    0.25f,
    1.0f
    };


    GLfloat diffuse[] =
    {
        0.85f,
        0.85f,
        0.85f,
        1.0f
    };


    GLfloat specular[] =
    {
        0.25f,
        0.25f,
        0.25f,
        1.0f
    };


    glLightfv(
        GL_LIGHT0,
        GL_POSITION,
        lightPosition
    );


    glLightfv(
        GL_LIGHT0,
        GL_AMBIENT,
        ambient
    );


    glLightfv(
        GL_LIGHT0,
        GL_DIFFUSE,
        diffuse
    );


    glLightfv(
        GL_LIGHT0,
        GL_SPECULAR,
        specular
    );


    GLfloat globalAmbient[] =
    {
        0.35f,
        0.35f,
        0.35f,
        1.0f
    };


    glLightModelfv(
        GL_LIGHT_MODEL_AMBIENT,
        globalAmbient
    );


    // smoother object appearance

    glEnable(GL_NORMALIZE);

}

// ----------------------------------------------------------------------
// GLUT callbacks
// ----------------------------------------------------------------------
void display() {
    // hospital daylight sky
    glClearColor(
        0.65f,
        0.82f,
        0.95f,
        1.0f
    );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    float lookX = camX + sinf(camAngle * (float)M_PI / 180.0f);

    float lookY = camHeight;

    float lookZ = camZ - cosf(camAngle * (float)M_PI / 180.0f);


    gluLookAt(
        camX,
        camHeight,
        camZ,

        lookX,
        lookY,
        lookZ,

        0,
        1,
        0
    );

    drawGround();
    drawMainGate();
    drawParkingArea();

    drawAmbulanceBay();
    {
        Vec2 p = getAmbulancePos();
        float heading = getAmbulanceHeading();
        drawAmbulanceVehicle(p.x, 0.9f, p.z, heading, ambLightOn);
    }

    drawReceptionBuilding();
    drawWaitingArea();
    drawSecurityDesk();
    drawTrees();

    // Emergency Department
    drawERBuilding();
    drawEmergencyBeds();
    drawWheelchairsER();
    drawMedicalEquipment();
    drawERStaff();
    drawNurseStation();

    // Outpatient Department
    drawOPDBuilding();
    drawRegistrationDesk();
    drawWaitingQueueOPD();
    drawDoctorChambers();
    drawConsultationRooms();

    // Patient Cabins Wing
    drawPatientCabinsBuilding();
    drawSingleCabin();
    drawVIPCabin();
    drawGeneralWard();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int, int) {
    const float moveSpeed = 1.0f;
    const float turnSpeed = 3.0f;

    if (key == GLUT_KEY_UP)
    {

        float angle = camAngle * (float)M_PI / 180.0f;


        camX += moveSpeed * sinf(angle);

        camZ -= moveSpeed * cosf(angle);


    }
    else if (key == GLUT_KEY_DOWN) {
        camX -= moveSpeed * sinf(camAngle * (float)M_PI / 180.0f);
        camZ += moveSpeed * cosf(camAngle * (float)M_PI / 180.0f);
    }
    else if (key == GLUT_KEY_LEFT) {
        camAngle -= turnSpeed;
    }
    else if (key == GLUT_KEY_RIGHT) {
        camAngle += turnSpeed;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) {
        exit(0);
    }
    else if (key == 'w' || key == 'W') {
        camHeight += 0.5f;
    }
    else if (key == 's' || key == 'S') {
        camHeight -= 0.5f;
    }
    else if (key == 'r' || key == 'R')
    {

        camX = 0.0f;

        camY = 10.0f;

        camZ = 65.0f;


        camAngle = 0.0f;

        camHeight = 10.0f;

    }
    glutPostRedisplay();
}

// ----------------------------------------------------------------------
// Ambulance animation timer: advances the ambulance along its path,
// pauses at each end, reverses direction, and loops forever.
// ----------------------------------------------------------------------
void updateAmbulance(int value)
{
    const float speed = 0.02f;


    // ==========================================================
    // AMBULANCE MOVEMENT
    // ==========================================================

    if (ambPauseTimer > 0)
    {
        ambPauseTimer--;
    }
    else
    {
        ambT += ambDir * speed;


        // Ambulance reached hospital
        if (ambT >= 3.0f)
        {
            ambT = 3.0f;
            ambDir = -1;

            // wait before going back
            ambPauseTimer = 100;
        }


        // Ambulance returned outside
        else if (ambT <= 0.0f)
        {
            ambT = 0.0f;
            ambDir = 1;

            // wait before next arrival
            ambPauseTimer = 80;
        }
    }
    // ==========================================================
// VISITOR WALKING ANIMATION
// ==========================================================

    visitorWalkX += visitorDirection * 0.02f;


    if (visitorWalkX > -8.5f)
    {
        visitorDirection = -1;
    }


    if (visitorWalkX < -12.5f)
    {
        visitorDirection = 1;
    }
    nurseWalkZ += nurseDirection * 0.02f;


    if (nurseWalkZ > -7)
    {
        nurseDirection = -1;
    }


    if (nurseWalkZ < -13)
    {
        nurseDirection = 1;
    }

    // ==========================================================
    // AMBULANCE BLINKING LIGHT
    // ==========================================================

    ambLightTimer++;

    if (ambLightTimer >= 10)
    {
        ambLightTimer = 0;

        ambLightOn = !ambLightOn;
    }



    // ==========================================================
    // GENERAL WARD MOVING NURSE
    // ==========================================================

    cabinNurseX += cabinNurseDir * 0.035f;


    // Nurse reached right side
    if (cabinNurseX >= 14.0f)
    {
        cabinNurseX = 14.0f;

        // Now move left
        cabinNurseDir = -1;
    }


    // Nurse reached left side
    else if (cabinNurseX <= 5.5f)
    {
        cabinNurseX = 5.5f;

        // Now move right
        cabinNurseDir = 1;
    }



    // ==========================================================
    // REDRAW SCREEN
    // ==========================================================

    glutPostRedisplay();


    // Run this function again after 30 milliseconds
    glutTimerFunc(
        30,
        updateAmbulance,
        0
    );
}

void init() {
    glEnable(GL_DEPTH_TEST);
    setupLighting();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("3D Hospital Management System - Entrance + ER");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, updateAmbulance, 0);

    glutMainLoop();
    return 0;
}