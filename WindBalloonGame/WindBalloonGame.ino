#include "config.h"
#include "Fan.h"
#include "Button.h"  
#include "GameManager.h"

// Initialisation du bouton de démarrage
Button startButton(BUTTON_PIN);

// Tableau des 5 ventilateurs initialisés avec leurs broches respectives définies dans Config.h
Fan fans[NUM_FANS] = {
  Fan(FAN_PINS[0]),
  Fan(FAN_PINS[1]),
  Fan(FAN_PINS[2]),
  Fan(FAN_PINS[3]),
  Fan(FAN_PINS[4])
};

// Initialisation du GameManager 
GameManager game(fans, NUM_FANS);

void setup() {
  Serial.begin(9600);
  
  // Initialisation des composants
  startButton.begin();
  game.begin();
  
  // Initialisation du générateur aléatoire (bruit sur une broche analogique non connectée A0)
  randomSeed(analogRead(A0));
  
  Serial.println("=== Systeme pret ! Appuyez sur le bouton pour lancer le jeu. ===");
}

void loop() 
{
  if (startButton.wasPressed()) 
  {
    game.toggleState();
  }

  game.update();
}
