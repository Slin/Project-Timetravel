//
// Created by Matthias Bruns on 29/10/2016.
//

#include "Dialog.h"

namespace TT {
    Dialog *Dialog::_instance = NULL;

    Dialog *Dialog::GetInstance() {
        if (!_instance) {
            _instance = new Dialog();
        }

        return _instance;
    }

    Dialog::Dialog() {
        _resetTimer = -1.0f;
        _font.loadFromFile("assets/fonts/PixelFJVerdana12pt.ttf");

        // disable smoothing
        const_cast<sf::Texture&>(_font.getTexture(12)).setSmooth(false);

        // select the font
        _text.setFont(_font); // font is a sf::Font

        // set the string to display
        _text.setString("TEST");

        // set the character size
        _text.setCharacterSize(24); // in pixels, not points!
    }

    Dialog::~Dialog() {
        _instance = NULL;
    }

    void Dialog::Update(float timeStep) {
        if(_resetTimer > 0.0f) {
            _resetTimer -= timeStep;
            if(_resetTimer <= 0.0f){
                SetText("");
                _resetTimer = -1.0f;
            }
        }
    }

    void Dialog::OnGUI(sf::RenderWindow *window) {
        _text.setPosition(18.0f, 0.5f * window->getSize().y - 128.0f);

        window->draw(_text);
    }

    void Dialog::SetText(const sf::String text) {
        // set the string to display
        _text.setString(text);
    }

    void Dialog::SetResetTimer(float seconds) {
        _resetTimer = seconds;
    }
}