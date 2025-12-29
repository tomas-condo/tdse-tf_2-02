#ifndef I2C_H_
#define I2C_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "stdint.h"
#include "main.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/
extern void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
extern void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
extern void EEPROM_PageErase (uint16_t page);

extern void EEPROM_Write_NUM (uint16_t page, uint16_t offset, float  fdata);
extern float EEPROM_Read_NUM (uint16_t page, uint16_t offset);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* I2C_H_ */

/********************** end of file ******************************************/
