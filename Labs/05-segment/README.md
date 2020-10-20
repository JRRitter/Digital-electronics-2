#Lab prerequisites
**Common Cathode (CC)** displays have all of their segments' cathodes connected to a common ground, the respective anodes are then connected to individual pins. Active high.

**Common Anode (Ca)** displays have all of their segments' anodes connected to a common source, the respective cathodes are then connected to individual pins. Active low.

| **Digit** | **A** | **B** | **C** | **D** | **E** | **F** | **G** | **DP** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 1 |
| 2 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 1 |
| 3 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 |
| 4 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 1 |
| 5 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 1 |
| 6 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 |
| 7 | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 1 |
| 8 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 9 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 1 |

The seven segment display is connected to the arduino with three pins: PB0[8] is the serial input, PD7[7] is the serial clock and PD4[4] is the reset.