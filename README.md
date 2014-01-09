BMP180_Breakout
===============

Breakout board and example code for the Bosch BMP180 barometric pressure sensor.

![BMP180 Breakout](https://dlnmh9ip6v2uc.cloudfront.net/images/products/1/1/8/2/4/11824-01.jpg)

Product page: [www.sparkfun.com/products/11824](https://www.sparkfun.com/products/11824)

Datasheet: [github.com/sparkfun/BMP180_Breakout/blob/master/BMP180 Datasheet V2.5.pdf](https://github.com/sparkfun/BMP180_Breakout/blob/master/BMP180%20Datasheet%20V2.5.pdf?raw=true)

Github repository: [github.com/sparkfun/BMP180_Breakout](https://github.com/sparkfun/BMP180_Breakout)

###Arduino library installation:

This archive contains an Arduino library and example sketch showing how to use this sensor. The library must be installed onto your computer in order for the example code to work correctly.

If you haven't, install the free Arduino IDE (Integrated Development Environment), available at [www.arduino.cc](http://www.arduino.cc). This code was tested using Arduino version 1.0.5.

TL;DR: The one-step procedure to install all of the required files is to open the "Arduino" folder contained in this archive, and drag the contents into your personal Arduino sketch folder (this is normally located in your personal documents folder). This will create a "libraries" folder containing the required library and example sketch.

If you get a warning that there is already a "libraries" folder, go ahead and add the included files to it. If there is an older version of this library in the folder, please overwrite it with the version in this archive. If it is running, restart the Arduino IDE to get it to recognize the new library.

###Running the example sketch:

<ol start=1>
<li>Connect the BMP180 breakout board to your Arduino. You can solder wires, use jumper wires and headers, etc.
<p>
"-" (GND) to GND
<br>
"+" (VDD) to 3.3V
<p>
(WARNING: do not connect "+" to 5V or the sensor will be damaged!)
<p>
You will also need to connect the I2C pins (SCL and SDA) to your Arduino.
These pins are different on different Arduino models:
<p>
<table>
<tr>
<td>Any Arduino</td>
<td>SDA&nbsp;</td>
<td>SCL</td>
</tr>
<tr>
<td>Uno, Redboard, Pro/Mini&nbsp;</td>
<td>A4</td>
<td>A5</td>
</tr>
<tr>
<td>Mega2560, Due</td>
<td>20</td>
<td>21</td>
</tr>
<tr>
<td>Leonardo, Pro/Micro</td>
<td>2</td>
<td>3</td>
</tr>
</table> 
<p>
Leave the IO (VDDIO) pin unconnected. This pin is for connecting
the BMP180 to systems with lower logic levels such as 1.8V.
</li>
<li>
Connect your Arduino to your computer.
<p>
</li>
<li>
Start the Arduino IDE. Select the proper COM port and board type.
<p>
</li>
<li>
In the Arduino IDE, go to the File menu, and down to Examples/SFE_BMP180/SFE_BMP180_example. If you do not see this item, you likely did not install the library properly. See above.
<p>
</li>
<li>
Upload the sketch to your Arduino.
<p>
</li>
<li>
Open the Serial Monitor window (magnifying glass icon un upper right of IDE).
<p>
</li>
<li>
Set the Serial Monitor to 9600 baud (menu in bottom right).
<p>
</li>
</ol>
You should now be seeing pressure measurements in the Serial Monitor window. If you see errors, you may not have connected the BMP180 Breakout Board to your Arduino properly. See step 1 above.

If you have questions, don't hesistate to contact us at techsupport@sparkfun.com.

Have fun!
Your friends at SparkFun.

License Informatiom
-------------------

 * For hardware, we use the [Creative Commons Share-Alike 3.0 License](http://creativecommons.org/licenses/by-sa/3.0).

 * For software, we use the "Beerware" license: you can do ANYTHING you want with this software. If you like it, and we meet someday, you can, but are under no obligation to, buy me a (root) beer in return.

Authors
-------

 * Mike Grusin, SparkFun Electronics

Acknowledgements
----------------

 * The SFE_BMP180 library uses [floating-point equations](http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf) for the BMP085 developed by the [Weather Station Data Logger project](http://wmrx00.sourceforge.net/).

Changelog
---------

+ hardware V10 (release)

	* Minor updates
	* Library fork from SFE_BMP085

+ hardware V02 (proto)

	* Rearranged header: put VDD/GND/SDA/SCL in "standard" order
	* I2C pullups to VDDIO

+ hardware V01 (review)