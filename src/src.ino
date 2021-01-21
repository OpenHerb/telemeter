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
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
#include <Lumex.h>
#include <Css.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define SAMPLE_SIZE 25

//Declaring the display name (display)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// sensor values
uint8_t idx = 0;

uint32_t sm[SAMPLE_SIZE];
uint32_t lx[SAMPLE_SIZE];

// init sensor interfaces
Css Css;
Lumex Lumex;

void write_oled(uint32_t sm, uint32_t lx){
	// frame setup 
	display.clearDisplay();
    display.setTextSize(1);
	display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Soil:");
    display.setTextSize(2);
    display.setCursor(0,18);
    display.println(sm);
    display.setCursor(50,0);
    display.setTextSize(1);
    display.println("Lux:");
    display.setCursor(50,18);
    display.setTextSize(2);
    display.println(lx);
	// write to display
	display.display();
}


void setup() {
    // setup serial interface
    Serial.begin(9600);
    Serial.println("OpenHerb Telemeter © 2021");
    Serial.println("-------------------------");
    Serial.println("Version 0.1");
    // Start the OLED display
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.display();
}

void loop() {
    // Poll sensors and save to sampling list
    sm[idx] = Css.read();
    lx[idx] = Lumex.read();
    if ( idx == SAMPLE_SIZE ) {
        idx = 0;
        publish_sensorframe();
    }
    // write to OLED
    write_oled(sm[idx], lx[idx]);
    // Serial.println(sm[idx], lx[idx]);
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
	//calculate std deviation
	stdd = sqrt(variance);
	// Serial.print("Standard Deviation: ");
	// Serial.println(stdd);
	return stdd;
}

void publish_sensorframe() {
    // compute averages
    uint32_t avg_sm = 0;
    uint32_t avg_lx = 0;
    // average all sensor readings
    for ( int i = 0; i < SAMPLE_SIZE; i++ ) {
        avg_sm += sm[i];
        avg_lx += lx[i];
    }
    avg_sm /= SAMPLE_SIZE;
    avg_lx /= SAMPLE_SIZE;
    
    // Construct sensorframe
    String sensorframe = String("SM&") + String(avg_sm) + "|" + "LX&" + String(avg_lx) + "|"+ "SM_SD&" + String(std_deviation(sm, avg_sm)) + "|" + "LX_SD&" + String(std_deviation(lx, avg_lx)) + "|";
    // Publish through serial for digest
    Serial.println(sensorframe);
}