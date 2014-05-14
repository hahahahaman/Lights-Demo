#include "GameDetails.h"

qdt::QuadTreeOccupant* GameDetails::pSelected = nullptr;

bool GameDetails::Debug = false;
bool GameDetails::HideUI = false;

bool GameDetails::ChangeTool = false;

static GameDetails::Tool CurrentTool = GameDetails::TOOL_LIGHT;
GameDetails::Tool GameDetails::PreviousTool = CurrentTool;
GameDetails::Tool GameDetails::SelectedTool = TOOL_MOUSE;

//default values for light point
float GameDetails::d_Radius = 50.f;
sf::Vector3f GameDetails::d_Color(1.0f, 1.0f, 1.0f);
float GameDetails::d_Size(10.f);
float GameDetails::d_SpreadAngle(360.f);
float GameDetails::d_SoftSpreadAngle(0.f);
float GameDetails::d_DirectionAngle(0.f);
float GameDetails::d_Bleed(0.01f);
float GameDetails::d_LinearizeFactor(0.5f);

//default for emissive lights
sf::Vector2f GameDetails::d_EmDims(100.f, 50.f);
sf::Vector3f GameDetails::d_EmColor(1.0f, 1.0f, 1.0f);
float GameDetails::d_EmRotation(1.f);

sf::Vector2f AABB_diff(0.f, 0.f);

GameDetails::GameDetails()
{
}

GameDetails::~GameDetails()
{
}


void GameDetails::SetTool(GameDetails::Tool tool)
{
    if(tool != CurrentTool)
    {
        PreviousTool = CurrentTool;
        CurrentTool = tool;
        //SelectedTool = tool;

        ChangeTool = true;
    }
}

GameDetails::Tool GameDetails::GetTool()
{
    return CurrentTool;
}
