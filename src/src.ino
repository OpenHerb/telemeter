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
#include <Adafruit_BME280.h>
#include <Lumex.h>
#include <Css.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDR 0x3C
#define BME_ADDR 0x76

#define SAMPLE_SIZE 25

//Declaring the display name (display)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// sensor values
uint8_t idx = 0;
uint32_t sm[SAMPLE_SIZE];   // soil moisture array
uint32_t lx[SAMPLE_SIZE];   // luminous flux array
uint32_t tp[SAMPLE_SIZE];   // ambient temperature array 
uint32_t pa[SAMPLE_SIZE];   // ambient pressure array
uint32_t rh[SAMPLE_SIZE];   // ambient pressure array

// init sensor interfaces
Css Css;
Lumex Lumex;
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
    display.println("hPa");

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
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    if (!bme.begin(BME_ADDR)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    Serial.println("OpenHerb Telemeter © 2021");
    Serial.println("-------------------------");
    Serial.println("Version 0.1");
    // Start the OLED display
	display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
	display.display();

}

void loop() {
    // Poll sensors and save to sampling list
    sm[idx] = Css.read();
    lx[idx] = Lumex.read();
    tp[idx] = bme.readTemperature();
    pa[idx] = bme.readPressure()/100; //hPa
    rh[idx] = bme.readHumidity();
    if ( idx == SAMPLE_SIZE ) {
        idx = 0;
        publish_sensorframe();
    }
    // write to OLED
    write_oled(sm[idx], lx[idx], tp[idx], pa[idx], rh[idx]);
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
    uint32_t avg_tp = 0;
    uint32_t avg_pa = 0;
    uint32_t avg_rh = 0;
    // average all sensor readings
    for ( int i = 0; i < SAMPLE_SIZE; i++ ) {
        avg_sm += sm[i];
        avg_lx += lx[i];
        avg_tp += tp[i];
        avg_pa += pa[i];
        avg_rh += rh[i];
    }
    avg_sm /= SAMPLE_SIZE;
    avg_lx /= SAMPLE_SIZE;
    avg_tp /= SAMPLE_SIZE;
    avg_pa /= SAMPLE_SIZE;
    avg_rh /= SAMPLE_SIZE;
    
    // Construct sensorframe
    String sensorframe = String("TP&") + String(avg_tp) + "|" + "RH&" + String(avg_rh) + "|" + "PA&" + String(avg_pa) + "|" + "SM&" + String(avg_sm) + "|" + "LX&" + String(avg_lx) + "|";
    // Publish through serial for digest
    Serial.println(sensorframe);
}