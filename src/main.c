#include "../include/ProjectDefines.h"
#include "../include/Uart.h"
#include "../include/timer1.h"

static void ConvertReceivedChar(char *received)
{
    if ((*received >= 'A' && *received <= 'Z') ||
        (*received >= 'a' && *received <= 'z')) {
        *received ^= Upper_Lower_Bit_Value;
    }
}

static void led_toggle(void)
{
    PORTB ^= (1 << RedLedBit);
}

int main(void)
{
    char received;

    DDRB |= (1 << RedLedBit);

    RS232Init();
    timer1_start_ms(500, led_toggle);
    sei();

    printf("\r\nUART klar. Send et bogstav.\r\n");

    for (;;) {
        received = (char)uart_getch(NULL);
        ConvertReceivedChar(&received);

        printf("Sendte tilbage: %c\r\n", received);
        uart_putch(received, NULL);
        printf("\r\n");
    }
}
