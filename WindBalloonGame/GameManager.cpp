#include "GameManager.h"
#include "config.h"

GameManager::GameManager(Fan* fanArray, int count) {
  fans = fanArray;
  numFans = count;
  isRunning = false;
}

void GameManager::begin() 
{
  for (int i = 0; i < NUM_FANS; i++) 
  {
    fans[i].begin();
  }

  turnOffAllFans();
}

void GameManager::toggleState() 
{
  isRunning = !isRunning;
  
  if(!isRunning)
  {
    Serial.println("Game stop!");
    turnOffAllFans();
    return;
  }

  Serial.println("Game start!");

  // Lance un premier ventilateur
  int firstFan = random(0, numFans);
  turnOnFan(firstFan);
}

void GameManager::update() 
{
  if (!isRunning) return;

  // En continu, on vérifie l'état de chaque ventilateur
  checkAndManageFans();
}

bool GameManager::getState() const {
  return isRunning;
}

void GameManager::checkAndManageFans() {
  int activeCount = 0;
  unsigned long currentTime = millis();

  // Compter les ventilateurs actif et éteindre les ventilateurs qui ont dépassé leur temps imparti
  for (int i = 0; i < numFans; i++) 
  {
    if (fans[i].isActive()) 
    {
      if (fans[i].hasExpired()) 
        turnOffFan(i);
      else 
        activeCount++; // Compte les ventilateurs encore en train de tourner
    }
  }

  // S'il y a moins de ventilateurs actifs que le max souhaité 
  if (activeCount < MAX_FANS_ACTIVE) 
  {
    if (random(0, 100) < FAN_SPAWN_CHANCE) // Fréquence de tentative d'allumage (ex:30% chance à chaque boucle)
    { 
      //Recherche prioritaire: ventilateur éteint depuis longtemps dépassant le MAX_WAITING_TIME
      int fanToTurnOn = getOldestWaitingFanIndex(currentTime);
      if (fanToTurnOn != -1) 
      {
        logFanAction(fanToTurnOn, "prioritaire (temps d'attente maximal dépassé).");
      }
      else //Sinon recherche aléatoire parmis les ventilateurs éteints
      {
        fanToTurnOn = getRandomAvailableFanIndex();
      }

      //Activation du ventilateur choisi
      if (fanToTurnOn != -1) 
      {
        turnOnFan(fanToTurnOn);
      }
    }
  }
}

int GameManager::getOldestWaitingFanIndex(unsigned long currentTime) const 
{
  int targetFanIndex = -1;
  unsigned long oldestTime = currentTime; // On initialise avec l'heure actuelle

  for (int i = 0; i < numFans; i++) {
    if (!fans[i].isActive()) {
      unsigned long lastAct = fans[i].getLastActivationTime();
      
      // On cherche le plus ancien lastActivationTime
      if (lastAct < oldestTime) {
        oldestTime = lastAct;
        targetFanIndex = i;
      }
    }
  }

  // Vérification : est-ce que le ventilateur le plus ancien dépasse le seuil MAX_WAIT_TIME
  if (targetFanIndex != -1) {
    if ((currentTime - oldestTime) > MAX_WAIT_TIME) {
      return targetFanIndex;
    }
  }

  return -1; // Aucun ventilateur n'a dépassé le seuil d'attente
}

int GameManager::getRandomAvailableFanIndex() const 
{
  int availableFans[NUM_FANS];
  int availableCount = 0;

  // On liste tous les ventilateurs éteints
  for (int i = 0; i < numFans; i++) 
  {
    if (!fans[i].isActive()) {
      availableFans[availableCount] = i;
      availableCount++;
    }
  }

  // S'il y a des ventilateurs disponibles, on en choisit un au hasard
  if (availableCount > 0) 
  {
    int randomChoice = random(0, availableCount);
    return availableFans[randomChoice];
  }

  return -1; // Aucun ventilateur de disponible (tous sont déjà allumés)
}

void GameManager::logFanAction(int fanIndex, const String& message) {
  Serial.print("Ventilateur #");
  Serial.print(fanIndex);
  Serial.print(" ");
  Serial.println(message);
}

unsigned long GameManager::calculateRandomDuration()
{
  return random(MIN_FAN_DURATION, MAX_FAN_DURATION + 1);
}

void GameManager::turnOnFan(int fanIndex) 
{
  unsigned long randomDuration = calculateRandomDuration();
  fans[fanIndex].turnOn(randomDuration);

  String details = "s'allume pour " + String(randomDuration / 1000) + " s.";
  logFanAction(fanIndex, details);
}

void GameManager::turnOffFan(int fanIndex) 
{
  fans[fanIndex].turnOff();
  logFanAction(fanIndex, "s'est éteint.");
}

void GameManager::turnOffAllFans() 
{
  for (int i = 0; i < numFans; i++) 
  {
    turnOffFan(i);
  }
}