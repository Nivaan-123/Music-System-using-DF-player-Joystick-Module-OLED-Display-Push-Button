#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Setup (128x64, I2C 0x3C)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DFPlayer Serial (D3=RX, D4=TX)
SoftwareSerial dfplayerSerial(3, 4);
DFRobotDFPlayerMini dfplayer;

// Joystick pins
const int JOY_VRx = A0;
const int JOY_VRy = A1;
const int JOY_SW = 2;

int currentSong = 1;
int currentVolume = 20;
int lastJoyX = 512;
int lastJoyY = 512;
bool lastButtonState = HIGH;
bool isPlaying = false;

unsigned long lastDisplayUpdate = 0;
const unsigned long DISPLAY_UPDATE_INTERVAL = 300;

void setup() {
  Serial.begin(115200);
  dfplayerSerial.begin(9600);
  
  pinMode(JOY_SW, INPUT_PULLUP);
  
  delay(500);
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("Initializing DFPlayer...");
  display.display();
  
  delay(2000);
  
  // Initialize DFPlayer
  if (!dfplayer.begin(dfplayerSerial)) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(2);
    display.println("DFPlayer");
    display.println("FAILED!");
    display.display();
    while (1);
  }
  
  dfplayer.setTimeOut(500);
  dfplayer.volume(currentVolume);
  dfplayer.play(1);
  isPlaying = true;
  
  updateDisplay();
}

void loop() {
  int joyX = analogRead(JOY_VRx);
  int joyY = analogRead(JOY_VRy);
  bool buttonPressed = !digitalRead(JOY_SW);
  
  // LEFT: Previous song
  if (joyX < 200 && lastJoyX >= 200) {
    currentSong--;
    if (currentSong < 1) currentSong = 1;
    dfplayer.play(currentSong);
    isPlaying = true;
  }
  
  // RIGHT: Next song
  if (joyX > 800 && lastJoyX <= 800) {
    currentSong++;
    dfplayer.play(currentSong);
    isPlaying = true;
  }
  
  // UP: Volume up
  if (joyY < 200 && lastJoyY >= 200) {
    if (currentVolume < 30) {
      currentVolume++;
      dfplayer.volume(currentVolume);
    }
  }
  
  // DOWN: Volume down
  if (joyY > 800 && lastJoyY <= 800) {
    if (currentVolume > 0) {
      currentVolume--;
      dfplayer.volume(currentVolume);
    }
  }
  
  // BUTTON: Play/Pause
  if (buttonPressed && !lastButtonState) {
    if (isPlaying) {
      dfplayer.pause();
      isPlaying = false;
    } else {
      dfplayer.start();
      isPlaying = true;
    }
  }
  
  lastJoyX = joyX;
  lastJoyY = joyY;
  lastButtonState = buttonPressed;
  
  // Update display periodically
  if (millis() - lastDisplayUpdate > DISPLAY_UPDATE_INTERVAL) {
    updateDisplay();
    lastDisplayUpdate = millis();
  }
  
  delay(80);
}

void updateDisplay() {
  display.clearDisplay();
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Music Player");
  
  // Separator line
  display.drawLine(0, 18, 128, 18, SSD1306_WHITE);
  
  // Song info
  display.setTextSize(1);
  display.setCursor(0, 22);
  display.print("Song: ");
  display.println(currentSong);
  
  // Volume info
  display.setCursor(0, 32);
  display.print("Volume: ");
  display.println(currentVolume);
  
  // Volume bar visualization
  int barWidth = (currentVolume * 80) / 30;
  display.drawRect(0, 42, 80, 8, SSD1306_WHITE);
  display.fillRect(0, 42, barWidth, 8, SSD1306_WHITE);
  
  // Status indicator
  display.setCursor(0, 54);
  if (isPlaying) {
    display.print(">> PLAYING");
  } else {
    display.print("|| PAUSED");
  }
  
  display.display();
}
