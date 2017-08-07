#include "Tile.h"

/*
 * Height vertices:
 * h1 = left
 * h2 = top
 * h3 = right
 * h4 = bottom
 *
 */

Tile::Tile(World *W, float x, float y, float z, float h1, float h2, float h3, float h4) : StaticObject(W, h1, true, true)
{
    position.x = x;
    position.y = y;
    position.z = z;   

    size = Conf::TILE_SIZE;

    float halfSize = size / 2.f;

    shape.clear();

    p1 = Point(-halfSize, h1, -halfSize);
    p2 = Point( halfSize, h2, -halfSize);
    p3 = Point( halfSize, h4,  halfSize);
    p4 = Point(-halfSize, h3,  halfSize);

    //generateColour();


    /*
    if (dynamicGenerate) {
        generateColour();
        p1.y = 0.0f + (rand() % 200);
        p2.y = 0.0f + (rand() % 200);
        p3.y = 0.0f + (rand() % 200);
        p4.y = 0.0f + (rand() % 200);
    }*/

    // FACE TOP
    shape.addTriangle(&p1, &p2, &p3);
    shape.addTriangle(&p3, &p4, &p1);
    //std::cout << "p4e.y=" << p4e.y << std::endl;

    //shape.addTriangle(&p3, &p4, &p1);


        p5 = Point(-halfSize, 0.f,  halfSize);
        p6 = Point( halfSize, 0.f,  halfSize);
        p7 = Point( halfSize, 0.f, -halfSize);
        p8 = Point(-halfSize, 0.f, -halfSize);

        // FACE FRONT LEFT
        shape.addTriangle(&p5, &p4, &p3);
        shape.addTriangle(&p3, &p6, &p5);

        // FACE FRONT RIGHT
        shape.addTriangle(&p6, &p3, &p2);
        shape.addTriangle(&p2, &p7, &p6);

        // FACE BACK LEFT
        shape.addTriangle(&p1, &p4, &p5);
        shape.addTriangle(&p5, &p8, &p1);

        // FACE BACK RIGHT
        shape.addTriangle(&p2, &p1, &p8);
        shape.addTriangle(&p8, &p7, &p2);

        // FACE BOTTOM
        shape.addTriangle(&p5, &p6, &p7);
        shape.addTriangle(&p7, &p8, &p5);


    shape.updateConnectivity();
}

void Tile::draw()
{
    /*
    if (getHeight() == 0)
    {
        glColor4f(0.9f, 0.9f, 0.9f, 1.f);
    }
    else
    {
        //glColor4f(0.4f, 0.4f, 0.4f, 1.f);
        glColor4f(Object::getR(), Object::getG(), Object::getB(), 1.f);
    }*/

    glColor4f(0.5f, 0.45f, 0.3f, 1.f);

    Object::draw();

/*    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Object::drawOutline();

    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDisable(GL_BLEND);*/

}

void Tile::generateColour() {
    int n;
    // Generate colour
    n = rand () % 10;
    r = n * 0.1f;
    n = rand () % 10;
    g = n * 0.1f;
    n = rand () % 10;
    b = n * 0.1f;
}

void Tile::drawOutline()
{
    glColor4f(0.9f, 0.9f, 0.9f, 0.7f);

    //glColor4f(0.f, 0.f, 0.f, 0.3);

    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    //shape.getTriangles().size()

    // First two triangles are top face
    for (unsigned int i = 0; i < 2; i ++)
    {
        shape.getTriangles()[i].setAllVertex();
    }
    glEnd();

}
