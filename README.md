# maniav2
A small controller for osu!mania. Works on mobile with osu!lazer too!


Items needed:

1 Pro Micro

4 mechanical key switches

4 keycaps

1 WS2812b LED (optional)

4 M3x12 screws

4 M3 Lock nuts, however mines didn't need these

Wires

----------------------------

Tools needed:

Soldering Iron

3d printer & filament

----------------------------

What to 3d print:

A Case, any height

A Cover, choose which one, if you are not using an LED, make the one without the hole in the middle.

A Transparent piece to have light shine through, ONLY if you are using LED

----------------------------

Assembly:

Wire up the Pro Micro like this

ark2000k/maniav2/images/Untitled30_20230319204649.png

The GND wire should go from the left side to the D switch, the F switch, then the LED, the J switch, and lastly the K switch

Each switch should be wired up to 12, 13, 14, and 15. All should be GPIO pins.

The LED has 3 pins. The 5v goes to the RAW pin and the DATA pin goes to any GPIO pin. I used pin 9

Connect the Pro Micro using a Data wire, then upload the sketch.ino into Arduino IDE.

WIP

If you have any questions, ask me on discord at 打打打打打打打打#2871
