# Lab prerequisites

## Overflow times

![image-equation](https://latex.codecogs.com/gif.latex?t_{\text{ovf}}&space;=&space;\frac{1}{f_{\text{CPU}}}\cdot&space;2^n&space;\cdot&space;N&space;=&space;\frac{1}{16\cdot&space;10^6}\cdot&space;2^8&space;\cdot&space;64&space;=&space;1024\&space;\mu\text{s})

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16u | 128u | -- | 1024u | -- | 4096u | 16,38m |
| Timer/Counter1 | 16 | 4096u | 32,77m | -- | 262,1m | -- | 1,049 | 4,194 |
| Timer/Counter2 | 8  |  16u | 128u | 512u | 1024u | 2048u | 4096u | 16,38m |

## Shield connections

The four LEDs are connected to pins PB5[13] (D1), PB4[12] (D2), PB3[~11] (D3), PB2[~10] (D4) in an active low fashion.

The three pushbuttons are connected to pins PC1[A1] (S1-A1), PC2[A2] (S2-A2), PC3[A3] (S3-A3) in an active low fashion. External pull-up resistors can be enabled with jumper J2.




