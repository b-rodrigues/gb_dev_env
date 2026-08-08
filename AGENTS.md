# Agent Operating Instructions (AGENTS.md)

This file defines the operational contract and constraints for AI coding agents working on this project.

## Environment

This repository uses Nix flakes for complete, reproducible environment management.

Do not install dependencies manually using `apt`, `brew`, `npm`, `pip`, or other host package managers.

Enter the development environment with:

```bash
nix develop
```

## Primary Commands

All operations are exposed via standard `make` targets:

* **Build the ROM**:
  ```bash
  make
  ```
  Produces `build/game.gb`.

* **Run in Emulator**:
  ```bash
  make run
  ```
  Builds the ROM (if needed) and launches it in the emulator.

* **Automated Validation**:
  ```bash
  make test
  ```
  Builds the ROM and validates its header and checksum.

* **Capture Visual Screenshot**:
  ```bash
  make screenshot
  ```
  Produces `build/screenshot.png` for visual inspection of gameplay.

* **Clean Build Artifacts**:
  ```bash
  make clean
  ```
  Removes generated artifacts in `build/`.

## Target Platform & Toolchain

* **Target Hardware**: Nintendo Game Boy (DMG) / Game Boy Color
* **C Toolchain**: GBDK-4 (`lcc`)
* **Assembly Toolchain**: RGBDS (`rgbasm`, `rgblink`, `rgbfix`)

## Project Structure

* `src/main.c`: Entry point and main game loop
* `src/game.c`, `src/game.h`: Game loop, state machine, and Tetris game logic
* `src/board.c`, `src/board.h`: 10x16 playfield, occupancy check, and line clearing
* `src/piece.c`, `src/piece.h`: Tetromino shapes, rotation, collision, and locking
* `src/input.c`, `src/input.h`: Joypad button reading and state tracking
* `src/render.c`, `src/render.h`: Game Boy VRAM background tile rendering
* `asm/`: Assembly routines (e.g. `asm/example.asm`)
* `build/`: Generated artifacts (`build/game.gb`, `build/*.o`, `build/screenshot.png`)

## Code Philosophy

1. **Simple C**: Prefer clear, explicit C code over complex macro magic or indirect callbacks.
2. **Small Functions**: Keep functions short and focused on a single responsibility.
3. **Explicit State**: Represent state using plain C structs and enums.
4. **Game Boy-Native**: Operate directly on 8-bit integers, tiles, and VRAM concepts.
5. **No External Dependencies**: Do not introduce modern engines, scripting runtimes, or non-Nix packages.

## Validation Workflow

After modifying code or gameplay logic, always validate your changes:

1. Run `make test` to verify compilation, linking, and ROM header integrity.
2. Run `make screenshot` or `make run` to visually inspect rendering and gameplay state.
