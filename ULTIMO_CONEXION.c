#include <16F877A.h>
#fuses NOWDT, XT, NOPROTECT, PUT, NOBROWNOUT, NOLVP
#use delay(clock=4000000)

#define lcd_rs_pin      pin_c6
#define lcd_rw_pin      pin_c5
#define lcd_enable_pin  pin_c7
#define lcd_data4       pin_d4
#define lcd_data5       pin_d5
#define lcd_data6       pin_d6
#define lcd_data7       pin_d7

#include <lcd.c>

#define INPUT_PIN_A0 PIN_A0
#define INPUT_PIN_A1 PIN_A1
#define INPUT_PIN_C0 PIN_C0

#define use_portb_kbd TRUE
#include <kbd.c>
#include <stdio.h> 

#define OUTPUT1_PIN pin_e0
#define OUTPUT2_PIN pin_e1
#define OUTPUT3_PIN pin_e2

float contador = 0;
int estado_anterior_A0 = 1;
int estado_anterior_A1 = 1;
int estado_anterior_C0 = 1;

char tecla;
char codigo[2];

int detectar_cambio_estado(int pin, int* estado_anterior) {
    int estado_actual = input(pin);

    if (*estado_anterior == 1 && estado_actual == 0) {
        *estado_anterior = estado_actual;
        return 1;
    }
    *estado_anterior = estado_actual;
    return 0;
}

void mostrar_saldo() {
    lcd_gotoxy(1,1);
    lcd_putc("\fTOTAL:");
    lcd_gotoxy(1,2);
    printf(lcd_putc, "%.1f", contador);
}

void main() {
    lcd_init();  
    kbd_init();  
    port_b_pullups(TRUE);
    output_low(OUTPUT1_PIN);  
    output_low(OUTPUT2_PIN);
    output_low(OUTPUT3_PIN);

    mostrar_saldo();

    while (TRUE) {
        if (detectar_cambio_estado(INPUT_PIN_A0, &estado_anterior_A0)) {
            contador += 1.0;
            mostrar_saldo();
            delay_ms(200);
        }
        
        if (detectar_cambio_estado(INPUT_PIN_A1, &estado_anterior_A1)) {
            contador += 0.5;
            mostrar_saldo();
            delay_ms(200);
        }

        if (detectar_cambio_estado(INPUT_PIN_C0, &estado_anterior_C0)) {
            lcd_gotoxy(1,1);
            printf(lcd_putc, "Total: %.1f", contador); 

            lcd_gotoxy(1,2);
            lcd_putc("Ingresa codigo:");

            int i = 0;
            
            while (i < 1) {
                tecla = kbd_getc();
                
                if (tecla != 0) {
                    if (tecla == '*') {
                        lcd_gotoxy(1,2);  
                        lcd_putc("Ingresa codigo:");
                        i = 0;
                    } else {
                        codigo[i] = tecla;
                        codigo[i+1] = '\0';
                        lcd_gotoxy(1, 2);
                        lcd_putc(codigo);
                        i++;
                    }
                }
            }
            
            codigo[1] = '\0';  // Asegúrate de que la cadena esté correctamente terminada

            output_low(OUTPUT1_PIN);
            output_low(OUTPUT2_PIN);
            output_low(OUTPUT3_PIN);
      
            if (codigo[0] == '1' && contador >= 0.5) {
                lcd_gotoxy(1,1);
                lcd_putc("\fProd 1 - Gracias");
                output_high(OUTPUT1_PIN);
                delay_ms(3000);
                output_low(OUTPUT1_PIN);
                contador -= 0.5;  // Resta el valor del producto 1
            } else if (codigo[0] == '2' && contador >= 1.5 ) {
                lcd_gotoxy(1,1);
                lcd_putc("\fProd 2 - Gracias");
                output_high(OUTPUT2_PIN);
                delay_ms(3000);
                output_low(OUTPUT2_PIN);
                contador -= 1.5;  // Resta el valor del producto 2
            } else if (codigo[0] == '3' && contador >= 2.0) {
                lcd_gotoxy(1,1);
                lcd_putc("\fProd 3 - Gracias");
                output_high(OUTPUT3_PIN);
                delay_ms(3000);
                output_low(OUTPUT3_PIN);
                contador -= 2.0;  // Resta el valor del producto 3
            } else {
                lcd_gotoxy(1,1);
                lcd_putc("\fCodigo invalido o no tiene saldo");
            }

            delay_ms(2000);
            mostrar_saldo();
        }

        delay_ms(50);  
    }
}

