# Smart Queue System — ESP32 Firmware

Button-operated electronic token/queue management system built on ESP32, with a live LCD display and audio alert for calling the next token.

---

## ✨ Features

- 🎫 **Token generation** — Press a button to issue the next sequential token number
- 📢 **Call next token** — Staff presses a button to advance to the next token in line
- 📟 **16x2 I2C LCD display** — Shows current status: token generated / now serving
- 🔔 **Buzzer alert** — Audible beep when a new token is called
- 🛑 **Boundary check** — Prevents calling a token if none are waiting

---

## 🏗 How It Works

```
        ┌────────────────┐         ┌────────────────┐
        │   BTN_NEXT (4)   │         │   BTN_CALL (5)   │
        │ "Take a Token"   │         │ "Call Next"      │
        └────────┬────────┘         └────────┬────────┘
                 │                            │
                 ▼                            ▼
        tokenNumber++                currentToken++
        (if tokens are
         waiting)
                 │                            │
                 └──────────────┬─────────────┘
                                ▼
                    ┌───────────────────────┐
                    │   ESP32 (Main Loop)     │
                    └───────────┬─────────────┘
                                │
                ┌────────────────┼────────────────┐
                ▼                                 ▼
      ┌──────────────────┐              ┌──────────────────┐
      │  16x2 I2C LCD      │              │     Buzzer (18)    │
      │  Shows token info  │              │  Beeps on "Call"    │
      └──────────────────┘              └──────────────────┘
```

**Logic:**
1. `tokenNumber` increases every time someone takes a new token (`BTN_NEXT`)
2. `currentToken` increases every time staff calls the next person (`BTN_CALL`)
3. If `currentToken < tokenNumber`, there's someone waiting → call them, beep, update LCD
4. If `currentToken == tokenNumber`, no one is waiting → LCD shows "No Tokens Left"

---

## 🛠 Hardware Components

| Component | Pin | Purpose |
|---|---|---|
| ESP32 Microcontroller | — | Processing unit — controls the whole system |
| 16x2 I2C LCD Display (address `0x27`) | SDA/SCL | Output unit — displays token number |
| TOKEN Button | GPIO 4 | Input unit — generates a new token number |
| NEXT Button | GPIO 5 | Input unit — calls the next token |
| Buzzer | GPIO 18 | Output unit — audio alert when next token is called |
| Breadboard & Jumper Wires | — | Circuit connections |
| Power Supply | 5V USB | Powers the entire system |

---

## 🧩 Software Components

- Arduino IDE
- Embedded C Programming
- ESP32 Board Drivers
- Libraries: `LiquidCrystal_I2C`

---

## 📦 Libraries Required

Install via Arduino IDE Library Manager:
- `Wire.h` (built-in)
- `LiquidCrystal_I2C` by Frank de Brabander (or similar)

---

## 🚀 How to Flash

1. Open the `.ino` file in Arduino IDE
2. Select Board → **ESP32 Dev Module**
3. Select the correct COM port
4. Install the `LiquidCrystal_I2C` library if not already installed
5. Click **Upload**
6. Open Serial Monitor (optional) to debug if LCD doesn't initialize

---

## 📂 Project Structure

```
smart-queue-firmware/
├── smart_queue.ino       # Main firmware file
└── README.md
```

---

## 🚧 Current Status

| Component | Status |
|---|---|
| Token generation (button) | ✅ Working |
| Call next token (button) | ✅ Working |
| LCD display | ✅ Working |
| Buzzer alert | ✅ Working |
| Backend sync (WiFi → Node.js/MongoDB) | 🟡 In progress |
| IR / Ultrasonic auto-detection | 🟡 In progress |

---

## 🔭 Roadmap

- [ ] Add WiFi connectivity to push token data to backend in real time
- [ ] Replace manual button trigger with IR/ultrasonic sensor-based auto-detection
- [ ] Add debounce handling for buttons (currently using simple delay)
- [ ] Persist token count across power loss (use ESP32 NVS/EEPROM)
- [ ] Add reset button to clear queue at end of day

---

## 📌 What I Learned

Working on this firmware taught me GPIO interfacing, I2C communication with peripheral displays, and structuring a simple state machine (`tokenNumber` vs `currentToken`) to manage real-world queue logic on embedded hardware.

---

## 👤 Author

**Onkar Garde**
[GitHub](https://github.com/Omkargarde123) · [LinkedIn](https://linkedin.com/in/onkar-garde-775364331)
