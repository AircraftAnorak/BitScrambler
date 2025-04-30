//
// Bit Scrambler Example
// Caspar B P 2025
// M0KRH
/*

This example is basic code to implement the 
G3RUH bit scramble algorithm for data
that takes the 12th and 17th bits in a 
bit register and applies an algorithm to
scramble and descramble the data that I
have put together

Please see my GitHub for a more detailed explanation

*/

// bit_stream read left to right to simulate bitstream being sent
//
// Wanted to keep this as binary instead of a binary string
// ASCII "heya"
uint32_t bit_stream = 0b01101000011001010111100101100001;

// Outputs
uint32_t scrambled  = 0;
uint32_t output = 0;

// Bit read from stream
byte bit_input = 0;

// Output of first XOR into register
byte bit0 = 0;

// Polynomial bits of the scrambler register
byte bit_xor = 0;
// 12th bit
byte bit11 = 0;
// 17th bit
byte bit16 = 0;

// This is to simulate a preamble of 0x5555
// but note that this is reversed from
// reading it left to right, it is right to
// left to simulate having been entered
// through a bitstream
uint16_t bit_register = 1010101010101010;

void setup() {
  Serial.begin(9600);
  

  //    SCRAMBLER   //
  Serial.println("Scrambled:");
  //
  for (int i = 0; i < 32; i++)
  {
    // Retrieve first bit
    bit_input = (bit_stream >> (32-1)-i) & 0b1;

    // Assign 12th and 17th bits
    bit11 = (bit_register >> 11) & 0b1;
    bit16 = (bit_register >> 16) & 0b1;

    // XOR the 12th and 17th positions
    bit_xor = bit11 ^ bit16;

    bit0 = bit_input ^ bit_xor;

    // Shift register and add new bit0
    bit_register = (bit_register << 1) + bit0;

    // For this algorithm output is bit0
    output = (output << 1) + bit0;

  }

  // Print values
  Serial.println(output, HEX);
  Serial.println(output, BIN);


  scrambled = output;

  // Reset variables
  output = 0;
  bit_input = 0;
  bit0 = 0;
  bit_xor = 0;
  bit11 = 0;
  bit16 = 0;
  bit_register = 1010101010101010;


  //    DE-SCRAMBLER   //
  Serial.println("\nDescrambled:");
  //
  for (int i = 0; i < 32; i++)
  {
    // Retrieve first bit
    bit_input = (scrambled >> (32-1)-i) & 0b1;

    bit0 = bit_input;

    // Assign 12th and 17th bits
    bit11 = (bit_register >> 11) & 0b1;
    bit16 = (bit_register >> 16) & 0b1;

    // XOR the 12th and 17th positions
    bit_xor = bit11 ^ bit16;

    bit_register = (bit_register << 1) + bit0;

    // For this algorithm, output is XOR of the input and the 12th + 17th bits
    output = (output << 1) + (bit_input^bit_xor);

  }

  Serial.println(output, HEX);
  Serial.println(output, BIN);

}

void loop() {
  // No need to loop
}
