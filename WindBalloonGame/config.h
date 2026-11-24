#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Configuration matérielle
const int BUTTON_PIN = 7;
const int FAN_PINS[] = {2, 3, 4, 5};
constexpr size_t NUM_FANS = sizeof(FAN_PINS) / sizeof(FAN_PINS[0]);

// Configuration du jeu
const int MAX_FANS_ACTIVE = 3;
const unsigned long SPAWN_CHANGE_MAX_ACTIVE = 5000;// 5 secondes 
const unsigned long MIN_FAN_DURATION = 3000; // 3 secondes
const unsigned long MAX_FAN_DURATION = 8000; // 8 secondes
const unsigned long MAX_WAIT_TIME = 15000;  // Seuil maximal d'attente 15 secondes d'un ventillateur
const unsigned long SPAWN_CHECK_INTERVAL = 800; // ms entre deux tentatives
const int FAN_SPAWN_CHANCE = 30; //30% de chance d'allumage à chaque boucle 
const bool USE_STARTSTOP_BUTTON = false;

// Configuration du bouton
const unsigned long DEBOUNCE_DELAY = 200;

#endif