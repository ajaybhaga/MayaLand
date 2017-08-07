#include "Cursor.h"

using namespace std;

Cursor::Cursor(World *W) : DynamicObject(W, 10.f, true)
{
    speed = 200.f;

    position.x = 512.f;
    position.z = 512.f;

    setSize(64.f);
}

void Cursor::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
     //   setPath(world->mouseX, world->mouseY);

        position.x = world->mouseX;
        position.z = world->mouseY;

    }
}

void Cursor::draw()
{
    glColor4f(1.f, 0.8f, 0.f, 1.f);

    int mapWidth = Conf::WORLD_WIDTH/Conf::TILE_SIZE;
    int mapHeight = Conf::WORLD_HEIGHT/Conf::TILE_SIZE;
    int dimSize = mapWidth*mapHeight;

    int gridX = (position.x/Conf::TILE_SIZE);
    int gridY = (position.z/Conf::TILE_SIZE);
    int m = gridY*mapWidth + gridX;

    if (world->getHeightMap()) {
        int* heightMap = world->getHeightMap();

        int m = gridY*mapWidth + gridX;
        int mNextRow = (gridY+1)*mapWidth + gridX;

        if (mNextRow+1 < dimSize) {
            int h1 = heightMap[m];
            int h2 = heightMap[m+1];
            int h3 = heightMap[mNextRow];
            int h4 = heightMap[mNextRow+1];

            float hAvg = (h1 + h2 + h3 + h4)/4.0f;
            position.y = hAvg;
        }
        //std::cout << "gridX=" << gridX << " gridY=" << gridY << " m=" << m << std::endl;
    }

    rotation.y += 0.08f;

    glPushMatrix();
    glRotatef(rotation.x, 1.f, 0.f, 0.f);
    glRotatef(rotation.y, 0.f, 1.f, 0.f);
    glRotatef(rotation.z, 0.f, 0.f, 1.f);
    Object::draw();
    glPopMatrix();
}

void Cursor::update(float time)
{
    move(time);
}


void Cursor::drawOutline()
{
    //glColor4f(0.9f, 0.9f, 0.9f, 0.7f);

    glColor4f(0.f, 0.f, 0.f, 0.6f);

    glLineWidth(0.9);

    glPushMatrix();
    glRotatef(rotation.x, 1.f, 0.f, 0.f);
    glRotatef(rotation.y, 0.f, 1.f, 0.f);
    glRotatef(rotation.z, 0.f, 0.f, 1.f);

    glBegin(GL_LINE_LOOP);

    // First two triangles are top face
    for (unsigned int i = 0; i < shape.getTriangles().size(); i ++)
    {
        shape.getTriangles()[i].setAllVertex();
    }
    glEnd();
    glPopMatrix();
}
