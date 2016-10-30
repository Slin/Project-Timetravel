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
    }

    Dialog::~Dialog() {
        _instance = NULL;
    }

    void Dialog::Update(float timeStep) {
        unsigned  int fontSize = (unsigned int)(18.0f * _scale);
        _text.setCharacterSize(fontSize < 14 ? 14 : fontSize);

        if(_resetTimer > 0.0f) {
            _resetTimer -= timeStep;
            if(_resetTimer <= 0.0f){
                SetText("");
                _resetTimer = -1.0f;
            }
        }
    }

    void Dialog::OnGUI(sf::RenderWindow *window) {
        _scale = window->getSize().y / 1080.0f;
        float aspectRatio = static_cast<float>(window->getSize().y)/static_cast<float>(window->getSize().x);
        _text.setPosition(18.0f, 410.0f * window->getSize().y/(1920.0f*aspectRatio) + _text.getCharacterSize());

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