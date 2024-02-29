#ifndef __ATK_MS601M_UART_H
#define __ATK_MS601M_UART_H
#include "zf_common_headfile.h"


/* UART接收FIFO缓冲大小 */
#define ATK_MS601M_UART_RX_FIFO_BUF_SIZE        128

/* 操作函数 */
uint8_t atk_ms601m_uart_rx_fifo_write(uint8_t *dat, uint16_t len);  /* ATK-MS601M UART接收FIFO写入数据 */
uint16_t atk_ms601m_uart_rx_fifo_read(uint8_t *dat, uint16_t len);  /* ATK-MS601M UART接收FIFO读取数据 */
void atk_ms601m_rx_fifo_flush(void);                                /* ATK-MS601M UART接收FIFO清空 */
void atk_ms601m_uart_send(uint8_t *dat, uint8_t len);               /* ATK-MS601M UART发送数据 */
void atk_ms601m_uart_init(uint32_t baudrate);                       /* ATK-MS601M UART初始化 */
void ATK_MS601M_UART_IRQHandler(void);
#endif
