#Raspberry Pi C Serial

Another little C program. This time to have a go at software GPIO serial UART communications. So my C GPIO library using the 'sysfs interface' is slowly moving along!

The code important to this little project is gpio/serial.c, gpio/serial.h and main.c.  This is where all the new GPIO serial UART code lives.

## How to clone (with GPIO sub module)

```bash
git clone --recursive https://github.com/mse240966/raspberry-pi-c-serial.git
```

## Example

```bash
$ ./gpioSerial -write
Enter data to send, enter 'STOP' to exit (max 128 characters) ...
This is a test
Enter data to send, enter 'STOP' to exit (max 128 characters) ...
This is another test
Enter data to send, enter 'STOP' to exit (max 128 characters) ...
This is the last test!!
Enter data to send, enter 'STOP' to exit (max 128 characters) ...
STOP
```

```bash
$ ./gpioSerial -read
This is a test
This is another test
This is the last test!!
STOP
```

## Circuit

![circuit](https://github.com/mse240966/raspberry-pi-c-serial/blob/master/docs/serialCircuit.png "Serial Circuit")

