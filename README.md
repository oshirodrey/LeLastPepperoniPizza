# 🍕 Le Last Pepperoni Pizza - v1.0.0

Welcome to **Le Last Pepperoni Pizza**, a top-down arcade-style game made with **Unreal Engine 5 (UE5)**.  
You play as a rotating pizza, defending against endless waves of pineapple invaders by shooting cheese projectiles. 🧀

---

## 🛠️ Features

- 🔫 **Click-to-shoot** mechanic with smooth rotation toward the mouse cursor
- 🌀 **RapidFire buff**: Pizza auto-fires bullets rapidly for a short duration
- ❤️ **Heal buff**: Instantly recover a chunk of HP
- 🎯 **Shoot-to-pickup system**: Buffs drop from enemies and must be shot to activate
- 🧠 Built with modular C++ (Pawn, Projectile, Powerup Target, Enemy, Components)
- 🧱 Custom object channels for clean collision handling

---

## 🎮 Controls

| Action     | Key / Input     |
|------------|------------------|
| Shoot      | Left Mouse Button |
| Aim        | Move your cursor |
| Buff Pickup | Shoot the glowing buff |

---

## 💡 How Buffs Work

- Enemies have a chance to **drop a PowerupTarget** on death.
- You must **shoot** the PowerupTarget to activate the buff.
- Current buff types:
  - `RapidFire`: auto-shoots bullets at high speed for a few seconds
  - `InstantHeal`: heals 30 HP on pickup


---

## 🚀 Version

**Current Version**: `v1.0.0`  
**Status**: Prototype / Playable

---

## 📦 Future Plans

- Add Leaderboard (score based on survival time + kills)
- Add More Buff ( uhh shield, fan-shaped shot)
- Add BGM / SFX polish ( still havent touch FL Studio so, maybe when I'm have more time)


---


>All in All, I'm kinda not very satisfied with this game tho I have learnt to combine both BP and C++ for the better result, a little of pixel art and animation(the game would have been completed much sooner without this), etc.
but yea, kinda burnt out now XD, I already started to make a new game while making this so yeah XD, it is what it is
