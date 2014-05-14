#include <ToolLight.h>

#include "libRocket/GameDetails.h"

ToolLight::ToolLight(ltbl::LightSystem* lSystem)
    :plSystem(lSystem)
{

}

/*
//Copy Constructor
ToolLight::ToolLight(const ToolLight& other)
    : Tool::Tool(ToolLight), plSystem(other.plSystem)
{
        
}

//Move Constructor
ToolLight::ToolLight(ToolLight&& other)
    : Tool::Tool(ToolLight), plSystem(other.plSystem)
{
    other = nullptr;
}
*/

ToolLight::~ToolLight()
{
    plSystem = nullptr;
}

void ToolLight::OnUpdate()
{

}

void ToolLight::OnRender()
{

}

void ToolLight::OnEvent(const Rocket::Core::Event& event)
{

}

void ToolLight::DisplayData()
{

}

void ToolLight::CreateLight()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*pRender_Window);
    ltbl::Light_Point* newLight = new ltbl::Light_Point();

    newLight->setCenter(sf::Vector2f(float(mousePos.x), float(mousePos.y)));

    newLight->setIntensity(1.5f); //affects whether or not the light is drawn, if it is <= 1 it will not draw
    newLight->setColor(GameDetails::d_Color);

    newLight->setRadius(GameDetails::d_Radius); //increases the size of the texture and the light radius
    newLight->setSize(GameDetails::d_Size); //affects shadow fins and hull intersection
    newLight->setSpreadAngle(GameDetails::d_SpreadAngle);
    newLight->setSoftSpreadAngle(GameDetails::d_SoftSpreadAngle);
    newLight->setDirectionAngle(GameDetails::d_DirectionAngle);
    newLight->setBleed(GameDetails::d_Bleed); //this is how large the center light circle
    newLight->setLinearizeFactor(GameDetails::d_LinearizeFactor); //how oblique the light is
    //newLight->calculateAABB();

    plSystem->addLight(newLight);

    pSelected = static_cast<qdt::QuadTreeOccupant*>(newLight);
}
