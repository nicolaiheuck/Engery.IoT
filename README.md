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
- [MQTT Topics](#mqtt-topics)
- [Libraries](#libraries)
- [Components](#components)
- [HIPO Diagram](#hipo-diagrams)
- [Flowcharts](#flowcharts)
- [Fritzing diagrams](#fritzing-diagrams)
  - [e-Paper](#e-paper)
  - [SCT-013-030](#sct-013)
  - [RTC](#rtc)
  - [Termometer](#thermometer)
  - [Relæ](#relæ)
- [License](#license)
- [Contact](#contact)
</details>

# Case
Inspireret af udenlandske eksempler ønsker IT-Center Syd at udvikle og implementere en række nye IT-services:
> Info ved lokaler: Display ved alle lokaler, der angiver aktivitet, periode og lærernavn.

> Energi- og Ressourceovervågning: En platform, der giver mulighed for overvågning og styring af skolernes energiforbrug og ressourceanvendelse. Dette kan inkludere intelligente målere og sensorer, der rapporterer forbrug i realtid og identificerer områder med potentiale for besparelser.
<p align="right">(<a href="#top">back to top</a>)</p>

# Requirements
- [X] Infodisplay ved alle lokaler
  - [X] Viser aktuel fag
  - [X] Viser periode for lokalet
  - [X] Viser lokale nummer/navn
  - [ ] Viser aktuel lærer
- [X] Energi- og ressourceovervågning
  - [x] Overvågning af energiforbrug i lokale/område
  - [x] Overvågning af temperatur og luftfugtighed
  - [x] Styring af strøm
  - [x] Styring af temperatur efter aktivitet i lokalet
  - [x] Alarmer for afvigelser
  - [x] Grafer/rapport over energiforbrug samt klima
<p align="right">(<a href="#top">back to top</a>)</p>

# Architecture diagram
![architecture diagram](/DOCS/EGON-Architecture-Diagram.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

# Roadmap
- [X] Måle temperatur og luftfugtighed
  - [x] Sende data i et overskueligt format
- [X] Måle strømforbrug
  - [x] Sende data i et overskueligt format
- [x] Modtage data om lokaler fra backend
  - [X] Vise aktuel fag i lokale
  - [x] Vise aktuel periode lokale er booket
  - [ ] Vise aktuel lærer
    * Dette var ikke muligt grundet begrænsninger ved ekstern API
  - [x] Automatisk opdatere lokale-info
  - [x] Styre temperatur/strøm efter lokalets brug
<p align="right">(<a href="#top">back to top</a>)</p>

#  Summary and rundown
EGON er lavet som et proof of concept i to dele. IoT (denne) samt en kombineret back- og frontend, hvor besøgende kan se info om lokalet, samt hvor ansatte i serviceafdelingen kan se hvordan "status" er for et lokale.

EGON kan samtidig styre både temperatur, samt lys/strøm i lokalerne alt efter om et lokale står tomt eller er i brug.

Serviceafd. kan ændre et givent setpunkt for temperatur i et lokale efter ønske. Er et lokale booket vil displayet selv opdatere med relevant info (fag, lokale, periode, studie linie)

> Nicolai er i tvivl om hvor "Sibiren" er, på hans skema står der kun 51.244. Nicolai kigger på displays rundt ved lokalerne og kan se både nummer, men også navn på lokalet.
> 
> Nicolai finder 51.244 - Sibirien og kan samtidig se at faget der kører er Embedded II på linien Datatekniker Prog. samt perioden hvor faget kører. Det fag stemmer overens med hans skema, og Nicolai har derved fundet det korrekte lokale.

> Serviceafdelingen vil gerne se om nogle lokaler bruger meget strøm i weekenden.
> 
> De slår op på webinterfacet, og kan se at den ene fløj bruger meget strøm i weekenden - de vælger at "drill down" i systemet, og kan se at et bestemt lokale bruger meget strøm. De kan så undersøge om det er relevant, eller om strømmen skal slukkes automatisk i weekenden.
<p align="right">(<a href="#top">back to top</a>)</p>

# Getting started
EGON er bygget op over en microcontroller af typen Arduino MKR WiFi 1010.

Hvert lokale skal have sin egen microcontroller, som har følgende moduler:
* DHT11 temperatur- og fugtighedsmåler
* E-Ink display
* Spændings transducer
* Relæ
* RTC (Real Time Clock)

Meningen med EGON er at man monterer klima sensoren et centralt sted i rummet, gerne skygget for solen.

Derudover skal transduceren monteres over den primære fase der går ind i lokalet (der kan monteres flere hvis rummet har
mere end en fase)

Når EGON er monteret vil den automatisk logge på det angivne WiFi netværk, og derefter kontakte den MQTT broker der er angivet i systemet.
Begge disse indstillinger angives i `/src/shared/secrets.h`
<p align="right">(<a href="#top">back to top</a>)</p>

# Pin layout
| Arduino pin | Component pin | Component name                  |
|:----------- |:------------- |:------------------------------- |
| 5V          | VCC           | DS3231 + DHT11 + relæ           |
| GND         | GND           | DS3231 + DHT11 + e-Paper + relæ |
| VCC         | VCC           | e-Paper display                 |
| D12         | SCL           | e-Paper display                 |
| D9          | CLK           | e-Paper display                 |
| D8          | DIN           | e-Paper display                 |
| D7          | DATA          | DHT11                           |
| D6          | CS            | e-Paper display                 |
| D5          | Input2        | Relæ                            |
| D2          | RST           | e-Paper display                 |
| D1          | DC            | e-Paper display                 |
| D0          | BUSY          | e-Paper display                 |
| A6          | K             | Transducer                      |
<p align="right">(<a href="#top">back to top</a>)</p>

# MQTT Topics
| Topics                                              | Who     | Method | Content        |
| :-------------------------------------------------- | :------ | :----- | :------------- |
| {skole}/{fløj}/{lokale}/pv/data                     | IoT     | Pub    | Telemetry data |
| {skole}/{fløj}/{lokale}/pv/data                     | Backend | Sub    | Telemetry data |
| {skole}/{fløj}/{lokale}/pv/requestlocation/location | IoT     | Pub    | (empty)        |
| {skole}/{fløj}/{lokale}/pv/requestlocation/location | Backend | Sub    | (empty)        |
| {skole}/{fløj}/{lokale}/pv/location                 | IoT     | Sub    | Location data  |
| {skole}/{fløj}/{lokale}/pv/location                 | Backend | Pub    | Location data  |
| {skole}/{fløj}/{lokale}/sp/thermostat               | IoT     | Sub    | SP for temp    |
| {skole}/{fløj}/{lokale}/sp/thermostat               | Backend | Pub    | SP for temp    |
| energy/onlinestate                                  | Backend | Pub    | Status for the backend (LWT) |
<p align="right">(<a href="#top">back to top</a>)</p>

# Libraries
| Name                    | Version | Component           |
| ----------------------- | ------- | ------------------- |
| WiFi NINA               | 1.8.13  | Wireless            |
| Adafruit GFX            | 1.11.3  | Display             |
| Adafruit Unified Sensor | 1.1.6   | DHT11               |
| Adafruit DHT Sensor     | 1.4.4   | DHT11               |
| ArduinoJson             | 6.21.3  | JSON (de)serializer |
| EmonLib                 | 1.1.0   | Transducer          |
| MQTT                    | 2.5.0   | MQTT client         |
| DS3231                  | 1.0.1   | RTC                 |
| EPD2IN9                 | 2.0.0   | e-Paper display     |
<p align="right">(<a href="#top">back to top</a>)</p>

# Components
| Device                 | Amount | Function                               |
|------------------------| ------ | -------------------------------------- |
| Arduino MKR1010        | 1      | Microcontroller                        |
| DHT11                  | 1      | Temperatur og fugtighedsmåler          |
| HL-525 relæ            | 1      | Relæ for strømstyring                  |
| SCT-013-030 Transducer | 1      | Spændingsmåler                         |
| DS3231 RTC             | 1      | Real Time Clock - Holder styr på tiden |
| Waveshare 2.9" e-Paper | 1      | Visning af lokale-info                 |
<p align="right">(<a href="#top">back to top</a>)</p>

# HIPO Diagrams
![hipo diagram](/DOCS/EGON-HIPO.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

# Flowcharts
![flowchart](/DOCS/EGON-Flowchart.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

# Fritzing diagrams
## E-paper
![E-paper wiring diagram](/DOCS/fritzing/E-Paper%20Display.png)
| Device                 | Amount | Function                               |
|------------------------| ------ | -------------------------------------- |
| Waveshare 2.9" e-Paper | 1      | Visning af lokale-info                 |

## SCT-013
![SCT-013 wiring diagram](/DOCS/fritzing/SCT013.png)
| Device                 | Amount | Function                               |
|------------------------| ------ | -------------------------------------- |
| SCT-013-030 Transducer | 1      | Spændingsmåler                         |

## RTC
![RTC wiring diagram](/DOCS/fritzing/RTC.png)
| Device                 | Amount | Function                               |
|------------------------| ------ | -------------------------------------- |
| DS3231 RTC             | 1      | Real Time Clock - Holder styr på tiden |

## Thermometer
![Thermostat wiring diagram](/DOCS/fritzing/Cooler&Heater&DHT11.png)
**Components used in diagram**<br>
| Device                 | Amount | Function                               |
|------------------------| ------ | -------------------------------------- |
| DHT11                  | 1      | Temperatur og fugtighedsmåler          |

## Relæ
![Relay wiring diagram](/DOCS/fritzing/Relay.png)
| Device                 | Amount | Function                               |
|------------------------| ------ | -------------------------------------- |
| HL-525 relæ            | 1      | Relæ for strømstyring                  |

# License
* Hardware: CC-BY-LA (Creative Commons)
* Software: MIT
<p align="right">(<a href="#top">back to top</a>)</p>

# Contact
- Peter Hymøller - peterhym21@gmail.com
  - [![Github][github-peter]][github-peter-link]
- Nicolai Heuck - nicolaiheuck@gmail.com
  - [![Github][github-nicolai]][github-nicolai-link]
- Jan Andreasen - jan@tved.it
  - [![Github][github-jan]][github-jan-link]

Project Link: [https://github.com/nicolaiheuck/Engery.IoT](https://github.com/nicolaiheuck/Engery.IoT)
<p align="right">(<a href="#top">back to top</a>)</p>


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
[github-peter]: https://img.shields.io/badge/Peter_Hymøller-green?logo=Github&label=Github
[github-peter-link]: https://github.com/peterhym21
[github-nicolai]: https://img.shields.io/badge/Nicolai_Heuck-green?logo=Github&label=Github
[github-nicolai-link]: https://github.com/nicolaiheuck
[github-jan]: https://img.shields.io/badge/Jan_Andreasen-green?logo=Github&label=Github
[github-jan-link]: https://github.com/Thoroughbreed
