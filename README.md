# Matchium (in-progress)

Low-latency matching engine built in modern C++20, featuring a custom HTTP server and modular architecture.

## Project Status

- HTTP layer complete (custom server, parser, router).
- Matching engine with lock-free queues under active development.

## Build & Run

### 1. Install CMake

```bash
# macOS
brew install cmake

# Ubuntu/Debian
sudo apt install cmake
```

### 2. Build the Project

```bash
./scripts/build.sh
```

This creates a `build/` directory and compiles the project with CMake.

### 3. Run the Server

```bash
./scripts/run_server.sh
```

Default port: `4221`

## Test in Browser

Visit:

```bash
http://localhost:4221/snapshot
```

You should see a response:

`Top 5 bids/asks (mock)` — confirming the HTTP layer is working end-to-end.
