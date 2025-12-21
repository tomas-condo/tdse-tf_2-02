/********************** inclusions *******************************************/
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "board.h"
#include "task_gameplay.h"
#include "task_gameplay_attribute.h"
#include "task_gameplay_interface.h"
#include "task_menu_interface.h"
#include "task_actuator_attribute.h"
#include "task_actuator_interface.h"
#include "display.h"
#include "logger.h"

/********************** macros and definitions *******************************/
#define G_TASK_GAME_CNT_INI         0ul
#define G_TASK_GAME_TICK_CNT_INI    0ul

#define MAX_SEQUENCE_LEN    100

// Tiempos en ms (asumiendo 1 tick = 1 ms)
#define DEL_GAME_XX_MIN 0ul
#define DEL_SHOW_ON_NORMAL  1000ul
#define DEL_SHOW_OFF_NORMAL 500ul
#define DEL_SHOW_ON_HARD    400ul
#define DEL_SHOW_OFF_HARD   200ul

#define GAME_DIFF_NORMAL    0
#define GAME_DIFF_HARD      1

/********************** internal data declaration ****************************/
task_gameplay_dta_t task_gameplay_dta =
{
    DEL_GAME_XX_MIN,
	ST_GAME_GEN_SEQ,
    EV_GAME_IDLE,
    false,
    0,
    {0},
    0,
    0,
    0,
    true,
    0,
    0,
    0,
    0,
};

#define GAMEPLAY_DTA_QTY	(sizeof(task_gameplay_dta)/sizeof(task_gameplay_dta_t))

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_gameplay 		= "Task Gameplay (Interactive Gameplay)";
const char *p_task_gameplay_ 		= "Non-Blocking & Update By Time Code";

/********************** external data declaration ****************************/
uint32_t g_task_gameplay_cnt;
volatile uint32_t g_task_gameplay_tick_cnt;

/********************** external functions definition ************************/

void task_gameplay_init(void *parameters)
{
	task_gameplay_dta_t *p_task_gameplay_dta;
	task_gameplay_state_t	state;
	task_gameplay_ev_t	event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - %s", GET_NAME(task_gameplay_init), p_task_gameplay);
	LOGGER_INFO("  %s is a %s", GET_NAME(task_gameplay), p_task_gameplay_);

	/* Init & Print out: Task execution counter */
	g_task_gameplay_cnt = G_TASK_GAME_CNT_INI;
	LOGGER_INFO("   %s = %lu", GET_NAME(g_task_gameplay_cnt), g_task_gameplay_cnt);

	init_queue_event_task_gameplay();

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_gameplay_dta = &task_gameplay_dta;

	/* Init & Print out: Task execution FSM */
	state = ST_GAME_IDLE;
	p_task_gameplay_dta->state = state;

	event = EV_GAME_IDLE;
	p_task_gameplay_dta->event = event;

	b_event = false;
	p_task_gameplay_dta->flag = b_event;

	LOGGER_INFO(" ");
	LOGGER_INFO("   %s = %lu   %s = %lu   %s = %s",
				 GET_NAME(state), (uint32_t)state,
				 GET_NAME(event), (uint32_t)event,
				 GET_NAME(b_event), (b_event ? "true" : "false"));

	p_task_gameplay_dta->score = 0;
    srand(HAL_GetTick()); // Inicializar semilla aleatoria
}

void task_gameplay_statechart(void)
{
    task_gameplay_dta_t *p_task_gameplay_dta;
    /* Update Task Gameplay Data Pointer */
    p_task_gameplay_dta = &task_gameplay_dta;

    if (true == any_event_task_gameplay()) {
        p_task_gameplay_dta -> flag = true;
        p_task_gameplay_dta -> event = get_event_task_gameplay();
    }

    if (true == p_task_gameplay_dta -> flag){
    	switch (p_task_gameplay_dta -> state) {
        	case ST_GAME_GEN_SEQ:

            	put_event_task_actuator(EV_LED_XX_OFF, ID_LED_AZ);
            	put_event_task_actuator(EV_LED_XX_OFF, ID_LED_AM);
            	put_event_task_actuator(EV_LED_XX_OFF, ID_LED_RO);
            	put_event_task_actuator(EV_LED_XX_OFF, ID_LED_VE);
        		p_task_gameplay_dta -> sequence[p_task_gameplay_dta -> seq_length] = rand() % 4;
        		p_task_gameplay_dta -> seq_length ++;

        		p_task_gameplay_dta -> seq_length = 0;
        		p_task_gameplay_dta -> tick = DEL_GAME_XX_MIN; // Pausa antes de mostrar
        		p_task_gameplay_dta -> state = ST_GAME_SHOW_SEQ_ON;

                //char buff[16];
                //sprintf(buff, "Nivel: %d", game.seq_length);
                //displayCharPositionWrite(0,2);
                //displayStringWrite(buff);
                break;

            case ST_GAME_SHOW_SEQ_ON:
            	if (p_task_gameplay_dta -> input_index < p_task_gameplay_dta -> seq_length) {
            		//led_control(game.sequence[game.play_index], 1); // ON
                    // Configurar tiempo según dificultad
            		p_task_gameplay_dta -> tick = (p_task_gameplay_dta ->difficulty == GAME_DIFF_NORMAL) ? DEL_SHOW_ON_NORMAL : DEL_SHOW_ON_HARD;
            		p_task_gameplay_dta -> state = ST_GAME_SHOW_SEQ_OFF;
                    } else {
                    p_task_gameplay_dta -> seq_index = 0;
                    //leds_all_off();
                    //displayCharPositionWrite(0,1);
                    //displayStringWrite("  Tu Turno   ");

                    // Limpiar cola de eventos
                    while(any_event_task_menu()) get_event_task_menu();
                    p_task_gameplay_dta ->state = ST_GAME_WAIT_INPUT;
                }
            	break;

            case ST_GAME_SHOW_SEQ_OFF:
            	//led_control(game.sequence[game.play_index], 0); // OFF
            	p_task_gameplay_dta -> seq_index++;
            	p_task_gameplay_dta -> tick = (p_task_gameplay_dta -> difficulty == GAME_DIFF_NORMAL) ? DEL_SHOW_OFF_NORMAL : DEL_SHOW_OFF_HARD;
            	p_task_gameplay_dta -> state = ST_GAME_SHOW_SEQ_ON;
                break;

            case ST_GAME_WAIT_INPUT:
            	if (any_event_task_menu()) {
            		//task_menu_ev_t ev = get_event_task_menu();
                    uint8_t pressed = 255;

                    //if (ev == EV_BTN_AZ_PRESS) pressed = COLOR_AZ;
                    //else if (ev == EV_BTN_RO_PRESS) pressed = COLOR_RO;
                    //else if (ev == EV_BTN_AM_PRESS) pressed = COLOR_AM;
                    //else if (ev == EV_BTN_VE_PRESS) pressed = COLOR_VE;

                    if (pressed != 255) {
                    	//led_control(pressed, 1); // Feedback visual
                        if (pressed == p_task_gameplay_dta -> sequence[p_task_gameplay_dta -> seq_index]) {
                        	p_task_gameplay_dta -> seq_index++;
                        	p_task_gameplay_dta -> tick = 200;
                        	p_task_gameplay_dta -> state = ST_GAME_CHECK_INPUT;
                        } else {
                        	p_task_gameplay_dta -> state = ST_GAME_OVER;
                        }
                    }
                }
                break;

            case ST_GAME_CHECK_INPUT:
            	//leds_all_off();
                if (p_task_gameplay_dta -> seq_index >= p_task_gameplay_dta -> seq_length) {
                	p_task_gameplay_dta -> score = p_task_gameplay_dta -> seq_length;
                	p_task_gameplay_dta -> tick = DEL_GAME_XX_MIN; // etq
                	p_task_gameplay_dta -> state = ST_GAME_GEN_SEQ;
                } else {
                	p_task_gameplay_dta -> state = ST_GAME_WAIT_INPUT;
                }
                break;

            case ST_GAME_OVER:
            	//displayCharPositionWrite(0,0);
                //displayStringWrite("   GAME OVER    ");
                //char score_str[16];
                //sprintf(score_str, "Puntaje: %d     ", task_gameplay_dta.score);
                //displayCharPositionWrite(0,1);
                //displayStringWrite(score_str);

                // Parpadeo final simple (usando ACTUATOR)
                p_task_gameplay_dta -> active = false; // Devuelve control (flag?)
                p_task_gameplay_dta -> state = ST_GAME_IDLE;
                break;

            default:
                p_task_gameplay_dta -> state = ST_GAME_IDLE;
                break;
        }
    }
}

// ---------------------------------------------------------------------
// 3. Lógica de Gameplay (para actualizar el juego)
// ---------------------------------------------------------------------

void task_gameplay_update(void *parameters)
{
	bool b_time_update_required = false;

	/* Protect shared resource */
	__asm("CPSID i");	/* disable interrupts */
    if (G_TASK_GAME_TICK_CNT_INI < g_task_gameplay_tick_cnt)
    {
		/* Update Tick Counter */
    	g_task_gameplay_tick_cnt--;
    	b_time_update_required = true;
    }
    __asm("CPSIE i");	/* enable interrupts */

    while (b_time_update_required)
    {
		/* Update Task Counter */
		g_task_gameplay_cnt++;

		/* Run Task Menu Statechart */
    	task_gameplay_statechart();

    	/* Protect shared resource */
		__asm("CPSID i");	/* disable interrupts */
		if (G_TASK_GAME_TICK_CNT_INI < g_task_gameplay_tick_cnt)
		{
			/* Update Tick Counter */
			g_task_gameplay_tick_cnt--;
			b_time_update_required = true;
		}
		else
		{
			b_time_update_required = false;
		}
		__asm("CPSIE i");	/* enable interrupts */
	}
}
/********************** end of file ******************************************/
