# IoT H4 — Opgave 1: UART + LED (ATmega328PB)

Pollet UART-echo med store/små bogstaver byttet, plus LED der blinker via Timer1.

**Hardware:** ATmega328PB Xplained Mini @ 16 MHz, 9600 baud, 8N1.

## Hvad løsningen gør

1. Initialiserer USART0 (PD0 = RX, PD1 = TX).
2. Starter Timer1, så den røde LED på **PB3** toggler ca. hvert 500 ms (interrupt).
3. Venter på et tegn fra PC’en.
4. Hvis tegnet er et bogstav, byttes case med `^= 0x20` (bit 5).
5. Sender resultatet tilbage over UART.

Eksempel: du sender `d` → boardet svarer `D`.

## Hvordan koden er bygget op

| Fil | Rolle |
|-----|--------|
| `src/main.c` | Setup, hovedloop, `ConvertReceivedChar`, LED-callback |
| `src/Uart.c` / `include/Uart.h` | Baud, init, `uart_getch` / `uart_putch`, `printf` via `stdout` |
| `src/timer1.c` / `include/timer1.h` | CTC-timer med callback hvert *n* ms |
| `include/ProjectDefines.h` | `F_CPU`, LED-bit, fælles includes |

### Case-toggle (`^= 0x20`)

I ASCII ligger `'A'`–`'Z'` og `'a'`–`'z'` 32 (= `0x20`) fra hinanden. At XOR’e bit 5 vender mellem store og små bogstaver uden `if` for hver retning.

### UART vs. timer

UART kører **polling** i main-loop (`uart_getch` venter på `RXC0`).  
LED’en drives af **Timer1-interrupt**, så blink fortsætter selv mens programmet venter på tegn.

## CP2102 (ekstern USB–UART)

USART0 er den samme linje som boardets indbyggede mEDBG (COM3). Med CP2102:

| CP2102 | Board |
|--------|--------|
| TXD | PD0 (RX) *eller omvendt — byt hvis tavst* |
| RXD | PD1 (TX) |
| GND | GND |

- **COM4** = CP2102 (opgavens eksterne UART)
- **Board-USB** = strøm + programmering
- Begge COM-porte kan ikke “eje” PD0/PD1 samtidigt; med CP2102 tilsluttet bruges typisk **COM4**

## Byg / flash

Byg og flash via MPLAB / XC8 som i undervisningen (mål: ATmega328PB).  
Åbn seriel monitor @ **9600** på den COM-port du bruger (COM3 uden CP2102, COM4 med CP2102).
