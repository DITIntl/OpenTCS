#include "threads.h"
#include "ssd1306.h"
#include "menu.h"

display_t display = {DISPLAY_OFF};

void showDiag(void);
void showAbout(void);
void setFunctions(void);
void setCutMode(void);
void setShifter(void);

menuItem_t settingsMenuList[] = {{"Functions", &setFunctions, 0}, {"Cut mode", &setCutMode, 0}, {"Shifter setup", &setShifter, 0} };

menuStruct_t settingsMenu = {"Settings Menu", 2, settingsMenuList};

menuItem_t mainMenuItemList[] = {{"Diagnostics", &showDiag, NULL}, {"Settings", NULL, &settingsMenu}, {"About", &showAbout, NULL}};

menuStruct_t mainMenu = {"Main Menu", sizeof(mainMenuItemList)/sizeof(menuItem_t), mainMenuItemList};

void startDisplay(void) {

    ssd1306Init(SSD1306_SWITCHCAPVCC);
    ssd1306TurnOn();
    display.state = DISPLAY_ON;
    gpioSetPad(GPIOC, GPIOC_LED4);

    ssd1306DrawString(40, 20, "OpenTCS", Font_System7x8);
//    nilThdSleepMilliseconds(100); // Fails
    gpioClearPad(GPIOC, GPIOC_LED4);

    while (true) {

        ssd1306TurnOff();
        display.state = DISPLAY_OFF;

        while (!BUTTON_SEL) /* Wait until the select button is pressed */
        {
            gpioTogglePad(GPIOC, GPIOC_LED4); /* Display heartbeat */
            nilThdSleepMilliseconds(250);
        }
        ssd1306ClearScreen();
        ssd1306TurnOn();
        display.state = DISPLAY_ON;
        openMenu(&mainMenu);
    }
}

void showDiag(void)
{

}

void showAbout(void)
{

}

void setFunctions(void)
{

}

void setCutMode(void)
{

}

void setShifter(void)
{

}
