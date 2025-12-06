// Example implementation using C++ libraries.
// Keep C++-only implementation here; call via the C API in user_cpp.h

#include "../Inc/user_cpp.h"
#include "main.h"
#include "OneButton.h"
#include "LiquidCrystalSerial.h"

// Manage C++ objects here so generated files don't get overwritten.
static OneButton SET_BUTTON;
static LiquidCrystalSerial lcd(LCD_Clock_GPIO_Port, LCD_Clock_Pin,
                               LCD_Data_GPIO_Port, LCD_Data_Pin,
                               LCD_Latch_GPIO_Port, LCD_Latch_Pin);

// local callback
static void Set_Single_Click()
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

extern "C" void UserCpp_Init(void)
{
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
}

extern "C" void UserCpp_Loop(void)
{
    // delegate periodic tasks
    SET_BUTTON.tick();
}
