/*
 * nordic.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Ravi
 */

#ifndef SOURCE_NORDIC_H_
#define SOURCE_NORDIC_H_

/********************************************************************************
@brief:Read the register and return the value

Read the register and return the value
@param:uit8_t register
@return:int8_t
********************************************************************************/
int8_t nrf_read_register(uint8_tregister);


/********************************************************************************
@brief:Write to the given register with the data

Write to the given register with the data
@param:uit8_t register,and the value to be written
@return:none
********************************************************************************/
void nrf_write_register(uint8_t register,uint8_t value);


/********************************************************************************
@brief:Reads the STATUS register

Reads the STATUS register
@param:none
@return:none
********************************************************************************/
uint8_t nrf_read_status();


/********************************************************************************
@brief:Write to CONFIG register

Write to CONFIG register
@param:config to be written
@return:none
********************************************************************************/
void nrf_write_config(uint8_tconfig);


/********************************************************************************
@brief:Read the CONFIG register

Read the CONFIG register
@param:none
@return:none
********************************************************************************/
uint8_t nrf_read_config();


/********************************************************************************
@brief:Reads RF_SETUP register

Reads RF_SETUP register
@param:none
@return:none
********************************************************************************/
uint8_t nrf_read_rf_setup();

/********************************************************************************
@brief:Writes to the RF_SETUP register

Writes to the RF_SETUP register
@param:config to be written
@return:none
********************************************************************************/
void nrf_write_rf_setup(uint8_tconfig);


/********************************************************************************
@brief:Reads RF_CH register

Reads RF_CH register
@param:none
@return:none
********************************************************************************/
uint8_t nrf_read_rf_ch();


/********************************************************************************
@brief:Writes to the RF_CH register

Writes to the RF_CH register
@param:channel
@return:none
********************************************************************************/
void nrf_write_rf_ch(uint8_tchannel);


/********************************************************************************
@brief:Reads the 5bytes of the TX_ADDR register

Reads the 5bytes of the TX_ADDR register
@param:pointer to address
@return:none
********************************************************************************/
void nrf_read_TX_ADDR(uint8_t* address);


/********************************************************************************
@brief:Writes the 5byte TX_ADDR register

Writes the 5byte TX_ADDR register
@param:pointer to tx address
@return:none
********************************************************************************/
void nrf_write_TX_ADDR(uint8_t* tx_addr);


/********************************************************************************
@brief:Reads FIFO_STATUS register

Reads FIFO_STATUS register
@param:none
@return:none
********************************************************************************/
uint8_t nrf_read_fifo_status();


/********************************************************************************
@brief:Sends the command FLUSH_TX

Sends the command FLUSH_TX
@param:none
@return:none
********************************************************************************/
void nrf_flush_tx_fifo();


/********************************************************************************
@brief:Sends the command FLUSH_R

Sends the command FLUSH_R
@param:config to be written
@return:none
********************************************************************************/
void nrf_flush_rx_fifo();



#endif /* SOURCE_NORDIC_H_ */
