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




| **Module** | **Operation** | **I/O register(s)** | **Bit(s)** |
| :-: | :-- | :-: | :-- |
| Timer/Counter0 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR0B<br><br>TCNT0<br>TIMSK0 | CS02, CS01, CS00<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT0[7:0]<br>TOIE0 |
| Timer/Counter1 | Prescaler<br><br>16-bit data value<br>Overflow interrupt enable | TCCR1B<br><br>TCNT1H, TCNT1L<br>TIMSK1 | CS12, CS11, CS10<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT1[15:0]<br>TOIE1 (1: enable, 0: disable) |
| Timer/Counter2 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR2B<br><br>TCNT2<br>TIMSK2 | CS22, CS21, CS20<br>(000: stopped, 001: 1, 010: 8, 011: 32, 100: 64, 101: 128, 110: 256, 111: 1024)<br>TCNT2[7:0]<br>TOIE2 |



| **Program address** | **Source** | **Vector name** | **Description** |
| :-: | :-- | :-- | :-- |
| 0x0000 | RESET | -- | Reset of the system |
| 0x0002 | INT0  | `INT0_vect` | External interrupt request number 0 |
| 0x004 | INT1 | `INT1_vect` | External Interrupt Request 1 |
| 0x0006 | PCINT0 | `PCINT0_vect` | Pin Change Interrupt Request 0 |
| 0x0008 | PCINT1 | `PCINT1_vect` | Pin Change Interrupt Request 1 |
| 0x000A | PCINT2 | `PCINT2_vect` | Pin Change Interrupt Request 2 |
| 0x000C | WDT | `WDT_vect` | Watchdog Time-out Interrupt |
| 0x0012 | TIMER2_OVF | `TIMER2_OVF_vect` | Timer/Counter2 Overflow |
| 0x0018 | TIMER1_COMPB | `TIMER1_COMPB_vect` | Compare match between Timer/Counter1 value and channel B compare value |
| 0x001A | TIMER1_OVF | `TIMER1_OVF_vect` | Overflow of Timer/Counter1 value |
| 0x0020 | TIMER0_OVF | `TIMER0_OVF_vect` | Timer/Counter0 Overflow |
| 0x0024 | USART_RX | `USART_RX_vect` | USART Rx Complete |
| 0x002A | ADC | `ADC_vect` | ADC Conversion Complete |
| 0x0030 | TWI | `TWI_vect` | 2-wire Serial Interface |


| **Module** | **Description** | **MCU pin** | **Arduino pin** |
| :-: | :-: | :-: | :-: |
| Timer/Counter0 | OC0A | PD6 |  6 |
|                | OC0B | PD5 |  5 |
| Timer/Counter1 | OC1A | PB1 |  9 |
|                | OC1B | PB2 | 10 |
| Timer/Counter2 | OC2A | PB3 | 11 |
|                | OC2B | PD3 |  3 |

