# CAR Black Box

A real-time automotive event logger built on the PIC18F4580 microcontroller. It captures speed, gear changes, and RTC timestamps across a 6-state FSM (dashboard → menu → log → set time → download → clear) and persists every event to internal EEPROM. Logs can be downloaded over UART at 9600 baud, just like a vehicle's actual black box recorder.

## Features

- 6-state finite state machine: dashboard → menu → log → set time → download → clear
- Real-time speed capture via ADC
- Gear-change detection and logging
- RTC timestamping via DS1307 over I2C
- Persistent storage to 256-byte internal EEPROM (25 fixed-size event records)
- Full log download over UART at 9600 baud
- Debounced matrix keypad navigation with no false state transitions

## Technologies Used

- Embedded C
- PIC18F4580
- I2C, UART
- GPIO, Timers, ADC
- Internal EEPROM
- Matrix Keypad, Character LCD
- DS1307 RTC

## Hardware Used

- PIC18F4580 microcontroller board
- DS1307 RTC module
- 4x4 matrix keypad
- 16x2 character LCD
- UART-to-USB converter (for log download to a PC)
- Crystal oscillator + standard power supply circuit

## Folder Structure

```
CAR_BLACK_BOX/                  # MPLAB X project root (PIC18F4580)
├── main.c                      # FSM dispatch loop
├── black_box.h                 # Shared State_t enum + module includes
├── view_dashboard.c            # e_dashboard state
├── display_main_menu.c         # e_main_menu state
├── view_log.c                  # e_view_log state
├── set_time.c                  # e_set_time state
├── download_log.c              # e_download_log state (UART)
├── adc.c / adc.h                # Speed capture
├── i2c.c / i2c.h                # I2C bus driver (used by DS1307)
├── ds1307.c / ds1307.h          # RTC timestamping
├── eeprom.c / eeprom.h          # 256-byte internal EEPROM persistence
├── matrix_keypad.c / matrix_keypad.h
├── clcd.c / clcd.h              # Character LCD driver
├── timer0.c / timer0.h
├── uart.c / uart.h
├── Makefile                     # MPLAB X-generated top-level makefile
├── nbproject/                   # MPLAB X project config (device, build steps)
├── build/                       # Generated object files (.p1, .i) — safe to .gitignore
└── dist/                        # Generated .hex/.elf/.map output — safe to .gitignore
```

> This matches your actual repo. `build/` and `dist/` are compiler output — consider adding them to `.gitignore` so the repo only shows source on GitHub.

## How to Build / Run

1. Open **MPLAB X IDE** and use `File → Open Project`, pointing it at the `CAR_BLACK_BOX` folder (the one containing `nbproject/`). The device (PIC18F4580) and XC8 compiler are already set in the project config.
2. Build the project (`Production → Build Main Project`, or `Clean and Build` for a fresh run). This regenerates `build/` and `dist/CAR_BLACK_BOX.X.production.hex`.
3. Flash `dist/default/production/CAR_BLACK_BOX.X.production.hex` to the PIC18F4580 using a PICkit programmer (or `Make and Program Device` directly from MPLAB X if the PICkit is connected).
4. Wire up the matrix keypad, character LCD, and DS1307 RTC module per the pin assignments in `matrix_keypad.h`, `clcd.h`, and `ds1307.h`.
5. Power on the board and navigate the FSM via the keypad: dashboard → menu → log → set time → download → clear (see the `State_t` enum in `black_box.h`).
6. To retrieve logs, connect a UART-to-USB adapter, open a serial terminal (e.g. PuTTY/minicom) at **9600 baud**, and trigger the download state.

## Key Learnings

- Eliminated false multi-state transitions caused by keypad bounce by implementing a key-release gate across all 6 FSM states, ensuring each physical press triggered exactly one valid transition.
- Prevented EEPROM corruption during ISR execution by enforcing the mandatory 0x55/0xAA write-unlock sequence with bracketed interrupt disable/re-enable, guaranteeing atomic writes across all 256 bytes.
- Designed a fixed 10-byte EEPROM record format for gear, speed, and timestamp fields, enabling storage of 25 event records with O(1) random-access retrieval and full UART download across power cycles.
