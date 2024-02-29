#ifndef __ATK_MS601M_UART_H
#define __ATK_MS601M_UART_H
#include "zf_common_headfile.h"


/* UART����FIFO�����С */
#define ATK_MS601M_UART_RX_FIFO_BUF_SIZE        128

/* �������� */
uint8_t atk_ms601m_uart_rx_fifo_write(uint8_t *dat, uint16_t len);  /* ATK-MS601M UART����FIFOд������ */
uint16_t atk_ms601m_uart_rx_fifo_read(uint8_t *dat, uint16_t len);  /* ATK-MS601M UART����FIFO��ȡ���� */
void atk_ms601m_rx_fifo_flush(void);                                /* ATK-MS601M UART����FIFO��� */
void atk_ms601m_uart_send(uint8_t *dat, uint8_t len);               /* ATK-MS601M UART�������� */
void atk_ms601m_uart_init(uint32_t baudrate);                       /* ATK-MS601M UART��ʼ�� */
void ATK_MS601M_UART_IRQHandler(void);
#endif
