## Lab prerequisites

| **Signal(s)** | **Pin(s)** | **Purpose** |
| :-: | :-: | :-- |
| RS | PB0 | Register selection signal. Selection between *Instruction register* (0) and *Data register* (1) |
| R/W | GND | Selecting reading or writing. GND means only writing is enabled |
| E | PB1 | Enable signal for communication |
| D[3:0] | N/A | Data transfer in 8-bit mode. |
| D[7:4] | PD[7:4] | Data transfer in both 8 and 4-bit modes. |

| **Signal(s)** | **Value(s)** | **Purpose** |
| :-: | :-: | :-- |
| RS | 1 | Selects *Data register* |
| D[7:4] | 0100 | Higher four bits of sent word |
| D[7:4] | 0011 | ASCII code: C|


The ASCII table is a form of look-up table. Computers can only understand numbers, so an ASCII code is the numerical representation of a character such as 'a' or '@' or an action of some sort.

Numbers (0 to 9) range from 0x30 to 0x39, uppercase letters (A to Z) from 0x41 to 0x5A and lowercase letters (a to z) from 0x61 to 0x7A.
