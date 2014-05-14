#include <Tool.h>

/** Constructor */
Tool::Tool()
    :pSelected(nullptr)
{
}

Tool::Tool(qdt::QuadTreeOccupant* pOccupant)
    :pSelected(pOccupant)
{
}


/** Copy Constructor */
/*
Tool::Tool (const Tool& other)
    :pSelected(other.pSelected)
{
}
*/

/** Move Constructor */
/*
Tool::Tool (Tool&& other)
    :pSelected(other.pSelected)
{
    other.pSelected = nullptr;
}
*/

/** Destructor */
Tool::~Tool()
{
    //since the pointer is only a observer imma not delete it here
}


/** Copy Assignment Operator */
/*
Tool& Tool::operator= (const Tool& other)
{
    Tool temporary (other);
    std::swap (pSelected, temporary.pSelected);
    return *this;
}
*/

/** Move Assignment Operator */
/*
Tool& Tool::operator= (Tool&& other)
{
    std::swap (pSelected, other.pSelected);
    return *this;
}
*/


void Tool::SetSelected(qdt::QuadTreeOccupant* pOccupant)
{
    pSelected = pOccupant;
}

void Tool::OnUpdate()
{

}

void Tool::OnRender()
{

}

void Tool::OnEvent(const Rocket::Core::Event& event)
{

}

void Tool::DisplayData()
{

}
