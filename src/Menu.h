/**
 * @file Menu.h
 * @brief Header file for the Menu class.
 *
 * This file defines the Menu class, which provides functionality for interacting with the system through a menu interface.
 *
 * @date 12-05-2024
 */

#ifndef PROJETODA2_MENU_H
#define PROJETODA2_MENU_H

#include "System.h"

/**
 * @class Menu
 * @brief Represents a menu interface for interacting with the system.
 */
class Menu {
public:
    /**
     * @brief Starts the menu.
     *
     * @param system The system object to interact with.
     */
    void start(System system);

    /**
     * @brief Displays the menu for generating a toy graph.
     *
     * @param system The system object to interact with.
     */
    void toyGraphMenu(System system);

    /**
     * @brief Displays the menu for selecting a real graph.
     *
     * @param system The system object to interact with.
     */
    void realGraphMenu(System system);

    /**
     * @brief Displays the menu for selecting a medium-sized graph.
     *
     * @param system The system object to interact with.
     */
    void mediumGraphMenu(System system);

    /**
     * @brief Displays the menu for selecting system functions.
     *
     * @param system The system object to interact with.
     */
    void functionsMenu(System system);
};

#endif //PROJETODA2_MENU_H
