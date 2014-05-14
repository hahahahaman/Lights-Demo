#ifndef GAMEDETAILS_H
#define GAMEDETAILS_H

#include <Rocket/Core/Types.h>
#include <LTBL/Light/Light_Point.h>
#include <LTBL/Light/EmissiveLight.h>
#include <LTBL/QuadTree/QuadTreeOccupant.h>

class GameDetails
{
public:
    enum Tool
    {
        TOOL_MOUSE = 0,
        TOOL_LIGHT,
        TOOL_EMISSIVE,
        TOOL_VERTEX,
        TOOL_CONVEXHULL,
        TOOL_IMAGE
    };

    static bool ChangeTool;
    static bool Debug;
    static bool HideUI;

    static qdt::QuadTreeOccupant* pSelected;

    static Tool SelectedTool;
    static Tool PreviousTool;

    //default for light point
    static float d_Radius;
    static sf::Vector3f d_Color;
    static float d_Size;
    static float d_SpreadAngle;
    static float d_SoftSpreadAngle;
    static float d_DirectionAngle;
    static float d_Bleed;
    static float d_LinearizeFactor;

    //default for emissive lights
    static sf::Vector2f d_EmDims;
    static sf::Vector3f d_EmColor;
    static float d_EmRotation;

    static sf::Vector2f AABB_diff;

    static void SetTool(Tool tool = TOOL_MOUSE);
    static Tool GetTool();

private:
    GameDetails();
    ~GameDetails();

};

#endif
