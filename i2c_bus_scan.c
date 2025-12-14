#include <stdio.h>

#include "pico/stdlib.h"
#include "pio_i2c.h"

#define PIN_SDA 2
#define PIN_SCL 3

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main() {
    stdio_init_all();

    PIO pio = pio0;
    PIO pir = pio1; 
    uint sm0 = pio_claim_unused_sm(pio,true);
    uint sm1 = pio_claim_unused_sm(pio,true);
    uint sm2 = pio_claim_unused_sm(pio,true);
    uint sm3 = pio_claim_unused_sm(pio,true);
    uint sm4 = pio_claim_unused_sm(pir,true);
    uint sm5 = pio_claim_unused_sm(pir,true);
    uint sm6 = pio_claim_unused_sm(pir,true);
    uint sm7 = pio_claim_unused_sm(pir,true);
    
    printf("\n sms.%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n",sm0,sm1,sm2,sm3,sm4,sm5,sm6,sm7);
//    uint sm3 = pio_claim_unused_sm(pio,true);

    uint offset = pio_add_program(pio, &i2c_program);
   // uint offset1 = pio_add_program(pir, &i2c_program);
    i2c_program_init(pio, sm0, offset, 2, 3);
    i2c_program_init(pio, sm1, offset, 4, 5);
    i2c_program_init(pio, sm2, offset, 6, 7);
    i2c_program_init(pio, sm3, offset, 8, 9);
    i2c_program_init(pir, sm4, offset, 10, 11);
    i2c_program_init(pir, sm5, offset, 12, 13);
    i2c_program_init(pir, sm6, offset, 14, 15);
    i2c_program_init(pir, sm7, offset, 16, 17);    
    //uint offset = pio_add_program(pio, &i2c_program);
    //i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);
 for (uint sm = 0; sm<=3;++sm) {
    printf("\nPIO I2C SM %i Bus Scan\n",sm);
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }
        // Perform a 0-byte read from the probe address. The read function
        // returns a negative result NAK'd any time other than the last data
        // byte. Skip over reserved addresses.
        int result;
        if (reserved_addr(addr))
            result = -1;
        else
            result = pio_i2c_read_blocking(pio, sm, addr, NULL, 0);

        printf(result < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");
}
 for (uint sm = 0; sm<=3;++sm) {
    printf("\nPIO I2C SM %i Bus Scan\n",sm);
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }
        // Perform a 0-byte read from the probe address. The read function
        // returns a negative result NAK'd any time other than the last data
        // byte. Skip over reserved addresses.
        int result;
        if (reserved_addr(addr))
            result = -1;
        else
            result = pio_i2c_read_blocking(pir, sm, addr, NULL, 0);

        printf(result < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");
}
    return 0;
}
