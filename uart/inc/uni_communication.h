/**************************************************************************
 * Copyright (C) 2017-2017  Junlon2006
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **************************************************************************
 *
 * Description : uni_communication.h
 * Author      : junlon2006@163.com
 * Date        : 2019.12.27
 *
 **************************************************************************/
#ifndef UTILS_UART_INC_UNI_COMMUNICATION_H_
#define UTILS_UART_INC_UNI_COMMUNICATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#define uni_bool            int

typedef unsigned short      CommCmd;
typedef unsigned short      CommPayloadLen;
typedef unsigned short      CommType;
typedef int                 (*CommWriteHandler)(char *buf, int len);

#define UNI_COMM_TYPE_BASE  (0)
#define UNI_CUSTOMER_TYPE   (UNI_COMM_TYPE_BASE + 1)
#define PACKED              __attribute__ ((packed))

typedef struct {
  CommCmd        cmd; /* air condition ctrl cmd such as power_on, power_off */
  CommPayloadLen payload_len; /* parameter length of command */
  char           payload[0];  /* parameter of command */
} PACKED CommPacket;

typedef struct {
  uni_bool need_acked;   /* set true means this packet need acked */
  int      timeout_msec; /* timeout for ack */
} CommAttribute;

typedef void (*RecvCommPacketHandler)(CommPacket *packet);

/**
 * @brief communication protocol init
 * @param write_handler the write handler, such as UartWrite int uni_uart.h
 * @param Recv_handler when uart data disassemble as communication protocol frame,
          the frame will be translate to struct CommPacket,
          then the CommPacket will callback to user
 * @return 0 means success, -1 means failed
 */
int CommProtocolInit(CommWriteHandler write_handler,
                     RecvCommPacketHandler Recv_handler);

/**
 * @brief communication protocol finalize
 * @param void
 * @return void
 */
void CommProtocolFinal(void);

/**
 * @brief send one packet(communication protocol frame format)
 * @param type customer type, 0 means Unisound
 * @param cmd command type, should define as enum (such as power_on、power_off)
 * @param payload the payload of cmd, can set as NULL
 * @param payload_len the payload length
 * @param attribute the attribute for this packet, such as packet need ACK
 * @return 0 means success, other means failed
 */
int CommProtocolPacketAssembleAndSend(CommType type, CommCmd cmd,
                                      char *payload,
                                      CommPayloadLen payload_len,
                                      CommAttribute *attribute);

/**
 * @brief receive orignial uart data
 * @param buf the uart data buffer pointer
 * @param len the uart data length
 * @return void
 */
void CommProtocolReceiveUartData(char *buf, int len);

#ifdef __cplusplus
}
#endif
#endif  // UTILS_UART_INC_UNI_COMMUNICATION_H_
