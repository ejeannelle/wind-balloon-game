# WindBalloonGame

An interactive **Arduino** target system designed for **archery training and club games**. Randomly activated fans create shifting air currents that keep balloons floating and moving unpredictably in mid-air as dynamic targets for archers.

## Overview

Instead of shooting at static targets, archers aim at balloons suspended over an array of fans. The Arduino dynamically turns individual fans on and off within configurable timing windows and concurrency limits, causing the balloons to rise, drift, and bob unpredictably. A physical push button allows easy start/stop control between ends (volées) or rounds.

## Project Structure

```text
wind-balloon-game/
├── WindBalloonGame.ino   # Main sketch: setup(), loop(), and object wiring
├── Config.h            # Default settings: fan count, max active fans, timing windows, pins
├── Fan.h               # Fan class declaration (pin, state, activation/deactivation)
├── Fan.cpp             # Fan class implementation
├── Button.h            # Button class declaration (input reading & debouncing)
├── Button.cpp          # Button class implementation
├── GameManager.h       # GameManager class declaration (game state & random fan scheduling)
├── GameManager.cpp     # GameManager class implementation
└── README.md           # Project documentation
