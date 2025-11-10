# Copilot Instructions for home-hub

## Project Overview
- **home-hub** is an IoT hub project with a multi-component architecture: C++ server/controller, Python webserver, and platform-specific integrations.
- Major directories:
  - `server/controller/`: C++ source and headers for core device control logic
  - `server/platform/windows/Controller/`: Windows-specific controller implementation
  - `webserver/`: Python webserver and app integrations
  - `libs/common/`: Third-party libraries (libupnp, zeromq)

## Build & Developer Workflows
- **Windows build:** Use VS Code task `Windows build` (MinGW-w64 g++). Output: `bin/controller.exe`.
- **Clean/Prepare:** Use VS Code tasks `Windows Clean` and `Windows Prepare` to manage build output directory.
- **Linux builds:** Use platform-specific Makefiles under `platform/linux/`.
- **Python webserver:** Entry point is `webserver/main.py`. Run with Python 3. No special build step.

## Key Patterns & Conventions
- **C++:**
  - Controller logic split into multiple files (`cmd_worker.cpp`, `controller.cpp`, etc.) with corresponding headers.
  - Platform-specific code in `server/platform/windows/Controller/` and `platform/linux/controller/`.
  - Third-party libraries are included via `libs/common/` but not built automatically—manual integration may be required.
- **Python:**
  - Apps and connections are modularized under `webserver/MyApps/` and `webserver/MyConns/`.
  - SSDP/UPnP logic in `webserver/MyLibs/`.

## Integration Points
- **ZeroMQ** and **libupnp** are used for messaging and device discovery/control. See `libs/common/` for sources.
- **Cross-component communication:** C++ controller and Python webserver are loosely coupled; integration is likely via sockets or REST (see code for details).

## Examples
- To build the Windows controller: use the VS Code build task or run the g++ command from the task definition.
- To run the Python webserver: `python webserver/main.py`

## Tips for AI Agents
- Always check for platform-specific code when making changes to controller logic.
- When adding new device logic, follow the pattern in `server/controller/src/` and update corresponding headers.
- For new Python integrations, add modules under `webserver/MyApps/` or `webserver/MyConns/`.
- Reference third-party library docs for advanced usage (libupnp, zeromq).

---
If any section is unclear or missing, please provide feedback for further refinement.
