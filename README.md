# Smart Component Identifier

An Arduino-based automated diagnostic system designed to instantly identify and measure passive electronic components, including resistors, capacitors, and Light Dependent Resistors (LDRs). By leveraging automated voltage divider networks and dynamic timing algorithms, this system eliminates manual multimeter calibration and speeds up component testing.

## 🚀 Key Features
* **Instant Auto-Detection:** Automatically identifies whether the inserted component is a Resistor, Capacitor, or LDR without manual switching.
* **Smart Measurement Algorithms:**
  * Uses **voltage divider networks** to compute highly precise resistance values.
  * Employs **RC time constant ($\tau = R \times C$) filtering** and high-speed timers to accurately capture capacitance.
  * Monitors real-time ambient light changes via calibrated LDR voltage tracking.
* **Dual-Output Display Interface:** 
  * Detailed diagnostic logs, component types, and raw telemetry data are streamed directly to the **Serial Monitor**.
  * Core values and essential status alerts are dynamically mapped onto a local **Seven-Segment Display**.
* **Efficiency Boost:** Achieved a **95% reduction in manual component testing time**, making it ideal for rapid sorting and prototyping.

---

## 🛠️ Hardware Requirements & Components
* Arduino Uno / Nano (or any compatible microcontroller)
* Seven-Segment Display (Common Anode/Cathode)
* Reference Resistors (for internal voltage divider networks)
* Test Bench Slots (for inserting unknown Resistors, Capacitors, and LDRs)
* Connecting Wires & Breadboard

---

## 📂 Project Structure
```text
Smart-Component-Identifier/
├── src/
│   └── component_identifier.ino  # Main Arduino source code with measurement algorithms
├── schematics/
│   └── circuit_diagram.png       # Complete hardware wiring layout
└── README.md                     # Project documentation<img width="1156" height="651" alt="Hardware_image" src="https://github.com/user-attachments/assets/b1d2a162-239a-4e61-a6d2-2047012a4c3f" />
<img width="1156" height="651" alt="rating capacito and resistor" src="https://github.com/user-attachments/assets/0e10acd9-20ea-41d1-8e78-42ef58aae46d" />


