#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "gpio/serial.h"

static int validArguments(const int numberOfArguments, char *arguments[]);
static void writeData(GPIO_SERIAL_PARAMETERS *serialParameters);
static void readData(GPIO_SERIAL_PARAMETERS *serialParameters);

static const char *ARGUMENT_WRITE = "-write";
static const char *ARGUMENT_READ = "-read";
static const char *STOP_INSTRUCTION = "STOP";

static const int MAX_BUFFER_SIZE = 128;

/*
 * Main program entry point
 */
int main(int argc, char *argv[])
{
    // Get argument -read or -write
    if (validArguments(argc, argv) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    // Set up paramters
    GPIO_SERIAL_PARAMETERS serialParameters = { .device = GPIO_SERIAL_DEFAULT_DEVICE };

    // Open device
    int returnStatus = gpioSerialOpenDevice(&serialParameters);
    assert(returnStatus == EXIT_SUCCESS);

    // Write data
    if (strcmp(argv[1], ARGUMENT_WRITE) == 0)
        writeData(&serialParameters);

    // Read data
    if (strcmp(argv[1], ARGUMENT_READ) == 0)
        readData(&serialParameters);

    // Close device
    returnStatus = gpioSerialCloseDevice(serialParameters);
    assert(returnStatus == EXIT_SUCCESS);

    return EXIT_SUCCESS;
}

/*
 * Validate arguments
 */
static int validArguments(const int numberOfArguments, char *arguments[])
{
    if (numberOfArguments == 1)
    {
        printf("gpioSerial: missing argument\n");
        return EXIT_FAILURE;
    }

    if (numberOfArguments > 2)
    {
        printf("gpioSerial: invalid number of arguments\n");
        return EXIT_FAILURE;
    }

    if (strcmp(arguments[1], ARGUMENT_WRITE) != 0 && strcmp(arguments[1], ARGUMENT_READ) != 0)
    {
        printf("gpioSerial: invalid argument, expected -write or -read\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Write data to serial device
 */
static void writeData(GPIO_SERIAL_PARAMETERS *serialParameters)
{
    int returnStatus = EXIT_SUCCESS;
    bool writeData = true;

    while(writeData == true && returnStatus == EXIT_SUCCESS)
    {
        // Get data to send
        char *data = malloc((sizeof(char) * MAX_BUFFER_SIZE) + 1);
        printf("Enter data to send, enter '%s' to exit (max %d characters) ...\n", STOP_INSTRUCTION, MAX_BUFFER_SIZE);
        fgets(data, MAX_BUFFER_SIZE + 1, stdin);

        // Send data
        serialParameters->data = malloc(sizeof(char) * strlen(data) + 1);
        serialParameters->data = data;
        returnStatus = gpioSerialWriteDevice(serialParameters);

        // Exit function
        if (strncmp(STOP_INSTRUCTION, data, strlen(STOP_INSTRUCTION)) == 0)
            writeData = false;
    }

    assert(returnStatus == EXIT_SUCCESS);
}

/*
 * Read data from serial device
 */
static void readData(GPIO_SERIAL_PARAMETERS *serialParameters)
{
    int returnStatus = EXIT_SUCCESS;
    bool readData = true;

    while(readData == true && returnStatus == EXIT_SUCCESS)
    {
        // Don't have to hammer the device
        sleep(1);

        // Read data
        serialParameters->bytesToRead = MAX_BUFFER_SIZE + 1;
        returnStatus = gpioSerialReadDevice(serialParameters);

        // Output data
        if (serialParameters->bytesRead > 0)
            printf("%s", serialParameters->data);

        // Exit function
        if (strncmp(STOP_INSTRUCTION, serialParameters->data, strlen(STOP_INSTRUCTION)) == 0)
            readData = false;
    }

    assert(returnStatus == EXIT_SUCCESS);
}
