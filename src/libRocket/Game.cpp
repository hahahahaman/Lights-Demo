#include "Game.h"
#include "GameDetails.h"
#include <Rocket/Core.h>
#include "ShellSFML.h"
#include "EventManager.h"

// The game's element Context (declared in main.cpp).
extern Rocket::Core::Context* Context;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialise()
{
    pRender_Window = Shell::GetWindowHandle();
    //pRender_Window->setVerticalSyncEnabled(true);

    sf::Vector2f screen_dimension(float(pRender_Window->getSize().x), float(pRender_Window->getSize().y));

    pLight_System = std::unique_ptr<ltbl::LightSystem>( new ltbl::LightSystem(AABB(sf::Vector2f(-screen_dimension.x, -screen_dimension.y), sf::Vector2f(float(pRender_Window->getSize().x), float(pRender_Window->getSize().y))),
                    //AABB(sf::Vector2f(-screen_dimension.x, -screen_dimension.y), sf::Vector2f(float(pRender_Window->getSize().x) *2.f, float(pRender_Window->getSize().y)*2.f )),
                    pRender_Window,
                    "data/lightFin.png",
                    "data/shaders/lightAttenuationShader.frag") );

    pLight_System->setView(pRender_Window->getView());
    //pLight_System.m_ambientColor = sf::Color::White;
    pLight_System->m_useBloom = true;
    pLight_System->m_checkForHullIntersect = true;
    pLight_System->m_obliqueShadows = true;

    //default to Mouse tool
    GameDetails::SetTool(GameDetails::TOOL_MOUSE);
    //CreateLight();

    GameDetails::pSelected =  nullptr;
    GameDetails::SelectedTool = GameDetails::TOOL_MOUSE;

    std::string str = "data/background.tga";

    sp_background.setTexture(*(gTextureManager.getResource(str)));
    sp_background.setScale(pRender_Window->getView().getSize().x / float(gTextureManager.getResource(str)->getSize().x),
                           pRender_Window->getView().getSize().y / float(gTextureManager.getResource(str)->getSize().y));

    hull = new ltbl::ConvexHull();
    hull->loadShape("data/testShape.txt");
    hull->setWorldCenter(sf::Vector2f(500.f, 500.f));
    hull->setFillColor(sf::Color(0.f, 255.0f, 255.0f, 255.f));
    hull->setRenderLightOverHull(false);
    pLight_System->addConvexHull(hull);
}

void Game::Update()
{
    if(GameDetails::ChangeTool)
        ResetTool();

    UpdateTool();

    if(GameDetails::GetTool() == GameDetails::TOOL_LIGHT)
    {
        DisplayLightPointEditorData();
    }
    else if(GameDetails::GetTool() == GameDetails::TOOL_EMISSIVE)
    {
        DisplayEmissiveLightEditorData();
    }
    else if(GameDetails::GetTool() == GameDetails::TOOL_MOUSE)
    {
        if(GameDetails::SelectedTool == GameDetails::TOOL_LIGHT)
        {
            DisplayLightPointEditorData();
        }
        else if(GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE)
        {
            DisplayEmissiveLightEditorData();
        }
    }

    //AABB* aabb = pSelectedLight->getAABB();
    //printf("Bounds:(%f, %f) (%f, %f)\n", aabb->getLowerBound().x, aabb->getLowerBound().y, aabb->getUpperBound().x, aabb->getUpperBound().y);
    //pSelectedLight->setRadius(float(rand()) / (float(RAND_MAX)/ 1000.f));
}

void Game::Render()
{
    pRender_Window->pushGLStates();
    pRender_Window->draw(sp_background);

    // calculate the lights
    pLight_System->renderLights();

    // Draw the lights
    pLight_System->renderLightTexture();

    if(GameDetails::Debug)
        pLight_System->debugRender();

    //Selection Box
    if(GameDetails::pSelected != nullptr)
    {
        if(GameDetails::GetTool() == GameDetails::TOOL_EMISSIVE)
        {
            static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected)->getAABB().debugRender();
        }
        else if(GameDetails::GetTool() == GameDetails::TOOL_LIGHT)
        {
            static_cast<ltbl::Light_Point*>(GameDetails::pSelected)->getAABB().debugRender();
        }
        else if(GameDetails::GetTool() == GameDetails::TOOL_MOUSE)
        {
            if(GameDetails::SelectedTool == GameDetails::TOOL_LIGHT)
            {
                static_cast<ltbl::Light_Point*>(GameDetails::pSelected)->getAABB().debugRender();
            }
            else if(GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE)
            {
                static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected)->getAABB().debugRender();
            }
        }

    }

    pRender_Window->popGLStates();

}

void Game::CreateLight()
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

    pLight_System->addLight(newLight);

    GameDetails::pSelected = static_cast<qdt::QuadTreeOccupant*>(newLight);

    //pSelectedLight = newLight;
    //GameDetails::pSelectedLight =pSelectedLight;

}

void Game::CreateEmissiveLight()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*pRender_Window);
    ltbl::EmissiveLight* newLight = new ltbl::EmissiveLight();

    newLight->setTexture(gTextureManager.getResource("data/emissive.png"));
    newLight->setCenter(sf::Vector2f(float(mousePos.x), float(mousePos.y)));
    newLight->setIntensity(1.5f); //affects whether or not the light is drawn, if it is <= 1 it will not draws
    newLight->setColor(GameDetails::d_EmColor);
    newLight->setDims(GameDetails::d_EmDims);
    newLight->setRotation(GameDetails::d_EmRotation);

    pLight_System->addEmissiveLight(newLight);

    GameDetails::pSelected = static_cast<qdt::QuadTreeOccupant*>(newLight);

    //pSelectedEmissiveLight = newLight;
    //GameDetails::pSelectedEmissiveLight = newLight;
}

void Game::DisplayLightPointEditorData()
{
    if(GameDetails::pSelected != nullptr &&
            (GameDetails::GetTool() == GameDetails::TOOL_LIGHT ||
             (GameDetails::GetTool() == GameDetails::TOOL_MOUSE && GameDetails::SelectedTool == GameDetails::TOOL_LIGHT)))
    {
        ltbl::Light_Point* pSelectedLight = static_cast<ltbl::Light_Point*>(GameDetails::pSelected);

        //display all the values in the Light Point Editor
        Rocket::Core::Element* out_center_x_element = Context->GetDocument("light_point_editor")->GetElementById("out_center_x");
        if (out_center_x_element != NULL)
            out_center_x_element->SetInnerRML(Rocket::Core::String(7, "%d", (int)pSelectedLight->getCenter().x).CString());

        Rocket::Core::Element* out_center_y_element = Context->GetDocument("light_point_editor")->GetElementById("out_center_y");
        if (out_center_y_element != NULL)
            out_center_y_element->SetInnerRML(Rocket::Core::String(7, "%d", (int)pSelectedLight->getCenter().y).CString());

        Rocket::Core::Element* out_radius_element = Context->GetDocument("light_point_editor")->GetElementById("out_radius");
        if (out_radius_element!= NULL)
            out_radius_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getRadius()).CString());

        Rocket::Core::Element* out_color_r_element = Context->GetDocument("light_point_editor")->GetElementById("out_color_r");
        if (out_color_r_element != NULL)
            out_color_r_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getColor().x).CString());

        Rocket::Core::Element* out_color_g_element = Context->GetDocument("light_point_editor")->GetElementById("out_color_g");
        if (out_color_g_element != NULL)
            out_color_g_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getColor().y).CString());

        Rocket::Core::Element* out_color_b_element = Context->GetDocument("light_point_editor")->GetElementById("out_color_b");
        if (out_color_b_element != NULL)
            out_color_b_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getColor().z).CString());

        Rocket::Core::Element* out_size_element = Context->GetDocument("light_point_editor")->GetElementById("out_size");
        if (out_size_element != NULL)
            out_size_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getSize()).CString());

        Rocket::Core::Element* out_spread_angle_element = Context->GetDocument("light_point_editor")->GetElementById("out_spread_angle");
        if (out_spread_angle_element != NULL)
            out_spread_angle_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getSpreadAngle()).CString());

        Rocket::Core::Element* out_soft_spread_angle_element = Context->GetDocument("light_point_editor")->GetElementById("out_soft_spread_angle");
        if (out_soft_spread_angle_element != NULL)
            out_soft_spread_angle_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getSoftSpreadAngle()).CString());

        Rocket::Core::Element* out_direction_angle_element = Context->GetDocument("light_point_editor")->GetElementById("out_direction_angle");
        if (out_direction_angle_element != NULL)
            out_direction_angle_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getDirectionAngle()).CString());

        Rocket::Core::Element* out_bleed_element = Context->GetDocument("light_point_editor")->GetElementById("out_bleed");
        if (out_bleed_element != NULL)
            out_bleed_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getBleed()).CString());

        Rocket::Core::Element* out_linearize_factor_element = Context->GetDocument("light_point_editor")->GetElementById("out_linearize_factor");
        if (out_linearize_factor_element != NULL)
            out_linearize_factor_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedLight->getLinearizeFactor()).CString());
    }
}

void Game::DisplayEmissiveLightEditorData()
{
    if(GameDetails::pSelected != nullptr &&
            (GameDetails::GetTool() == GameDetails::TOOL_EMISSIVE ||
             (GameDetails::GetTool() == GameDetails::TOOL_MOUSE && GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE)))
    {
        ltbl::EmissiveLight* pSelectedEmissiveLight = static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected);

        //display all the values in the Emissive Light Editor
        Rocket::Core::Element* out_center_x_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_center_x");
        if (out_center_x_element != NULL)
            out_center_x_element->SetInnerRML(Rocket::Core::String(7, "%d", (int)pSelectedEmissiveLight->getCenter().x).CString());

        Rocket::Core::Element* out_center_y_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_center_y");
        if (out_center_y_element != NULL)
            out_center_y_element->SetInnerRML(Rocket::Core::String(7, "%d", (int)pSelectedEmissiveLight->getCenter().y).CString());

        Rocket::Core::Element* out_dim_width_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_dim_width");
        if (out_dim_width_element!= NULL)
            out_dim_width_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedEmissiveLight->getDims().x).CString());

        Rocket::Core::Element* out_dim_height_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_dim_height");
        if (out_dim_height_element != NULL)
            out_dim_height_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedEmissiveLight->getDims().y).CString());

        Rocket::Core::Element* out_color_r_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_color_r");
        if (out_color_r_element != NULL)
            out_color_r_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedEmissiveLight->getColor().x).CString());

        Rocket::Core::Element* out_color_g_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_color_g");
        if (out_color_g_element != NULL)
            out_color_g_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedEmissiveLight->getColor().y).CString());

        Rocket::Core::Element* out_color_b_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_color_b");
        if (out_color_b_element != NULL)
            out_color_b_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedEmissiveLight->getColor().z).CString());

        Rocket::Core::Element* out_rotation_element = Context->GetDocument("emissive_light_editor")->GetElementById("out_rotation");
        if (out_rotation_element != NULL)
            out_rotation_element->SetInnerRML(Rocket::Core::String(7, "%f", pSelectedEmissiveLight->getRotation()).CString());
    }
}

void Game::UpdateTool()
{
    GameDetails::Tool tool = GameDetails::GetTool();

    if(tool == GameDetails::TOOL_MOUSE)
    {
        Context->ShowMouseCursor(true);
        //Context->GetDocument("light_point_editor")->Hide();
    }
    else if(tool == GameDetails::TOOL_LIGHT)
    {
        Context->ShowMouseCursor(false);

        if(GameDetails::pSelected == nullptr)
        {
            CreateLight();
            //Context->GetDocument("light_point_editor")->Show();
        }

        ltbl::Light_Point* pSelectedLight = static_cast<ltbl::Light_Point*>(GameDetails::pSelected);

        sf::Vector2i mousePos = sf::Mouse::getPosition(*pRender_Window);

        // convert it to world coordinates
        sf::Vector2f worldPos = pRender_Window->mapPixelToCoords(mousePos);

        // Update light

        pSelectedLight->setCenter(sf::Vector2f(static_cast<float>(worldPos.x),
                                               static_cast<float>(worldPos.y)));

    }
    else if(tool == GameDetails::TOOL_EMISSIVE)
    {
        Context->ShowMouseCursor(false);

        if(GameDetails::pSelected == nullptr)
        {
            CreateEmissiveLight();
        }

        ltbl::EmissiveLight* pSelectedEmissiveLight = static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected);

        sf::Vector2i mousePos = sf::Mouse::getPosition(*pRender_Window);

        // convert it to world coordinates
        sf::Vector2f worldPos = pRender_Window->mapPixelToCoords(mousePos);

        // Update light
        pSelectedEmissiveLight->setCenter(sf::Vector2f(static_cast<float>(worldPos.x),
                                          static_cast<float>(worldPos.y)));

        //fixes up the issue of the change in center changing the dimensions of the rotation
        pSelectedEmissiveLight->setRotation(GameDetails::d_EmRotation);
    }
    //pRender_Window->resetGLStates();
}

void Game::ResetTool()
{
    GameDetails::ChangeTool = false;

    if(GameDetails::PreviousTool != GameDetails::TOOL_MOUSE)
    {
        if(GameDetails::pSelected != nullptr)
        {
            if(GameDetails::PreviousTool == GameDetails::TOOL_LIGHT)
            {
                pLight_System->removeLight(static_cast<ltbl::Light_Point*>(GameDetails::pSelected));
            }
            else if(GameDetails::PreviousTool == GameDetails::TOOL_EMISSIVE)
            {
                pLight_System->removeEmissiveLight(static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected));
            }
            ClearSelection();
        }
    }
    else
        ClearSelection();
}

void Game::ClearSelection()
{
    GameDetails::pSelected = nullptr;
    //GameDetails::SelectedTool = GameDetails::TOOL_MOUSE;
}

void Game::QueryRegion()
{
    ClearSelection();

    //max size for selecting objets
    //sf::Vector2f maxDims(200.f, 200.f);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*pRender_Window);

    // convert it to world coordinates
    sf::Vector2f worldPos = pRender_Window->mapPixelToCoords(mousePos);

    qdt::QuadTree* lightTree = pLight_System->getLightTree();
    qdt::QuadTree* emissiveTree = pLight_System->getEmissiveTree();

    std::vector<qdt::QuadTreeOccupant*> selection;

    lightTree->query_Region(AABB(sf::Vector2f(worldPos.x - 10.f, worldPos.y -10.f), sf::Vector2f(worldPos.x + 10.f, worldPos.y + 10.f)), selection);
    if(selection.size() > 0)
    {
        GameDetails::pSelected = selection[0];
        GameDetails::SelectedTool = GameDetails::TOOL_LIGHT;
    }
    else
    {
        emissiveTree->query_Region(AABB(sf::Vector2f(worldPos.x - 10.f, worldPos.y -10.f), sf::Vector2f(worldPos.x + 10.f, worldPos.y + 10.f)), selection);

        if(selection.size() > 0)
        {
            GameDetails::pSelected = selection[0];
            GameDetails::SelectedTool = GameDetails::TOOL_EMISSIVE;
        }
        else
        {

        }
    }
}
