#ifndef __ATM_MS601M_H
#define __ATM_MS601M_H

#include "atk_ms601m_uart.h"

/* ATK-MS601M UARTͨѶ֡������󳤶� */
#define ATK_MS601M_FRAME_DAT_MAX_SIZE       28

/* ATK-MS601M�����ϴ�֡ID */
#define ATK_MS601M_FRAME_ID_ATTITUDE        0x01    /* ��̬�� */
#define ATK_MS601M_FRAME_ID_QUAT            0x02    /* ��Ԫ�� */
#define ATK_MS601M_FRAME_ID_GYRO_ACCE       0x03    /* �����ǡ����ٶȼ� */
#define ATK_MS601M_FRAME_ID_PORT            0x06    /* �˿� */

/* ATK-MS601MӦ��֡ID */
#define ATK_MS601M_FRAME_ID_REG_SAVE        0x00    /* ��  W�����浱ǰ���õ�Flash */
#define ATK_MS601M_FRAME_ID_REG_SENCAL      0x01    /* ��  W�����ô�����У׼ */
#define ATK_MS601M_FRAME_ID_REG_SENSTA      0x02    /* ��R  ����ȡ������У׼״̬ */
#define ATK_MS601M_FRAME_ID_REG_GYROFSR     0x03    /* ��R/W���������������� */
#define ATK_MS601M_FRAME_ID_REG_ACCFSR      0x04    /* ��R/W�����ü��ٶȼ����� */
#define ATK_MS601M_FRAME_ID_REG_GYROBW      0x05    /* ��R/W�����������Ǵ��� */
#define ATK_MS601M_FRAME_ID_REG_ACCBW       0x06    /* ��R/W�����ü��ٶȼƴ��� */
#define ATK_MS601M_FRAME_ID_REG_BAUD        0x07    /* ��R/W������UARTͨѶ������ */
#define ATK_MS601M_FRAME_ID_REG_RETURNSET   0x08    /* ��R/W�����ûش����� */
#define ATK_MS601M_FRAME_ID_REG_RETURNSET2  0x09    /* ��R/W�����ûش�����2�������� */
#define ATK_MS601M_FRAME_ID_REG_RETURNRATE  0x0A    /* ��R/W�����ûش����� */
#define ATK_MS601M_FRAME_ID_REG_ALG         0x0B    /* ��R/W�������㷨 */
#define ATK_MS601M_FRAME_ID_REG_ASM         0x0C    /* ��R/W�����ð�װ���� */
#define ATK_MS601M_FRAME_ID_REG_GAUCAL      0x0D    /* ��R/W��������������У׼���� */
#define ATK_MS601M_FRAME_ID_REG_LEDOFF      0x0F    /* ��R/W������LED���� */
#define ATK_MS601M_FRAME_ID_REG_D0MODE      0x10    /* ��R/W�����ö˿�D0ģʽ */
#define ATK_MS601M_FRAME_ID_REG_D1MODE      0x11    /* ��R/W�����ö˿�D1ģʽ */
#define ATK_MS601M_FRAME_ID_REG_D2MODE      0x12    /* ��R/W�����ö˿�D2ģʽ */
#define ATK_MS601M_FRAME_ID_REG_D3MODE      0x13    /* ��R/W�����ö˿�D3ģʽ */
#define ATK_MS601M_FRAME_ID_REG_D1PULSE     0x16    /* ��R/W�����ö˿�D1 PWM�ߵ�ƽ���� */
#define ATK_MS601M_FRAME_ID_REG_D3PULSE     0x1A    /* ��R/W�����ö˿�D3 PWM�ߵ�ƽ���� */
#define ATK_MS601M_FRAME_ID_REG_D1PERIOD    0x1F    /* ��R/W�����ö˿�D1 PWM���� */
#define ATK_MS601M_FRAME_ID_REG_D3PERIOD    0x23    /* ��R/W�����ö˿�D3 PWM���� */
#define ATK_MS601M_FRAME_ID_REG_RESET       0x7F    /* ��  W���ָ�Ĭ������ */

/* ATK-MS601M֡���� */
#define ATK_MS601M_FRAME_ID_TYPE_UPLOAD     0       /* ATK-MS601M�����ϴ�֡ID */
#define ATK_MS601M_FRAME_ID_TYPE_ACK        1       /* ATK-MS601MӦ��֡ID */

/* ��̬�����ݽṹ�� */
typedef struct
{
    float roll;                                     /* ����ǣ���λ���� */
    float pitch;                                    /* �����ǣ���λ���� */
    float yaw;                                      /* ����ǣ���λ���� */
} atk_ms601m_attitude_data_t;

/* ��Ԫ�����ݽṹ�� */
typedef struct
{
    float q0;                                       /* Q0 */
    float q1;                                       /* Q1 */
    float q2;                                       /* Q2 */
    float q3;                                       /* Q3 */
} atk_ms601m_quaternion_data_t;

/* ���������ݽṹ�� */
typedef struct
{
    struct
    {
        int16_t x;                                  /* X��ԭʼ���� */
        int16_t y;                                  /* Y��ԭʼ���� */
        int16_t z;                                  /* Z��ԭʼ���� */
    } raw;
    float x;                                        /* X����ת���ʣ���λ��dps */
    float y;                                        /* Y����ת���ʣ���λ��dps */
    float z;                                        /* Z����ת���ʣ���λ��dps */
} atk_ms601m_gyro_data_t;

/* ���ٶȼ����ݽṹ�� */
typedef struct
{
    struct
    {
        int16_t x;                                  /* X��ԭʼ���� */
        int16_t y;                                  /* Y��ԭʼ���� */
        int16_t z;                                  /* Z��ԭʼ���� */
    } raw;
    float x;                                        /* X����ٶȣ���λ��G */
    float y;                                        /* Y����ٶȣ���λ��G */
    float z;                                        /* Z����ٶȣ���λ��G */
} atk_ms601m_accelerometer_data_t;

/* �˿����ݽṹ�� */
typedef struct
{
    uint16_t d0;                                    /* �˿�D0���� */
    uint16_t d1;                                    /* �˿�D1���� */
    uint16_t d2;                                    /* �˿�D2���� */
    uint16_t d3;                                    /* �˿�D3���� */
} atk_ms601m_port_data_t;

/* ATK-MS601M LED״̬ö�� */
typedef enum
{
    ATK_MS601M_LED_STATE_ON  = 0x00,                /* LED�ƹر� */
    ATK_MS601M_LED_STATE_OFF = 0x01,                /* LED�ƴ� */
} atk_ms601m_led_state_t;

/* ATK-MS601M�˿�ö�� */
typedef enum
{
    ATK_MS601M_PORT_D0 = 0x00,                      /* �˿�D0 */
    ATK_MS601M_PORT_D1 = 0x01,                      /* �˿�D1 */
    ATK_MS601M_PORT_D2 = 0x02,                      /* �˿�D2 */
    ATK_MS601M_PORT_D3 = 0x03,                      /* �˿�D3 */
} atk_ms601m_port_t;

/* ATK-MS601M�˿�ģʽö�� */
typedef enum
{
    ATK_MS601M_PORT_MODE_ANALOG_INPUT   = 0x00,     /* ģ������ */
    ATK_MS601M_PORT_MODE_INPUT          = 0x01,     /* �������� */
    ATK_MS601M_PORT_MODE_OUTPUT_HIGH    = 0x02,     /* ������ָߵ�ƽ */
    ATK_MS601M_PORT_MODE_OUTPUT_LOW     = 0x03,     /* ������ֵ͵�ƽ */
    ATK_MS601M_PORT_MODE_OUTPUT_PWM     = 0x04,     /* ���PWM */
} atk_ms601m_port_mode_t;

/* ������� */
#define ATK_MS601M_EOK      0                       /* û�д��� */
#define ATK_MS601M_ERROR    1                       /* ���� */
#define ATK_MS601M_EINVAL   2                       /* ���������� */
#define ATK_MS601M_ETIMEOUT 3                       /* ��ʱ���� */

/* �������� */
uint8_t atk_ms601m_read_reg_by_id(uint8_t id, uint8_t *dat, uint32_t timeout);                                                                      /* ͨ��֡ID��ȡATK-MS601M�Ĵ��� */
uint8_t atk_ms601m_write_reg_by_id(uint8_t id, uint8_t len, uint8_t *dat);                                                                          /* ͨ��֡IDд��ATK-MS601M�Ĵ��� */
uint8_t atk_ms601m_init(uint32_t baudrate);                                                                                                         /* ATK-MS601M��ʼ�� */
uint8_t atk_ms601m_get_attitude(atk_ms601m_attitude_data_t *attitude_dat, uint32_t timeout);                                                        /* ��ȡATK-MS601M��̬������ */
uint8_t atk_ms601m_get_quaternion(atk_ms601m_quaternion_data_t *quaternion_dat, uint32_t timeout);                                                  /* ��ȡATK-MS601M��Ԫ������ */
uint8_t atk_ms601m_get_gyro_accelerometer(atk_ms601m_gyro_data_t *gyro_dat, atk_ms601m_accelerometer_data_t *accelerometer_dat, uint32_t timeout);  /* ��ȡATK-MS601M�����ǡ����ٶȼ����� */
uint8_t atk_ms601m_get_port(atk_ms601m_port_data_t *port_dat, uint32_t timeout);                                                                    /* ��ȡATK-MS601M�˿����� */
uint8_t atk_ms601m_get_led_state(atk_ms601m_led_state_t *state, uint32_t timeout);                                                                  /* ��ȡATK-MS601M LED��״̬ */
uint8_t atk_ms601m_set_led_state(atk_ms601m_led_state_t state, uint32_t timeout);                                                                   /* ����ATK-MS601M LED��״̬ */
uint8_t atk_ms601m_get_port_mode(atk_ms601m_port_t port, atk_ms601m_port_mode_t *mode, uint32_t timeout);                                           /* ��ȡATK-MS601Mָ���˿�ģʽ */
uint8_t atk_ms601m_set_port_mode(atk_ms601m_port_t port, atk_ms601m_port_mode_t mode, uint32_t timeout);                                            /* ����ATK-MS601Mָ���˿�ģʽ */
uint8_t atk_ms601m_get_port_pwm_pulse(atk_ms601m_port_t port, uint16_t *pulse, uint32_t timeout);                                                   /* ��ȡATK-MS601Mָ���˿�PWM�ߵ�ƽ�Ŀ��� */
uint8_t atk_ms601m_set_port_pwm_pulse(atk_ms601m_port_t port, uint16_t pulse, uint32_t timeout);                                                    /* ����ATK-MS601Mָ���˿�PWM�ߵ�ƽ�Ŀ��� */
uint8_t atk_ms601m_get_port_pwm_period(atk_ms601m_port_t port, uint16_t *period, uint32_t timeout);                                                 /* ��ȡATK-MS601Mָ���˿�PWM���� */
uint8_t atk_ms601m_set_port_pwm_period(atk_ms601m_port_t port, uint16_t period, uint32_t timeout);                                                  /* ����ATK-MS601Mָ���˿�PWM���� */


#endif