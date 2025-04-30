Bit scrambling, specifically for radio, is a method of 'forcing' more bit changes in transmitted data without increasing the length of transmission, such as Manchester Encoding.

Many methods can be chosen to complete this, however, a common method is using the G3RUH scrambler, which takes the `XOR` of the 12th and 17th positions in a bit register and depending on whether scrambling or descrambling will be manipulated by a bit stream input.

---
## Scrambler

![Scrambler-Scrambler drawio](https://github.com/user-attachments/assets/ef86a0c4-f849-4179-be28-801f460e8820)

Above is the algorithm to scramble the data. The input data is parsed, bit by bit, through the shift register (which would normally be filled with the preamble data from a packet) to scramble the data.

The XOR of bits is actually an addition of the bits in binary.

To do this in C++, the shift register values are assigned to a variable:

```c++
// 12th bit
bit11 = (bit_register >> 11) & 0b1;
// 17th bit
bit16 = (bit_register >> 16) & 0b1;
```

Then the algorithm is applied to the data:

```c++
// XOR the 12th and 17th positions
bit_xor = bit11 ^ bit16;


bit0 = bit_input ^ bit_xor;

// Shift register and add new bit0
bit_register = (bit_register << 1) + bit0;


// For this algorithm output is bit0
output = (output << 1) + bit0;
```

---
## Descrambler

![Scrambler-Descrambler drawio](https://github.com/user-attachments/assets/053dafc9-3a42-4286-915f-2eb4f45812ab)

Above is the algorithm to descramble the data. This is reversing the operation that was applied during scrambling to recover the data.

```c++
// XOR the 12th and 17th positions
bit_xor = bit11 ^ bit16;

bit_register = (bit_register << 1) + bit0;

// For this algorithm, output is XOR of the input and 12th + 17th bits
output = (output << 1) + (bit_input^bit_xor);
```
