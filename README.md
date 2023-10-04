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
- [HIPO Diagrams](#hipo-diagrams)
- [Flowcharts](#flowcharts)
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

#  Summary and rundown
EGON er lavet som et proof of concept i to dele IoT (denne) samt en kombineret back- og frontend, hvor besøgende kan se info om lokalet, samt hvor ansatte i serviceafdelingen kan se hvordan "status" er for et lokale.

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
## Home
| Arduino pin | Component pin | Component name     |
|:------------|:--------------|:-------------------|
| 5V          | VCC           |                    |
<p align="right">(<a href="#top">back to top</a>)</p>

# MQTT Topics
| Topics                               | Access   | Method  |
| :----------------------------------- | :------- | :------ |
| home/alarm/arm                       | External | Pub/Sub |

# Libraries
| Name               | Version | Component                    |
| ------------------ | ------- | ---------------------------- |
| Adafruit SSD1306   | 2.5.7   | OLED display                 |
<p align="right">(<a href="#top">back to top</a>)</p>

# Components
| Device              | Amount | Function                       |
|---------------------| ------ | ------------------------------ |
| Arduino MKR1010     | 1      | Microcontroller                |
| DHT11               | 1      | Temperatur og fugtighedsmåler  |
| Relæ ting           | 1      | Relæ for strømstyring          |
| Transducer ting     | 1      | Spændingsmåler                 |
| RTC ting            | 1      | Holder styr på tiden           |
| Skærm ting          | 1      | Visning af lokale-info         |
<p align="right">(<a href="#top">back to top</a>)</p>

# HIPO Diagrams
![alarm hipo diagram](/Docs/Alarm_HIPO.png)
`/Docs/Alarm_HIPO.png`
<p align="right">(<a href="#top">back to top</a>)</p>

# Flowcharts
![alarm flowchart](/Docs/Alarm_Flowchart.png)
`/Docs/Alarm_Flowchart.png`
<p align="right">(<a href="#top">back to top</a>)</p>

# License
* Hardware: CC-BY-LA (Creative Commons)
* Software: MIT
<p align="right">(<a href="#top">back to top</a>)</p>

# Contact
- Peter Hymøller - peterhym21@gmail.com
  - [![Twitter][twitter-shield-ptr]][twitter-url-ptr]
- Nicolai Heuck - nicolaiheuck@gmail.com
- Jan Andreasen - jan@tved.it
  - [![Twitter][twitter-shield]][twitter-url]

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
[twitter-shield]: https://img.shields.io/twitter/follow/andreasen_jan?style=social
[twitter-url]: https://twitter.com/andreasen_jan
[twitter-shield-ptr]: https://img.shields.io/twitter/follow/peter_hym?style=social
[twitter-url-ptr]: https://twitter.com/peter_hym
