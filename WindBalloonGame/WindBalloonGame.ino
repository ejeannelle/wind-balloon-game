#include "config.h"
#include "Fan.h"
#include "Button.h"  
#include "GameManager.h"

// Initialisation du bouton de démarrage
Button startButton(BUTTON_PIN);

// Tableau des ventilateurs
Fan fans[NUM_FANS];

// Initialisation du GameManager 
GameManager game(fans, NUM_FANS);

void setup() {
  Serial.begin(9600);
  
  // Initialisation des composants
  startButton.begin();
  
  for(int i = 0; i < NUM_FANS; i++){ 
    fans[i].begin(FAN_PINS[i]);
  }

  game.begin();
  
  // Initialisation du générateur aléatoire (bruit sur une broche analogique non connectée A0)
  randomSeed(analogRead(A0));
  
  if(USE_STARTSTOP_BUTTON)
  {
    Serial.println("=== Systeme pret ! Appuyez sur le bouton pour lancer le jeu. ===");
  }
  else
  {
    Serial.println("=== Systeme pret ! ===");
    //Lancer le jeu
    game.toggleState(); 
  }
}

void loop() 
{
  if (USE_STARTSTOP_BUTTON && startButton.wasPressed()) 
  {
    game.toggleState();
  }

  game.update();
}
