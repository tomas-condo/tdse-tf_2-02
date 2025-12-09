

/********************** inclusions *******************************************/
#include "main.h"
#include "board.h"
#include "task_gameplay.h"
#include "task_menu_interface.h"
#include "display.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>

/********************** macros and definitions *******************************/
#define G_TASK_GAME_CNT_INI         0ul
#define G_TASK_GAME_TICK_CNT_INI    0ul

#define MAX_SEQUENCE_LEN    100

// Tiempos en ms (asumiendo 1 tick = 1 ms)
#define DELAY_SHOW_ON_NORMAL 1000ul
#define DELAY_SHOW_OFF_NORMAL 500ul
#define DELAY_SHOW_ON_HARD    400ul
#define DELAY_SHOW_OFF_HARD   200ul

// Estados de la FSM del juego
typedef enum {
    ST_GAME_IDLE,
    ST_GAME_GEN_SEQ,
    ST_GAME_SHOW_SEQ_ON,
    ST_GAME_SHOW_SEQ_OFF,
    ST_GAME_WAIT_INPUT,
    ST_GAME_CHECK_INPUT,
    ST_GAME_OVER
} game_state_t;

/********************** internal data declaration ****************************/
typedef struct {
    game_state_t state;
    game_difficulty_t difficulty;
    
    uint8_t sequence[MAX_SEQUENCE_LEN];
    uint8_t seq_length;
    uint8_t play_index;
    uint8_t user_index;
    
    uint32_t timer_delay; // Contador para retardos no bloqueantes
} gameplay_internal_t;

static gameplay_internal_t game;

/********************** external data declaration ****************************/
task_gameplay_dta_t task_gameplay_dta;

uint32_t g_task_gameplay_cnt;
volatile uint32_t g_task_gameplay_tick_cnt;

/********************** internal functions declaration ***********************/
void leds_all_off(void);
void led_control(uint8_t color_code, uint8_t action); // 1 ON, 0 OFF

// Mapeo interno de colores
#define COLOR_AZ 0
#define COLOR_RO 1
#define COLOR_AM 2
#define COLOR_VE 3

/********************** external functions definition ************************/

void task_gameplay_init(void *parameters)
{
    /* Init Task counters */
    g_task_gameplay_cnt = G_TASK_GAME_CNT_INI;
    g_task_gameplay_tick_cnt = G_TASK_GAME_TICK_CNT_INI;

    /* Init Data */
    task_gameplay_dta.active = false;
    task_gameplay_dta.score = 0;
    game.state = ST_GAME_IDLE;
    
    srand(HAL_GetTick()); // Inicializar semilla aleatoria
    
    LOGGER_INFO("  task_gameplay initialized");
}

void gameplay_start(game_difficulty_t difficulty) {
    game.difficulty = difficulty;
    game.seq_length = 0;
    game.score = 0;
    task_gameplay_dta.score = 0;
    task_gameplay_dta.active = true;
    game.state = ST_GAME_GEN_SEQ;
}

void task_gameplay_update(void *parameters)
{
    bool b_time_update_required = false;

    /* Protect shared resource */
    __asm("CPSID i");   /* disable interrupts */
    if (G_TASK_GAME_TICK_CNT_INI < g_task_gameplay_tick_cnt)
    {
        g_task_gameplay_tick_cnt--;
        b_time_update_required = true;
    }
    __asm("CPSIE i");   /* enable interrupts */

    while (b_time_update_required)
    {
        g_task_gameplay_cnt++;

        // Si el juego no está activo, no hacemos nada en la FSM
        if (!task_gameplay_dta.active) {
            // Solo consumimos el ciclo
        } else {
            
            // Manejo de Timer No Bloqueante
            if (game.timer_delay > 0) {
                game.timer_delay--;
            } else {
                
                // --- FSM del Juego ---
                switch (game.state) {
                    case ST_GAME_GEN_SEQ:
                        game.sequence[game.seq_length] = rand() % 4;
                        game.seq_length++;
                        
                        game.play_index = 0;
                        game.timer_delay = 500; // Pausa antes de mostrar
                        game.state = ST_GAME_SHOW_SEQ_ON;
                        
                        char buff[16];
                        sprintf(buff, "Nivel: %d", game.seq_length);
                        displayCharPositionWrite(0,2);
                        displayStringWrite(buff);
                        break;

                    case ST_GAME_SHOW_SEQ_ON:
                        if (game.play_index < game.seq_length) {
                            led_control(game.sequence[game.play_index], 1); // ON
                            // Configurar tiempo según dificultad
                            game.timer_delay = (game.difficulty == GAME_DIFF_NORMAL) ? DELAY_SHOW_ON_NORMAL : DELAY_SHOW_ON_HARD;
                            game.state = ST_GAME_SHOW_SEQ_OFF;
                        } else {
                            game.user_index = 0;
                            leds_all_off();
                            displayCharPositionWrite(0,1);
                            displayStringWrite("  Tu Turno   ");
                            
                            // Limpiar cola de eventos
                            while(any_event_task_menu()) get_event_task_menu();
                            
                            game.state = ST_GAME_WAIT_INPUT;
                        }
                        break;

                    case ST_GAME_SHOW_SEQ_OFF:
                        led_control(game.sequence[game.play_index], 0); // OFF
                        game.play_index++;
                        game.timer_delay = (game.difficulty == GAME_DIFF_NORMAL) ? DELAY_SHOW_OFF_NORMAL : DELAY_SHOW_OFF_HARD;
                        game.state = ST_GAME_SHOW_SEQ_ON;
                        break;

                    case ST_GAME_WAIT_INPUT:
                        if (any_event_task_menu()) {
                            task_menu_ev_t ev = get_event_task_menu();
                            uint8_t pressed = 255;
                            
                            if (ev == EV_BTN_AZ_PRESS) pressed = COLOR_AZ;
                            else if (ev == EV_BTN_RO_PRESS) pressed = COLOR_RO;
                            else if (ev == EV_BTN_AM_PRESS) pressed = COLOR_AM;
                            else if (ev == EV_BTN_VE_PRESS) pressed = COLOR_VE;

                            if (pressed != 255) {
                                led_control(pressed, 1); // Feedback visual
                                if (pressed == game.sequence[game.user_index]) {
                                    game.user_index++;
                                    game.timer_delay = 200; 
                                    game.state = ST_GAME_CHECK_INPUT;
                                } else {
                                    game.state = ST_GAME_OVER;
                                }
                            }
                        }
                        break;

                    case ST_GAME_CHECK_INPUT:
                        leds_all_off();
                        if (game.user_index >= game.seq_length) {
                            task_gameplay_dta.score = game.seq_length;
                            game.timer_delay = 800;
                            game.state = ST_GAME_GEN_SEQ;
                        } else {
                            game.state = ST_GAME_WAIT_INPUT;
                        }
                        break;

                    case ST_GAME_OVER:
                        displayCharPositionWrite(0,0);
                        displayStringWrite("   GAME OVER    ");
                        char score_str[16];
                        sprintf(score_str, "Puntaje: %d     ", task_gameplay_dta.score);
                        displayCharPositionWrite(0,1);
                        displayStringWrite(score_str);
                        
                        // Parpadeo final simple (usando timer)
                        static int blink_cnt = 0;
                        if (blink_cnt < 6) {
                            if (blink_cnt % 2 == 0) led_control(COLOR_RO, 1);
                            else led_control(COLOR_RO, 0);
                            blink_cnt++;
                            game.timer_delay = 200;
                        } else {
                            blink_cnt = 0;
                            task_gameplay_dta.active = false; // Devuelve control
                            game.state = ST_GAME_IDLE;
                        }
                        break;
                        
                    default:
                        game.state = ST_GAME_IDLE;
                        break;
                }
            }
        }

        /* Check tick again */
        __asm("CPSID i");   /* disable interrupts */
        if (G_TASK_GAME_TICK_CNT_INI < g_task_gameplay_tick_cnt)
        {
            g_task_gameplay_tick_cnt--;
            b_time_update_required = true;
        }
        else
        {
            b_time_update_required = false;
        }
        __asm("CPSIE i");   /* enable interrupts */
    }
}

/********************** internal functions definition ************************/

void leds_all_off(void) {
    HAL_GPIO_WritePin(LED_AZ_PORT, LED_AZ_PIN, LED_AZ_OFF);
    HAL_GPIO_WritePin(LED_RO_PORT, LED_RO_PIN, LED_RO_OFF);
    HAL_GPIO_WritePin(LED_AM_PORT, LED_AM_PIN, LED_AM_OFF);
    HAL_GPIO_WritePin(LED_VE_PORT, LED_VE_PIN, LED_VE_OFF);
}

void led_control(uint8_t color_code, uint8_t action) {
    // action: 1 = ON, 0 = OFF
    switch(color_code) {
        case COLOR_AZ: 
            HAL_GPIO_WritePin(LED_AZ_PORT, LED_AZ_PIN, action ? LED_AZ_ON : LED_AZ_OFF); 
            break;
        case COLOR_RO: 
            HAL_GPIO_WritePin(LED_RO_PORT, LED_RO_PIN, action ? LED_RO_ON : LED_RO_OFF); 
            break;
        case COLOR_AM: 
            HAL_GPIO_WritePin(LED_AM_PORT, LED_AM_PIN, action ? LED_AM_ON : LED_AM_OFF); 
            break;
        case COLOR_VE: 
            HAL_GPIO_WritePin(LED_VE_PORT, LED_VE_PIN, action ? LED_VE_ON : LED_VE_OFF); 
            break;
    }
}
/********************** end of file ******************************************/
