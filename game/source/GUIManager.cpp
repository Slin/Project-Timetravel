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
        for(Widget *widget : _widgets)
        {
            delete widget;
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

    void GUIManager::RemoveWidget(Widget *widget)
    {
        if(widget)
        {
            _widgetsToRemove.push_front(widget);
        }
    }

    void GUIManager::AddWidget(Widget *widget)
    {
        if(widget)
        {
            _widgetsToAdd.push_back(widget);
        }
    }

    void GUIManager::Update(float timeStep)
    {
        //add queued entities
        for(Widget *widget:_widgetsToAdd)
        {
            _widgets.push_back(widget);
        }
        _widgetsToAdd.clear();

        //remove queued entities
        for(Widget *widget:_widgetsToRemove)
        {
            _widgets.remove(widget);
            delete widget;
        }
        _widgetsToRemove.clear();

        //update entities
        for(Widget *widget:_widgets)
        {
            widget->Update(timeStep);
        }
    }
}