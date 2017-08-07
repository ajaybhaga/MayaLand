#include "Player.h"

using namespace std;

Player::Player(World *W) : DynamicObject(W, 30.f, true)
{
    speed = 200.f;

    Object::setDynamicGenerate();

    position.x = 512.f;
    position.z = 512.f;
    setSize(64.f);
}

void Player::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
        setPath(world->mouseX, world->mouseY);
    }
}

void Player::draw()
{    
    glColor4f(Object::getR(), Object::getG(), Object::getB(), 1.f);

    int mapWidth = Conf::WORLD_WIDTH/Conf::TILE_SIZE;
    int mapHeight = Conf::WORLD_HEIGHT/Conf::TILE_SIZE;

    int gridX = (position.x/Conf::TILE_SIZE);
    int gridY = (position.z/Conf::TILE_SIZE);
    int m = gridY*mapWidth + gridX;

    if (world->getHeightMap()) {
        std::cout << "gridX=" << gridX << " gridY=" << gridY << " m=" << m << std::endl;
        int* heightMap = world->getHeightMap();
        std::cout << "heightMap[0]=" << heightMap[0] << std::endl;
        //position.y = world->getHeightMap()[m];
    }

    Object::draw();
}

void Player::update(float time)
{
    move(time);
}


void Player::drawOutline()
{
    //glColor4f(0.9f, 0.9f, 0.9f, 0.7f);

    glColor4f(0.f, 0.f, 0.f, 0.6f);

    glLineWidth(0.9);
    glBegin(GL_LINE_LOOP);
    //shape.getTriangles().size()

    // First two triangles are top face
    for (unsigned int i = 0; i < 6; i ++)
    {
        shape.getTriangles()[i].setAllVertex();
    }
    glEnd();

}
