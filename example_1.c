char uart_rd;

void close_all_leds() {
    portb.b0 = 0;
    portb.b1 = 0;
    portb.b2 = 0;
    portb.b3 = 0;
    portb.b4 = 0;
    portb.b5 = 0;
    portb.b6 = 0;
    portb.b7 = 0;
}

void main() {
  // Setting output frequency to 140MHz
  PLLFBD = 70;             // PLL multiplier M=70
  CLKDIV = 0x0000;         // PLL prescaler N1=2, PLL postscaler N2=2

  ANSELA = 0x00;           // Convert all I/O pins to digital
  ANSELB = 0x00;
  ANSELC = 0x00;
  ANSELD = 0x00;
  ANSELE = 0x00;
  ANSELG = 0x00;

  TRISB = 0x00;  // PORTB'yi çikis olarak ayarla
  close_all_leds(); // Tüm LED'leri sifirla

  PPS_Mapping(100, _INPUT,  _U1RX);              // Sets pin RP100 to be Input, and maps U1RX to it
  PPS_Mapping(101, _OUTPUT, _U1TX);              // Sets pin RP101 to be Output, and maps U1TX to it

  UART1_Init(56000);              // Initialize UART module at 56000 bps
  Delay_ms(100);                  // Wait for UART module to stabilize

  UART1_Write_Text("Start");
  UART1_Write(13);
  UART1_Write(10);

  while (1) {                     
    if (UART1_Data_Ready()) {     // If data is received
      uart_rd = UART1_Read();     // read the received data
      UART1_Write(uart_rd);       // and send data via UART
    }

    switch(uart_rd) {
       case 'a':
         portb.b0 =  ~portb.b0;
         uart_rd = 0;
         break;

       case 'b':
         portb.b1 =  ~portb.b1;
         uart_rd = 0;
         break;
    }
  }
}
