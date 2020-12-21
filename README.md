# Project-Haar-Primal
A minimal temp/pressure/RH sensor designed for environmental monitoring. Built off the Haar system, developed by Bobby Schulz at Northern Widget 

# Project-Haar-Primal
A minimal temp/pressure/RH sensor designed for environmental monitoring. Built off the Haar system, developed by Bobby Schulz at Northern Widget 

# Repo Roadmap
#### [Documents](Documents/) 

General document and image storage for repo and README

#### [Hardware](Hardware/)

Current board files (Eagle), Bill of Materials (BoM), and other design documents

#### [Production](Production/)

Contains the various Gerber and pick and place files required to have the Printed Circuit Boards (PCBs) manufactured or populated 

<!-- #### [Software](Software/)

The software associated with the piece of hardware, this is usually diagnostic software used for verifying or investigating the hardware -->

<!-- #### [Testing](Testing/)

Scripts and results from the testing process and development process. Contains more detailed information about documented issues among other testing. 
 -->


## Overview
* **Type:** Sensor
* **Interfaces:** I<sup>2</sup>C
* **Release Version:** v0.0 - 2020/03/19

![Haar v0.0 - Top](Documents/Images/Haar_0v0_Top_Cropped.jpg)

<!-- ![Haar v0.0 - Bottom](Documents/Images/Haar_0v0_Bottom_Cropped.jpg) -->

## Features
### On-Board
* Selectable Pullups
* Reverse Polarity Protection  

### Interface
* I<sup>2</sup>C


## Specifications
* **Voltage - Supply:** 3.3V
* **Voltage - Logic:** 3.3V
* **Input Current (Avg):**


## Jumper Settings 

**Configuration Jumpers**
| Jumper | Purpose | Open | Closed | Default | 
| ------ | ------- | ---------- | ---------- | ----- | 
| `JP1` | Onboard I<sup>2</sup>C pullups | Pullups Disabled | Pullups Enabled | Closed <sup>1</sup> |

<sup>1</sup> - See Errata!   


## Known Issues/Errata

#### Solder Jumper Stencil

**Issue:** Depending on the thickness of the solder stencil used for populating the board, the solder jumpers may not bridge when desired. This is due to lack of stencil thickness specification and pad geometry.

**Workaround:** Make a note on the board assembly (if working with a board house) as to which jumpers should be connected (see jumper tables). Otherwise, if assembling manually, check the jumpers are connected, and bridge them using solder wire and a soldering iron if they have failed to jump where desired. 

#### Pullup Jumper

**Issue:** Due to the resistor configuration with the solder jumper, if the jumper is left open, the resistors form a voltage divider which pulls down the I<sup>2</sup>C rails and causes a variety of bus failures.

**Workaround:** Leave jumper closed on device, this will pull the lines up to the 3.3V rail and prevent the issue 

**Expectation:** Expect a change in the jumper configuration in `v0.1` to fix this issue by using a shunted SPDT jumper or jumper resistors for configuration  