# Chaos 8 Ball 🔮💀  
A cursed Magic 8 Ball that doesn't give answers — it gives *warnings*. Built using an ESP32, vape batteries, and poor decision-making.

---

## ⚠️ What Is This?

This is a DIY project for building your own **Chaos 8 Ball** — a chaotic prophecy orb that responds to shakes with awful advice like:

- "Run."
- "File your taxes in crayon."
- "Ask your ex for closure."
- "The end is nigh."

This is not a tutorial. It's more of a vibes-based guide through a hardware hack made for laughs and mild existential fear.

---

## 🧠 Features

- Shake-to-activate OLED display
- Random cursed responses (currently hardcoded in the sketch)
- Rechargeable with USB-C
- Designed to confuse guests and disappoint family

---

## 🧰 Parts List

| Part | Notes |
|------|-------|
| ESP32-C3 Mini | Small, cheap, and just enough GPIO for chaos |
| OLED Display (SSD1306) | 128x64, I2C |
| Shock Sensor | Detects a shake to trigger prophecy |
| TP4056 Charging Module | For charging the vape cell |
| 3.7V Vape Battery | Please don’t steal these from the bin like I did |
| Boost Converter | To bump battery voltage to 5V if needed |
| Power Switch | Optional, but helps keep the demons contained |
| 3D Printed Shell | Modeled in FreeCAD (STLs included) |

---

## 🔧 Setup Instructions

1. Flash the ESP32-C3 using Arduino IDE or PlatformIO.
2. Wire up OLED display to I2C pins (SDA/SCL).
3. Attach the shock sensor to a digital input pin (configured in code).
4. Connect power via battery + TP4056.
5. Print the shell, glue things irresponsibly.
6. Shake it. Accept your fate.

---

## 📦 Dependencies

Install these libraries in Arduino IDE:

- Adafruit SSD1306
- Adafruit GFX
- Wire.h (included by default)

---

## 🧪 Testing

Shake it. It should display a random line from the list. If not:
- Make sure the OLED is wired properly.
- Confirm your shock sensor triggers HIGH/LOW correctly.
- Recheck your I2C address if using a different display.

---

## 💡 Improvement Ideas

Here’s some cursed potential for v2 if you are up to the task:

- **OTA updates** (so you can remotely change the prophecies, currently it is sealed shut)
- **Sound module** to make it growl or whisper weird stuff
- **RGB LED glow** for a dramatic effect

---

## 🎬 As Seen In

This project appeared in my YouTube video:  
👉 [I Built a Cursed Magic 8 Ball That Gives Bad Advice](https://www.youtube.com/watch?v=-yIj9mfP2Uo)

---

## 📮 Contribute Your Own Chaos

Have better cursed advice? Suggest them by opening an Issue or editing the hardcoded list in the sketch file.  
If you build one, I would love to see it!

---

## 🖤 License

Do whatever. Just don’t blame me when it combusts.
