EESchema Schematic File Version 4
EELAYER 30 0
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
L STM32G030J6M6:STM32G030J6M6 IC2
U 1 1 62EE6DA3
P 2050 3750
F 0 "IC2" H 3600 4015 50  0000 C CNN
F 1 "STM32G030J6M6" H 3600 3924 50  0000 C CNN
F 2 "SOIC127P600X175-8N" H 5000 3850 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/STM32G030J6M6.pdf" H 5000 3750 50  0001 L CNN
F 4 "MCU 32-bit ARM Cortex M0+ RISC 32KB Flash 2.5V/3.3V 8-Pin SO N Tube" H 5000 3650 50  0001 L CNN "Description"
F 5 "1.75" H 5000 3550 50  0001 L CNN "Height"
F 6 "STMicroelectronics" H 5000 3450 50  0001 L CNN "Manufacturer_Name"
F 7 "STM32G030J6M6" H 5000 3350 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "511-STM32G030J6M6" H 5000 3250 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/STMicroelectronics/STM32G030J6M6?qs=uwxL4vQweFMe%2Fiu4dY6izA%3D%3D" H 5000 3150 50  0001 L CNN "Mouser Price/Stock"
F 10 "STM32G030J6M6" H 5000 3050 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/stm32g030j6m6/stmicroelectronics?region=nac" H 5000 2950 50  0001 L CNN "Arrow Price/Stock"
	1    2050 3750
	1    0    0    -1  
$EndComp
Text GLabel 2050 3850 0    50   Input ~ 0
VCC_3V3
Text GLabel 2050 3950 0    50   Input ~ 0
GND
$Comp
L MAX485CPA+:MAX485CPA+ IC1
U 1 1 62EE8E3C
P 1650 1000
F 0 "IC1" H 2150 1265 50  0000 C CNN
F 1 "MAX485CPA+" H 2150 1174 50  0000 C CNN
F 2 "DIP794W56P254L938H457Q8N" H 2500 1100 50  0001 L CNN
F 3 "https://pdfserv.maximintegrated.com/en/ds/MAX1487-MAX491.pdf" H 2500 1000 50  0001 L CNN
F 4 "RS-422/RS-485 Interface IC Low-Power, Slew-Rate-Limited RS-485/RS-422 Transceivers" H 2500 900 50  0001 L CNN "Description"
F 5 "4.572" H 2500 800 50  0001 L CNN "Height"
F 6 "Maxim Integrated" H 2500 700 50  0001 L CNN "Manufacturer_Name"
F 7 "MAX485CPA+" H 2500 600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "700-MAX485CPA" H 2500 500 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Maxim-Integrated/MAX485CPA%2b?qs=1THa7WoU59FcxPgOoQv70A%3D%3D" H 2500 400 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 2500 300 50  0001 L CNN "Arrow Part Number"
F 11 "" H 2500 200 50  0001 L CNN "Arrow Price/Stock"
	1    1650 1000
	1    0    0    -1  
$EndComp
$Comp
L LD1117V33:LD1117V33 IC3
U 1 1 62EEB0CC
P 5100 1650
F 0 "IC3" H 6028 1596 50  0000 L CNN
F 1 "LD1117V33" H 6028 1505 50  0000 L CNN
F 2 "TO255P460X1020X2008-3P" H 6050 1750 50  0001 L CNN
F 3 "http://www.st.com/web/en/resource/technical/document/datasheet/CD00000544.pdf" H 6050 1650 50  0001 L CNN
F 4 "800mA,3.3V,LDO Voltage Reg.,LD1117V33 STMicroelectronics LD1117V33, LDO Voltage Regulator, 1.3A, 3.3 V +/-1%, 3-Pin TO-220" H 6050 1550 50  0001 L CNN "Description"
F 5 "4.6" H 6050 1450 50  0001 L CNN "Height"
F 6 "STMicroelectronics" H 6050 1350 50  0001 L CNN "Manufacturer_Name"
F 7 "LD1117V33" H 6050 1250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "511-LD1117V33" H 6050 1150 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/STMicroelectronics/LD1117V33?qs=arR7071FstdSYX%2FAthFGRA%3D%3D" H 6050 1050 50  0001 L CNN "Mouser Price/Stock"
F 10 "LD1117V33" H 6050 950 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/ld1117v33/stmicroelectronics?region=europe" H 6050 850 50  0001 L CNN "Arrow Price/Stock"
	1    5100 1650
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 62EEBEAF
P 3850 1200
F 0 "J3" H 3822 1082 50  0000 R CNN
F 1 "Conn_01x04_Male" H 3822 1173 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 3850 1200 50  0001 C CNN
F 3 "~" H 3850 1200 50  0001 C CNN
	1    3850 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 62EED523
P 1400 3900
F 0 "R1" H 1470 3946 50  0000 L CNN
F 1 "10k" H 1470 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1330 3900 50  0001 C CNN
F 3 "~" H 1400 3900 50  0001 C CNN
	1    1400 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 62EED8D1
P 5050 1850
F 0 "C3" V 5302 1850 50  0000 C CNN
F 1 "100n" V 5211 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5088 1700 50  0001 C CNN
F 3 "~" H 5050 1850 50  0001 C CNN
	1    5050 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C4
U 1 1 62EEDEF8
P 5050 2100
F 0 "C4" V 4795 2100 50  0000 C CNN
F 1 "CP" V 4886 2100 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.4" H 5088 1950 50  0001 C CNN
F 3 "~" H 5050 2100 50  0001 C CNN
	1    5050 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	2050 4050 1400 4050
Text GLabel 1400 3750 1    50   Input ~ 0
VCC_3V3
$Comp
L Device:R R4
U 1 1 62EEF612
P 5150 3450
F 0 "R4" H 5220 3496 50  0000 L CNN
F 1 "10k" H 5220 3405 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5080 3450 50  0001 C CNN
F 3 "~" H 5150 3450 50  0001 C CNN
	1    5150 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3750 5150 3600
Text GLabel 5150 3300 1    50   Input ~ 0
GND
Wire Wire Line
	1650 1200 1650 1100
Text GLabel 1650 1000 0    50   Input ~ 0
MAX485_TX
Text GLabel 1650 1300 0    50   Input ~ 0
MAX485_RX
Text GLabel 1650 1150 0    50   Input ~ 0
MAX485_SELEKTOR
Text GLabel 2650 1000 2    50   Input ~ 0
VCC_5V
Text GLabel 2650 1300 2    50   Input ~ 0
GND
Text GLabel 3650 1000 1    50   Input ~ 0
VCC_5V
Text GLabel 3650 1300 3    50   Input ~ 0
GND
Wire Wire Line
	3050 1100 2650 1100
$Comp
L Device:C C6
U 1 1 62EF5ED2
P 6700 1450
F 0 "C6" H 6815 1496 50  0000 L CNN
F 1 "100n" H 6815 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6738 1300 50  0001 C CNN
F 3 "~" H 6700 1450 50  0001 C CNN
	1    6700 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 62EF6063
P 5400 2000
F 0 "C5" V 5652 2000 50  0000 C CNN
F 1 "100n" V 5561 2000 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5438 1850 50  0001 C CNN
F 3 "~" H 5400 2000 50  0001 C CNN
	1    5400 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C7
U 1 1 62EF61F1
P 7050 1450
F 0 "C7" H 7165 1496 50  0000 L CNN
F 1 "100n" H 7165 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 7088 1300 50  0001 C CNN
F 3 "~" H 7050 1450 50  0001 C CNN
	1    7050 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 62EF6370
P 7350 1450
F 0 "C8" H 7465 1496 50  0000 L CNN
F 1 "100n" H 7465 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 7388 1300 50  0001 C CNN
F 3 "~" H 7350 1450 50  0001 C CNN
	1    7350 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1650 4900 1650
Wire Wire Line
	4900 1650 4900 1850
Wire Wire Line
	5200 1650 5200 1850
Wire Wire Line
	4900 1850 4900 2000
Wire Wire Line
	4900 2000 5250 2000
Connection ~ 4900 1850
Wire Wire Line
	5300 1650 5550 1650
Wire Wire Line
	5550 1650 5550 2000
$Comp
L Device:CP C2
U 1 1 62EFA111
P 4100 1150
F 0 "C2" H 4218 1196 50  0000 L CNN
F 1 "CP" H 4218 1105 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.4" H 4138 1000 50  0001 C CNN
F 3 "~" H 4100 1150 50  0001 C CNN
	1    4100 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1000 4100 1000
Wire Wire Line
	3650 1300 4100 1300
Connection ~ 4900 2000
Wire Wire Line
	6700 1300 7050 1300
Wire Wire Line
	7050 1300 7350 1300
Connection ~ 7050 1300
Wire Wire Line
	6700 1600 7050 1600
Wire Wire Line
	7050 1600 7350 1600
Connection ~ 7050 1600
Text GLabel 7050 1600 3    50   Input ~ 0
GND
Text GLabel 7050 1300 1    50   Input ~ 0
VCC_3V3
Text GLabel 4900 2000 0    50   Input ~ 0
GND
Wire Wire Line
	5200 1850 5200 2100
Connection ~ 5200 1850
Wire Wire Line
	4900 2100 4900 2000
Text GLabel 5550 2000 3    50   Input ~ 0
VCC_5V
Text GLabel 5200 2100 3    50   Input ~ 0
VCC_3V3
Text GLabel 2050 3750 0    50   Input ~ 0
MAX485_TX
Text GLabel 5350 3750 2    50   Input ~ 0
MAX485_RX
Text GLabel 5350 3850 2    50   Input ~ 0
MAX485_SELEKTOR
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 62F0369A
P 2450 2100
F 0 "J1" H 2558 2481 50  0000 C CNN
F 1 "Conn_01x05_Male" H 2558 2390 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 2450 2100 50  0001 C CNN
F 3 "~" H 2450 2100 50  0001 C CNN
	1    2450 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 62F03F5E
P 3300 2050
F 0 "J2" H 3408 2431 50  0000 C CNN
F 1 "Conn_01x05_Male" H 3408 2340 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 3300 2050 50  0001 C CNN
F 3 "~" H 3300 2050 50  0001 C CNN
	1    3300 2050
	1    0    0    1   
$EndComp
Text GLabel 3650 1850 2    50   Input ~ 0
VCC_3V3
Text GLabel 3650 1950 2    50   Input ~ 0
GND
Text GLabel 3650 2050 2    50   Input ~ 0
SCL
Text GLabel 3650 2150 2    50   Input ~ 0
SDA
Text GLabel 3950 2250 2    50   Input ~ 0
GND
$Comp
L Device:C C1
U 1 1 62F05571
P 3550 1800
F 0 "C1" H 3665 1846 50  0000 L CNN
F 1 "100n" H 3665 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3588 1650 50  0001 C CNN
F 3 "~" H 3550 1800 50  0001 C CNN
	1    3550 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1950 3550 1950
Wire Wire Line
	3550 1950 3650 1950
Connection ~ 3550 1950
Wire Wire Line
	3500 1850 3500 1650
Wire Wire Line
	3500 1650 3550 1650
Wire Wire Line
	3550 1650 3650 1650
Wire Wire Line
	3650 1650 3650 1850
Connection ~ 3550 1650
Wire Wire Line
	3500 2050 3650 2050
Wire Wire Line
	3500 2150 3650 2150
Wire Wire Line
	3500 2250 3650 2250
$Comp
L Device:R R3
U 1 1 62F081DB
P 3800 2250
F 0 "R3" V 3593 2250 50  0000 C CNN
F 1 "360" V 3684 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 3730 2250 50  0001 C CNN
F 3 "~" H 3800 2250 50  0001 C CNN
	1    3800 2250
	0    1    1    0   
$EndComp
Text GLabel 2650 1900 2    50   Input ~ 0
SWCLK
Text GLabel 2650 2000 2    50   Input ~ 0
SWDIO
Text GLabel 2650 2100 2    50   Input ~ 0
VCC_5V
Text GLabel 2650 2200 2    50   Input ~ 0
GND
Text GLabel 2650 2300 2    50   Input ~ 0
RST
Text GLabel 1400 4050 3    50   Input ~ 0
RST
Wire Wire Line
	5150 3750 5350 3750
Connection ~ 5150 3750
Text GLabel 5200 3750 1    50   Input ~ 0
SWCLK
Text GLabel 5300 3850 1    50   Input ~ 0
SWDIO
Wire Wire Line
	5150 3850 5350 3850
Text GLabel 5150 4050 2    50   Input ~ 0
SCL
Text GLabel 5150 3950 2    50   Input ~ 0
SDA
$Comp
L Device:R R2
U 1 1 62F0FA0E
P 3150 1050
F 0 "R2" H 3220 1096 50  0000 L CNN
F 1 "120" H 3220 1005 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 3080 1050 50  0001 C CNN
F 3 "~" H 3150 1050 50  0001 C CNN
	1    3150 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 900  3050 900 
Wire Wire Line
	3050 900  3050 1100
Wire Wire Line
	2650 1200 3150 1200
Wire Wire Line
	3650 1100 3450 1100
Wire Wire Line
	3450 1100 3450 900 
Wire Wire Line
	3450 900  3150 900 
Connection ~ 3150 900 
Wire Wire Line
	3650 1200 3150 1200
Connection ~ 3150 1200
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 62F23CF9
P 1650 2850
F 0 "J4" H 1758 3031 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1758 2940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1650 2850 50  0001 C CNN
F 3 "~" H 1650 2850 50  0001 C CNN
	1    1650 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 62F24578
P 2400 2850
F 0 "J5" H 2508 3031 50  0000 C CNN
F 1 "Conn_01x01_Male" H 2508 2940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2400 2850 50  0001 C CNN
F 3 "~" H 2400 2850 50  0001 C CNN
	1    2400 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 62F27DEB
P 5850 2450
F 0 "J6" H 5958 2631 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5958 2540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5850 2450 50  0001 C CNN
F 3 "~" H 5850 2450 50  0001 C CNN
	1    5850 2450
	1    0    0    -1  
$EndComp
Text GLabel 6050 2450 2    50   Input ~ 0
SCL
Text GLabel 6050 2550 2    50   Input ~ 0
SDA
$EndSCHEMATC
