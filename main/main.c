#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht11.h"


void app_main(void)
{
    printf("ESP32 DHT11 TEST:%s,%s!\r\n", __DATE__, __TIME__);
    double humidity, temperature;

    while (1)
    {
        dht_read_data(4, &humidity, &temperature);
        printf("Temp=%f, Humi=%f\r\n", temperature, humidity);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
