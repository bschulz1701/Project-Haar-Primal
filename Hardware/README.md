# Hardware Overview - Project Hyena

## Files

<!-- * [Legacy](Legacy/) - File storage for older hardware versions   -->
* Haar_Primal.sch - Eagle Schematic
* Haar_Primal.brd - Eagle Board File
* [Haar_Primal_0v0_DimensionalDrawing.pdf](Haar_Primal_0v0_DimensionalDrawing.png) - Mechanical Drawing
<!-- * [PrimaryLogger_BoM.csv](PrimaryLogger_BoM.csv) - BoM (For reference only, see [Production](../Production) for production ready BoM) -->
<!-- * [PrimaryLogger.pdf](PrimaryLogger_0v2.pdf) - PDF of Schematic  -->

## I2C Addresses 

| Device | Address | 
| ------ | ------- | 
| DPS368 | 0x77 | 
| SHT30 | 0x44 |


<!-- ## Pinout

| Particle Pin | Hyena Pin Name | Control | Function | 
| ------------ | -------------- | ------- | -------- |
| 8 | `3V3_EXT_EN` | Output | Enables the external 3.3v rail (active high, nominally low) | 
| 7 | `WD_HOLD` | Output | Controls the hardware watchdog timer, pulse high to "feed" timer |
| 6 | `GPIO1D` | IO | General digital IO pin for external sensors (J1 Connector) | 
| 5 | `GPIO2D` | IO | General digital IO pin for external sensors (J2 Connector) | 
| 4 | `GPIO3D` | IO | General digital IO pin for external sensors (J3 Connector) | 
| 3 | `RTC_INT` | Input | Interrupt line from RTC, natively high active low (open drain), triggers on falling edge |
| 2 | `SDA_CTRL` | Output | Used to turn internal I2C on or off (active high, I2C_OB on, natively low) |
| 1 | `SCL` | Output | I2C clock line |
| 0 | `SDA` | IO | I2C Data line |
| 9 | `3V3_SD_EN` | Output | Enable line for SD card 3.3v supply (active high, natively low) |
| 10 | `IO_EXP_INT` | Input | Global interrupt from the IO expander (functionality configurable via software) |
| 11 | `MISO` | Input | MasterInSlaveOut, part of SPI bus |
| 12 | `MOSI` | Output | MasterOutSlaveIn, part of SPI bus | 
| 13 | `SCK` | Output | SerialClocK, part of SPI bus | 
| 14 | `SD_CS` | Output | SD chip select line, active low |
| 15/ADC4 | `TIP` | IO | Designed as tipping bucket rain gauge input, connected to J6, pulled high by default |
| 16/ADC3 | `GPIOXA` | IO | Intended as analog input for potentiometric input (J5) |
| 17/ADC2 | `GPIO1A` | IO | General digital/analog IO pin for external sensors (J1 Connector) |
| 18/ADC1 | `GPIO2A` | IO | General digital/analog IO pin for external sensors (J2 Connector) |
| 19/ADC0 | `GPIO3A` | IO | General digital/analog IO pin for external sensors (J3 Connector) |

| IO Expander Pin | Hyena Pin Name | Control | Function |
| --------------- | -------------- | ------- | -------- |
| 0 | `3V3_EXT_FAULT` | Input | Monitor pin for external 3v3 rail, if over current trip, pin is pulled low, natively high |
| 1 | `3V3_SD_FAULT` | Input | Monitor pin for SD card 3v3 rail, if over current trip, pin is pulled low, natively high |
| 2 | `SD_CD` | Input | Card detect pin for SD card, natively high, pulled low to indicate physical presence of SD card | 
| 3 | `I2C_EXT_EN` | Output | Control line for external I2C buffer, natively high (on), can be pulled low to turn off the external I2C bus | 
| 4 | `PAR_INT` | Input | Event interrupt line from TCS3400 light sensor (used for PAR measurement), active low interrupt |

## Hardware Testing:
See Testing sub folder -->