/*
 * nordic.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Ravi
 */

#ifndef SOURCE_NORDIC_H_
#define SOURCE_NORDIC_H_

#include<stdint.h>



/* Instructions  */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX_FIFO 0xE1
#define FLUSH_RX_FIFO 0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

/* Memory Map */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATE       0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

/* Bits  */
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define PLL_LOCK    4
#define RF_DR       3
#define RF_PWR      6
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0
#define DPL_P5	    5
#define DPL_P4	    4
#define DPL_P3	    3
#define DPL_P2	    2
#define DPL_P1	    1
#define DPL_P0	    0
#define EN_DPL	    2
#define EN_ACK_PAY  1
#define EN_DYN_ACK  0


/********************************************************************************
@brief:Read the register and return the value

Read the register and return the value
@param:uit8_t register
@return:int8_t
********************************************************************************/
uint8_t nrf_read_register(uint8_t);


/********************************************************************************
@brief:Write to the given register with the data

Write to the given register with the data
@param:uit8_t register,and the value to be written
@return:none
********************************************************************************/
void nrf_write_register(uint8_t,uint8_t);


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
void nrf_write_config(uint8_t);


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
void nrf_write_rf_setup(uint8_t);


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
void nrf_write_rf_ch(uint8_t);


/********************************************************************************
@brief:Reads the 5bytes of the TX_ADDR register

Reads the 5bytes of the TX_ADDR register
@param:pointer to address
@return:none
********************************************************************************/
void nrf_read_TX_ADDR(uint8_t*);


/********************************************************************************
@brief:Writes the 5byte TX_ADDR register

Writes the 5byte TX_ADDR register
@param:pointer to tx address
@return:none
********************************************************************************/
void nrf_write_TX_ADDR(uint8_t*);


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
