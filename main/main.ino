// -*- lsst-c++ -*-
/**
 * OpenHerb Telemeter Main
 * 
 * @file src.ino
 *
 * @brief Main event loop for telemetry collection and serial publishing
 *
 * @author Christian Sargusingh
 * 
 * Copyright © 2020 OpenHerb.
 */
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include <Lumex.h>
#include <Css.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDR 0x3C
#define BME_ADDR 0x76
#define H20_PIN 7

#define SAMPLE_SIZE 10

//Declaring the display name (display)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// sensor values
uint8_t idx = 0;
uint32_t tp[SAMPLE_SIZE];   // ambient temperature array 
uint32_t pa[SAMPLE_SIZE];   // ambient pressure array
uint32_t rh[SAMPLE_SIZE];   // relative humidity

// init sensor interfaces
Css* css;
Lumex* lumex;
Adafruit_BME280 bme; // I2C Interface

void write_oled(uint32_t sm, uint32_t lx, uint32_t tp, uint32_t pa, uint32_t rh){
	// frame setup 
	display.clearDisplay();
    display.setTextSize(1);
	display.setTextColor(WHITE);

    display.setCursor(0,0);
    display.println("SOIL");
    display.setCursor(0,10);
    display.println(sm);
    display.setCursor(0,20);
    display.println("%");

    display.setCursor(27,0);
    display.println("PRES");
    display.setCursor(27,10);
    display.println(pa);
    display.setCursor(27,20);
    display.println("kPa");

    display.setCursor(54,0);
    display.println("TEMP");
    display.setCursor(54,10);
    display.println(tp);
    display.setCursor(54,20);
    display.print(static_cast<char>(247));
    display.println("C");

    display.setCursor(81,0);
    display.println("LUX");
    display.setCursor(81,10);
    display.println(lx);
    display.setCursor(81,20);
    display.println("Lux");

    display.setCursor(109,0);
    display.println("RH");
    display.setCursor(109,10);
    display.println(rh);
    display.setCursor(109,20);
    display.println("%");
	// write to display
	display.display();
}


void setup() {
    // setup serial interface
    Serial.begin(9600);
    const Css::Spec css_spec = { .css_pin = A6, .buffer_size = 5, .av = 620, .sv = 310 };
    css = new Css(css_spec);
    const Lumex::Spec lumex_spec = { .lx_pin = A7, .buffer_size = 10, .vin = 5, .sr = 10000 };
    lumex = new Lumex(lumex_spec);
    // relay module output (active high)
    pinMode(H20_PIN, OUTPUT);
    digitalWrite(H20_PIN,HIGH);
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    if (!bme.begin(BME_ADDR)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    // Start the OLED display
	display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
	display.display();

}

void loop() {
    uint8_t sm;
    uint16_t lx;
    if ( idx == SAMPLE_SIZE ) {
        idx = 0;
        digitalWrite(H20_PIN,LOW);
        delay(2000);
        digitalWrite(H20_PIN,HIGH);
    }
    // poll sensors (updates internal buffers)
    sm = css->read();
    lx = lumex->read();

    tp[idx] = bme.readTemperature();
    pa[idx] = bme.readPressure()/1000; //kPa
    rh[idx] = bme.readHumidity();
    // write to OLED
    write_oled(sm, lx, tp[idx], pa[idx], rh[idx]);
    publish_sensorframe(sm,lx);
    // Serial.println("Index: " + String(idx));
    delay(500);
    idx += 1;
}

/**
 * Computes the standard deviation of the samples.
 *
 * @return standard deviation of the cached sensor metrics
 */
uint32_t std_deviation(uint32_t samples[], int avg){
	uint32_t stdd = 0;
	uint32_t variance = 0;
	// compute variance
	for (uint8_t i = 0; i < SAMPLE_SIZE; i++) {
		uint32_t sample = sq(samples[i] - avg);
		// Serial.print("Sample: ");
		// Serial.println(sample);
		variance += sample;
	}
	variance /= SAMPLE_SIZE;
	// Serial.print("Variance: ");
	// Serial.println(variance);
	// calculate std deviation
	stdd = sqrt(variance);
	// Serial.print("Standard Deviation: ");
	// Serial.println(stdd);
	return stdd;
}

void publish_sensorframe(uint8_t sm, uint16_t lx) {
    // compute averages
    uint32_t avg_tp = 0;
    uint32_t avg_pa = 0;
    uint32_t avg_rh = 0;
    // average all sensor readings
    for ( int i = 0; i < SAMPLE_SIZE; i++ ) {
        avg_tp += tp[i];
        avg_pa += pa[i];
        avg_rh += rh[i];
    }
    avg_tp /= SAMPLE_SIZE;
    avg_pa /= SAMPLE_SIZE;
    avg_rh /= SAMPLE_SIZE;
    // Construct sensorframe
    String sensorframe = String("TP&") + String(avg_tp) + "|" + "RH&" + String(avg_rh) + "|" + "PA&" + String(avg_pa) + "|" + "SM&" + String(sm) + "|" + "LX&" + String(lx) + "|";
    // Publish through serial for digest
    Serial.println(sensorframe);
}