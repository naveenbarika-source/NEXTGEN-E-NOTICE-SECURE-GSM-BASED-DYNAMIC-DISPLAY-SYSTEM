# NextGen E-Notice: Secure GSM-Based Dynamic Display System

> Remotely update a scrolling LED notice board via SMS — with built-in security to block unauthorized access.

![Hardware Setup](https://github.com/user-attachments/assets/154d6e13-3a6d-4ffd-b721-737485679399)


---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Hardware Connections](#hardware-connections)
- [SMS Command Format](#sms-command-format)
- [How It Works](#how-it-works)
- [Security Mechanism](#security-mechanism)
- [EEPROM Memory Map](#eeprom-memory-map)
- [Getting Started](#getting-started)
- [AT Commands Reference](#at-commands-reference)

---

## Overview

The **NextGen E-Notice Board** is an embedded systems project that enables an authorized administrator to update a public LED notice board remotely via SMS. Built on the **LPC2148 ARM7 microcontroller**, the system communicates with a **GSM module (M660A)** over UART, stores persistent data in an **I2C EEPROM (AT24C256)**, and drives four **8×8 dot-matrix displays** through **74HC164 SIPO shift registers**.


https://github.com/user-attachments/assets/8396eb50-d34f-4899-9fc5-bb18ba9ba1bf


---

## Features

| Feature | Description |
|---|---|
| 📱 Remote SMS Updates | Update the display message from anywhere via SMS |
| 🔐 Security Code Authentication | Only messages with the correct 4-digit security key are processed |
| 📲 Authorized Number Verification | Only a pre-registered phone number can issue commands |
| 💾 Non-Volatile EEPROM Storage | Messages and authorized numbers survive power cycles |
| 🚨 Unauthorized Access Alerts | System sends an SMS alert when an unauthorized number attempts to send a command |
| 📜 Scrolling Display | Long messages scroll smoothly across four dot-matrix panels |
| 🔄 Dynamic Number Update | The authorized phone number can be changed remotely via SMS |

---

## System Architecture

```
┌─────────────┐        UART        ┌─────────────┐
│  GSM Module │ ◄────────────────► │             │
│   (M660A)   │                    │   LPC2148   │        I2C       ┌──────────────┐
└─────────────┘                    │  (ARM7)     │ ◄──────────────► │  AT24C256    │
       ▲                           │             │                   │   (EEPROM)   │
       │ SMS / Cellular            └──────┬──────┘                   └──────────────┘
       ▼                                  │
  Mobile Phone                            │ GPIO (P0.8 – P0.15)
                                          ▼
                               ┌─────────────────────┐
                               │  4× 74HC164 (SIPO)  │
                               │   Shift Registers   │
                               └──────────┬──────────┘
                                          │ Column Data
                                          ▼
                               ┌─────────────────────┐
                               │  4× 8×8 Dot Matrix  │
                               │      Displays        │
                               └─────────────────────┘
                                          ▲
                               ┌──────────┴──────────┐
                               │  74HC573 (Latch)    │
                               │   Row Control        │
                               │  (P0.0 – P0.7)      │
                               └─────────────────────┘
```

<img width="812" height="629" alt="image" src="https://github.com/user-attachments/assets/0a3b40fc-b5c5-47fe-91ae-06125c9574f0" />


---

## Hardware Requirements

| Component | Quantity | Description |
|---|---|---|
| LPC2148 | 1 | ARM7TDMI-S microcontroller |
| 8×8 Dot Matrix Display | 4 | LED dot matrix panels |
| 74HC164 | 4 | 8-bit Serial-In Parallel-Out shift register |
| 74HC573 | 1 | Octal D-type transparent latch (row control) |
| AT24C256 | 1 | 256Kb I2C EEPROM |
| M660A GSM Module | 1 | GSM modem for SMS communication |
| MAX232 | 1 | RS-232 level shifter (optional, for PC debugging) |
| USB to UART Converter | 1 | For flashing and debugging |

---

## Software Requirements

- **Embedded C** — firmware language
- **Keil µVision (ARM C Compiler)** — IDE and compiler
- **Flash Magic** — firmware flashing tool for LPC2148

---

## Hardware Connections

### Dot Matrix — Column Control (74HC164 Shift Registers)

| Shift Register | DSA (Serial In) | CP (Clock) | Drives |
|---|---|---|---|
| 74HC164 #1 | P0.8 | P0.9 | Display 1 COL1–COL8 |
| 74HC164 #2 | P0.10 | P0.11 | Display 2 COL1–COL8 |
| 74HC164 #3 | P0.12 | P0.13 | Display 3 COL1–COL8 |
| 74HC164 #4 | P0.14 | P0.15 | Display 4 COL1–COL8 |

### Dot Matrix — Row Control (74HC573 Latch)

| LPC2148 Pin | 74HC573 Pin | Dot Matrix Row |
|---|---|---|
| P0.16 | D0 → Q0 | ROW1 |
| P0.17 | D1 → Q1 | ROW2 |
| P0.18 | D2 → Q2 | ROW3 |
| P0.19 | D3 → Q3 | ROW4 |
| P0.20 | D4 → Q4 | ROW5 |
| P0.21 | D5 → Q5 | ROW6 |
| P0.22 | D6 → Q6 | ROW7 |
| P0.23 | D7 → Q7 | ROW8 |

### I2C EEPROM (AT24C256)

| LPC2148 Pin | Function |
|---|---|
| P0.2 | SCL |
| P0.3 | SDA |

### UART0 (GSM Module)

| LPC2148 Pin | Function |
|---|---|
| P0.0 (TXD0) | Transmit to GSM |
| P0.1 (RXD0) | Receive from GSM |


---

## SMS Command Format

### 1. Update Display Message

```
1404D<message>$
```

| Part | Description |
|---|---|
| `1404` | Security code |
| `D` | Command: Display update |
| `<message>` | Text to scroll on the LED board |
| `$` | End-of-message terminator |

**Example:** `1404DHELLO WORLD$` → Displays `HELLO WORLD` on the notice board.

### 2. Update Authorized Mobile Number

```
1404M<10-digit number>$
```

**Example:** `1404M9876543210$` → Changes the authorized number to `9876543210`.

---

## How It Works

1. **Power ON** — All peripherals initialize (UART, I2C, GSM, dot-matrix).
2. **EEPROM Check** — The previously stored message and authorized number are loaded from EEPROM.
3. **Display Loop** — The stored message scrolls continuously on the dot-matrix display.
4. **SMS Interrupt** — When the GSM module detects an incoming SMS, a `+CMTI` notification triggers the `sms_flag` via the UART0 ISR.
5. **Read & Verify** — The SMS is read using `AT+CMGR=1`. The sender's number and message format are validated by `verify_format()`.
6. **Process Command:**
   - ✅ Valid display command → extract message → update EEPROM → update display
   - ✅ Valid number-change command → extract new number → update EEPROM
   - ⚠️ Authorized sender with wrong format → send format-error SMS back to sender
   - ❌ Unauthorized sender → send alert SMS to the authorized number with the intruder's number
7. **Delete SMS** — The processed SMS is deleted from GSM memory (`AT+CMGD=1`).
8. **Return to Loop** — The system resumes scrolling with the (possibly updated) message.

<!-- 🎥 INSERT VIDEO HERE: A short demo video showing the full flow — send SMS → display updates on board -->
<!-- Upload to YouTube or GitHub Releases, then embed like this: -->
<!-- [![Watch Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=YOUR_VIDEO_ID) -->

---

## Security Mechanism

| Scenario | System Response |
|---|---|
| Correct security code + correct format + authorized number | ✅ Command executed |
| Correct authorized number + wrong format or security code | ⚠️ Format-error SMS sent to authorized number |
| Unauthorized number (any format) | 🚨 Alert SMS with intruder's number sent to authorized number |
| Missing `$` terminator | ❌ Message rejected |

### Unauthorized Access Example

When an SMS is received from an unregistered number, the system rejects the request and immediately sends an alert to the authorized number, including the intruder's phone number for identification.

![unauthorized number](https://github.com/user-attachments/assets/de9a72bb-8566-4992-8498-f3a89e53770a)


### Invalid Format Example

When the authorized number sends a message with an incorrect format, the system responds with a helpful correction showing the proper format to use.

![Invalid Format](https://github.com/user-attachments/assets/0dbfbd24-e1a2-467e-a807-871fb47cf71e)

> **The authorized phone number is stored in EEPROM and survives reboots.** It can only be changed by the currently authorized number using the `1404M` command.

---

## EEPROM Memory Map

| Address | Purpose |
|---|---|
| `0x00` (`EE_MOBI`) | Indicator byte for stored mobile number (`'4'` = valid) |
| `0x01` (`EE_MOB`) | Authorized mobile number (up to 10 digits) |
| `0x14` (`EE_MSGI`) | Indicator byte for stored message (`'7'` = valid) |
| `0x15` (`EE_MSG`) | Display message string |

---

## Project Structure

```
├── main4.c                          # Main application — system init, SMS handling loop
├── uart.c / uart.h                  # UART0 driver with interrupt-based receive
├── uart_def.h                       # UART configuration macros (baud rate, pins)
├── uart0.h                          # Alternate UART0 prototype declarations
├── gsm.c / gsm.h                    # GSM module AT command interface
├── security.c / security.h          # SMS format verification & content extraction
├── i2c.c / i2c.h                    # I2C master driver
├── i2c_eeprom.c / i2c_eeprom.h      # EEPROM read/write functions
├── i2c_eeprom_defines.h             # EEPROM slave addresses & memory map
├── dotmatrix.c / dotmatrix.h        # Display scrolling logic
├── sipo_74hc164.c / sipo_74hc164.h  # Shift register serial data driver
├── dot_mat_def.h                    # 5×8 character font bitmap array (96 ASCII chars)
├── defines.h                        # Bit-manipulation macros (SETBIT, WRITEBIT, etc.)
└── types.h                          # Embedded type aliases (u8, u16, u32, s8, etc.)
```

---

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/<your-username>/<repo-name>.git
```

### 2. Open in Keil µVision

- Create a new project targeting the **LPC2148**
- Add all `.c` source files to the project
- Ensure all `.h` header files are in the include path

### 3. Configure the Authorized Number

In `main4.c`, set your default authorized number:

```c
u8 auth_number[] = "9999999999";  // Replace with your number
```

> This can also be updated remotely via SMS after flashing.

### 4. Build and Flash

- Compile with Keil (zero errors expected)
- Flash the `.hex` output to LPC2148 using **Flash Magic** over the USB-UART converter


### 5. Test the GSM Module

Use HyperTerminal or any Serial Monitor:

```
AT                        → Check communication (expect: OK)
ATE0                      → Disable echo
AT+CMGF=1                 → Set SMS text mode
AT+CNMI=2,1,0,0,0         → Enable new SMS notifications
AT+CMGR=1                 → Read SMS at slot 1
AT+CMGD=1                 → Delete SMS at slot 1
AT+CMGS="<num>"           → Send SMS (enter message, end with Ctrl+Z)
```

---

## AT Commands Reference

| Command | Purpose |
|---|---|
| `AT` | Test communication with GSM module |
| `ATE0` | Disable command echo |
| `AT+CMGF=1` | Set SMS mode to text |
| `AT+CNMI=2,1,0,0,0` | Route new SMS notifications to UART |
| `AT+CMGR=1` | Read SMS stored at memory slot 1 |
| `AT+CMGD=1` | Delete SMS at memory slot 1 |
| `AT+CMGS="<number>"` | Send SMS to the specified number |

---

## Side-by-side Of Phone Sending SMS And The Dot Matrix Displaying The Result:

<!-- 🎥 INSERT VIDEO HERE: Full demo video showing:
     1. Sending a valid SMS → message appears on dot matrix
     2. Sending from unauthorized number → alert SMS received
     3. Sending wrong format → format-error SMS received
     Upload to YouTube and embed using the format below: -->

<!-- [![Project Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=YOUR_VIDEO_ID) -->

https://github.com/user-attachments/assets/3bde4ab9-1600-43d7-8d11-a8ed610d4d2f


---

## Author

**Barika Naveen**
🎓 EEE Student | Embedded Systems Enthusiast
💡 Interested in ARM, Embedded C & IoT

---

## License

This project was developed for educational purposes. Feel free to use and modify it for your own embedded systems learning.

---

## ⭐ Support

If you find this project helpful:
- ⭐ Star this repository
- 🍴 Fork it
- 🛠️ Contribute improvements

Happy Coding! 🚀
