# Bessie_GPS-Tracker
Bessie is the 1st gen custom-built tracker designed and developed in-house for the sounding rocket built for SACUP 24, Agneya.

Bessie is powered by the ESP32-S3-N4R8 microcontroller, chosen for its familiar development environment and comprehensive functionality. It integrates a GPS module for high positional accuracy and a flash module to store data on board.

The telemetry consists of latitude, longitude, altitude, speed, heading, and satellite fix, which is transmitted over a 915 MHz frequency using a LoRa module to a ground station receiver, which is connected to a teammate's mobile phone.

This tracker aids in rocket recovery post-launch, serving as a redundant mechanism in the event of a main flight computer failure, still ensuring critical data availability.

# Repo Structure
The PCB was designed entirely in EasyEDA. I've included the design files, 3D files, gerber, schematic, test code and media files.

To replicate or explore this project, download the repository files and open them in EasyEDA, ensuring all file paths are correctly linked
    
	1. 3D_Files
	   .mtl & .obj exports -  can be used to visualize the PCB and its components in external 3D viewers or CAD tools.
	
	2. Design_Files
	   schematic & PCB .json - can be directly opened or imported in EasyEDA for editing and modification.
	
	3. Gerber_Files
		 PCB files for fabrication.
	
	4. media 
		 a. images 
            - contains PCB (bare and soldered), assembly & integration with the avionics bay pictures.
		 b. testing_vid
            - contains testing videos.
	
	5. BOM_Bessie.csv
	   List all components used in the project.
	
	6. Bessie_Schematics
	   Quick reference schematic.
	
	7. GPS Tracker code.ino 
	   ESP32 Firmaware code.
    
 # Components used
 - NEO-6M (Global Navigation Satellite System)
 - RFM95W (Lora module @ 915Mhz)
 - HJ-SMA507 (Right-angled THT SMA female connector)
 - W25Q128 (128-Mbit serial flash memory chip)
 - WS2812B (Addressable RGB Led)
 - AMS1117 (LDO Regulator @ 3.3V)
 - XT30 (Overload connector @ 30A)
 - FT232RL (UART module)
 - ESP32-S3-N4R8 (32bit microcontroller)

# Pinouts
#### _Communication Interface_
MOSI | MISO | SCK
:----: | :----: | :----:
IO23 | IO19 | 1018

#### _SPI Peripherals_
RFM95W | GPIO | W25Q128 | GPIO
:------: | :----: | :-------: | :----:
  MOSI | IO23 | MOSI    | IO23
  MISO | IO19 |   MISO  | IO19
   SCK | IO18 |   SCK   | IO18
   NSS |  IO5 |   CS    | IO25
 RESET | IO32 |   -     | -
   DI0 | IO33 |   -     | -

  #### _UART Peripherals: NEO-6M_
  TX | RX
:----: | :----: 
IO17 | IO16
  
 
