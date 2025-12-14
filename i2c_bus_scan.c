#include <stdio.h>

#include "pico/stdlib.h"
#include "pio_i2c.h"

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main() {
    stdio_init_all();

    uint sm[8];
    for(uint i=0;i<8;i++){
        PIO pio= i < 4 ? pio0 : pio1;
        sm[i] = pio_claim_unused_sm(pio,true);
    }

    uint offset = pio_add_program(pio0, &i2c_program);

    for(uint i=0;i<8;i++){
        PIO pio= i < 4 ? pio0 : pio1;    
        i2c_program_init(pio, sm[i], offset, 2*i+2, 2*i+3);
    }    

    for (int i=0;i<8;i++){
        PIO pio= i < 4 ? pio0 : pio1;
        printf("\nPIO I2C SM %i Bus Scan\n",sm[i]);
        printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

        for (int addr = 0; addr < (1 << 7); ++addr) {
            if (addr % 16 == 0) {
                printf("%02x ", addr);
            }

            int result;
            if (reserved_addr(addr))
                result = -1;
            else
                result = pio_i2c_read_blocking(pio, sm[i], addr, NULL, 0);

            printf(result < 0 ? "." : "@");
            printf(addr % 16 == 15 ? "\n" : "  ");
        }
    printf("Done.\n");
    }
    return 0;
}
