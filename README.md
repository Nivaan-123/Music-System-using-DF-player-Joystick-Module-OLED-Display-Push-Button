# Music-System-using-DF-player-Joystick-Module-OLED-Display-Push-Button
# Arduino DFPlayer Mini Music Player

A fully functional portable music player built with Arduino Uno, DFPlayer Mini, joystick control, and SSD1306 OLED display.

## Features

- 🎵 Play/pause MP3 songs from micro-SD card
- 🕹️ Joystick control for song selection and volume adjustment
- 📺 Real-time OLED display showing current song, volume, and playback status
- 🔊 Audio amplification via 8Ω speaker
- ⚡ Simple and intuitive controls

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Microcontroller |
| DFPlayer Mini | 1 | MP3 playback module |
| SSD1306 OLED Display | 1 | 128x64 I²C |
| Analog Joystick | 1 | 5-pin module |
| Speaker | 1 | 8Ω, 0.5W minimum |
| Micro-SD Card | 1 | With MP3 files loadeD(ANY MUSIC YOU LIKE SAVE AS 001.mp3 002.mp3 etc)|
| USB Cable | 1 | For power and programming |
| 1kΩ Resistor | 1 | For TX level shifting |

## Wiring Diagram

```
ARDUINO UNO CONNECTIONS:

DFPlayer Mini:
  TX → D3 (SoftwareSerial RX)
  RX → D4 (SoftwareSerial TX) + 1kΩ resistor
  VCC → 5V
  GND → GND
  SPK1/SPK2 → 8Ω Speaker

SSD1306 OLED (I²C):
  SDA → A4
  SCL → A5
  VCC → 5V
  GND → GND

Analog Joystick:
  VRx → A0
  VRy → A1
  SW → D2
  VCC → 5V
  GND → GND

Power Distribution:
  5V → DFPlayer, OLED, Joystick
  GND → All components (common ground)
  
Note: Use 7.4V battery or external 5V power supply for best results.
```

## Software Setup

### 1. Install Arduino IDE
Download from: https://www.arduino.cc/en/software

### 2. Install Required Libraries

In Arduino IDE, go to **Sketch → Include Library → Manage Libraries** and search for:

1. **DFRobot DFPlayer Mini** by DFRobot
2. **Adafruit SSD1306** by Adafruit
3. **Adafruit GFX Library** by Adafruit (installs with SSD1306)

### 3. Prepare Micro-SD Card

1. Format the micro-SD card to FAT32
2. Create a folder named `mp3` on the root of the card
3. Add your MP3 files and name them:
   - `001.mp3`
   - `002.mp3`
   - `003.mp3`
   - etc. (up to 255 files)
4. Insert into DFPlayer Mini

### 4. Upload Code

1. Connect Arduino to computer via USB
2. Open `dfplayer_complete_working.ino` in Arduino IDE
3. Select Board: Arduino Uno
4. Select Port: (your connected Arduino port)
5. Click **Upload**

## Controls

| Action | Control |
|--------|---------|
| Next Song | Push joystick **RIGHT** |
| Previous Song | Push joystick **LEFT** |
| Volume Up | Push joystick **UP** |
| Volume Down | Push joystick **DOWN** |
| Play/Pause | Press joystick **BUTTON** (SW) |

## Display Information

The OLED shows in real-time:

```
Music Player
─────────────
Song: 5
Volume: 15
[████████░░░░░░░]
>> PLAYING
```

- **Song**: Current track number (001-255)
- **Volume**: Level 0-30 (DFPlayer range)
- **Bar**: Visual volume representation
- **Status**: PLAYING or PAUSED

## Troubleshooting

### DFPlayer not responding
- **Check wiring**: Verify D3 (RX) and D4 (TX) connections
- **1kΩ resistor**: Ensure it's on D4 → DFPlayer RX line (voltage level shifting)
- **Micro-SD card**: Verify it's inserted and files are in `/mp3/` folder with correct naming
- **Power**: DFPlayer needs stable 5V supply; USB power may be insufficient

### OLED not displaying
- **I²C address**: Verify 0x3C address (use I2C scanner if needed)
- **Wiring**: Check A4 (SDA) and A5 (SCL) connections
- **Libraries**: Ensure Adafruit_SSD1306 and Adafruit_GFX are installed

### Joystick not responding
- **Check pins**: Verify A0, A1, D2 connections
- **Analog drift**: Joystick values are thresholded at 200/800; adjust in code if needed
- **Pull-up**: D2 uses INPUT_PULLUP; button should work as-is

### Audio issues
- **Speaker impedance**: Use 8Ω speaker; 4Ω may overload
- **Volume level**: Start at volume 15-20; too high may cause distortion
- **Power supply**: Weak power can cause audio pops/glitches

## Customization

### Change Volume Thresholds
Edit in `loop()`:
```cpp
if (joyY < 200 && lastJoyY >= 200) {  // Adjust 200 to 150/250 for sensitivity
```

### Adjust Display Update Speed
Edit near top of `loop()`:
```cpp
const unsigned long DISPLAY_UPDATE_INTERVAL = 300;  // milliseconds
```

### Change Default Volume
Edit in `setup()`:
```cpp
dfplayer.volume(currentVolume);  // Change currentVolume value (0-30)
```

## Pinout Reference

```
Arduino Uno Pinout (used pins):
A0 - Joystick VRx
A1 - Joystick VRy
A4 - OLED SDA (I²C)
A5 - OLED SCL (I²C)
D2 - Joystick SW
D3 - DFPlayer RX (SoftwareSerial)
D4 - DFPlayer TX (SoftwareSerial)
GND - Common Ground
5V - Power Rail
```

## Power Requirements

- **Arduino**: 500mA (USB)
- **DFPlayer**: 50-200mA (depending on volume)
- **OLED**: 20mA
- **Joystick**: 5mA
- **Speaker**: Up to 200mA at max volume

**Recommended**: External 5V power supply (2A+) for stable operation and max volume.

## Known Limitations

- Maximum 255 MP3 files on micro-SD card
- DFPlayer volume range: 0-30 (limited by hardware)
- No shuffle or repeat modes in this code
- Single song playback (not playlist)

## Future Enhancements

- [ ] Shuffle and repeat modes
- [ ] Brightness control for OLED
- [ ] Song duration display
- [ ] Equalizer presets
- [ ] SD card file browser on OLED

## References

- [DFPlayer Mini Documentation](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299)
- [Arduino Software Serial](https://www.arduino.cc/en/Reference/SoftwareSerial)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

## License

MIT License - Feel free to use and modify for your projects.

## Author
Nivaan                                                                                                                        

Created on 3 AUG 2026

Created for Arduino hobbyists and makers.

---

**Questions or issues?** Check the troubleshooting section or verify your wiring connections first. 
