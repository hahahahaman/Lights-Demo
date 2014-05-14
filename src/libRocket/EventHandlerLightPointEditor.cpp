#include <Rocket/Core/Log.h>
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Controls.h>

#include "EventHandlerLightPointEditor.h"
#include "EventManager.h"

EventHandlerLightPointEditor::EventHandlerLightPointEditor()
{
}

EventHandlerLightPointEditor::~EventHandlerLightPointEditor()
{
}

void EventHandlerLightPointEditor::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
    // Rocket::Core::Element::ProcessEvent(event);
    if (value == "SetLight")
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

void EventHandlerLightPointEditor::SetData(Rocket::Core::Event& event)
{
    if(GameDetails::SelectedTool ==  GameDetails::TOOL_LIGHT || GameDetails::GetTool() == GameDetails::TOOL_LIGHT)
    {
        ltbl::Light_Point* pSelectedLight = static_cast<ltbl::Light_Point*>(GameDetails::pSelected);

        if(pSelectedLight)
        {
            //Rocket::Core::Element* input_width= event.GetTargetElement()->GetElementById("input_width");
            //Rocket::Core::Element* input_height= event.GetTargetElement()->GetElementById("input_height");
            //Rocket::Core::String width = input_height->GetAttribute<Rocket::Core::String>("value", "");
            //Rocket::Core::String height = input_width->GetAttribute<Rocket::Core::String>("value", "");

            //get input elements
            //Rocket::Core::Element* input_center_x = event.GetTargetElement()->GetElementById("center_x");
            //Rocket::Core::Element* input_center_y = event.GetTargetElement()->GetElementById("center_y");
            Rocket::Core::Element* input_radius= event.GetTargetElement()->GetElementById("in_radius");
            Rocket::Core::Element* input_color_r= event.GetTargetElement()->GetElementById("in_color_r");
            Rocket::Core::Element* input_color_g= event.GetTargetElement()->GetElementById("in_color_g");
            Rocket::Core::Element* input_color_b= event.GetTargetElement()->GetElementById("in_color_b");
            Rocket::Core::Element* input_size= event.GetTargetElement()->GetElementById("in_size");
            Rocket::Core::Element* input_spread_angle= event.GetTargetElement()->GetElementById("in_spread_angle");
            Rocket::Core::Element* input_soft_spread_angle= event.GetTargetElement()->GetElementById("in_soft_spread_angle");
            Rocket::Core::Element* input_direction_angle= event.GetTargetElement()->GetElementById("in_direction_angle");
            Rocket::Core::Element* input_bleed = event.GetTargetElement()->GetElementById("in_bleed");
            Rocket::Core::Element* input_linearize_factor= event.GetTargetElement()->GetElementById("in_linearize_factor");

            //get all values from input
            //Rocket::Core::String s_center_x = input_center_x->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getCenter().x));
            //Rocket::Core::String s_center_y = input_center_y->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getCenter().y));
            Rocket::Core::String s_radius = input_radius->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getRadius()));
            Rocket::Core::String s_color_r= input_color_r->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getColor().x));
            Rocket::Core::String s_color_g= input_color_g->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getColor().y));
            Rocket::Core::String s_color_b= input_color_b->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getColor().z));
            Rocket::Core::String s_size= input_size->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getSize()));
            Rocket::Core::String s_spread_angle= input_spread_angle->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getSpreadAngle()));
            Rocket::Core::String s_soft_spread_angle= input_soft_spread_angle->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getSoftSpreadAngle()));
            Rocket::Core::String s_direction_angle= input_direction_angle->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getDirectionAngle()));
            Rocket::Core::String s_bleed= input_bleed->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getBleed()));
            Rocket::Core::String s_linearize_factor= input_linearize_factor->GetAttribute<Rocket::Core::String>("value", Rocket::Core::String(32, "%f", pSelectedLight->getLinearizeFactor()));

            //set all the values
            //pSelectedLight->setCenter(sf::Vector2f((float)atof(s_center_x.CString()), (float)atof(s_center_y.CString())));
            //printf("%f\n", (float)atof(s_radius.CString()));

            //wtf man but it works i guess
            float radius = atof(s_radius.CString());
            pSelectedLight->setRadius(radius);
            pSelectedLight->setColor(sf::Vector3f((float)atof(s_color_r.CString()), (float)atof(s_color_g.CString()), (float)atof(s_color_b.CString())));
            pSelectedLight->setSize((float)atof(s_size.CString()));
            pSelectedLight->setSpreadAngle((float)atof(s_spread_angle.CString()));
            pSelectedLight->setSoftSpreadAngle((float)atof(s_soft_spread_angle.CString()));
            pSelectedLight->setDirectionAngle((float)atof(s_direction_angle.CString()));
            pSelectedLight->setBleed((float)atof(s_bleed.CString()));
            pSelectedLight->setLinearizeFactor((float)atof(s_linearize_factor.CString()));

            GameDetails::d_Radius = pSelectedLight->getRadius();
            GameDetails::d_Color = pSelectedLight->getColor();
            GameDetails::d_Size = pSelectedLight->getSize();
            GameDetails::d_SpreadAngle = pSelectedLight->getSpreadAngle();
            GameDetails::d_SoftSpreadAngle = pSelectedLight->getSoftSpreadAngle();
            GameDetails::d_DirectionAngle = pSelectedLight->getDirectionAngle();
            GameDetails::d_Bleed = pSelectedLight->getBleed();
            GameDetails::d_LinearizeFactor = pSelectedLight->getLinearizeFactor();

        }
    }
}

/*
static KeydownListener keydownlistener;

void KeydownListener::RegisterKeydownObject(Rocket::Core::Element* element)
{
    element->AddEventListener("keydown", &keydownlistener);
}

void KeydownListener::ProcessEvent(Rocket::Core::Event& event)
{
    if(event == "keydown")
    {
        Rocket::Core::Input::KeyIdentifier key_identifier = (Rocket::Core::Input::KeyIdentifier) event.GetParameter< int >("key_identifier", 0);
        if(key_identifier == Rocket::Core::Input::KI_RETURN)
        {
            EventHandlerLightPointEditor::SetData(event);
        }
    }
}
*/

