#include "dht11.h"

void dht11_init()
{
    gpio_init(DHT11_DATA_PIN);      
    gpio_set_dir(DHT11_DATA_PIN, GPIO_OUT);
    gpio_put(DHT11_DATA_PIN, 0);
    sleep_ms(18);
    gpio_put(DHT11_DATA_PIN, 1);
    sleep_us(20);
    gpio_set_dir(DHT11_DATA_PIN, GPIO_IN);
    while(gpio_get(DHT11_DATA_PIN) == 1) {}
    while(gpio_get(DHT11_DATA_PIN) == 0) {}
    while(gpio_get(DHT11_DATA_PIN) == 1) {}
}

int dht11_read_data(float *temperature, float *humidity)
{
    uint8_t data[5] = {0, 0, 0, 0, 0};
    for (int i=0; i<40; i++)
    {
        while(gpio_get(DHT11_DATA_PIN) == 0) {}
        uint32_t start_time = time_us_32();
        while (gpio_get(DHT11_DATA_PIN) == 1) {}
        uint32_t duration = time_us_32() - start_time;
        data[i / 8] <<= 1;
        if (duration > 40)
        {
            data[i / 8] |= 1;
        }
    }
    if (data[4] == (data[0] + data[1] + data[2] + data[3]))
    {
        *humidity = data[0];
        *temperature = data[2];
        return 0;
    }
    else return -1;

}