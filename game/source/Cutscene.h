//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_CUTSCENE_H
#define TIMETRAVEL_CUTSCENE_H

#include "Entity.h"

namespace TT {
    class Cutscene : public Entity {
    public:

        static Cutscene *GetInstance();
        ~Cutscene();

        virtual void Update(float timeStep);
        virtual void Draw(sf::RenderWindow *window);

        void StartCutscene(unsigned int id);
        void CancelCutscene();
        void SkipStep();

    protected:
        struct Step {
            string text;
            float duration = 2.0f;
            int loadLevel = -1;
            bool spawnCharacter;
            sf::Vector2f spawnCharacterPosition;
            string spawnCharacterSprite;

            bool playSound = false;
            sf::Sound sound;
            float soundVolume = 50.0f;

            bool playMusic = false;
            string musicPath;
            bool musicLoop = false;
            float musicVolume = 100.0f;
        };

    private:
        Cutscene(unsigned int id);
        static Cutscene *_instance;

        int _id = 0;
        float _nextStepTimer = 0.0f;

        int _currentStep = 0;
        Step _steps_0[6];
        Step _steps_1[6];

        sf::Music _music;

    };
}

#endif //TIMETRAVEL_CUTSCENE_H
