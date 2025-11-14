/*
File: q1.cpp
Triggered when a specific CAN frame is received
    Analog read PIN_PC0,
    Send the reading over CAN.
While this happens, make an LED turn on to indicate activity.
    This LED is connected to PIN_PD2.
The CAN frames are received and sent via an MCP2515 CAN controller.
    It is connected via SPI with CS on PIN_PB2.
    The crystal is 20MHz and the CAN speed is 500kbps.
*/

// include the necessary libraries
#include <Arduino.h>
#include <mcp2515.h>

// create MCP2515 object
MCP2515 mcp2515(PIN_PD2)
/* todo 1 */

void setup() {
    // set the pinMode on the input pin
    pinMode(PIN_PC0, INPUT); 
    /* todo 1 */
    // set the pinMode on the LED pin
    /pinMode(PIN_PD2, INPUT)
    // initialize the CAN controller at 500kbps
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_20MHZ);
    mcp2515.setNormalMode();
}

void loop() {
    // create CAN frame objects
    struct can_frame rxFrame;
    // make one for receiving, another for transmitting
    struct can_frame txFrame;
    /* todo 2 */

    // check if a CAN frame is received
    if (mcp2515.readMessage(&rxFrame) == MCP2515::ERROR_OK) {
        // check if the received frame is of ID 0x420 and first data byte is 0x69
        if (frameName.can_id == 0x420 && frameName.data[0] == 0x69) {
            // turn on the LED to indicate activity
            /* todo 3 */
            digitalWrite(PIN_PB2, HIGH)

            // read the analog value from the input pin and store it as a variable
            analogValue = analogRead(PIN_PC0)
            /* todo 3 */;

            // prepare the CAN frame to send
            txFrame.can_id = 0x690; // replace with desired send ID
            txFrame.can_dlc = 2; // data length code
            txFrame.data[0] = (analogValue >> 8) & 0xFF; // high byte
            txFrame.data[1] = analogValue & 0xFF; // low byte

            // send the CAN frame
            /* todo 3 */
            mcp2515.sendMessage(&rxFrame);

            // turn off the LED after sending
            digitalWrite(PIN_PB2, LOW)
            /* todo 3 */
        }
    }
}