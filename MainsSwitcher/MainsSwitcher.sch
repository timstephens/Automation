EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:TJS
LIBS:SeeedOPL-Transistor-2016
LIBS:SeeedOPL-Switch-2016
LIBS:SeeedOPL-Sensor-2016
LIBS:SeeedOPL-Relay-2016
LIBS:SeeedOPL-LED-2016
LIBS:SeeedOPL-Inductor-2016
LIBS:SeeedOPL-IC-2016
LIBS:SeeedOPL-Fuse-2016
LIBS:SeeedOPL-Display-2016
LIBS:SeeedOPL-Diode-2016
LIBS:SeeedOPL-Crystal Oscillator-2016
LIBS:SeeedOPL-Connector-2016
LIBS:SeeedOPL-Capacitor-2016
LIBS:SeeedOPL-Resistor-2016
LIBS:MainsSwitcher-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MOSFET_N Q1
U 1 1 58A8B8DB
P 4400 2800
F 0 "Q1" H 4410 2970 60  0000 R CNN
F 1 "MOSFET_N" H 4410 2650 60  0000 R CNN
F 2 "TJS:SOT-23_Handsoldering" H 4400 2800 60  0001 C CNN
F 3 "" H 4400 2800 60  0000 C CNN
	1    4400 2800
	1    0    0    -1  
$EndComp
$Comp
L ESP-12 U1
U 1 1 58A8C0B8
P 2300 2800
F 0 "U1" H 2300 4200 60  0000 C CNN
F 1 "ESP-12" H 2050 2950 60  0000 C CNN
F 2 "ESP8266:ESP-12" H -500 3650 60  0001 C CNN
F 3 "" H -500 3650 60  0001 C CNN
	1    2300 2800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR01
U 1 1 58A8C1BD
P 1450 1300
F 0 "#PWR01" H 1450 1400 30  0001 C CNN
F 1 "VCC" H 1450 1400 30  0000 C CNN
F 2 "" H 1450 1300 60  0001 C CNN
F 3 "" H 1450 1300 60  0001 C CNN
	1    1450 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1300 1450 2000
Wire Wire Line
	1450 1600 1500 1600
$Comp
L GND #PWR02
U 1 1 58A8C253
P 1400 3950
F 0 "#PWR02" H 1400 3950 30  0001 C CNN
F 1 "GND" H 1400 3880 30  0001 C CNN
F 2 "" H 1400 3950 60  0001 C CNN
F 3 "" H 1400 3950 60  0001 C CNN
	1    1400 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3800 1400 3800
Wire Wire Line
	1400 3800 1400 3950
$Comp
L MCP1700T-3302E/TT Q2
U 1 1 58A8C28F
P 9550 2450
F 0 "Q2" H 9700 2050 60  0000 C CNN
F 1 "MCP1700T-3302E/TT" H 9550 2750 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9550 2450 60  0001 C CNN
F 3 "" H 9550 2450 60  0001 C CNN
	1    9550 2450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 58A8C41D
P 9550 3200
F 0 "#PWR03" H 9550 3300 30  0001 C CNN
F 1 "VCC" H 9550 3300 30  0000 C CNN
F 2 "" H 9550 3200 60  0001 C CNN
F 3 "" H 9550 3200 60  0001 C CNN
	1    9550 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	9550 2950 9550 3200
$Comp
L GND #PWR04
U 1 1 58A8C53C
P 4500 3200
F 0 "#PWR04" H 4500 3200 30  0001 C CNN
F 1 "GND" H 4500 3130 30  0001 C CNN
F 2 "" H 4500 3200 60  0001 C CNN
F 3 "" H 4500 3200 60  0001 C CNN
	1    4500 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 58A8C550
P 8900 2650
F 0 "#PWR05" H 8900 2650 30  0001 C CNN
F 1 "GND" H 8900 2580 30  0001 C CNN
F 2 "" H 8900 2650 60  0001 C CNN
F 3 "" H 8900 2650 60  0001 C CNN
	1    8900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 2450 8900 2450
Wire Wire Line
	8900 2450 8900 2650
Wire Wire Line
	4500 3000 4500 3200
Wire Wire Line
	4200 2800 3100 2800
$Comp
L CONN_3 J1
U 1 1 58A8C722
P 3650 1000
F 0 "J1" V 3600 1000 50  0000 C CNN
F 1 "SERIAL" V 3700 1000 40  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 3650 1000 60  0001 C CNN
F 3 "" H 3650 1000 60  0001 C CNN
	1    3650 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 1800 3750 1800
Wire Wire Line
	3100 1600 3650 1600
$Comp
L GND #PWR06
U 1 1 58A8C88A
P 3550 1450
F 0 "#PWR06" H 3550 1450 30  0001 C CNN
F 1 "GND" H 3550 1380 30  0001 C CNN
F 2 "" H 3550 1450 60  0001 C CNN
F 3 "" H 3550 1450 60  0001 C CNN
	1    3550 1450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 58A8CDFE
P 10350 4250
F 0 "#PWR07" H 10350 4350 30  0001 C CNN
F 1 "VCC" H 10350 4350 30  0000 C CNN
F 2 "" H 10350 4250 60  0001 C CNN
F 3 "" H 10350 4250 60  0001 C CNN
	1    10350 4250
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 58A8CE1D
P 10350 4650
F 0 "R4" V 10430 4650 40  0000 C CNN
F 1 "10k" V 10357 4651 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 10280 4650 30  0001 C CNN
F 3 "" H 10350 4650 30  0000 C CNN
	1    10350 4650
	-1   0    0    1   
$EndComp
$Comp
L +5VD #PWR08
U 1 1 58A8CFAB
P 10300 2250
F 0 "#PWR08" H 10300 2200 20  0001 C CNN
F 1 "+5VD" H 10300 2350 30  0000 C CNN
F 2 "" H 10300 2250 60  0001 C CNN
F 3 "" H 10300 2250 60  0001 C CNN
	1    10300 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 2450 10300 2450
Wire Wire Line
	10300 2450 10300 2250
$Comp
L C C3
U 1 1 58A8D1D2
P 10200 2900
F 0 "C3" H 10200 3000 40  0000 L CNN
F 1 "33u" H 10206 2815 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 10238 2750 30  0001 C CNN
F 3 "" H 10200 2900 60  0000 C CNN
	1    10200 2900
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58A8D20D
P 9250 3100
F 0 "C2" H 9250 3200 40  0000 L CNN
F 1 "33u" H 9256 3015 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 9288 2950 30  0001 C CNN
F 3 "" H 9250 3100 60  0000 C CNN
	1    9250 3100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 58A8D25B
P 9050 3250
F 0 "#PWR09" H 9050 3250 30  0001 C CNN
F 1 "GND" H 9050 3180 30  0001 C CNN
F 2 "" H 9050 3250 60  0001 C CNN
F 3 "" H 9050 3250 60  0001 C CNN
	1    9050 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 58A8D281
P 10200 3250
F 0 "#PWR010" H 10200 3250 30  0001 C CNN
F 1 "GND" H 10200 3180 30  0001 C CNN
F 2 "" H 10200 3250 60  0001 C CNN
F 3 "" H 10200 3250 60  0001 C CNN
	1    10200 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 2700 10200 2450
Connection ~ 10200 2450
Wire Wire Line
	10200 3100 10200 3250
Wire Wire Line
	9450 3100 9550 3100
Connection ~ 9550 3100
Wire Wire Line
	9050 3100 9050 3250
$Comp
L Hitek5v PS1
U 1 1 58A8D8E8
P 9600 1200
F 0 "PS1" H 9650 1450 60  0000 C CNN
F 1 "Hitek5v" H 9600 950 60  0000 C CNN
F 2 "TJS:HLK-P0X" H 9600 1200 60  0001 C CNN
F 3 "" H 9600 1200 60  0001 C CNN
	1    9600 1200
	1    0    0    -1  
$EndComp
$Comp
L +5VD #PWR011
U 1 1 58A8D9E2
P 10350 1000
F 0 "#PWR011" H 10350 950 20  0001 C CNN
F 1 "+5VD" H 10350 1100 30  0000 C CNN
F 2 "" H 10350 1000 60  0001 C CNN
F 3 "" H 10350 1000 60  0001 C CNN
	1    10350 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 58A8DA33
P 10400 1450
F 0 "#PWR012" H 10400 1450 30  0001 C CNN
F 1 "GND" H 10400 1380 30  0001 C CNN
F 2 "" H 10400 1450 60  0001 C CNN
F 3 "" H 10400 1450 60  0001 C CNN
	1    10400 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 1350 10400 1350
Wire Wire Line
	10400 1350 10400 1450
Wire Wire Line
	10200 1050 10350 1050
Wire Wire Line
	10350 1050 10350 1000
$Comp
L CONN_2 J4
U 1 1 58A8DAD6
P 8000 1150
F 0 "J4" V 7950 1150 40  0000 C CNN
F 1 "MAINS_IN" V 8050 1150 40  0000 C CNN
F 2 "TJS:PhoenixContact_PT1,5-2-5.0-V" H 8000 1150 60  0001 C CNN
F 3 "" H 8000 1150 60  0001 C CNN
	1    8000 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	8350 1350 8350 1250
$Comp
L SPST SW2
U 1 1 58A8E35D
P 3850 5350
F 0 "SW2" H 3850 5450 70  0000 C CNN
F 1 "PROG" H 3850 5250 70  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_PUSH_6mm" H 3850 5350 60  0001 C CNN
F 3 "" H 3850 5350 60  0000 C CNN
	1    3850 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 2000 1500 2000
Connection ~ 1450 1600
$Comp
L R R2
U 1 1 58A8E9BD
P 3850 4350
F 0 "R2" V 3930 4350 40  0000 C CNN
F 1 "10k" V 3857 4351 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3780 4350 30  0001 C CNN
F 3 "" H 3850 4350 30  0000 C CNN
	1    3850 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	3850 4600 3850 4900
$Comp
L VCC #PWR013
U 1 1 58A8EA7E
P 3850 3900
F 0 "#PWR013" H 3850 4000 30  0001 C CNN
F 1 "VCC" H 3850 4000 30  0000 C CNN
F 2 "" H 3850 3900 60  0001 C CNN
F 3 "" H 3850 3900 60  0001 C CNN
	1    3850 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3900 3850 4100
$Comp
L GND #PWR014
U 1 1 58A8EAF9
P 3850 6050
F 0 "#PWR014" H 3850 6050 30  0001 C CNN
F 1 "GND" H 3850 5980 30  0001 C CNN
F 2 "" H 3850 6050 60  0001 C CNN
F 3 "" H 3850 6050 60  0001 C CNN
	1    3850 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5850 3850 6050
Wire Wire Line
	3100 3600 3500 3600
Wire Wire Line
	3500 3600 3500 4900
Wire Wire Line
	3500 4900 3850 4900
Connection ~ 3850 4850
$Comp
L Relay K1
U 1 1 58A8F8C7
P 5850 2400
F 0 "K1" H 5850 2750 60  0000 C CNN
F 1 "Relay" H 5900 2050 60  0000 C CNN
F 2 "TJS:COTO_SIP_ReedRelay-9007-05-00" H 5850 2400 60  0001 C CNN
F 3 "" H 5850 2400 60  0001 C CNN
	1    5850 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2500 5350 2500
Wire Wire Line
	4500 2500 4500 2600
Wire Wire Line
	5150 2000 5150 2250
Wire Wire Line
	5150 2250 5350 2250
$Comp
L CONN_2 J3
U 1 1 58A8FD35
P 7100 2500
F 0 "J3" V 7050 2500 40  0000 C CNN
F 1 "SWITCHING" V 7150 2500 40  0000 C CNN
F 2 "TJS:PhoenixContact_PT1,5-2-5.0-V" H 7100 2500 60  0001 C CNN
F 3 "" H 7100 2500 60  0001 C CNN
	1    7100 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 2400 6750 2400
Wire Wire Line
	6500 2550 6550 2550
Wire Wire Line
	6550 2550 6550 2600
Wire Wire Line
	6550 2600 6750 2600
Wire Wire Line
	9000 4900 10350 4900
$Comp
L CONN_3 J2
U 1 1 58AB6630
P 4600 1050
F 0 "J2" V 4550 1050 50  0000 C CNN
F 1 "LED_STRIP" V 4650 1050 40  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 4600 1050 60  0001 C CNN
F 3 "" H 4600 1050 60  0001 C CNN
	1    4600 1050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3750 1800 3750 1350
Wire Wire Line
	3650 1600 3650 1350
Wire Wire Line
	3550 1350 3550 1450
Wire Wire Line
	3100 2000 4600 2000
Wire Wire Line
	4600 2000 4600 1400
$Comp
L +5VD #PWR015
U 1 1 58AB6C00
P 5000 1100
F 0 "#PWR015" H 5000 1050 20  0001 C CNN
F 1 "+5VD" H 5000 1200 30  0000 C CNN
F 2 "" H 5000 1100 60  0001 C CNN
F 3 "" H 5000 1100 60  0001 C CNN
	1    5000 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1400 4700 1500
Wire Wire Line
	4700 1500 5000 1500
Wire Wire Line
	5000 1500 5000 1100
$Comp
L GND #PWR016
U 1 1 58AB6E05
P 4500 1500
F 0 "#PWR016" H 4500 1500 30  0001 C CNN
F 1 "GND" H 4500 1430 30  0001 C CNN
F 2 "" H 4500 1500 60  0001 C CNN
F 3 "" H 4500 1500 60  0001 C CNN
	1    4500 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1400 4500 1500
$Comp
L C C1
U 1 1 58AB72CE
P 5500 1400
F 0 "C1" H 5500 1500 40  0000 L CNN
F 1 "33u" H 5506 1315 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5538 1250 30  0001 C CNN
F 3 "" H 5500 1400 60  0000 C CNN
	1    5500 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 58AB7320
P 5500 1700
F 0 "#PWR017" H 5500 1700 30  0001 C CNN
F 1 "GND" H 5500 1630 30  0001 C CNN
F 2 "" H 5500 1700 60  0001 C CNN
F 3 "" H 5500 1700 60  0001 C CNN
	1    5500 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1600 5500 1700
Wire Wire Line
	5500 1200 5000 1200
Connection ~ 5000 1200
$Comp
L SPST SW1
U 1 1 58AB7F40
P 1000 3000
F 0 "SW1" H 1000 3100 70  0000 C CNN
F 1 "RESET" H 1000 2900 70  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_PUSH_6mm" H 1000 3000 60  0001 C CNN
F 3 "" H 1000 3000 60  0000 C CNN
	1    1000 3000
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 58AB7F46
P 1000 2000
F 0 "R1" V 1080 2000 40  0000 C CNN
F 1 "10k" V 1007 2001 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 930 2000 30  0001 C CNN
F 3 "" H 1000 2000 30  0000 C CNN
	1    1000 2000
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR018
U 1 1 58AB7F4D
P 1000 1550
F 0 "#PWR018" H 1000 1650 30  0001 C CNN
F 1 "VCC" H 1000 1650 30  0000 C CNN
F 2 "" H 1000 1550 60  0001 C CNN
F 3 "" H 1000 1550 60  0001 C CNN
	1    1000 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1550 1000 1750
$Comp
L GND #PWR019
U 1 1 58AB7F54
P 1000 3700
F 0 "#PWR019" H 1000 3700 30  0001 C CNN
F 1 "GND" H 1000 3630 30  0001 C CNN
F 2 "" H 1000 3700 60  0001 C CNN
F 3 "" H 1000 3700 60  0001 C CNN
	1    1000 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 3500 1000 3700
Wire Wire Line
	1000 2250 1000 2500
Wire Wire Line
	1000 2300 1500 2300
$Comp
L DIODE D1
U 1 1 58AB9A3D
P 4850 2850
F 0 "D1" H 4850 2950 40  0000 C CNN
F 1 "1N4001" H 4850 2750 40  0000 C CNN
F 2 "Diodes_SMD:D_SMA-SMB_Universal_Handsoldering" H 4850 2850 60  0001 C CNN
F 3 "" H 4850 2850 60  0000 C CNN
	1    4850 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 2650 4850 2500
Connection ~ 4850 2500
$Comp
L GND #PWR020
U 1 1 58AB9C70
P 4850 3150
F 0 "#PWR020" H 4850 3150 30  0001 C CNN
F 1 "GND" H 4850 3080 30  0001 C CNN
F 2 "" H 4850 3150 60  0001 C CNN
F 3 "" H 4850 3150 60  0001 C CNN
	1    4850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3050 4850 3150
Wire Wire Line
	10350 4400 10350 4250
$Comp
L R R3
U 1 1 58ABC6B1
P 4700 4150
F 0 "R3" V 4780 4150 40  0000 C CNN
F 1 "10k" V 4707 4151 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4630 4150 30  0001 C CNN
F 3 "" H 4700 4150 30  0000 C CNN
	1    4700 4150
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR021
U 1 1 58ABC6B8
P 4700 3700
F 0 "#PWR021" H 4700 3800 30  0001 C CNN
F 1 "VCC" H 4700 3800 30  0000 C CNN
F 2 "" H 4700 3700 60  0001 C CNN
F 3 "" H 4700 3700 60  0001 C CNN
	1    4700 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3700 4700 3900
Wire Wire Line
	3100 3400 3850 3400
Wire Wire Line
	3850 3400 3850 3750
Wire Wire Line
	3850 3750 4450 3750
Wire Wire Line
	4450 3750 4450 4550
Wire Wire Line
	4450 4550 4700 4550
Wire Wire Line
	4700 4550 4700 4400
$Comp
L CONN_3 J5
U 1 1 58AE05D4
P 9050 5450
F 0 "J5" V 9000 5450 50  0000 C CNN
F 1 "TEMP_SEN1" V 9100 5450 40  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 9050 5450 60  0001 C CNN
F 3 "" H 9050 5450 60  0001 C CNN
	1    9050 5450
	0    1    1    0   
$EndComp
$Comp
L CONN_3 J6
U 1 1 58AE0681
P 9900 5450
F 0 "J6" V 9850 5450 50  0000 C CNN
F 1 "TEMP_SEN2" V 9950 5450 40  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 9900 5450 60  0001 C CNN
F 3 "" H 9900 5450 60  0001 C CNN
	1    9900 5450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR022
U 1 1 58AE0F81
P 9400 5500
F 0 "#PWR022" H 9400 5500 30  0001 C CNN
F 1 "GND" H 9400 5430 30  0001 C CNN
F 2 "" H 9400 5500 60  0001 C CNN
F 3 "" H 9400 5500 60  0001 C CNN
	1    9400 5500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 58AE0FCB
P 10250 5500
F 0 "#PWR023" H 10250 5500 30  0001 C CNN
F 1 "GND" H 10250 5430 30  0001 C CNN
F 2 "" H 10250 5500 60  0001 C CNN
F 3 "" H 10250 5500 60  0001 C CNN
	1    10250 5500
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR024
U 1 1 58AE1015
P 8450 5050
F 0 "#PWR024" H 8450 5150 30  0001 C CNN
F 1 "VCC" H 8450 5150 30  0000 C CNN
F 2 "" H 8450 5050 60  0001 C CNN
F 3 "" H 8450 5050 60  0001 C CNN
	1    8450 5050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR025
U 1 1 58AE105F
P 9600 5100
F 0 "#PWR025" H 9600 5200 30  0001 C CNN
F 1 "VCC" H 9600 5200 30  0000 C CNN
F 2 "" H 9600 5100 60  0001 C CNN
F 3 "" H 9600 5100 60  0001 C CNN
	1    9600 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5100 9800 5100
Wire Wire Line
	8950 5100 8450 5100
Wire Wire Line
	9150 5100 9400 5100
Wire Wire Line
	9400 5100 9400 5500
Wire Wire Line
	10000 5100 10250 5100
Wire Wire Line
	10250 5100 10250 5500
Wire Wire Line
	9900 5100 9900 4900
Connection ~ 9900 4900
Wire Wire Line
	9050 5100 9050 4900
Connection ~ 9050 4900
$Comp
L CONN_7 P1
U 1 1 58AE1CE6
P 6650 1100
F 0 "P1" V 6620 1100 60  0000 C CNN
F 1 "GPIO" V 6720 1100 60  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-07_07x2.54mm_Straight" H 6650 1100 60  0001 C CNN
F 3 "" H 6650 1100 60  0001 C CNN
	1    6650 1100
	-1   0    0    1   
$EndComp
Text Label 3100 2200 0    60   ~ 0
GPIO15
Text Label 3100 2400 0    60   ~ 0
GPIO14
Text Label 3100 2600 0    60   ~ 0
GPIO13
Text Label 3100 3000 0    60   ~ 0
GPIO5
Text Label 3100 3800 0    60   ~ 0
ADC
$Comp
L GND #PWR026
U 1 1 58AE29AA
P 7150 1450
F 0 "#PWR026" H 7150 1450 30  0001 C CNN
F 1 "GND" H 7150 1380 30  0001 C CNN
F 2 "" H 7150 1450 60  0001 C CNN
F 3 "" H 7150 1450 60  0001 C CNN
	1    7150 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1400 7150 1400
Wire Wire Line
	7150 1400 7150 1450
Text Label 7000 1300 0    60   ~ 0
ADC
Text Label 7000 1200 0    60   ~ 0
GPIO5
Text Label 7000 1100 0    60   ~ 0
GPIO13
Text Label 7000 1000 0    60   ~ 0
GPIO14
Text Label 7000 900  0    60   ~ 0
GPIO15
Wire Wire Line
	7150 800  7000 800 
$Comp
L VCC #PWR027
U 1 1 58AE32C5
P 7150 700
F 0 "#PWR027" H 7150 800 30  0001 C CNN
F 1 "VCC" H 7150 800 30  0000 C CNN
F 2 "" H 7150 700 60  0001 C CNN
F 3 "" H 7150 700 60  0001 C CNN
	1    7150 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 700  7150 800 
Wire Wire Line
	8450 5100 8450 5050
Text GLabel 9000 4550 0    60   Input ~ 0
D~Q
Wire Wire Line
	9000 4550 9000 4900
Text GLabel 3300 3200 2    60   Input ~ 0
D~Q
Wire Wire Line
	3300 3200 3100 3200
Wire Wire Line
	1000 2300 1000 2350
Connection ~ 1000 2350
$Comp
L VR VR1
U 1 1 58AE8155
P 8900 1100
F 0 "VR1" V 8960 1054 40  0000 C TNN
F 1 "VR" V 8900 1100 40  0000 C CNN
F 2 "TJS:MOV-EPCOS-B72214S0421K101" H 8900 1100 60  0001 C CNN
F 3 "" H 8900 1100 60  0000 C CNN
	1    8900 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1050 8700 1050
Wire Wire Line
	8700 1050 8700 850 
Wire Wire Line
	8700 850  9100 850 
Wire Wire Line
	9100 850  9100 1050
Connection ~ 8900 850 
Connection ~ 8900 1350
$Comp
L +5VD #PWR028
U 1 1 58B2024B
P 5150 2000
F 0 "#PWR028" H 5150 1950 20  0001 C CNN
F 1 "+5VD" H 5150 2100 30  0000 C CNN
F 2 "" H 5150 2000 60  0001 C CNN
F 3 "" H 5150 2000 60  0001 C CNN
	1    5150 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2500 5350 2550
$Comp
L LED D2
U 1 1 58B348D4
P 6600 5100
F 0 "D2" H 6600 5200 50  0000 C CNN
F 1 "LED" H 6600 5000 50  0000 C CNN
F 2 "Diodes_SMD:D_1206" H 6600 5100 60  0000 C CNN
F 3 "" H 6600 5100 60  0000 C CNN
F 4 "SC08092" H 6600 5100 60  0001 C CNN "CPC Part Number"
	1    6600 5100
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 58B34B20
P 6600 4500
F 0 "R5" V 6680 4500 40  0000 C CNN
F 1 "100R" V 6607 4501 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 6530 4500 30  0001 C CNN
F 3 "" H 6600 4500 30  0000 C CNN
	1    6600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4750 6600 4900
$Comp
L GND #PWR029
U 1 1 58B34ED2
P 6600 5450
F 0 "#PWR029" H 6600 5450 30  0001 C CNN
F 1 "GND" H 6600 5380 30  0001 C CNN
F 2 "" H 6600 5450 60  0001 C CNN
F 3 "" H 6600 5450 60  0001 C CNN
	1    6600 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4250 6250 4250
Text Label 6250 4250 0    60   ~ 0
GPIO5
Wire Wire Line
	6600 5300 6600 5450
$Comp
L FUSE F1
U 1 1 58B4A8B2
P 8600 1350
F 0 "F1" H 8700 1400 40  0000 C CNN
F 1 "FUSE" H 8500 1300 40  0000 C CNN
F 2 "TJS:Schurter_Fuseholder(20x5mm)0031.8211" H 8600 1350 60  0001 C CNN
F 3 "" H 8600 1350 60  0000 C CNN
	1    8600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1350 9100 1350
$EndSCHEMATC
