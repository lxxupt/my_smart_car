#include "zf_common_headfile.h"
#include "atk_ms601m_uart.h"

static struct
{
    uint8_t buf[ATK_MS601M_UART_RX_FIFO_BUF_SIZE];  /* ���� */
    uint16_t size;                                  /* �����С */
    uint16_t reader;                                /* ��ָ�� */
    uint16_t writer;                                /* дָ�� */
} g_uart_rx_fifo;                                   /* UART����FIFO */

/**
 * @brief       ATK-MS601M UART����FIFOд������
 * @param       dat: ��д������
 *              len: ��д�����ݵĳ���
 * @retval      0: ����ִ�гɹ�
 *              1: FIFOʣ��ռ䲻��
 */
uint8_t atk_ms601m_uart_rx_fifo_write(uint8_t *dat, uint16_t len)
{
    uint16_t i;
    
    /* ������д��FIFO
     * ������FIFOд��ָ��
     */
    for (i=0; i<len; i++)
    {
        g_uart_rx_fifo.buf[g_uart_rx_fifo.writer] = dat[i];
        g_uart_rx_fifo.writer = (g_uart_rx_fifo.writer + 1) % g_uart_rx_fifo.size;
    }
    
    return 0;
}

/**
 * @brief       ATK-MS601M UART����FIFO��ȡ����
 * @param       dat: ��ȡ���ݴ��λ��
 *              len: ����ȡ���ݵĳ���
 * @retval      0: FIFO��������
 *              ����ֵ: ʵ�ʶ�ȡ�����ݳ���
 */
uint16_t atk_ms601m_uart_rx_fifo_read(uint8_t *dat, uint16_t len)
{
    uint16_t fifo_usage;
    uint16_t i;
    
    /* ��ȡFIFO��ʹ�ô�С */
    if (g_uart_rx_fifo.writer >= g_uart_rx_fifo.reader)
    {
        fifo_usage = g_uart_rx_fifo.writer - g_uart_rx_fifo.reader;
    }
    else
    {
        fifo_usage = g_uart_rx_fifo.size - g_uart_rx_fifo.reader + g_uart_rx_fifo.writer;
    }
    
    /* FIFO���������� */
    if (len > fifo_usage)
    {
        len = fifo_usage;
    }
    
    /* ��FIFO��ȡ����
     * ������FIFO��ȡָ��
     */
    for (i=0; i<len; i++)
    {
        dat[i] = g_uart_rx_fifo.buf[g_uart_rx_fifo.reader];
        g_uart_rx_fifo.reader = (g_uart_rx_fifo.reader + 1) % g_uart_rx_fifo.size;
    }
    
    return len;
}

/**
 * @brief       ATK-MS601M UART����FIFO���
 * @param       ��
 * @retval      ��
 */
void atk_ms601m_rx_fifo_flush(void)
{
    g_uart_rx_fifo.writer = g_uart_rx_fifo.reader;
}

/**
 * @brief       ATK-MS601M UART��������
 * @param       dat: �����͵�����
 *              len: ���������ݵĳ���
 * @retval      ��
 */
void atk_ms601m_uart_send(uint8_t *dat, uint8_t len)
{
	  uart_write_buffer(UART_8, dat, len);
}

/**
 * @brief       ATK-MS601M UART��ʼ��
 * @param       baudrate: UARTͨѶ������
 * @retval      ��
 */
void atk_ms601m_uart_init(uint32_t baudrate)
{
		uart_init(UART_8,baudrate, UART8_TX_D16, UART8_RX_D17);           
    uart_rx_interrupt(UART_8, 1);	
    g_uart_rx_fifo.size = ATK_MS601M_UART_RX_FIFO_BUF_SIZE;         /* UART����FIFO�����С */
    g_uart_rx_fifo.reader = 0;                                      /* UART����FIFO��ָ�� */
    g_uart_rx_fifo.writer = 0;                                      /* UART����FIFOдָ�� */
}

/**
 * @brief       ATK-MS601M UART�жϻص�����
 * @param       ��
 * @retval      ��
 */
void ATK_MS601M_UART_IRQHandler(void)
{
    uint8_t tmp;
	  uart_query_byte(UART_8,&tmp);
    atk_ms601m_uart_rx_fifo_write(&tmp, 1);                         /* ���յ������ݣ�д��UART����FIFO */
}
