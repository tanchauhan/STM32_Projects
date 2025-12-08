// Example implementation using C++ libraries.
// Keep C++-only implementation here; call via the C API in user_cpp.h

#include "../Inc/user_cpp.h"
#include "main.h"
#include "OneButton.h"
#include "MCP4725.h"
#include "LiquidCrystalSerial.h"
#include <cmath>

// HAL peripheral handles defined in main.c
extern I2C_HandleTypeDef hi2c1;

// --- Constants ---
constexpr float DAC_MAX_VOLTAGE = 3.3f;
const uint8_t MCP4725_ADDR = 0x60; // Use 0x62 or 0x63 based on your module
const uint16_t SINE_TABLE_SIZE = 128;

// Manage C++ objects here so generated files don't get overwritten.
static OneButton SET_BUTTON;
static LiquidCrystalSerial lcd(LCD_Clock_GPIO_Port, LCD_Clock_Pin,
                               LCD_Data_GPIO_Port, LCD_Data_Pin,
                               LCD_Latch_GPIO_Port, LCD_Latch_Pin);
static MCP4725 dac(MCP4725_ADDR, &hi2c1);

// --- Local Variables ---
static uint16_t sine_lookup[SINE_TABLE_SIZE];
uint16_t DAC_SET_VALUE = 0;

// local callback
static void Set_Single_Click()
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

extern "C" void UserCpp_Init(void)
{
    // --- Pre-calculate sine wave for the DAC ---
    for (int i = 0; i < SINE_TABLE_SIZE; i++) {
        // Generates a sine wave from 0 to 2*PI
        float rad = (2.0 * M_PI * i) / SINE_TABLE_SIZE;
        // Scale the sine wave (-1 to 1) to the DAC's 12-bit range (0 to 4095)
        sine_lookup[i] = static_cast<uint16_t>((sin(rad) + 1.0) * 2047.5);
    }


    // initialize C++ objects and wiring
    SET_BUTTON.setup(PB1_GPIO_Port, PB1_Pin, true, true, false);
    SET_BUTTON.setDebounceMs(20);
    SET_BUTTON.setClickMs(100);
    SET_BUTTON.setPressMs(3000);
    SET_BUTTON.attachClick(Set_Single_Click);

    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello World !");

    // --- Initialize MCP4725 DAC ---
    if (dac.begin()) {
        dac.setMaxVoltage(DAC_MAX_VOLTAGE);
        lcd.setCursor(0, 1);
        lcd.print("DAC OK");
    } else {
        // DAC not found, indicate error on LCD
        lcd.setCursor(0, 1);
        lcd.print("DAC Init FAILED!");
        // You might want to halt here or blink an LED
    }
}

extern "C" void UserCpp_Loop(void)
{
    static uint8_t sine_index = 0;

    // delegate periodic tasks
    SET_BUTTON.tick();

    // Update DAC output to generate a sine wave
    dac.setValue(sine_lookup[sine_index]);
    sine_index = (sine_index + 1) % SINE_TABLE_SIZE;
    HAL_Delay(500);
}
