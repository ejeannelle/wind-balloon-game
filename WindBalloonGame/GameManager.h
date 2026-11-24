#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <Arduino.h>
#include "Fan.h"

class GameManager 
{
  private:
    Fan* fans;
    int numFans;
    int maxFansActive;
    bool isRunning;
    unsigned long lastSpawnAttemptTime;
    unsigned long lastMaxActiveChangeTime; 

    void turnOffAllFans();
    void turnOnFan(int fanIndex);
    void turnOffFan(int fanIndex);
    void checkAndManageFans();
    void logFanAction(int fanIndex, const String& message);

    unsigned long calculateRandomDuration();
    int getOldestWaitingFanIndex(unsigned long currentTime) const;
    int getRandomAvailableFanIndex() const;

  public:
    GameManager(Fan* fanArray, int count);
    void begin();
    void toggleState();
    void update();
    bool getState() const;
};

#endif