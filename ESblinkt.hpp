#ifndef ESBLINKT_HPP
#define ESBLINKT_HPP

#include <Arduino.h>
#include <NeoPixelBus.h>

struct RgbColor color_wheel(uint8_t pos);
void fill_rainbow(uint8_t offset, struct strip leds);
void fill_solid(struct RgbColor color, struct strip leds);
void rainbow(struct strip leds);
void solid(struct RgbColor color, struct strip leds);
void three_sided(struct three_sided three_sided_config, struct strip leds);

struct strip
{
    uint16_t pixelCount;
    void (*setPixelColor)(uint16_t, Neo3ByteElements::ColorObject);
    void (*commit)(void);
};

struct three_sided
{
    bool anim;
    uint32_t speed;
    uint16_t endRight;
    uint16_t endTop;
    struct RgbColor colors[3];
};

#endif
