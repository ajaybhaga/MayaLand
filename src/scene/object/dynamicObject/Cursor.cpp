#include "Cursor.h"

using namespace std;

Cursor::Cursor(World *W) : DynamicObject(W, 10.f, true)
{
    speed = 200.f;

    position.x = 512.f;
    position.z = 512.f;

    //setSize(64.f);
    setPoints(anchor, position);
}

void Cursor::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
     //   setPath(world->mouseX, world->mouseY);

        // Set anchor
        if (anchor.x < 0) {
            anchor.x = world->mouseX;
            anchor.y = 0.0;
            anchor.z = world->mouseY;
        }

        if ((anchor.x > position.x) || (anchor.z > position.z)) {
            anchor.x = -1;
            anchor.y = -1;
            anchor.z = -1;
        }

        position.x = world->mouseX;
        position.y = 0.0;
        position.z = world->mouseY;

        setPoints(anchor, Vector3(position.x, 0.0, position.z));

        //std::cout << "anchor.x=" << anchor.x << " anchor.y=" << anchor.y << " anchor.z=" << anchor.z << std::endl;
        //std::cout << "position.x=" << position.x << " position.y=" << position.y << " position.z=" << position.z << std::endl;

    }

    if (type == World::ON_MOUSE_LEFT_UP) {
        anchor.x = -1;
        anchor.y = -1;
        anchor.z = -1;
        //std::cout << "Reset anchor." << std::endl;
    }
}

void Cursor::draw()
{
    if (anchor.x > 0) {
        glColor4f(0.3f, 1.0f, 0.3f, 0.5f);

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
              //  position.y = hAvg;
            }
            //std::cout << "gridX=" << gridX << " gridY=" << gridY << " m=" << m << std::endl;
        }

        rotation.y += 0.00f;

        glPushMatrix();

        // Reset matix
        glLoadIdentity();

        // Isometric angle
        glRotatef(30.f, 1.f, 0.f, 0.f);
        glRotatef(-45.f, 0.f, 1.f, 0.f);

        // Scale
        glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));

        // Reverse camera
        glTranslatef(-world->getCamera().getX(), -world->getCamera().getY(), -world->getCamera().getZ());

        glRotatef(rotation.x, 1.f, 0.f, 0.f);
        glRotatef(rotation.y, 0.f, 1.f, 0.f);
        glRotatef(rotation.z, 0.f, 0.f, 1.f);
        Object::draw();
        glPopMatrix();
    }
}

void Cursor::update(float time)
{
    move(time);
}


void Cursor::drawOutline()
{
    if (anchor.x > 0) {
        //glColor4f(0.9f, 0.9f, 0.9f, 0.7f);

        glColor4f(0.f, 0.f, 0.f, 0.6f);

        glLineWidth(0.9);

        glPushMatrix();

        // Reset matix
        glLoadIdentity();

        // Isometric angle
        glRotatef(30.f, 1.f, 0.f, 0.f);
        glRotatef(-45.f, 0.f, 1.f, 0.f);

        // Scale
        glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));

        // Reverse camera
        glTranslatef(-world->getCamera().getX(), -world->getCamera().getY(), -world->getCamera().getZ());

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
}
