/********************************************************
 * menus module
 * Internal representation and handling of the game menus
 ********************************************************/
#ifndef MENU_H
#define MENU_H

#include "game.h"

// ==== CONSTANTS ====
#define MAX_MENU_OPTIONS 4   // Max number of options in a menu
#define MAX_OPTION_LENGTH 20 // Max length of each menu option

// ==== TYPES ===

// Internal menu representation
typedef struct {
    char options[MAX_MENU_OPTIONS][MAX_OPTION_LENGTH];
    int numOptions;
    int selectedOption;
    bool selectionDone;
} Menu;

// Enum members differentiate the various game menus
typedef enum {
    MENU_MAIN, MENU_EXIT, MENU_OK, MENU_GAME_OVER
} MenuType;

// ==== FUNCTIONS ====
Menu getMenu(MenuType type);               // Create a new menu of the given type
Menu updateMenu(Menu menu, Action action); // Update the menu state based on action

#endif
