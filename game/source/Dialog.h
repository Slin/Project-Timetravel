//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_DIALOG_H
#define TIMETRAVEL_DIALOG_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Widget.h"

namespace TT
{
    class Dialog : public Widget
    {
    public:
        static Dialog *GetInstance();

        void Update(float timeStep);
        void OnGUI(sf::RenderWindow *window);

        void SetText(const sf::String text);

    private:
        sf::Font _font;
        sf::Text _text;

        Dialog();
        static Dialog *_instance;
    };
}

#endif //TIMETRAVEL_DIALOG_H
