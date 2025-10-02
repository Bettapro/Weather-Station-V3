# Use Solar Panel and 18650 battery
A solar panel and a rechargable battery could be use as power supply, this ease the installation as you don't need to connect the weather station to the grid.   
The weather station doesn't consume much energy (it sleeps most of the time), a 2.5W solar panel is more than enough to power this project.   
One 18650 cell is required to store the energy produced by the solar panel, it acts as reservoir to ensure  to power to the weather station when there's no sun.

## Bill of materials
- 18650 cell
- TP4056 battery charger
- 2.5W solar panel

### Power optimization
18650 produces a voltage between 3.7v to 4.2V, it must be regulated to 3.3v. You can use the 5v pin of the ESP board if available.
Normally ESP dev boards are not power optimized, this boards have LEDS and some additional circuits that are not required when the weather station is working, all this things waste power. This option is the easiest but not the most efficient.

A 3.3V LDO voltage regulator is a good option to minimize the power consumption, the 3.3v produced could be connected the the 3.3V PIN of the ESP board.   
*Note: some LDO requires one or more capacitors on output/input side to ensure a stable voltage*

LDO tested:
- [HT7833](https://pdf1.alldatasheet.com/datasheet-pdf/view/205881/HOLTEK/HT7833.html)

## Wiring

![Alt text](<../images/solar panel.png>)