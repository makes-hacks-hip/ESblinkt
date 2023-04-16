#include "ESblinkt.hpp"

struct RgbColor color_wheel(uint8_t pos)
{
    uint16_t p = (uint8_t)pos;

    if (p < 85)
    {
        return RgbColor((uint8_t)(255 - p * 3), (uint8_t)(p * 3), (uint8_t)0);
    }
    else if (p < 170)
    {
        p -= 85;
        return RgbColor((uint8_t)0, (uint8_t)(255 - p * 3), (uint8_t)(p * 3));
    }
    else
    {
        p -= 170;
        return RgbColor((uint8_t)(p * 3), (uint8_t)0, (uint8_t)(255 - p * 3));
    }
}

void fill_rainbow(uint8_t offset, struct strip leds)
{
    uint16_t color_index = 0;
    for (uint16_t i = 0; i < leds.pixelCount; i++)
    {
        color_index = (i + (uint16_t)offset) % 256;
        leds.setPixelColor(i, color_wheel(color_index));
    }
}

void fill_solid(struct RgbColor color, struct strip leds)
{
    for (uint16_t i = 0; i < leds.pixelCount; i++)
    {
        leds.setPixelColor(i, color);
    }
}

void rainbow(uint32_t rainbow_speed, struct strip leds)
{
    for (int i = 0; i < 256; i++)
    {
        fill_rainbow(i, leds);
        leds.commit();
        vTaskDelay(rainbow_speed / portTICK_PERIOD_MS);
    }
}

void solid(struct RgbColor color, struct strip leds)
{
    fill_solid(color, leds);
    leds.commit();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void three_sided(struct three_sided three_sided_config, struct strip leds)
{
    uint32_t delay = 1000;
    uint8_t n = 1;

    if (three_sided_config.anim)
    {
        delay = three_sided_config.speed;
        n = 3;
    }

    for (int off = 0; off < n; off++)
    {

        for (int j = 0; j < three_sided_config.endRight; j++)
        {
            leds.setPixelColor(j, three_sided_config.colors[(off) % 3]);
        }
        for (int j = three_sided_config.endRight; j < three_sided_config.endTop; j++)
        {
            leds.setPixelColor(j, three_sided_config.colors[(off + 1) % 3]);
        }
        for (int j = three_sided_config.endTop; j < leds.pixelCount; j++)
        {
            leds.setPixelColor(j, three_sided_config.colors[(off + 2) % 3]);
        }
        leds.commit();
        vTaskDelay(delay / portTICK_PERIOD_MS);
    }
}
