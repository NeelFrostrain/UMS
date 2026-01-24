# Unreal Engine Multiplayer: Battle Royale Prototype

A high-performance multiplayer Battle Royale prototype built in **Unreal Engine**, focused on mastering the core framework of Steam-integrated networking. This project prioritizes rapid iteration by leveraging a Blueprint-first workflow while maintaining robust multiplayer logic.

## 🚀 Key Features

* **Steam Integration:** Full lobby management, matchmaking, and friend invitations powered by SteamCorePro.
* **The "Drop" System:** Fully replicated airplane flight path and parachute deployment mechanics.
* **Combat Framework:** Hitscan shooting system with "unlimited ammo" logic for high-action testing.
* **Loot System:** Procedural loot spawning via interactive chests scattered across the map.
* **Optimized Prototyping:** Built entirely in Blueprints for rapid feature deployment and testing.

## 🛠 Tech Stack & Plugins

| Plugin | Purpose |
| --- | --- |
| **SteamCorePro** | Handles Subsystem integration, Sessions, and Steam-specific networking. |
| **Blueprint Assist** | Ensures clean, readable, and professional node architecture. |
| **Blockout Prototype** | Rapid level design and grey-boxing for the battle map. |

### Prerequisites

- **Unreal Engine 5.4**
- **Visual Studio 2022** (or compatible C++ compiler)
- **Steam Client** (running for multiplayer testing)

## 🏗 Multiplayer Architecture

This project follows the **Client-Server model** strictly to ensure gameplay integrity:

* **GameState:** Handles the win/loss state and player spawning (Server-side only).
* **Character:** Replicated movement and state (Health, Parachute status).
* **SteamCore Integration:** Utilizes the Steam Overlay for seamless multiplayer connectivity without needing dedicated servers for the prototype phase.

## 📸 Preview

- [Preview 1](https://raw.githubusercontent.com/NeelFrostrain/UMS/refs/heads/dev/imgs/Screenshot_2026-01-15_002931.png?token=GHSAT0AAAAAADT6BSFGFH4SJ6GWJ4UYVQGU2LVBKYQ)
- [Preview 2](https://raw.githubusercontent.com/NeelFrostrain/UMS/refs/heads/dev/imgs/image.png?token=GHSAT0AAAAAADT6BSFHSJVCBDWXHGI22G4A2LVBLHQ)
