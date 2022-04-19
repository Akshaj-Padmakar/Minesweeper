#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "main.h"
#include "Nokia5110.h"
#include <time.h>

#define up 15
#define down 14
#define left 13
#define right 12
#define clik 11
#define flag 10

#define LED_PIN 25

int main() {

    //intialize stdio
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_init(up);
    gpio_init(down);
    gpio_init(left);
    gpio_init(right);
    gpio_init(clik);
    gpio_init(flag);

    // set direction of two gpios
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(up, GPIO_IN);
    // Enable the internal pullup resistor to Button
    gpio_pull_up(up);

    gpio_set_dir(down, GPIO_IN);
    // Enable the internal pullup resistor to Button
    gpio_pull_up(down);

    gpio_set_dir(left, GPIO_IN);
    // Enable the internal pullup resistor to Button
    gpio_pull_up(left);

    gpio_set_dir(right, GPIO_IN);
    // Enable the internal pullup resistor to Button
    gpio_pull_up(right);

    gpio_set_dir(clik, GPIO_IN);
    // Enable the internal pullup resistor to Button
    gpio_pull_up(clik);

    gpio_set_dir(flag, GPIO_IN);
    // Enable the internal pullup resistor to Button
    gpio_pull_up(flag);

    // intialize the SPI0 of Raspberry Pi
    // This example will use SPI0 at 4MHz.
    spi_init(SPI_PORT, 4000 * 1000);
    //gpio_set_function(LCD_MISO, GPIO_FUNC_SPI);
    gpio_set_function(LCD_SCK, GPIO_FUNC_SPI);
    gpio_set_function(LCD_MOSI, GPIO_FUNC_SPI);

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(LCD_RST);
    gpio_set_dir(LCD_RST, GPIO_OUT);
    gpio_init(LCD_CS);
    gpio_set_dir(LCD_CS, GPIO_OUT);
    gpio_init(LCD_DC);
    gpio_set_dir(LCD_DC, GPIO_OUT);

    // call the LCD initialization
    Nokia5110_Init();
    clearDisplay();

    // LCD_Demo("hello");

    // while (1){

    // }
    grid();
    bool flg = false, start = false;
    while (1) {
        if (gpio_get(up) == false) {
            sleep_ms(100);
            if (gpio_get(up) == false) {
                if (flg) {
                    continue;
                }
                move_cursor(0, -1);
                flg = true;
                sleep_ms(100);
                display();
                gpio_put(LED_PIN, 1);
            }
        }
        else if (gpio_get(down) == false) {
            sleep_ms(100);
            if (gpio_get(down) == false) {
                if (flg) {
                    continue;
                }
                move_cursor(0, 1);
                flg = true;
                sleep_ms(100);
                display();
                gpio_put(LED_PIN, 1);
            }
        }
        else if (gpio_get(left) == false) {
            sleep_ms(100);
            if (gpio_get(left) == false) {
                if (flg) {
                    continue;
                }
                move_cursor(-1, 0);
                flg = true;
                sleep_ms(100);
                display();
                gpio_put(LED_PIN, 1);
            }
        }
        else if (gpio_get(right) == false) {
            sleep_ms(100);
            if (gpio_get(right) == false) {
                if (flg) {
                    continue;
                }
                move_cursor(1, 0);
                flg = true;
                sleep_ms(100);
                display();
                gpio_put(LED_PIN, 1);
            }
        }
        else if (gpio_get(clik) == false) {
            sleep_ms(100);
            if (gpio_get(clik) == false) {
                if (flg) {
                    continue;
                }
                if (!start) {
                    start = true;
                    start = generate();
                }
                else {
                    start = cl();
                }
                gridd();
                flg = true;
                gpio_put(LED_PIN, 1);
            }
        }
        else if (gpio_get(flag) == false) {
            sleep_ms(100);
            if (gpio_get(flag) == false) {
                if (flg) {
                    continue;
                }
                gpio_put(LED_PIN, 1);
                flagg();
                flg = true;
                sleep_ms(100);
                display();
            }
        }
        else {
            gpio_put(LED_PIN, 0);
            flg = false;
        }
    }

    return 0;
}
