#include <Rocket/Core/Log.h>
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Controls.h>

#include "EventHandlerEmissiveLightEditor.h"
#include "EventManager.h"

#include <typeinfo>

EventHandlerEmissiveLightEditor::EventHandlerEmissiveLightEditor()
{

}

EventHandlerEmissiveLightEditor::~EventHandlerEmissiveLightEditor()
{

}

void EventHandlerEmissiveLightEditor::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
    // Rocket::Core::Element::ProcessEvent(event);
    if (value == "SetEmissiveLight")
    {
        SetData(event);
    }

    if(event == "keydown")
    {
        Rocket::Core::Input::KeyIdentifier key_identifier = (Rocket::Core::Input::KeyIdentifier) event.GetParameter< int >("key_identifier", 0);
        if(key_identifier == Rocket::Core::Input::KI_RETURN)
        {
            SetData(event);
        }
    }
}

void EventHandlerEmissiveLightEditor::SetData(Rocket::Core::Event& event)
{
    if(GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE || GameDetails::GetTool() == GameDetails::TOOL_EMISSIVE)
    {
        ltbl::EmissiveLight* pSelectedEmissiveLight = static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected);

        if(pSelectedEmissiveLight != nullptr)
        {
            //get input elements
            Rocket::Core::Element* input_dim_width= event.GetTargetElement()->GetElementById("in_dim_width");
            Rocket::Core::Element* input_dim_height= event.GetTargetElement()->GetElementById("in_dim_height");
            Rocket::Core::Element* input_color_r= event.GetTargetElement()->GetElementById("in_color_r");
            Rocket::Core::Element* input_color_g= event.GetTargetElement()->GetElementById("in_color_g");
            Rocket::Core::Element* input_color_b= event.GetTargetElement()->GetElementById("in_color_b");
            Rocket::Core::Element* input_rotation= event.GetTargetElement()->GetElementById("in_rotation");

            //get value from input
            Rocket::Core::String s_dim_width = input_dim_width->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedEmissiveLight->getDims().x));
            Rocket::Core::String s_dim_height= input_dim_height->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedEmissiveLight->getDims().y));
            Rocket::Core::String s_color_r= input_color_r->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedEmissiveLight->getColor().x));
            Rocket::Core::String s_color_g= input_color_g->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedEmissiveLight->getColor().y));
            Rocket::Core::String s_color_b= input_color_b->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedEmissiveLight->getColor().z));
            Rocket::Core::String s_rotation= input_rotation->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedEmissiveLight->getRotation()));

            //set all the values
            pSelectedEmissiveLight->setDims(sf::Vector2f((float)atof(s_dim_width.CString()), (float)atof(s_dim_height.CString())));
            pSelectedEmissiveLight->setColor(sf::Vector3f((float)atof(s_color_r.CString()), (float)atof(s_color_g.CString()), (float)atof(s_color_b.CString())));
            pSelectedEmissiveLight->setRotation((float)atof(s_rotation.CString()));

            GameDetails::d_EmDims = sf::Vector2f((float)atof(s_dim_width.CString()), (float)atof(s_dim_height.CString()));
            GameDetails::d_EmColor = pSelectedEmissiveLight->getColor();
            GameDetails::d_EmRotation = pSelectedEmissiveLight->getRotation();
        }
    }
}
