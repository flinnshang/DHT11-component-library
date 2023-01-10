# _DHT11-component-library_

Esp-idf v5.0 driver component for DHT11 temperature and humidity sensor

## Install

Esp-idf v5.0 project

## How to use
examples file：main.c

uint8_t dht_read_data(gpio_num_t pin, uint8_t *humidity, uint8_t *temperature);

<b>WARNING</b>: dht_read_data() is a blocking function.