/*
 * Commands.h
 *
 *  Created on: 4 wrz 2022
 *      Author: Marcin
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_
#define LS_START_MEASURMENT_COMMAND                  "LS+START\n"
#define LS_START_MEASURMENT_COMMAND_NUMBER           0
#define LS_DEBUG_COMMUNICATION_COMMAND               "LS+DEBUG=COMMUNICATION\n"
#define LS_DEBUG_COMMUNICATION_COMMAND_NUMBER        1
#define LS_DEBUG_ALL_COMMAND                         "LS+DEBUG=ALL\n"
#define LS_DEBUG_ALL_COMMAND_NUMBER                  2
#define LS_DEBUG_MEASURMENT_COMMAND                  "LS+DEBUG=MEASURMENT\n"
#define LS_DEBUG_MEASURMENT_COMMAND_NUMBER           3
#define LS_DEBUG_GET_STATUS_AND_PARAM_COMMAND        "LS+DEBUG=GET_STATUS_AND_PARAM\n"
#define LS_DEBUG_GET_STATUS_AND_PARAM_COMMAND_NUMBER 4
#define LS_DEBUG_STOP_COMMAND                        "LS+DEBUG=NO\n"
#define LS_DEBUG_STOP_COMMAND_NUMBER                 5
#define LS_STATUS_COMMAND                            "LS\n"
#define LS_STATUS_COMMAND_NUMBER                     6
#define LS_RESET                                     "LS+RESET\n"
#define LS_RESET_NUMBER                              7

#endif /* INC_COMMANDS_H_ */
