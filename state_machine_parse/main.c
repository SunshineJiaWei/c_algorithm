#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



/*
    串口状态机解析函数
    | head | length | payload | crc |
    | 2    | 1      | n       | 1   |
*/

typedef enum
{
    UART_STAGE_HEAD,
    UART_STAGE_LEN,
    UART_STAGE_PAYLOAD,
    UART_STAGE_CRC
} stage_t;

typedef struct
{
    uint8_t len;
    uint8_t temp_buf[16];
} rx_t;


#define FRAME_MAX_LEN 256
typedef struct
{
    uint8_t len;
    uint8_t idx;
    uint8_t payload[FRAME_MAX_LEN];
    uint8_t crc8;
} frame_t;

typedef struct 
{
    stage_t stage;
    rx_t rx;
    frame_t frame;
} uart_ctrl_t;

static uart_ctrl_t uart_ctrl;
static bool full_pkt;

void uart_ctrl_reset(void)
{
    uart_ctrl.stage = UART_STAGE_HEAD;
    uart_ctrl.rx.len = 0;
    uart_ctrl.frame.len = 0;
    uart_ctrl.frame.idx = 0;
}

uint8_t crc8_calc(uint8_t *data, uint8_t len, uint8_t crc)
{
    // crc运算校验值
    return crc;
}

bool uart_data_verify(frame_t* frame)
{
    uint8_t ccrc8 = crc8_calc(frame->payload, frame->len, frame->crc8);
    return (frame->crc8 == ccrc8);
}

void uart_rx_byte_handler(uint8_t byte)
{
    uart_ctrl.rx.temp_buf[uart_ctrl.rx.len++] = byte;
    switch(uart_ctrl.stage)
    {
        case UART_STAGE_HEAD:
        {
            if (uart_ctrl.rx.len == 2)
            {
                if (uart_ctrl.rx.temp_buf[0] == 0xAA && uart_ctrl.rx.temp_buf[1] == 0x55)
                {
                    uart_ctrl.stage = UART_STAGE_LEN;
                    uart_ctrl.rx.len = 0;
                    printf("recv head %x %x\n", uart_ctrl.rx.temp_buf[0], uart_ctrl.rx.temp_buf[1]);
                }
                else
                {
                    uart_ctrl_reset();
                }
            }
            break;
        }
        case UART_STAGE_LEN:
        {
            uint8_t len = uart_ctrl.rx.temp_buf[0];
            if (len <= FRAME_MAX_LEN)
            {
                uart_ctrl.frame.len = len;
                uart_ctrl.stage = UART_STAGE_PAYLOAD;
                uart_ctrl.rx.len = 0;
                printf("recv len %x\n", uart_ctrl.rx.temp_buf[0]);
            }
            
            break;
        }
        case UART_STAGE_PAYLOAD:
        {
            uart_ctrl.frame.payload[uart_ctrl.frame.idx++] = uart_ctrl.rx.temp_buf[0];
            uart_ctrl.rx.len = 0;
            if (uart_ctrl.frame.idx == uart_ctrl.frame.len)
            {
                uart_ctrl.stage = UART_STAGE_CRC;
                uart_ctrl.frame.idx = 0;
                printf("recv data\n");
            }
            break;
        }
        case UART_STAGE_CRC:
        {
            uart_ctrl.frame.crc8 = uart_ctrl.rx.temp_buf[0];
            printf("recv crc8 %x\n", uart_ctrl.rx.temp_buf[0]);
            if (uart_data_verify(&uart_ctrl.frame))
            {
                full_pkt = true;
                printf("verify success\n");
            }
            else
            {
                uart_ctrl_reset();
            }
            break;
        }
        default:
        {
            uart_ctrl_reset();
            break;
        }
    }
}


void main()
{
    uint8_t data[] = { 0xAA, 0x55, 0x05, 0x01, 0x41, 0x01, 0x2C, 0x02, 0x67};
    while (1)
    {
        for (uint8_t i = 0; i < sizeof(data); i++)
        {
            uart_rx_byte_handler(data[i]);
        }
        if (full_pkt)
        {
            // 一帧数据接收完成，处理数据
            printf("recv full packet success\n");
            full_pkt = false;
            uart_ctrl_reset();
            break;
        }
    }
}