
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

    /* flag */ 			 {false,false,false,false}
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
	/*LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - %s", GET_NAME(task_display_init), p_task_display);
	LOGGER_INFO("  %s is a %s", GET_NAME(task_display), p_task_display_);*/

	/* Init & Print out: Task execution counter */
	g_task_display_cnt = G_TASK_DIS_CNT_INI;
	//LOGGER_INFO("   %s = %lu", GET_NAME(g_task_display_cnt), g_task_display_cnt);

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_display_dta = &task_display_dta;

	/* Init & Print out: LCD Display */
	state = ST_DISP_IDLE;
    p_task_display_dta->state = state;

    for(int i=0; i<DISPLAY_ROWS; i++)
    	p_task_display_dta->dirty_rows[i] = false;

	displayInit( DISPLAY_CONNECTION_GPIO_4BITS );

	/*LOGGER_INFO(" ");
	LOGGER_INFO("   %s = %lu   %s = %s",
				 GET_NAME(state), (uint32_t)state,
				 GET_NAME(b_event), (b_event ? "true" : "false"));*/
}

// --------------------------------------------------------------------------
// OPTIMIZACIÓN 1: Comparar antes de copiar ("Lazy Update")
// OPTIMIZACIÓN 2: Sección Crítica (Atomicidad)
// --------------------------------------------------------------------------

void task_display_set_line(uint8_t row, const char *str)
{
    if (row >= DISPLAY_ROWS) return;

    // Preparamos una línea temporal en la pila (Stack) para ver cómo quedaría el texto nuevo.
    char temp_buffer[DISPLAY_COLS];
    int i;

    // Copiamos el texto al temporal
    for(i = 0; i < DISPLAY_COLS; i++) {
        if(str[i] != '\0') {
            temp_buffer[i] = str[i];
        } else {
            break;
        }
    }
    // Rellenamos con espacios el resto (Padding)
    for(; i < DISPLAY_COLS; i++) { temp_buffer[i] = ' '; }

    // Verificamos si la línea nueva es IGUAL a la que ya tenemos en memoria.
    if (memcmp(task_display_dta.screen_buffer[row], temp_buffer, DISPLAY_COLS) == 0)
        return;

    // Si son diferentes, procedemos a copiar, pero protegemos la operación.
    __asm("CPSID i"); // Deshabilitar interrupciones

    // Copiamos del temporal al buffer real (memcopy es más rápido que el for)
    memcpy(task_display_dta.screen_buffer[row], temp_buffer, DISPLAY_COLS);

    // Activamos la bandera para que la máquina de estados trabaje
    task_display_dta.dirty_rows[row] = true;

    __asm("CPSIE i"); // Habilitar interrupciones
}

void task_display_printf(uint8_t row, const char *fmt, ...)
{
    if (row >= DISPLAY_ROWS) return;

    // Buffer temporal local
    char local_buffer[DISPLAY_COLS + 1];

    va_list args;
    va_start(args, fmt);

    // Formateo seguro
    vsnprintf(local_buffer, sizeof(local_buffer), fmt, args);

    va_end(args);

    // Llamamos a set_line optimizado
    task_display_set_line(row, local_buffer);
}

/*void task_display_set_line(uint8_t row, const char *str)
{
    if (row >= DISPLAY_ROWS) return;

    int i;
    for(i = 0; i < DISPLAY_COLS; i++) {
        if(str[i] != '\0') {
            task_display_dta.screen_buffer[row][i] = str[i];
        } else {
            break;
        }
    }

    for(; i < DISPLAY_COLS; i++) {
        task_display_dta.screen_buffer[row][i] = ' ';
    }

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
}*/

// --- Máquina de Estados (Se llama cada 1ms) ---

void task_display_statechart(void){
    task_display_dta_t *p_task_display_dta;
    /* Update Task Display Data Pointer */
    p_task_display_dta = &task_display_dta;

    switch (p_task_display_dta->state)
    {
    case ST_DISP_IDLE:
                for (int i = 0; i < DISPLAY_ROWS; i++) {
                    if (p_task_display_dta->dirty_rows[i] == true) {

                        p_task_display_dta->curr_row = i; // Usar 'i', no '0'
                        p_task_display_dta->curr_col = 0;
                        p_task_display_dta->state = ST_DISP_SET_CURSOR;

                        // IMPORTANTE: Salir de la función inmediatamente.
                        // Esto asegura que el costo de IDLE sea casi cero.
                        return;
                    }
                }
                break;


        case ST_DISP_SET_CURSOR:
            displayCharPositionWrite(0, p_task_display_dta->curr_row);

            p_task_display_dta->state = ST_DISP_WRITE_CHAR;
            break;


        case ST_DISP_WRITE_CHAR:
            // Escribimos UN solo caracter
        	displayCharWrite(p_task_display_dta->screen_buffer[p_task_display_dta->curr_row][p_task_display_dta->curr_col]);

            // Avanzamos columna
            p_task_display_dta->curr_col++;

            // Verificamos si terminamos la fila
            if (p_task_display_dta->curr_col >= DISPLAY_COLS) {
            	p_task_display_dta->dirty_rows[p_task_display_dta->curr_row] = false;
            	p_task_display_dta->state = ST_DISP_IDLE;
            }
            break;

        default:
        	p_task_display_dta->state = ST_DISP_IDLE;
            break;
    }
}

void task_display_update(void *parameters)
{
    // Eliminamos la variable local b_time_update_required y el while complejo

    /* Sección Crítica: Verificar y descontar SOLO UN tick */
    __asm("CPSID i");   /* Deshabilitar interrupciones */

    // CAMBIO CLAVE: Usamos IF, no WHILE.
    // Si hay 1, 5 o 20 ticks acumulados, solo atendemos UNO por vuelta de loop.
    if (G_TASK_DIS_TICK_CNT_INI < g_task_display_tick_cnt)
    {
        g_task_display_tick_cnt--;

        // Habilitamos interrupciones ANTES de ejecutar la lógica pesada
        __asm("CPSIE i");

        g_task_display_cnt++;

        // Ejecutamos la máquina UNA sola vez (Costo fijo: ~130us)
        task_display_statechart();
    }
    else
    {
        // Si no había ticks, habilitamos interrupciones y salimos
        __asm("CPSIE i");
    }
}
