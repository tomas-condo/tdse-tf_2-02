
/********************** inclusions *******************************************/
#include "main.h"
#include "logger.h"
#include "dwt.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "task_display.h"
#include "task_display_attribute.h"
#include "display.h"

/********************** macros and definitions *******************************/
#define G_TASK_DIS_CNT_INI      0ul
#define G_TASK_DIS_TICK_CNT_INI 0ul

#define INITROW 0
#define INITCOL 0

/********************** internal data declaration ****************************/
task_display_dta_t task_display_dta =
{
    /* state          */ ST_DISP_IDLE,

    // Inicializamos el buffer con ceros (seguridad).
    // La función task_display_init() se encargará luego de llenarlo con espacios ' '.
    /* screen_buffer  */ {{0}},

    /* curr_row       */ INITROW,
    /* curr_col       */ INITCOL,

    /* flag */ 			 false
};

#define DISPLAY_DTA_QTY	(sizeof(task_display_dta)/sizeof(task_display_dta_t))

/********************** internal data definition *****************************/
const char *p_task_display 		= "Task Display";
const char *p_task_display_ 	= "Non-Blocking & Update By Time Code";

/********************** external data declaration ****************************/
uint32_t g_task_display_cnt;
volatile uint32_t g_task_display_tick_cnt;

/********************** external functions definition ************************/
void task_display_init(void *parameters)
{
	task_display_dta_t *p_task_display_dta;
	task_display_state_t state;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - %s", GET_NAME(task_display_init), p_task_display);
	LOGGER_INFO("  %s is a %s", GET_NAME(task_display), p_task_display_);

	/* Init & Print out: Task execution counter */
	g_task_display_cnt = G_TASK_DIS_CNT_INI;
	LOGGER_INFO("   %s = %lu", GET_NAME(g_task_display_cnt), g_task_display_cnt);

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_display_dta = &task_display_dta;

	/* Init & Print out: LCD Display */
	state = ST_DISP_IDLE;
    p_task_display_dta->state = state;

	b_event = false;
    p_task_display_dta->flag = b_event;

	displayInit( DISPLAY_CONNECTION_GPIO_4BITS );

	LOGGER_INFO(" ");
	LOGGER_INFO("   %s = %lu   %s = %s",
				 GET_NAME(state), (uint32_t)state,
				 GET_NAME(b_event), (b_event ? "true" : "false"));
}

void task_display_set_line(uint8_t row, const char *str)
{
    if (row >= DISPLAY_ROWS) return;

    int i;
    for(i = 0; i < DISPLAY_COLS; i++) {
        if(str[i] != '\0') {
            // CORRECCIÓN: Usamos la variable global con punto (.)
            task_display_dta.screen_buffer[row][i] = str[i];
        } else {
            break;
        }
    }

    for(; i < DISPLAY_COLS; i++) {
        // CORRECCIÓN: Usamos punto (.)
        task_display_dta.screen_buffer[row][i] = ' ';
    }

    // CORRECCIÓN: Usamos punto (.) y el nombre correcto del campo
    task_display_dta.flag = true;
}

void task_display_printf(uint8_t row, const char *fmt, ...)
{
    if (row >= DISPLAY_ROWS) return;

    // Buffer temporal local para realizar el formateo
    // +1 para el caracter nulo
    char local_buffer[DISPLAY_COLS + 1];

    va_list args;
    va_start(args, fmt);

    // vsnprintf es la versión segura que acepta la lista de argumentos
    // Formatea el string y lo guarda en local_buffer
    vsnprintf(local_buffer, sizeof(local_buffer), fmt, args);

    va_end(args);

    // Reutilizamos la función set_line para copiar al buffer real
    // y rellenar con espacios si es necesario
    task_display_set_line(row, local_buffer);
}

// --- Máquina de Estados (Se llama cada 1ms) ---

void task_display_statechart(void){
    task_display_dta_t *p_task_display_dta;
    /* Update Task Display Data Pointer */
    p_task_display_dta = &task_display_dta;

    switch (p_task_display_dta->state)
    {
        case ST_DISP_IDLE:
            // Si alguien actualizó el buffer, empezamos el ciclo de refresco
            if (p_task_display_dta->flag) {
            	p_task_display_dta->curr_row = 0;
            	p_task_display_dta->curr_col = 0;
                p_task_display_dta->state = ST_DISP_SET_CURSOR;

                // Opcional: bajamos la bandera aquí si queremos un solo refresco
                // o la gestionamos al final. Por seguridad, la bajamos al terminar.
            }
            break;

        case ST_DISP_SET_CURSOR:
            // Configura la posición del cursor para la fila actual
            // Nota: curr_col siempre debería ser 0 al entrar aquí
            displayCharPositionWrite(0, p_task_display_dta->curr_row);

            // Pasamos a escribir caracteres
            p_task_display_dta->state = ST_DISP_WRITE_CHAR;
            break;

        case ST_DISP_WRITE_CHAR:
            // Escribimos UN solo caracter
        	displayCharWrite(p_task_display_dta->screen_buffer[p_task_display_dta->curr_row][p_task_display_dta->curr_col]);

            // Avanzamos columna
            p_task_display_dta->curr_col++;

            // Verificamos si terminamos la fila
            if (p_task_display_dta->curr_col >= DISPLAY_COLS) {
            	p_task_display_dta->curr_col = 0;
            	p_task_display_dta->curr_row++;

                // Verificamos si terminamos todas las filas
                if (p_task_display_dta->curr_row >= DISPLAY_ROWS) {
                	p_task_display_dta->flag = false; // Refresco completo
                	p_task_display_dta->state = ST_DISP_IDLE;
                } else {
                    // Si faltan filas, siguiente ciclo movemos cursor
                	p_task_display_dta->state = ST_DISP_SET_CURSOR;
                }
            }
            // Si no hemos terminado la fila, en el siguiente tick (1ms después)
            // volveremos a entrar a ST_DISP_WRITE_CHAR para el siguiente caracter.
            break;

        default:
        	p_task_display_dta->state = ST_DISP_IDLE;
            break;
    }
}

void task_display_update(void *parameters)
{
    bool b_time_update_required = false;

    /* Protect shared resource */
    __asm("CPSID i");   /* disable interrupts */
    if (G_TASK_DIS_TICK_CNT_INI < g_task_display_tick_cnt)
    {
        /* Update Tick Counter */
        g_task_display_tick_cnt--;
        b_time_update_required = true;
    }
    __asm("CPSIE i");   /* enable interrupts */

    while (b_time_update_required)
    {
        /* Update Task Counter */
        g_task_display_cnt++;

        /* Run Task Display Statechart */
        task_display_statechart();

        /* Protect shared resource */
        __asm("CPSID i");   /* disable interrupts */
        if (G_TASK_DIS_TICK_CNT_INI < g_task_display_tick_cnt)
        {
            /* Update Tick Counter */
            g_task_display_tick_cnt--;
            b_time_update_required = true;
        }
        else
        {
            b_time_update_required = false;
        }
        __asm("CPSIE i");   /* enable interrupts */
    }
}

