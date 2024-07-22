# ClickTracker

ClickTracker is a C++ program that records and replays mouse clicks. It allows users to save recorded clicks to a file and load them for replay. 

### Please, install msys64 or msys32 before use for correct operation of the program

## Features

- Record mouse clicks with precise timings.
- Replay recorded mouse clicks.
- Save recorded clicks to a file.
- Load recorded clicks from a file.

## How It Works

The program runs in a loop, waiting for specific key presses to start and stop recording or replaying clicks, and to save or load click data from a file.

- **Press 'J'** to start/stop recording clicks.
- **Press 'R'** to start/stop replaying clicks.
- **Press 'H'** to save recorded clicks to a file.
- **Press 'L'** to load clicks from a file.

The recorded click delays are stored in microseconds to ensure high precision.

## Getting Started

### Prerequisites

- Windows operating system
- C++ compiler

## Usage

1. “**Recording Clicks**:
 * Press 'J' to start recording. Click the left mouse button to record clicks.
 * Press 'J' again to stop recording.”

2. “**Replaying Clicks**:
 * Press 'R' to start replaying recorded clicks.
 * Press 'R' again to stop replaying.

3. “**Saving Clicks**:
 * Press 'H' to save recorded clicks to clicks.txt.

4. “**Loading Clicks**:
 * Press 'L' to load clicks from clicks.txt.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

### License

This project is licensed under the MIT License - see the LICENSE file for details.
