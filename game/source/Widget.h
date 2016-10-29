//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_WIDGET_H
#define TIMETRAVEL_WIDGET_H

#include "GUIManager.h"

namespace TT {
    class Widget {
        public:
            Widget()
            {
                GUIManager::GetInstance()->AddWidget(this);
            }
            virtual ~Widget()
            {
                GUIManager::GetInstance()->RemoveWidget(this);
            }

            virtual void Update(float timeStep) = 0;
            virtual void OnGUI(sf::RenderWindow *window) = 0;
    };
};

#endif //TIMETRAVEL_WIDGET_H
