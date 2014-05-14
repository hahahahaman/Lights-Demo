#ifndef _TOOL_MOUSE_H_
#define _TOOL_MOUSE_H_

#include <Tool.h>


/*****************************
was going to add more modularity
to the tool bar, but w/e
*****************************/

class ToolMouse: public Tool
{
public:
    ToolMouse();
    ~ToolMouse();

    virtual void OnUpdate() override;

    virtual void OnRender() override;

    virtual void OnEvent(const Rocket::Core::Event event&) override;

    virtual void DisplayData() override;
protected:
private:
};


#endif // _TOOL_MOUSE_H_

