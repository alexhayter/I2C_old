Multiple Software I2C interfaces on the pico.

My robotics project, a 6dof robot arm that requires 6 AS5600 magnetic angle sensors. 
Unfortunatly I only have the standard AS5600 with a fixed address, not the AS5600L.

So I have been playing with the pio_i2c in the pico examples. I soon discovered that
you only need to load the i2c.pio once into one of the two pio's then copy it to each of
the state machines without running out instruction memory.

I have hacked the original i2c_bus_scan.c to iterate over the eight pio_i2c interfaces 
and find i2c boards connected.

My implimentation is very buggy but as a proof of concept it works.
