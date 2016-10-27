#include "_safe_arduino.hpp"
#include <SoftwareSerial.h>
#include <SSD1306Spi.h>
#include <OLEDDisplayUi.h>
#include <algorithm>

#include "pins.hpp"
#include "World.hpp"
#include "entities/Bird.hpp"
#include "entities/Pipe.hpp"

SSD1306Spi display{builtin_tx_led, spi_oled_dc, spi_oled_cs};
OLEDDisplayUi ui{&display};
World world;
SoftwareSerial bluetooth{softserial_tx, softserial_rx};
unsigned int bird_id;

static void score_counter(OLEDDisplay* display, OLEDDisplayUiState* state) {
    static unsigned int start_time = millis();
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    unsigned int score = (millis() - start_time) / 1000;
    display->drawString(128, 5, String(score));
}

static void world_frame(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    state->isIndicatorDrawen = false;

    world.update();
    for (auto& entity : world) {
        entity->render(*display, *state, {x, y});
    }
}

constexpr uint8_t frame_count = 1;
FrameCallback frames[frame_count] = { world_frame };

constexpr uint8_t overlay_count = 1;
OverlayCallback overlays[overlay_count] = { score_counter };

void setup() {
    pinMode(flash_button_pin, INPUT_PULLUP);

    bluetooth.begin(115200);

    bluetooth.println("Now attempting to connect to OLED display on SPI.");
    if (!display.init()) {
        bluetooth.println("FATAL ERROR: Couldn't connect to the SPI display! Stopping.");
        while (true) { delay(0); }
    }

    ui.setFrameAnimation(SLIDE_LEFT);
    ui.setFrames(frames, frame_count);
    ui.setOverlays(overlays, overlay_count);
    ui.setTargetFPS(60);
    ui.disableIndicator();
    ui.disableAutoTransition();
    ui.init();
    ui.switchToFrame(0);

    display.setContrast(255);
    display.normalDisplay();
    display.clear();

    auto bird = std::unique_ptr<Entity>(new Bird({1000, 1000}));
    bird_id = bird->get_id();
    world.add(std::move(bird));
    world.add(std::unique_ptr<Entity>(new Pipe({12800, 0})));

    ui.update();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setColor(INVERSE);
    display.drawString(64, 20, "PRESS BUTTON");
    display.display();

    bluetooth.println("Setup complete.");

    while (digitalRead(flash_button_pin)) delay(0);
    while (!digitalRead(flash_button_pin)) delay(0);

    bluetooth.println("Game start.");
}

void loop() {
    auto spare = ui.update();
    auto start = millis();

    auto iterator_to_bird = std::find_if(world.begin(), world.end(),
        [](const std::unique_ptr<Entity>& entity) {
            return entity->get_id() == bird_id;
        }
    );

    if (iterator_to_bird == world.end()) { // Bird is destroyed
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.setColor(INVERSE);
        display.drawString(64, 10, "Game Over");
        display.drawString(64, 25, "Press Reset");
        display.display();

        while (true) { delay(100000); }
    }

    display.display();

    auto time_to_wait = spare - (int)(millis() - start);
    delay(time_to_wait >= 0 ? time_to_wait : 0);
}
