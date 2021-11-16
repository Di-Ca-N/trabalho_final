#include "menus.h"


/**
 * Generate and return a menu of the requested type.
 * 
 * Arguments:
 *     type (MenuType): Requested menu type 
 */
Menu getMenu(MenuType type) {
    Menu menu = {.numOptions = 0};
    // Creating menu according to the menu type
    switch (type) {
        case MENU_MAIN: {
            Menu menu = {
                .options = {"Novo Jogo", "Carregar Jogo", "Ranking", "Sair"},
                .numOptions = 4,
                .selectedOption = 0,
                .selectionDone = false,
            };
            return menu;
        }
        case MENU_OK: {
            Menu menu = {
                .options = {"OK"},
                .numOptions = 1,
                .selectedOption = 0,
                .selectionDone = false,
            };
            return menu;
        }

        case MENU_YES_NO: {
            Menu menu = {
                .options = {"Sim", "Não"},
                .numOptions = 2,
                .selectedOption = 0,
                .selectionDone = false,
            };
            return menu;
        }

        default:
            return menu;
            break;
    }
}

/**
 * Update a menu state according to the action taken. Return the 
 * updated menu
 *
 * Arguments:
 *     menu (Menu): Menu to be updated.
 *     action (Action): Action taken by the user
 */
Menu updateMenu(Menu menu, Action action) {
    switch (action) {
        // Down or right actions select the next option
        case ACTION_DOWN:
        case ACTION_RIGHT:
            if (menu.selectedOption < menu.numOptions - 1)
                menu.selectedOption++;
            break;
        // Up and down actions select the previous option
        case ACTION_UP:
        case ACTION_LEFT:
            if (menu.selectedOption > 0) menu.selectedOption--;
            break;
        // Selection confirmation
        case ACTION_YES:
            menu.selectionDone = true;
            break;
        default:
            break;
    }
    return menu;
}