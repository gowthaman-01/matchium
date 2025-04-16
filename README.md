# TCP HTTP Server

A modular, extensible TCP-based HTTP server and client built using **modern C++**.


## Installation

### 1. Install CMake (if not already installed)

```bash
# macOS
brew install cmake

# Ubuntu/Debian
sudo apt install cmake
```

### 2. Build the Project

Switch to the root of the project and run:

```bash
./scripts/build.sh
```

This will create a `build/` directory and compile the project using CMake.


### 3. Run the Server or Client

```bash
./scripts/run_server.sh    # Starts the server (default: port 4221)
./scripts/run_client.sh    # Starts the client and sends a message
```
