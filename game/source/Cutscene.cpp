//
// Created by Matthias Bruns on 29/10/2016.
//

#include "Cutscene.h"
#include "Dialog.h"

namespace TT {

    Cutscene *Cutscene::_instance = NULL;

    Cutscene *Cutscene::GetInstance() {
        if (!_instance)
            _instance = new Cutscene(0);

        return _instance;
    }

    Cutscene::Cutscene(unsigned int id) {
        _id = id;

        Step step;
        step.duration = 3.0f;
        step.text = "I remember him stepping out of the portal that opened in our home, the enemy I thought defeated.";
        _steps_0[0] = step;
        step.duration = 3.0f;
        step.text = "I remember him slinging his spells at us, telling me I had created my own doom.";
        _steps_0[1] = step;
        step.duration = 3.0f;
        step.text = "I remember you slumping down, me cradling you, while you died in my arms, Corra, my love, my life.";
        _steps_0[2] = step;
        step.duration = 3.0f;
        step.text = "The power of time he claimed to have conquered before he fled, laughing at my misery...";
        _steps_0[3] = step;
        step.duration = 2.0f;
        step.text = "I will take it from him. I will take his power and save you!";
        _steps_0[4] = step;
        step.duration = 1.0f;
        step.text = "";
        step.loadLevel = 1;
        _steps_0[5] = step;

        step.loadLevel = -1;
        step.duration = 3.0f;
        step.text = "In the depth of ancient towers\nI call thee, you mystic powers";
        _steps_1[0] = step;
        step.duration = 3.0f;
        step.text = "Rip the cloth of space and time\nAncient knowledge that is mine";
        _steps_1[1] = step;
        step.duration = 3.0f;
        step.text = "Door that past and future holds,\nLead me where my path unfolds!";
        _steps_1[2] = step;
        step.duration = 3.0f;
        step.text = "Open up and bring me where\nMy desires lead me there.";
        _steps_1[3] = step;
    }

    Cutscene::~Cutscene() {
        _instance = NULL;
    }

    void Cutscene::Update(float timeStep) {
        int length = 0;
        Step step;

        if (_id == 0) {
            length = 6;
            step = _steps_0[_currentStep];
        }
        if (_id == 1) {
            length = 4;
            step = _steps_1[_currentStep];
        }

        if (_currentStep < length && _nextStepTimer <= 0.0f) {
            Dialog::GetInstance()->SetText(step.text);
            Dialog::GetInstance()->SetResetTimer(step.duration);

            if (step.loadLevel >= 0) {
                World::GetInstance()->LoadLevel(step.loadLevel);
            }
            _nextStepTimer = step.duration;
            _currentStep++;
        }

        _nextStepTimer -= timeStep;

        if (_nextStepTimer < 0.0f) {
            _nextStepTimer = 0.0f;
        }
    }

    void Cutscene::Draw(sf::RenderWindow *window) {

    }

    void Cutscene::StartCutscene(unsigned int id) {
        _id = id;
        _currentStep = 0;
    }

    void Cutscene::CancelCutscene() {

    }
}