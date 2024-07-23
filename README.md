# iCE40 DevBoard

This project was made as part of [Hack Club Arcade 2024](https://hackclub.com/arcade/).

## Warning

The current board design has not been tested and has known mistakes:
1. **R3 is placed on the wrong side of the level shifter.** Do not solder R3 on and add a 1k pullup to 3v3 on the FPGA's _CDONE_ pin (via TP4).
2. **The FPGA's _SPI\_SS_ pin is missing a pullup resistor.** Add a 10k pullup to 3v3 on the FPGA's _SPI\_SS_ pin (via TP9).

These changes will be permanently applied to the design in a future iteration.

## Hardware

All required libraries can be downloaded from [SnapEDA](https://www.snapeda.com/home/).

- **iCE5LP2K-SG48ITR** FPGA
- **10118194-0011LF** USB micro connector
- **AMS1117** 3.3V and 1.2V voltage regulators
- **AT25DN011** SPI flash
- **CCBTLV3257MPWREP** multiplexer
- **TXS0108EPWR** level shifter
