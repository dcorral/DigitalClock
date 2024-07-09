# DigitalClock

DigitalClock is a simple Qt-based application that functions as a digital clock with a 30-minute countdown timer. When the countdown finishes, it plays a sound for a specified duration or until clicked, at which point it restarts the counter to 30 minutes.

## Features

- Digital clock display
- 30-minute countdown timer
- Plays a sound when the countdown finishes
- Clickable clock to reset the timer

## Prerequisites

- Qt5 (Qt5 Widgets and Qt5 Multimedia modules)
- CMake

## Installation

### Building from Source

1. Clone the repository:
   ```sh
   git clone https://github.com/dcorral/DigitalClock.git
   cd DigitalClock
   ```

2. Create a build directory and navigate to it:
   ```sh
   mkdir build
   cd build
   ```

3. Run CMake to generate the Makefile:
   ```sh
   cmake ..
   ```

4. Build the application:
   ```sh
   make
   ```

5. Install the application (you might need superuser permissions):
   ```sh
   sudo make install
   ```

## Usage

After installation, you can run the DigitalClock application by typing:
```sh
DigitalClock
```

## Configuration

You can change the initial countdown time and the alarm duration by modifying the following variables in `main.cpp`:

```cpp
const int initialCountdownMinutes = 30; // Initial countdown time in minutes
const int alarmDurationSeconds = 300;   // Alarm duration in seconds (5 minutes)
```

Rebuild and reinstall the application after making any changes to these variables.

## License

This project is licensed under the MIT License.
