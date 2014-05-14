#ifndef _TOOL_LIGHT_H_
#define _TOOL_LIGHT_H_

#include <Tool.h>
#include <LTBL/Light/LightSystem.h>
#include <Rocket/Core/Event.h>


/*****************************
was going to add more modularity
to the tool bar, but w/e
*****************************/

class ToolLight : public Tool
{
public:
    //Constructor
    ToolLight(ltbl::LightSystem* lSystem);

    /*
    //Copy Constructor
    ToolLight(const ToolLight& other);

    //Move Constructor
    ToolLight(ToolLight&& other);
*/

    //Destructor
    ~ToolLight();

    virtual void OnUpdate() override;

    virtual void OnRender() override;

    virtual void OnEvent(const Rocket::Core::Event& event) override;

    virtual void DisplayData() override;
protected:
private:
    //pointer to LightSystem, observer only
    ltbl::LightSystem* plSystem;
    void CreateLight();
};


#endif // _TOOL_LIGHT_H_

