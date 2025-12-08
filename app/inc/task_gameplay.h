/*
 * @file   : task_gameplay.h
 */
#ifndef TASK_GAMEPLAY_H_
#define TASK_GAMEPLAY_H_

#include "main.h"
#include "task_menu_attribute.h"

// Definición de dificultades
typedef enum {
    GAME_DIFF_NORMAL,
    GAME_DIFF_HARD
} game_difficulty_t;

// Estructura de datos pública del juego
typedef struct {
    uint32_t score;
    bool active;
} task_gameplay_dta_t;

extern task_gameplay_dta_t task_gameplay_dta;

// Funciones públicas
void task_gameplay_init(void *parameters);
void task_gameplay_update(void *parameters);
void gameplay_start(game_difficulty_t difficulty);

#endif /* TASK_GAMEPLAY_H_ */
