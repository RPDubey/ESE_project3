/********************************************************************************
@file:nordic.c
@brief:function declarations for nordic library

This file declares functions for nordic library
@author:Ravi Dubey
@date:12/06/2017
********************************************************************************/


int8_t nrf_read_register(uint8_tregister);


void nrf_write_register(uint8_t register,uint8_t value);


uint8_t nrf_read_status();


void nrf_write_config(uint8_tconfig);


uint8_t nrf_read_config();


uint8_t nrf_read_rf_setup();

void nrf_write_rf_setup(uint8_tconfig);


uint8_t nrf_read_rf_ch();


void nrf_write_rf_ch(uint8_tchannel);


void nrf_read_TX_ADDR(uint8_t* address);


void nrf_write_TX_ADDR(uint8_t* tx_addr);


uint8_t nrf_read_fifo_status();


void nrf_flush_tx_fifo();


void nrf_flush_rx_fifo();


