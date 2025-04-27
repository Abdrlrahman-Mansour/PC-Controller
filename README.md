# PC Controller using Voice Commands

This project allows controlling a PC via voice commands using a server-client architecture. The client listens to the user's voice and sends HTTP requests to the server. The server executes the corresponding command on the PC based on the received voice input.

## Features
- Voice recognition using the `SpeechRecognition` library.
- Server listens for HTTP requests to execute commands (e.g., open websites).
- Simple command system that allows opening websites or performing predefined actions.
- The server can be hosted on a local network.

## Requirements

### Server (C++):
1. **C++ Compiler** (e.g., GCC or Visual Studio)
2. **Libraries**:
   - **Winsock2** (for Windows)
   - **sys/socket.h** and **netinet/in.h** (for Linux)

### Client (Python):
1. Python 3.x
2. Libraries:
   - `speech_recognition`
   - `requests`
   - `pyaudio`

To install the required libraries for the client, run the following:

```bash
pip install SpeechRecognition requests pyaudio

