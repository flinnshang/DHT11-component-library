#include <stdio.h>
#include "driver/gpio.h"
#include "esp32/rom/gpio.h"
#include "esp32/rom/ets_sys.h"

static gpio_num_t DHT11_PIN;

static void DHT11_Init(void)
{
    gpio_pad_select_gpio(DHT11_PIN);
    gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(DHT11_PIN, 0);
    ets_delay_us(19 * 1000);
    gpio_set_level(DHT11_PIN, 1);
    ets_delay_us(30);
    gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);
    while (!gpio_get_level(DHT11_PIN))
        ;
    while (gpio_get_level(DHT11_PIN))
        ;
}

static uint8_t DHT11_ReadValue(void)
{
    uint8_t i, sbuf = 0;
    for (i = 8; i > 0; i--)
    {
        sbuf <<= 1;
        while (!gpio_get_level(DHT11_PIN))
            ;
        ets_delay_us(30);
        if (gpio_get_level(DHT11_PIN))
        {
            sbuf |= 1;
        }
        else
        {
            sbuf |= 0;
        }
        while (gpio_get_level(DHT11_PIN))
            ;
    }
    return sbuf;
}

static uint8_t DHT11_ReadTemHum(uint8_t *buf)
{
    uint8_t check;
    buf[0] = DHT11_ReadValue();
    buf[1] = DHT11_ReadValue();
    buf[2] = DHT11_ReadValue();
    buf[3] = DHT11_ReadValue();
    check = DHT11_ReadValue();
    if (check == buf[0] + buf[1] + buf[2] + buf[3])
        return 1;
    else
        return 0;
}
static double get_float_by_int(uint8_t front, uint8_t back)
{

    char observable[8];
    double f;
    sprintf(observable, "%d.%d", front, back);
    sscanf(observable, "%lf", &f);
    return f;
}
uint8_t dht_read_data(gpio_num_t pin, double *humidity, double *temperature)
{
    DHT11_PIN = pin;
    DHT11_Init();
    uint8_t Data[4] = {0};
    if (DHT11_ReadTemHum(Data))
    {
        *humidity = get_float_by_int(Data[0], Data[1]);
        *temperature = get_float_by_int(Data[2], Data[3]);

        return 1;
    }
    else
    {
        return 0;
    }
}
