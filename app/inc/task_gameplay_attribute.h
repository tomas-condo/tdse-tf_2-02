#ifndef TASK_INC_TASK_GAMEPLAY_ATTRIBUTE_H_
#define TASK_INC_TASK_GAMEPLAY_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/* Events to excite Task Gameplay */
// task_gameplay_attribute.h
typedef enum {
    ST_GAME_IDLE,
    ST_GAME_GEN_SEQ,
    ST_GAME_SHOW_SEQ_ON,
    ST_GAME_SHOW_SEQ_OFF,
    ST_GAME_WAIT_INPUT,
    ST_GAME_CHECK_INPUT,
    ST_GAME_OVER
} task_gameplay_state_t;


typedef enum task_gameplay_ev {
	EV_GAME_IDLE,
	EV_GAME_NONE = 0,

	/* Eventos asociados a task_sensor */
	EV_GAME_BTN_RO,
	EV_GAME_BTN_VE,
	EV_GAME_BTN_AZ,
	EV_GAME_BTN_AM,
} task_gameplay_ev_t;


typedef struct
{
    uint32_t tick;
    task_gameplay_state_t state;
    task_gameplay_ev_t event;
    bool flag;

    bool  difficulty; 			/* 0 es normal, 1 es dificil */
    uint8_t  sequence[32];   	/* Secuencia máxima (ejemplo) */
    uint8_t  seq_length;     	/* Largo actual de la secuencia */
    uint8_t  seq_index;      	/* Índice al mostrar la secuencia */
    uint8_t  input_index;    	/* Índice mientras el jugador responde */
    bool     active;
    uint16_t score;
    bool     running;
    bool     finished;
    /* Manejo de tiempo y fases de LED */
    bool     led_on_phase;   /* true: LED encendido, false: pausa */
} task_gameplay_dta_t;

/********************** external data declaration ****************************/
extern task_gameplay_dta_t task_gameplay_dta;

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_GAMEPLAY_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
