//
// Created by Matthias Bruns on 29/10/2016.
//

#include "PlayerEntity.h"
#include "Cutscene.h"
#include "Dialog.h"
#include "FakeCharacter.h"

namespace TT {

    Cutscene *Cutscene::_instance = NULL;

    Cutscene *Cutscene::GetInstance() {
        if (!_instance)
            _instance = new Cutscene(0);

        return _instance;
    }

    Cutscene::Cutscene(unsigned int id) : _currentStep(-1)
    {
        _id = id;

        // STEP 0
        Step step;
        step.duration = 6.0f;
        step.hidePlayer = true;
        step.text = "I remember him stepping out of the portal that opened in our home, the enemy I thought defeated.";
        step.spawnCharacter = true;
        step.spawnCharacterPosition = sf::Vector2f(550.0f, 275.0f);
        step.spawnCharacterSprite = "assets/textures/characters/player_startscene.png";
        step.playMusic = true;
        step.musicPath = "assets/sounds/startscreen/bgm.ogg";
        step.musicLoop = true;
        _steps_0[0] = step;

        step.duration = 5.0f;
        step.playMusic = false;
        step.text = "I remember him slinging his spells at us, telling me I had created my own doom.";
        step.spawnCharacter = true;
        step.spawnCharacterMaxAlpha = 100.0f;
        step.spawnCharacterPosition = sf::Vector2f(1700.0f, 140.0f);
        step.spawnCharacterSprite = "assets/textures/characters/wizzard_startscene.png";
        _steps_0[1] = step;

        step.spawnCharacter = false;
        step.duration = 5.0f;
        step.text = "I remember you slumping down, me cradling you, while you died in my arms, Corra, my love, my life.";
        _steps_0[2] = step;

        step.duration = 5.0f;
        step.text = "The power of time he claimed to have conquered before he fled, laughing at my misery...";
        _steps_0[3] = step;

        step.duration = 3.0f;
        step.text = "I will take it from him. I will take his power and save you!";
        _steps_0[4] = step;

        step.duration = 3.0f;
        step.text = "";
        step.loadLevel = true;
        step.loadLevelId = 1;
        _steps_0[5] = step;

        // STEP 1

        step.loadLevel = false;
        step.duration = 3.0f;
        step.hidePlayer = false;
        step.playMusic = true;
        step.musicPath = "assets/sounds/level_3/magic.ogg";
        step.musicLoop = true;
        step.text = "In the depth of ancient towers\nI call thee, you mystic powers";
        _steps_1[0] = step;

        step.playMusic = false;
        step.duration = 3.0f;
        step.text = "Rip the cloth of space and time\nAncient knowledge that is mine";
        _steps_1[1] = step;

        step.duration = 3.0f;
        step.text = "Door that past and future holds,\nLead me where my path unfolds!";
        _steps_1[2] = step;

        step.duration = 3.0f;
        step.musicLoop = false;
        step.text = "Open up and bring me where\nMy desires lead me there.";
        _steps_1[3] = step;

        // STEP 2
        step.loadLevel = false;
        step.duration = 0.5f;
        step.hidePlayer = true;
        step.text = "";
        step.playMusic = true;
        step.musicPath = "assets/sounds/level_3/dramatic.ogg";
        step.musicLoop = false;
        step.spawnCharacter = true;
        step.spawnCharacterMaxAlpha = 255.0f;
        step.spawnCharacterPosition = sf::Vector2f(1250.0f, 140.0f);
        step.spawnCharacterSprite = "assets/textures/characters/wizzard_endscene.png";
        _steps_2[0] = step;

        step.loadLevel = false;
        step.duration = 3.0f;
        step.text = "What? The portal is powered? But how?\nEven I could never uncover all its secrets! ";
        step.playMusic = false;
        step.spawnCharacter = false;
        _steps_2[1] = step;

        step.duration = 3.0f;
        step.text = "Ah well, who cares. \nNow I can finally use it.";
        _steps_2[2] = step;

        step.duration = 3.0f;
        step.text = "Now I can finally make him pay.";
        _steps_2[3] = step;

        step.duration = 3.0f;
        step.text = "I'll make him suffer for all he has done to me!";
        _steps_2[4] = step;

        step.duration = 3.0f;
        step.text = "";
        step.loadLevel = true;
        step.loadLevelId = 5;
        _steps_2[5] = step;

        // STEP 3
        step.duration = 5.0f;
        step.hidePlayer = true;
        step.loadLevel = false;
        step.text = "I went through the portal.\nThe knowledge I had gotten led me back to the moment\nwhere I could see myself with my dear Corra happy side by side.";
        step.spawnCharacter = false;
        step.playMusic = true;
        step.musicPath = "assets/sounds/endscreen/bgm.ogg";
        step.musicLoop = true;
        _steps_3[0] = step;

        step.duration = 5.0f;
        step.playMusic = false;
        step.text = "I hid and waited for the portal to open, an arrow notched on my bow.";
        _steps_3[1] = step;

        step.duration = 5.0f;
        step.text = "But when the portal opened everything happened like it had the first time.";
        _steps_3[2] = step;

        step.duration = 5.0f;
        step.text = "My arrows could not stop him from killing Corra, they only drove him away.";
        _steps_3[3] = step;

        step.duration = 5.0f;
        step.text = "I had to watch her die again.\nAnd that's when I realized, that the portal had been inactive until I used it to return.";
        _steps_3[4] = step;

        step.duration = 5.0f;
        step.text = "It was I who had handed my Archenemy the power to travel through time.";
        _steps_3[5] = step;

        step.duration = 3.0f;
        step.text = "Le Fin";
        step.loadLevel = true;
        step.loadLevelId = 0;
        _steps_3[6] = step;
    }

    Cutscene::~Cutscene() {
        _instance = NULL;
    }

    void Cutscene::Update(float timeStep)
    {
        if(_currentStep < 0 || _currentStep >= _cutsceneFrames)
            return;

        Step step;

        if (_id == 0) {
            step = _steps_0[_currentStep];
        }
        if (_id == 1) {
            step = _steps_1[_currentStep];
        }
        if (_id == 2) {
            step = _steps_2[_currentStep];
        }
        if (_id == 3) {
            step = _steps_3[_currentStep];
        }

        _cutsceneRunning = _currentStep < _cutsceneFrames && _currentStep >= 0;
        if(World::GetInstance()->GetPlayer()) {
            World::GetInstance()->GetPlayer()->_disabled = _cutsceneRunning;
        }

        if (_currentStep < _cutsceneFrames && _nextStepTimer <= 0.0f)
        {
            Dialog::GetInstance()->SetText(step.text);
            Dialog::GetInstance()->SetResetTimer(step.duration);
            if (step.spawnCharacter) {
                FakeCharacter *character = new FakeCharacter(step.spawnCharacterPosition, step.spawnCharacterSprite);
                character->maxAlpha = step.spawnCharacterMaxAlpha;
                character->minAlpha = step.spawnCharacterMinAlpha;
                character->StartFadeIn(true);
            }

            if(step.playMusic) {
                _music.openFromFile(World::GetInstance()->GetBundlePath()+step.musicPath);
                _music.play();
                _music.setVolume(step.musicVolume);
            }

	        _music.setLoop(step.musicLoop);

            if(step.playSound) {
                step.sound.setVolume(step.soundVolume);
                step.sound.play();
            }

            if(World::GetInstance()->GetPlayer()) {
                World::GetInstance()->GetPlayer()->_hidden = step.hidePlayer;
            }

            if (step.loadLevel) {
                World::GetInstance()->LoadLevel(step.loadLevelId);
                _music.stop();
            }

            _nextStepTimer = step.duration;
            _currentStep++;
        }

        if(_currentStep >= _cutsceneFrames)
        {
	        _currentStep = -1;
            if(World::GetInstance()->GetPlayer()) {
                World::GetInstance()->GetPlayer()->_disabled = false;
                World::GetInstance()->GetPlayer()->_hidden = false;
            }
        }

        _nextStepTimer -= timeStep;

        if (_nextStepTimer < 0.0f) {
            _nextStepTimer = 0.0f;
        }
    }

    void Cutscene::Draw(sf::RenderWindow *window) {

    }

    void Cutscene::StartCutscene(unsigned int id)
    {
	    if(_currentStep != -1)
		    return;

        _id = id;
        _nextStepTimer = 0.0f;
        _currentStep = 0;

        if (_id == 0) {
            _cutsceneFrames = 6;
        }
        if (_id == 1) {
            _cutsceneFrames = 4;
        }
        if (_id == 2) {
            _cutsceneFrames = 6;
        }
        if (_id == 3) {
            _cutsceneFrames = 7;
        }
    }

    void Cutscene::CancelCutscene() {

    }

    void Cutscene::SkipStep() {
        _nextStepTimer = 0.0f;
    }
}