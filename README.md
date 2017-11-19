# Arduino Flip Watch (Candy)

This is a Arduino IDE project to run flip clock on a i2c monochrom OLED display with a atmega chip.

# Circuit

I add a Bluefruit UART nRF51 friend in this Branch and a RGB LED.

# features

- Big Clock (set hours+minutes)
- LED Lamp (different colors)
- flipping seconds
- use buttons as bluetooth keyboard (volume keys, cursor keys, media previous/next)

# Usage

## Bluetooth modes

If the Display is on you can use the watch as Bluetooth Keyboard. Button 1 and 2 has 3 modes:

- media prev or next
- volume up or down
- cursor up or down

## Display off

### Button 1

**short press** : Display on

**long press** : Display on + set hours up

### Button 2

**hold** : run through 6 different LED colors + Black. If color is black, display shows the
new bluetooth mode

## Display on

### Button 1

**short press** : *media prev*, *volume up* or *cursor up*

**long press** : set minutes up

### Button 2

**short press** : *media next*, *volume down* or *cursor down*

