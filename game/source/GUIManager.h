//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_GUIMANAGER_H
#define TIMETRAVEL_GUIMANAGER_H

#include <list>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

namespace TT {
    class Widget;
    class GUIManager {
        private:
            GUIManager();
            static GUIManager *_instance;

            list<Widget*> _widgets;
            list<Widget*> _widgetsToAdd;
            list<Widget*> _widgetsToRemove;

        public:
            void AddWidget(Widget *entity);
            void RemoveWidget(Widget *entity);
            void Update(float timeStep);
            void Draw(sf::RenderWindow *windows);
            void RemoveAllWidgets();

            static GUIManager *GetInstance();
        };
}


#endif //TIMETRAVEL_GUIMANAGER_H
