//
// Created by Matthias Bruns on 29/10/2016.
//

#include "GUIManager.h"
#include "Widget.h"

namespace TT
{
    GUIManager *GUIManager::_instance = NULL;

    GUIManager* GUIManager::GetInstance()
    {
        if(!_instance)
            _instance = new GUIManager();

        return _instance;
    }

    GUIManager::GUIManager()
    {

    }

    void GUIManager::RemoveAllWidgets()
    {
        for(Widget *eidgets : _widgets)
        {
            delete eidgets;
        }
        _widgets.clear();
        _widgetsToRemove.clear();
        _widgetsToAdd.clear();
    }

    void GUIManager::Draw(sf::RenderWindow *window)
    {
        //draw widgets
        for(Widget *widget:_widgets)
        {
            widget->OnGUI(window);
        }
    }

    void GUIManager::RemoveWidget(TT::Widget *widgets)
    {
        if(widgets)
        {
            _widgetsToRemove.push_front(widgets);
        }
    }

    void GUIManager::AddWidget(TT::Widget *widgets)
    {
        if(widgets)
        {
            _widgetsToAdd.push_back(widgets);
        }
    }

    void GUIManager::Update(float timeStep)
    {
        //add queued entities
        for(Widget *widgets:_widgetsToAdd)
        {
            _widgets.push_back(widgets);
        }
        _widgetsToAdd.clear();

        //update entities
        for(Widget *widgets:_widgets)
        {
            widgets->Update(timeStep);
        }

        //remove queued entities
        for(Widget *widgets:_widgetsToRemove)
        {
            _widgets.remove(widgets);
        }
        _widgetsToRemove.clear();
    }
}