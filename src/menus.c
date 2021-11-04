#include "menus.h"

Menu getMenu(MenuType type) {
    Menu menu = {.numOptions=0};
    switch (type) {
    case MENU_MAIN: {
        Menu menu = {
            .options = {"New game", "Load game", "Ranking", "Exit"},
            .numOptions = 4,
            .selectedOption = 0,
            .selectionDone = false,
        };
        return menu;
    }
    case MENU_RANKING: {
        Menu menu = {
            .options = {"Back"},
            .numOptions = 1,
            .selectedOption = 0,
            .selectionDone = false,
        };
        return menu;
    }
    
    case MENU_GAME_OVER: {
        Menu menu = {
            .options = {"Menu principal", "Jogar novamente"},
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

Menu updateMenu(Menu menu, Action action) {
    switch (action) {
    case ACTION_DOWN:
    case ACTION_RIGHT:
        if (menu.selectedOption < menu.numOptions - 1)
            menu.selectedOption++;
        break;
    case ACTION_UP:
    case ACTION_LEFT:
        if (menu.selectedOption > 0)
            menu.selectedOption--;
        break;
    case ACTION_YES:
        menu.selectionDone = true;
        break;
    default:
        break;
    }
    return menu;
}