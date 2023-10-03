![Build succeeded][build-shield]
![Test passing][test-shield]
[![Issues][issues-shield]][issues-url]
[![Issues][closed-shield]][issues-url]
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![License][license-shield]][license-url]

# EGON
#### Energy Grid Optimization Network
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>

- [Case](#case)
- [Requirements](#requirements)
- [Architecture diagram](#architecture-diagram)
- [Roadmap](#roadmap)
- [Summary and rundown](#summary-and-rundown)
- [Getting started](#getting-started)
- [Pin layout](#pin-layout)
  - [Home](#home)
- [MQTT Topics](#mqtt-topics)
- [Libraries](#libraries)
- [Components](#components)
- [HIPO Diagrams](#hipo-diagrams)
  - [Alarm](#alarm-1)
- [Flowcharts](#flowcharts)
  - [Alarm](#alarm-2)
- [License](#license)
- [Contact](#contact)
</details>

# Case
Case bla bla bla
* Punkt 1
* Punkt 2
* Punkt 3
<p align="right">(<a href="#top">back to top</a>)</p>

# Requirements
- [X] Done
- [X] Done
- [ ] Todo
<p align="right">(<a href="#top">back to top</a>)</p>

# Architecture diagram
![architecture diagram](/Docs/Architecture_Diagram.png)
`/Docs/Architecture_Diagram.png`

# Roadmap
- [X] Done
  - [ ] Sub thingy not done
- [X] Done
- [ ] Not done
- [ ] Not done


#  Summary and rundown
Summary with a sup message<sup>like this</sup> - neat right?
> This is a quote in the summary
<p align="right">(<a href="#top">back to top</a>)</p>


# Getting started
Quick guide with a `code block` 

We also have a code block block thing
```csharp
temperature2 = newDHT.readTemperature();
humidity2 = newDHT.readHumidity();
```

Make sure to read the setup!
<p align="right">(<a href="#top">back to top</a>)</p>

# Pin layout

## Home
| Arduino pin | Component pin | Component name     | Volt                   |
|:------------|:--------------|:-------------------|:-----------------------|
| 5V          | VCC           | HC-SR04 Ultrasound | 5V                     |
| D6          | Trigger       | HC-SR04            |                        |
| D5          | Echo          | HC-SR04            | 3,3v (voltage divider) |
| GND         | GND           | HC-SR04            |                        |
| SDA (D11)   | SDA           | SSD1306 OLED       |                        |
| SCL (D12)   | SCL           | SSD1306            |                        |
| 5V          | VCC           | SSD1306            | 5V                     |
| GND         | GND           | SSD1306            |                        |
| D7          | RST           | RC522 RFID reader  |                        |
| D13         | SDA (SS)      | RC522              |                        |
| SCK (D9)    | SCK           | RC522              |                        |
| MOSI (D8)   | MOSI          | RC522              |                        |
| MISO (D10)  | MISO          | RC522              |                        |
| VCC         | VCC           | RC522              | 3,3V                   |   
| GND         | GND           | RC522              |                        |  
| D14         | SIG           | SG90 Servo         |                        |  
| VCC         | VCC           | SG90               | 3,3V                   |  
| GND         | GND           | SG90               |                        |  
| A3/D18      | 1             | 4x4 Matrix keypad  |                        |  
| A4/D19      | 2             | Keypad             |                        |  
| A5/D20      | 3             | Keypad             |                        |  
| A6/D21      | 4             | Keypad             |                        |  
| D0          | 5             | Keypad             |                        |  
| D1          | 6             | Keypad             |                        |  
| D2          | 7             | Keypad             |                        |  
| D3          | 8             | Keypad             |                        |  
<p align="right">(<a href="#top">back to top</a>)</p>

# MQTT Topics
| Topics                               | Access   | Method  |
| :----------------------------------- | :------- | :------ |
| home/alarm/arm                       | External | Pub/Sub |
| home/alarm/alarm                     | External | Sub     |
| home/alarm/alarm                     | Internal | Pub     |
| home/climate/status/#                | External | Sub     |
| home/climate/status/[section]/[type] | Internal | Pub     |
| home/climate/servo                   | External | Pub     |
| home/log/[logLevel]/[type]           | Internal | Pub     |
| home/log/#                           | External | Sub     |

# Libraries
| Name               | Version | Component                    |
| ------------------ | ------- | ---------------------------- |
| Adafruit SSD1306   | 2.5.7   | OLED display                 |
| DHT sensor library | 1.4.4   | DHT11 sensor                 |
| NTPClient          | 3.2.1   |                              |
| Servo              | 1.1.8   | Servo motors                 |
| WiFiNINA           | 1.8.13  |                              |
| MQTT               | 2.5.0   |                              |
| Keypad             | 3.1.1   | 4x4 keypad                   |
| MFRC522            | 1.4.10  | RFID reader                  |
| Wire               | 1.8.2   | I<sup>2</sup>C communication |
| SPI                | 1.9.8   | SPI communication            |
<p align="right">(<a href="#top">back to top</a>)</p>


# Components
| Device              | Amount | Function                                                     | Controller |
|---------------------| ------ | ------------------------------------------------------------ | ---------- |
| Arduino MKR1010     | 3      | Microcontroller                                              |            |
| DHT11               | 3      | Temperature and humidity sensor                              | Climate    |
| MQ-2                | 1      | Gas/air quality sensor                                       | Climate    |
| Servo               | 2      | Controlling window and garage door                           | Climate    |
| REED switch         | 1      | Intrusion detection, front door                              | Alarm      |
| HC-SR501 PIR sensor | 2      | Intrusion (motion) detection, living room                    | Alarm      |
| HC-SR04 Ultrasound  | 1      | Automatic doors                                              | Home/entry |
| RC522 RFID reader   | 1      | Entry system                                                 | Home/entry |
| 4x4 Keypad          | 1      | Entry system                                                 | Home/entry |
| SSD1306 128x64 OLED | 1      | Peripheral display around the house (time, temp, status etc. | Home/entry |
* The system is built for expansion, there is very little work in attaching multiple devices to the system, that could be more intrusion sensors, a buzzer, multiple displays etc.
<p align="right">(<a href="#top">back to top</a>)</p>

# HIPO Diagrams
<p align="right">(<a href="#top">back to top</a>)</p>

## Alarm
![alarm hipo diagram](/Docs/Alarm_HIPO.png)
`/Docs/Alarm_HIPO.png`
<p align="right">(<a href="#top">back to top</a>)</p>

# Flowcharts

## Alarm
![alarm flowchart](/Docs/Alarm_Flowchart.png)
`/Docs/Alarm_Flowchart.png`
<p align="right">(<a href="#top">back to top</a>)</p>


# License
* Hardware: CC-BY-LA (Creative Commons)
* API: GPLv3
* Frontend: GPLv3
<p align="right">(<a href="#top">back to top</a>)</p>

# Contact
- Peter Hymøller - peterhym21@gmail.com
  - [![Twitter][twitter-shield-ptr]][twitter-url-ptr]
- Nicolai Heuck - nicolaiheuck@gmail.com
- Jan Andreasen - jan@tved.it
  - [![Twitter][twitter-shield]][twitter-url]

Project Link: [https://github.com/nicolaiheuck/Engery.IoT](https://github.com/nicolaiheuck/Engery.IoT)
<p align="right">(<a href="#top">back to top</a>)</p>

<sup>1</sup> - Look at me!


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[build-shield]: https://img.shields.io/badge/Build-passed-brightgreen.svg
[test-shield]: https://img.shields.io/badge/Tests-passed-brightgreen.svg
[contributors-shield]: https://img.shields.io/github/contributors/nicolaiheuck/Engery.IoT.svg?style=badge
[contributors-url]: https://github.com/nicolaiheuck/Engery.IoT/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/nicolaiheuck/Engery.IoT.svg?style=badge
[forks-url]: https://github.com/nicolaiheuck/Engery.IoT/network/members
[issues-shield]: https://img.shields.io/github/issues/nicolaiheuck/Engery.IoT.svg?style=badge
[closed-shield]: https://img.shields.io/github/issues-closed/nicolaiheuck/Engery.IoT?label=%20
[issues-url]: https://github.com/nicolaiheuck/Engery.IoT/issues
[license-shield]: https://img.shields.io/github/license/nicolaiheuck/Engery.IoT.svg?style=badge
[license-url]: https://github.com/nicolaiheuck/Engery.IoT/blob/master/LICENSE
[twitter-shield]: https://img.shields.io/twitter/follow/andreasen_jan?style=social
[twitter-url]: https://twitter.com/andreasen_jan
[twitter-shield-ptr]: https://img.shields.io/twitter/follow/peter_hym?style=social
[twitter-url-ptr]: https://twitter.com/peter_hym
