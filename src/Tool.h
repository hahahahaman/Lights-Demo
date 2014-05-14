#ifndef _TOOL_H_
#define _TOOL_H_
#include <iostream>
#include <cstdio>

#include <LTBL/QuadTree/QuadTree.h>
#include <Rocket/Core/Event.h>

/*****************************
was going to add more modularity
to the tool bar, but w/e
*****************************/

class Tool
{
public:
    //Constructor
    Tool();

    Tool(qdt::QuadTreeOccupant* pOccupant);
/*
    //Copy Constructor
    Tool(const Tool& other);

    //Move Constructor
    Tool(Tool&& other);
*/

    //Destructor
    virtual ~Tool();

/*
    //Copy Assignment Operator
    Tool& operator= (const Tool& other);

    //Move Assignment Operator
    Tool& operator= (Tool&& other);
*/

    void SetSelected(qdt::QuadTreeOccupant* pOccupant);

    virtual void OnUpdate();

    virtual void OnRender();

    virtual void OnEvent(const Rocket::Core::Event& event);

    virtual void DisplayData();

protected:
    qdt::QuadTreeOccupant* pSelected; //pointer is only an observer
private:
};


#endif // _TOOL_H_

