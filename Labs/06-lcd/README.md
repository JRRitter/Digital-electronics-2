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


| **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off <br>&nbsp;<br>&nbsp;<br>&nbsp; | `lcd_init(LCD_DISP_OFF);`<br>&nbsp;<br>&nbsp;<br>&nbsp; |
   | `lcd_clrscr` | `void` | Clear display and set cursor to home position | `lcd_clrscr();` |
   | `lcd_gotoxy` | `uint8_t x`<br> `uint8_t y`| Set cursor to specified position <br>  | `lcd_gotoxy(2,3);` |
   | `lcd_putc` | `char c` | Display character at current cursor position. | `lcd_putc(c);` |
   | `lcd_puts` | `const char* s` | Display string without auto linefeed. | `lcd_puts(s);` |
   | `lcd_command` | `uint8_t cmd` | Send LCD controller instruction command. | `lcd_command(cmd);` |
   | `lcd_data` | `uint8_t data` | Send data byte to LCD controller. | `lcd_data(data);` |