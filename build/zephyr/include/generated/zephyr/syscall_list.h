/* auto-generated by gen_syscalls.py, don't edit */

#ifndef ZEPHYR_SYSCALL_LIST_H
#define ZEPHYR_SYSCALL_LIST_H

#define K_SYSCALL_DEVICE_DEINIT 0
#define K_SYSCALL_DEVICE_GET_BINDING 1
#define K_SYSCALL_DEVICE_GET_BY_DT_NODELABEL 2
#define K_SYSCALL_DEVICE_INIT 3
#define K_SYSCALL_DEVICE_IS_READY 4
#define K_SYSCALL_ENTROPY_GET_ENTROPY 5
#define K_SYSCALL_GPIO_GET_PENDING_INT 6
#define K_SYSCALL_GPIO_PIN_CONFIGURE 7
#define K_SYSCALL_GPIO_PIN_GET_CONFIG 8
#define K_SYSCALL_GPIO_PIN_INTERRUPT_CONFIGURE 9
#define K_SYSCALL_GPIO_PORT_CLEAR_BITS_RAW 10
#define K_SYSCALL_GPIO_PORT_GET_DIRECTION 11
#define K_SYSCALL_GPIO_PORT_GET_RAW 12
#define K_SYSCALL_GPIO_PORT_SET_BITS_RAW 13
#define K_SYSCALL_GPIO_PORT_SET_MASKED_RAW 14
#define K_SYSCALL_GPIO_PORT_TOGGLE_BITS 15
#define K_SYSCALL_HWINFO_CLEAR_RESET_CAUSE 16
#define K_SYSCALL_HWINFO_GET_DEVICE_EUI64 17
#define K_SYSCALL_HWINFO_GET_DEVICE_ID 18
#define K_SYSCALL_HWINFO_GET_RESET_CAUSE 19
#define K_SYSCALL_HWINFO_GET_SUPPORTED_RESET_CAUSE 20
#define K_SYSCALL_K_BUSY_WAIT 21
#define K_SYSCALL_K_CONDVAR_BROADCAST 22
#define K_SYSCALL_K_CONDVAR_INIT 23
#define K_SYSCALL_K_CONDVAR_SIGNAL 24
#define K_SYSCALL_K_CONDVAR_WAIT 25
#define K_SYSCALL_K_EVENT_CLEAR 26
#define K_SYSCALL_K_EVENT_INIT 27
#define K_SYSCALL_K_EVENT_POST 28
#define K_SYSCALL_K_EVENT_SET 29
#define K_SYSCALL_K_EVENT_SET_MASKED 30
#define K_SYSCALL_K_EVENT_WAIT 31
#define K_SYSCALL_K_EVENT_WAIT_ALL 32
#define K_SYSCALL_K_FLOAT_DISABLE 33
#define K_SYSCALL_K_FLOAT_ENABLE 34
#define K_SYSCALL_K_FUTEX_WAIT 35
#define K_SYSCALL_K_FUTEX_WAKE 36
#define K_SYSCALL_K_IS_PREEMPT_THREAD 37
#define K_SYSCALL_K_MSGQ_ALLOC_INIT 38
#define K_SYSCALL_K_MSGQ_GET 39
#define K_SYSCALL_K_MSGQ_GET_ATTRS 40
#define K_SYSCALL_K_MSGQ_NUM_FREE_GET 41
#define K_SYSCALL_K_MSGQ_NUM_USED_GET 42
#define K_SYSCALL_K_MSGQ_PEEK 43
#define K_SYSCALL_K_MSGQ_PEEK_AT 44
#define K_SYSCALL_K_MSGQ_PURGE 45
#define K_SYSCALL_K_MSGQ_PUT 46
#define K_SYSCALL_K_MUTEX_INIT 47
#define K_SYSCALL_K_MUTEX_LOCK 48
#define K_SYSCALL_K_MUTEX_UNLOCK 49
#define K_SYSCALL_K_OBJECT_ACCESS_GRANT 50
#define K_SYSCALL_K_OBJECT_ALLOC 51
#define K_SYSCALL_K_OBJECT_ALLOC_SIZE 52
#define K_SYSCALL_K_OBJECT_RELEASE 53
#define K_SYSCALL_K_PIPE_ALLOC_INIT 54
#define K_SYSCALL_K_PIPE_BUFFER_FLUSH 55
#define K_SYSCALL_K_PIPE_CLOSE 56
#define K_SYSCALL_K_PIPE_FLUSH 57
#define K_SYSCALL_K_PIPE_GET 58
#define K_SYSCALL_K_PIPE_INIT 59
#define K_SYSCALL_K_PIPE_PUT 60
#define K_SYSCALL_K_PIPE_READ 61
#define K_SYSCALL_K_PIPE_READ_AVAIL 62
#define K_SYSCALL_K_PIPE_RESET 63
#define K_SYSCALL_K_PIPE_WRITE 64
#define K_SYSCALL_K_PIPE_WRITE_AVAIL 65
#define K_SYSCALL_K_POLL 66
#define K_SYSCALL_K_POLL_SIGNAL_CHECK 67
#define K_SYSCALL_K_POLL_SIGNAL_INIT 68
#define K_SYSCALL_K_POLL_SIGNAL_RAISE 69
#define K_SYSCALL_K_POLL_SIGNAL_RESET 70
#define K_SYSCALL_K_QUEUE_ALLOC_APPEND 71
#define K_SYSCALL_K_QUEUE_ALLOC_PREPEND 72
#define K_SYSCALL_K_QUEUE_CANCEL_WAIT 73
#define K_SYSCALL_K_QUEUE_GET 74
#define K_SYSCALL_K_QUEUE_INIT 75
#define K_SYSCALL_K_QUEUE_IS_EMPTY 76
#define K_SYSCALL_K_QUEUE_PEEK_HEAD 77
#define K_SYSCALL_K_QUEUE_PEEK_TAIL 78
#define K_SYSCALL_K_RESCHEDULE 79
#define K_SYSCALL_K_SCHED_CURRENT_THREAD_QUERY 80
#define K_SYSCALL_K_SEM_COUNT_GET 81
#define K_SYSCALL_K_SEM_GIVE 82
#define K_SYSCALL_K_SEM_INIT 83
#define K_SYSCALL_K_SEM_RESET 84
#define K_SYSCALL_K_SEM_TAKE 85
#define K_SYSCALL_K_SLEEP 86
#define K_SYSCALL_K_STACK_ALLOC_INIT 87
#define K_SYSCALL_K_STACK_POP 88
#define K_SYSCALL_K_STACK_PUSH 89
#define K_SYSCALL_K_STR_OUT 90
#define K_SYSCALL_K_THREAD_ABORT 91
#define K_SYSCALL_K_THREAD_CREATE 92
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_GET 93
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_SET 94
#define K_SYSCALL_K_THREAD_DEADLINE_SET 95
#define K_SYSCALL_K_THREAD_JOIN 96
#define K_SYSCALL_K_THREAD_NAME_COPY 97
#define K_SYSCALL_K_THREAD_NAME_SET 98
#define K_SYSCALL_K_THREAD_PRIORITY_GET 99
#define K_SYSCALL_K_THREAD_PRIORITY_SET 100
#define K_SYSCALL_K_THREAD_RESUME 101
#define K_SYSCALL_K_THREAD_STACK_ALLOC 102
#define K_SYSCALL_K_THREAD_STACK_FREE 103
#define K_SYSCALL_K_THREAD_STACK_SPACE_GET 104
#define K_SYSCALL_K_THREAD_SUSPEND 105
#define K_SYSCALL_K_THREAD_TIMEOUT_EXPIRES_TICKS 106
#define K_SYSCALL_K_THREAD_TIMEOUT_REMAINING_TICKS 107
#define K_SYSCALL_K_TIMER_EXPIRES_TICKS 108
#define K_SYSCALL_K_TIMER_REMAINING_TICKS 109
#define K_SYSCALL_K_TIMER_START 110
#define K_SYSCALL_K_TIMER_STATUS_GET 111
#define K_SYSCALL_K_TIMER_STATUS_SYNC 112
#define K_SYSCALL_K_TIMER_STOP 113
#define K_SYSCALL_K_TIMER_USER_DATA_GET 114
#define K_SYSCALL_K_TIMER_USER_DATA_SET 115
#define K_SYSCALL_K_UPTIME_TICKS 116
#define K_SYSCALL_K_USLEEP 117
#define K_SYSCALL_K_WAKEUP 118
#define K_SYSCALL_K_YIELD 119
#define K_SYSCALL_LOG_BUFFERED_CNT 120
#define K_SYSCALL_LOG_FILTER_SET 121
#define K_SYSCALL_LOG_FRONTEND_FILTER_SET 122
#define K_SYSCALL_LOG_PANIC 123
#define K_SYSCALL_LOG_PROCESS 124
#define K_SYSCALL_RESET_LINE_ASSERT 125
#define K_SYSCALL_RESET_LINE_DEASSERT 126
#define K_SYSCALL_RESET_LINE_TOGGLE 127
#define K_SYSCALL_RESET_STATUS 128
#define K_SYSCALL_SYS_CLOCK_GETRTOFFSET 129
#define K_SYSCALL_SYS_CLOCK_HW_CYCLES_PER_SEC_RUNTIME_GET 130
#define K_SYSCALL_SYS_CLOCK_NANOSLEEP 131
#define K_SYSCALL_SYS_CLOCK_SETTIME 132
#define K_SYSCALL_SYS_CSRAND_GET 133
#define K_SYSCALL_SYS_RAND_GET 134
#define K_SYSCALL_UART_CONFIGURE 135
#define K_SYSCALL_UART_CONFIG_GET 136
#define K_SYSCALL_UART_DRV_CMD 137
#define K_SYSCALL_UART_ERR_CHECK 138
#define K_SYSCALL_UART_IRQ_ERR_DISABLE 139
#define K_SYSCALL_UART_IRQ_ERR_ENABLE 140
#define K_SYSCALL_UART_IRQ_IS_PENDING 141
#define K_SYSCALL_UART_IRQ_RX_DISABLE 142
#define K_SYSCALL_UART_IRQ_RX_ENABLE 143
#define K_SYSCALL_UART_IRQ_TX_DISABLE 144
#define K_SYSCALL_UART_IRQ_TX_ENABLE 145
#define K_SYSCALL_UART_IRQ_UPDATE 146
#define K_SYSCALL_UART_LINE_CTRL_GET 147
#define K_SYSCALL_UART_LINE_CTRL_SET 148
#define K_SYSCALL_UART_POLL_IN 149
#define K_SYSCALL_UART_POLL_IN_U16 150
#define K_SYSCALL_UART_POLL_OUT 151
#define K_SYSCALL_UART_POLL_OUT_U16 152
#define K_SYSCALL_UART_RX_DISABLE 153
#define K_SYSCALL_UART_RX_ENABLE 154
#define K_SYSCALL_UART_RX_ENABLE_U16 155
#define K_SYSCALL_UART_TX 156
#define K_SYSCALL_UART_TX_ABORT 157
#define K_SYSCALL_UART_TX_U16 158
#define K_SYSCALL_ZEPHYR_FPUTC 159
#define K_SYSCALL_ZEPHYR_FWRITE 160
#define K_SYSCALL_ZEPHYR_READ_STDIN 161
#define K_SYSCALL_ZEPHYR_WRITE_STDOUT 162
#define K_SYSCALL_Z_LOG_MSG_SIMPLE_CREATE_0 163
#define K_SYSCALL_Z_LOG_MSG_SIMPLE_CREATE_1 164
#define K_SYSCALL_Z_LOG_MSG_SIMPLE_CREATE_2 165
#define K_SYSCALL_Z_LOG_MSG_STATIC_CREATE 166
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_LOCK 167
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_UNLOCK 168
#define K_SYSCALL_BAD 169
#define K_SYSCALL_LIMIT 170


/* Following syscalls are not used in image */
#define K_SYSCALL_ADC_CHANNEL_SETUP 171
#define K_SYSCALL_ADC_READ 172
#define K_SYSCALL_ADC_READ_ASYNC 173
#define K_SYSCALL_ATOMIC_ADD 174
#define K_SYSCALL_ATOMIC_AND 175
#define K_SYSCALL_ATOMIC_CAS 176
#define K_SYSCALL_ATOMIC_NAND 177
#define K_SYSCALL_ATOMIC_OR 178
#define K_SYSCALL_ATOMIC_PTR_CAS 179
#define K_SYSCALL_ATOMIC_PTR_SET 180
#define K_SYSCALL_ATOMIC_SET 181
#define K_SYSCALL_ATOMIC_SUB 182
#define K_SYSCALL_ATOMIC_XOR 183
#define K_SYSCALL_AUXDISPLAY_BACKLIGHT_GET 184
#define K_SYSCALL_AUXDISPLAY_BACKLIGHT_SET 185
#define K_SYSCALL_AUXDISPLAY_BRIGHTNESS_GET 186
#define K_SYSCALL_AUXDISPLAY_BRIGHTNESS_SET 187
#define K_SYSCALL_AUXDISPLAY_CAPABILITIES_GET 188
#define K_SYSCALL_AUXDISPLAY_CLEAR 189
#define K_SYSCALL_AUXDISPLAY_CURSOR_POSITION_GET 190
#define K_SYSCALL_AUXDISPLAY_CURSOR_POSITION_SET 191
#define K_SYSCALL_AUXDISPLAY_CURSOR_SET_ENABLED 192
#define K_SYSCALL_AUXDISPLAY_CURSOR_SHIFT_SET 193
#define K_SYSCALL_AUXDISPLAY_CUSTOM_CHARACTER_SET 194
#define K_SYSCALL_AUXDISPLAY_CUSTOM_COMMAND 195
#define K_SYSCALL_AUXDISPLAY_DISPLAY_OFF 196
#define K_SYSCALL_AUXDISPLAY_DISPLAY_ON 197
#define K_SYSCALL_AUXDISPLAY_DISPLAY_POSITION_GET 198
#define K_SYSCALL_AUXDISPLAY_DISPLAY_POSITION_SET 199
#define K_SYSCALL_AUXDISPLAY_IS_BUSY 200
#define K_SYSCALL_AUXDISPLAY_POSITION_BLINKING_SET_ENABLED 201
#define K_SYSCALL_AUXDISPLAY_WRITE 202
#define K_SYSCALL_BBRAM_CHECK_INVALID 203
#define K_SYSCALL_BBRAM_CHECK_POWER 204
#define K_SYSCALL_BBRAM_CHECK_STANDBY_POWER 205
#define K_SYSCALL_BBRAM_GET_SIZE 206
#define K_SYSCALL_BBRAM_READ 207
#define K_SYSCALL_BBRAM_WRITE 208
#define K_SYSCALL_BC12_SET_RESULT_CB 209
#define K_SYSCALL_BC12_SET_ROLE 210
#define K_SYSCALL_CAN_ADD_RX_FILTER_MSGQ 211
#define K_SYSCALL_CAN_CALC_TIMING 212
#define K_SYSCALL_CAN_CALC_TIMING_DATA 213
#define K_SYSCALL_CAN_GET_BITRATE_MAX 214
#define K_SYSCALL_CAN_GET_BITRATE_MIN 215
#define K_SYSCALL_CAN_GET_CAPABILITIES 216
#define K_SYSCALL_CAN_GET_CORE_CLOCK 217
#define K_SYSCALL_CAN_GET_MAX_FILTERS 218
#define K_SYSCALL_CAN_GET_MODE 219
#define K_SYSCALL_CAN_GET_STATE 220
#define K_SYSCALL_CAN_GET_TIMING_DATA_MAX 221
#define K_SYSCALL_CAN_GET_TIMING_DATA_MIN 222
#define K_SYSCALL_CAN_GET_TIMING_MAX 223
#define K_SYSCALL_CAN_GET_TIMING_MIN 224
#define K_SYSCALL_CAN_GET_TRANSCEIVER 225
#define K_SYSCALL_CAN_RECOVER 226
#define K_SYSCALL_CAN_REMOVE_RX_FILTER 227
#define K_SYSCALL_CAN_SEND 228
#define K_SYSCALL_CAN_SET_BITRATE 229
#define K_SYSCALL_CAN_SET_BITRATE_DATA 230
#define K_SYSCALL_CAN_SET_MODE 231
#define K_SYSCALL_CAN_SET_TIMING 232
#define K_SYSCALL_CAN_SET_TIMING_DATA 233
#define K_SYSCALL_CAN_START 234
#define K_SYSCALL_CAN_STATS_GET_ACK_ERRORS 235
#define K_SYSCALL_CAN_STATS_GET_BIT0_ERRORS 236
#define K_SYSCALL_CAN_STATS_GET_BIT1_ERRORS 237
#define K_SYSCALL_CAN_STATS_GET_BIT_ERRORS 238
#define K_SYSCALL_CAN_STATS_GET_CRC_ERRORS 239
#define K_SYSCALL_CAN_STATS_GET_FORM_ERRORS 240
#define K_SYSCALL_CAN_STATS_GET_RX_OVERRUNS 241
#define K_SYSCALL_CAN_STATS_GET_STUFF_ERRORS 242
#define K_SYSCALL_CAN_STOP 243
#define K_SYSCALL_CHARGER_CHARGE_ENABLE 244
#define K_SYSCALL_CHARGER_GET_PROP 245
#define K_SYSCALL_CHARGER_SET_PROP 246
#define K_SYSCALL_COMPARATOR_GET_OUTPUT 247
#define K_SYSCALL_COMPARATOR_SET_TRIGGER 248
#define K_SYSCALL_COMPARATOR_TRIGGER_IS_PENDING 249
#define K_SYSCALL_COUNTER_CANCEL_CHANNEL_ALARM 250
#define K_SYSCALL_COUNTER_GET_FREQUENCY 251
#define K_SYSCALL_COUNTER_GET_GUARD_PERIOD 252
#define K_SYSCALL_COUNTER_GET_MAX_TOP_VALUE 253
#define K_SYSCALL_COUNTER_GET_NUM_OF_CHANNELS 254
#define K_SYSCALL_COUNTER_GET_PENDING_INT 255
#define K_SYSCALL_COUNTER_GET_TOP_VALUE 256
#define K_SYSCALL_COUNTER_GET_VALUE 257
#define K_SYSCALL_COUNTER_GET_VALUE_64 258
#define K_SYSCALL_COUNTER_IS_COUNTING_UP 259
#define K_SYSCALL_COUNTER_RESET 260
#define K_SYSCALL_COUNTER_SET_CHANNEL_ALARM 261
#define K_SYSCALL_COUNTER_SET_GUARD_PERIOD 262
#define K_SYSCALL_COUNTER_SET_TOP_VALUE 263
#define K_SYSCALL_COUNTER_START 264
#define K_SYSCALL_COUNTER_STOP 265
#define K_SYSCALL_COUNTER_TICKS_TO_US 266
#define K_SYSCALL_COUNTER_US_TO_TICKS 267
#define K_SYSCALL_DAC_CHANNEL_SETUP 268
#define K_SYSCALL_DAC_WRITE_VALUE 269
#define K_SYSCALL_DEVMUX_SELECT_GET 270
#define K_SYSCALL_DEVMUX_SELECT_SET 271
#define K_SYSCALL_DMA_CHAN_FILTER 272
#define K_SYSCALL_DMA_RELEASE_CHANNEL 273
#define K_SYSCALL_DMA_REQUEST_CHANNEL 274
#define K_SYSCALL_DMA_RESUME 275
#define K_SYSCALL_DMA_START 276
#define K_SYSCALL_DMA_STOP 277
#define K_SYSCALL_DMA_SUSPEND 278
#define K_SYSCALL_EEPROM_GET_SIZE 279
#define K_SYSCALL_EEPROM_READ 280
#define K_SYSCALL_EEPROM_WRITE 281
#define K_SYSCALL_EMUL_FUEL_GAUGE_IS_BATTERY_CUTOFF 282
#define K_SYSCALL_EMUL_FUEL_GAUGE_SET_BATTERY_CHARGING 283
#define K_SYSCALL_ESPI_CONFIG 284
#define K_SYSCALL_ESPI_FLASH_ERASE 285
#define K_SYSCALL_ESPI_GET_CHANNEL_STATUS 286
#define K_SYSCALL_ESPI_READ_FLASH 287
#define K_SYSCALL_ESPI_READ_LPC_REQUEST 288
#define K_SYSCALL_ESPI_READ_REQUEST 289
#define K_SYSCALL_ESPI_RECEIVE_OOB 290
#define K_SYSCALL_ESPI_RECEIVE_VWIRE 291
#define K_SYSCALL_ESPI_SAF_ACTIVATE 292
#define K_SYSCALL_ESPI_SAF_CONFIG 293
#define K_SYSCALL_ESPI_SAF_FLASH_ERASE 294
#define K_SYSCALL_ESPI_SAF_FLASH_READ 295
#define K_SYSCALL_ESPI_SAF_FLASH_UNSUCCESS 296
#define K_SYSCALL_ESPI_SAF_FLASH_WRITE 297
#define K_SYSCALL_ESPI_SAF_GET_CHANNEL_STATUS 298
#define K_SYSCALL_ESPI_SAF_SET_PROTECTION_REGIONS 299
#define K_SYSCALL_ESPI_SEND_OOB 300
#define K_SYSCALL_ESPI_SEND_VWIRE 301
#define K_SYSCALL_ESPI_WRITE_FLASH 302
#define K_SYSCALL_ESPI_WRITE_LPC_REQUEST 303
#define K_SYSCALL_ESPI_WRITE_REQUEST 304
#define K_SYSCALL_FLASH_COPY 305
#define K_SYSCALL_FLASH_ERASE 306
#define K_SYSCALL_FLASH_EX_OP 307
#define K_SYSCALL_FLASH_FILL 308
#define K_SYSCALL_FLASH_FLATTEN 309
#define K_SYSCALL_FLASH_GET_PAGE_COUNT 310
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_IDX 311
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_OFFS 312
#define K_SYSCALL_FLASH_GET_PARAMETERS 313
#define K_SYSCALL_FLASH_GET_SIZE 314
#define K_SYSCALL_FLASH_GET_WRITE_BLOCK_SIZE 315
#define K_SYSCALL_FLASH_READ 316
#define K_SYSCALL_FLASH_READ_JEDEC_ID 317
#define K_SYSCALL_FLASH_SFDP_READ 318
#define K_SYSCALL_FLASH_SIMULATOR_GET_MEMORY 319
#define K_SYSCALL_FLASH_WRITE 320
#define K_SYSCALL_FUEL_GAUGE_BATTERY_CUTOFF 321
#define K_SYSCALL_FUEL_GAUGE_GET_BUFFER_PROP 322
#define K_SYSCALL_FUEL_GAUGE_GET_PROP 323
#define K_SYSCALL_FUEL_GAUGE_GET_PROPS 324
#define K_SYSCALL_FUEL_GAUGE_SET_PROP 325
#define K_SYSCALL_FUEL_GAUGE_SET_PROPS 326
#define K_SYSCALL_GNSS_GET_ENABLED_SYSTEMS 327
#define K_SYSCALL_GNSS_GET_FIX_RATE 328
#define K_SYSCALL_GNSS_GET_LATEST_TIMEPULSE 329
#define K_SYSCALL_GNSS_GET_NAVIGATION_MODE 330
#define K_SYSCALL_GNSS_GET_SUPPORTED_SYSTEMS 331
#define K_SYSCALL_GNSS_SET_ENABLED_SYSTEMS 332
#define K_SYSCALL_GNSS_SET_FIX_RATE 333
#define K_SYSCALL_GNSS_SET_NAVIGATION_MODE 334
#define K_SYSCALL_HAPTICS_START_OUTPUT 335
#define K_SYSCALL_HAPTICS_STOP_OUTPUT 336
#define K_SYSCALL_HWSPINLOCK_GET_MAX_ID 337
#define K_SYSCALL_HWSPINLOCK_LOCK 338
#define K_SYSCALL_HWSPINLOCK_TRYLOCK 339
#define K_SYSCALL_HWSPINLOCK_UNLOCK 340
#define K_SYSCALL_I2C_CONFIGURE 341
#define K_SYSCALL_I2C_GET_CONFIG 342
#define K_SYSCALL_I2C_RECOVER_BUS 343
#define K_SYSCALL_I2C_TARGET_DRIVER_REGISTER 344
#define K_SYSCALL_I2C_TARGET_DRIVER_UNREGISTER 345
#define K_SYSCALL_I2C_TRANSFER 346
#define K_SYSCALL_I2S_BUF_READ 347
#define K_SYSCALL_I2S_BUF_WRITE 348
#define K_SYSCALL_I2S_CONFIGURE 349
#define K_SYSCALL_I2S_TRIGGER 350
#define K_SYSCALL_I3C_DO_CCC 351
#define K_SYSCALL_I3C_TRANSFER 352
#define K_SYSCALL_IPM_COMPLETE 353
#define K_SYSCALL_IPM_MAX_DATA_SIZE_GET 354
#define K_SYSCALL_IPM_MAX_ID_VAL_GET 355
#define K_SYSCALL_IPM_SEND 356
#define K_SYSCALL_IPM_SET_ENABLED 357
#define K_SYSCALL_IVSHMEM_ENABLE_INTERRUPTS 358
#define K_SYSCALL_IVSHMEM_GET_ID 359
#define K_SYSCALL_IVSHMEM_GET_MAX_PEERS 360
#define K_SYSCALL_IVSHMEM_GET_MEM 361
#define K_SYSCALL_IVSHMEM_GET_OUTPUT_MEM_SECTION 362
#define K_SYSCALL_IVSHMEM_GET_PROTOCOL 363
#define K_SYSCALL_IVSHMEM_GET_RW_MEM_SECTION 364
#define K_SYSCALL_IVSHMEM_GET_STATE 365
#define K_SYSCALL_IVSHMEM_GET_VECTORS 366
#define K_SYSCALL_IVSHMEM_INT_PEER 367
#define K_SYSCALL_IVSHMEM_REGISTER_HANDLER 368
#define K_SYSCALL_IVSHMEM_SET_STATE 369
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_IN_GET 370
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_OUT_GET 371
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_EVICTION_GET 372
#define K_SYSCALL_K_MEM_PAGING_STATS_GET 373
#define K_SYSCALL_K_MEM_PAGING_THREAD_STATS_GET 374
#define K_SYSCALL_LED_BLINK 375
#define K_SYSCALL_LED_GET_INFO 376
#define K_SYSCALL_LED_OFF 377
#define K_SYSCALL_LED_ON 378
#define K_SYSCALL_LED_SET_BRIGHTNESS 379
#define K_SYSCALL_LED_SET_CHANNEL 380
#define K_SYSCALL_LED_SET_COLOR 381
#define K_SYSCALL_LED_WRITE_CHANNELS 382
#define K_SYSCALL_LLEXT_GET_FN_TABLE 383
#define K_SYSCALL_MAXIM_DS3231_GET_SYNCPOINT 384
#define K_SYSCALL_MAXIM_DS3231_REQ_SYNCPOINT 385
#define K_SYSCALL_MBOX_MAX_CHANNELS_GET 386
#define K_SYSCALL_MBOX_MTU_GET 387
#define K_SYSCALL_MBOX_SEND 388
#define K_SYSCALL_MBOX_SET_ENABLED 389
#define K_SYSCALL_MDIO_BUS_DISABLE 390
#define K_SYSCALL_MDIO_BUS_ENABLE 391
#define K_SYSCALL_MDIO_READ 392
#define K_SYSCALL_MDIO_READ_C45 393
#define K_SYSCALL_MDIO_WRITE 394
#define K_SYSCALL_MDIO_WRITE_C45 395
#define K_SYSCALL_MSPI_CONFIG 396
#define K_SYSCALL_MSPI_DEV_CONFIG 397
#define K_SYSCALL_MSPI_GET_CHANNEL_STATUS 398
#define K_SYSCALL_MSPI_SCRAMBLE_CONFIG 399
#define K_SYSCALL_MSPI_TIMING_CONFIG 400
#define K_SYSCALL_MSPI_TRANSCEIVE 401
#define K_SYSCALL_MSPI_XIP_CONFIG 402
#define K_SYSCALL_NET_ADDR_NTOP 403
#define K_SYSCALL_NET_ADDR_PTON 404
#define K_SYSCALL_NET_ETH_GET_PTP_CLOCK_BY_INDEX 405
#define K_SYSCALL_NET_IF_GET_BY_INDEX 406
#define K_SYSCALL_NET_IF_IPV4_ADDR_ADD_BY_INDEX 407
#define K_SYSCALL_NET_IF_IPV4_ADDR_LOOKUP_BY_INDEX 408
#define K_SYSCALL_NET_IF_IPV4_ADDR_RM_BY_INDEX 409
#define K_SYSCALL_NET_IF_IPV4_SET_GW_BY_INDEX 410
#define K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_ADDR_BY_INDEX 411
#define K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_INDEX 412
#define K_SYSCALL_NET_IF_IPV6_ADDR_ADD_BY_INDEX 413
#define K_SYSCALL_NET_IF_IPV6_ADDR_LOOKUP_BY_INDEX 414
#define K_SYSCALL_NET_IF_IPV6_ADDR_RM_BY_INDEX 415
#define K_SYSCALL_NET_SOCKET_SERVICE_REGISTER 416
#define K_SYSCALL_NRF_QSPI_NOR_XIP_ENABLE 417
#define K_SYSCALL_PECI_CONFIG 418
#define K_SYSCALL_PECI_DISABLE 419
#define K_SYSCALL_PECI_ENABLE 420
#define K_SYSCALL_PECI_TRANSFER 421
#define K_SYSCALL_PS2_CONFIG 422
#define K_SYSCALL_PS2_DISABLE_CALLBACK 423
#define K_SYSCALL_PS2_ENABLE_CALLBACK 424
#define K_SYSCALL_PS2_READ 425
#define K_SYSCALL_PS2_WRITE 426
#define K_SYSCALL_PTP_CLOCK_GET 427
#define K_SYSCALL_PWM_CAPTURE_CYCLES 428
#define K_SYSCALL_PWM_DISABLE_CAPTURE 429
#define K_SYSCALL_PWM_ENABLE_CAPTURE 430
#define K_SYSCALL_PWM_GET_CYCLES_PER_SEC 431
#define K_SYSCALL_PWM_SET_CYCLES 432
#define K_SYSCALL_RENESAS_ELC_DISABLE 433
#define K_SYSCALL_RENESAS_ELC_ENABLE 434
#define K_SYSCALL_RENESAS_ELC_LINK_BREAK 435
#define K_SYSCALL_RENESAS_ELC_LINK_SET 436
#define K_SYSCALL_RENESAS_ELC_SOFTWARE_EVENT_GENERATE 437
#define K_SYSCALL_RETAINED_MEM_CLEAR 438
#define K_SYSCALL_RETAINED_MEM_READ 439
#define K_SYSCALL_RETAINED_MEM_SIZE 440
#define K_SYSCALL_RETAINED_MEM_WRITE 441
#define K_SYSCALL_RTC_ALARM_GET_SUPPORTED_FIELDS 442
#define K_SYSCALL_RTC_ALARM_GET_TIME 443
#define K_SYSCALL_RTC_ALARM_IS_PENDING 444
#define K_SYSCALL_RTC_ALARM_SET_TIME 445
#define K_SYSCALL_RTC_GET_CALIBRATION 446
#define K_SYSCALL_RTC_GET_TIME 447
#define K_SYSCALL_RTC_SET_CALIBRATION 448
#define K_SYSCALL_RTC_SET_TIME 449
#define K_SYSCALL_RTIO_CQE_COPY_OUT 450
#define K_SYSCALL_RTIO_CQE_GET_MEMPOOL_BUFFER 451
#define K_SYSCALL_RTIO_RELEASE_BUFFER 452
#define K_SYSCALL_RTIO_SQE_CANCEL 453
#define K_SYSCALL_RTIO_SQE_COPY_IN_GET_HANDLES 454
#define K_SYSCALL_RTIO_SQE_SIGNAL 455
#define K_SYSCALL_RTIO_SUBMIT 456
#define K_SYSCALL_SDHC_CARD_BUSY 457
#define K_SYSCALL_SDHC_CARD_PRESENT 458
#define K_SYSCALL_SDHC_DISABLE_INTERRUPT 459
#define K_SYSCALL_SDHC_ENABLE_INTERRUPT 460
#define K_SYSCALL_SDHC_EXECUTE_TUNING 461
#define K_SYSCALL_SDHC_GET_HOST_PROPS 462
#define K_SYSCALL_SDHC_HW_RESET 463
#define K_SYSCALL_SDHC_REQUEST 464
#define K_SYSCALL_SDHC_SET_IO 465
#define K_SYSCALL_SENSOR_ATTR_GET 466
#define K_SYSCALL_SENSOR_ATTR_SET 467
#define K_SYSCALL_SENSOR_CHANNEL_GET 468
#define K_SYSCALL_SENSOR_GET_DECODER 469
#define K_SYSCALL_SENSOR_RECONFIGURE_READ_IODEV 470
#define K_SYSCALL_SENSOR_SAMPLE_FETCH 471
#define K_SYSCALL_SENSOR_SAMPLE_FETCH_CHAN 472
#define K_SYSCALL_SENT_REGISTER_CALLBACK 473
#define K_SYSCALL_SENT_START_LISTENING 474
#define K_SYSCALL_SENT_STOP_LISTENING 475
#define K_SYSCALL_SIP_SUPERVISORY_CALL 476
#define K_SYSCALL_SIP_SVC_PLAT_ASYNC_RES_REQ 477
#define K_SYSCALL_SIP_SVC_PLAT_ASYNC_RES_RES 478
#define K_SYSCALL_SIP_SVC_PLAT_FORMAT_TRANS_ID 479
#define K_SYSCALL_SIP_SVC_PLAT_FREE_ASYNC_MEMORY 480
#define K_SYSCALL_SIP_SVC_PLAT_FUNC_ID_VALID 481
#define K_SYSCALL_SIP_SVC_PLAT_GET_ERROR_CODE 482
#define K_SYSCALL_SIP_SVC_PLAT_GET_TRANS_IDX 483
#define K_SYSCALL_SIP_SVC_PLAT_UPDATE_TRANS_ID 484
#define K_SYSCALL_SMBUS_BLOCK_PCALL 485
#define K_SYSCALL_SMBUS_BLOCK_READ 486
#define K_SYSCALL_SMBUS_BLOCK_WRITE 487
#define K_SYSCALL_SMBUS_BYTE_DATA_READ 488
#define K_SYSCALL_SMBUS_BYTE_DATA_WRITE 489
#define K_SYSCALL_SMBUS_BYTE_READ 490
#define K_SYSCALL_SMBUS_BYTE_WRITE 491
#define K_SYSCALL_SMBUS_CONFIGURE 492
#define K_SYSCALL_SMBUS_GET_CONFIG 493
#define K_SYSCALL_SMBUS_HOST_NOTIFY_REMOVE_CB 494
#define K_SYSCALL_SMBUS_PCALL 495
#define K_SYSCALL_SMBUS_QUICK 496
#define K_SYSCALL_SMBUS_SMBALERT_REMOVE_CB 497
#define K_SYSCALL_SMBUS_WORD_DATA_READ 498
#define K_SYSCALL_SMBUS_WORD_DATA_WRITE 499
#define K_SYSCALL_SPI_RELEASE 500
#define K_SYSCALL_SPI_TRANSCEIVE 501
#define K_SYSCALL_STEPPER_DISABLE 502
#define K_SYSCALL_STEPPER_ENABLE 503
#define K_SYSCALL_STEPPER_GET_ACTUAL_POSITION 504
#define K_SYSCALL_STEPPER_GET_MICRO_STEP_RES 505
#define K_SYSCALL_STEPPER_IS_MOVING 506
#define K_SYSCALL_STEPPER_MOVE_BY 507
#define K_SYSCALL_STEPPER_MOVE_TO 508
#define K_SYSCALL_STEPPER_RUN 509
#define K_SYSCALL_STEPPER_SET_EVENT_CALLBACK 510
#define K_SYSCALL_STEPPER_SET_MICROSTEP_INTERVAL 511
#define K_SYSCALL_STEPPER_SET_MICRO_STEP_RES 512
#define K_SYSCALL_STEPPER_SET_REFERENCE_POSITION 513
#define K_SYSCALL_STEPPER_STOP 514
#define K_SYSCALL_SYSCON_GET_BASE 515
#define K_SYSCALL_SYSCON_GET_SIZE 516
#define K_SYSCALL_SYSCON_READ_REG 517
#define K_SYSCALL_SYSCON_WRITE_REG 518
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_AND_INVD_RANGE 519
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_RANGE 520
#define K_SYSCALL_SYS_CACHE_DATA_INVD_RANGE 521
#define K_SYSCALL_TEE_CANCEL 522
#define K_SYSCALL_TEE_CLOSE_SESSION 523
#define K_SYSCALL_TEE_GET_VERSION 524
#define K_SYSCALL_TEE_INVOKE_FUNC 525
#define K_SYSCALL_TEE_OPEN_SESSION 526
#define K_SYSCALL_TEE_SHM_ALLOC 527
#define K_SYSCALL_TEE_SHM_FREE 528
#define K_SYSCALL_TEE_SHM_REGISTER 529
#define K_SYSCALL_TEE_SHM_UNREGISTER 530
#define K_SYSCALL_TEE_SUPPL_RECV 531
#define K_SYSCALL_TEE_SUPPL_SEND 532
#define K_SYSCALL_TGPIO_PIN_CONFIG_EXT_TIMESTAMP 533
#define K_SYSCALL_TGPIO_PIN_DISABLE 534
#define K_SYSCALL_TGPIO_PIN_PERIODIC_OUTPUT 535
#define K_SYSCALL_TGPIO_PIN_READ_TS_EC 536
#define K_SYSCALL_TGPIO_PORT_GET_CYCLES_PER_SECOND 537
#define K_SYSCALL_TGPIO_PORT_GET_TIME 538
#define K_SYSCALL_UPDATEHUB_AUTOHANDLER 539
#define K_SYSCALL_UPDATEHUB_CONFIRM 540
#define K_SYSCALL_UPDATEHUB_PROBE 541
#define K_SYSCALL_UPDATEHUB_REBOOT 542
#define K_SYSCALL_UPDATEHUB_REPORT_ERROR 543
#define K_SYSCALL_UPDATEHUB_UPDATE 544
#define K_SYSCALL_USER_FAULT 545
#define K_SYSCALL_W1_CHANGE_BUS_LOCK 546
#define K_SYSCALL_W1_CONFIGURE 547
#define K_SYSCALL_W1_GET_SLAVE_COUNT 548
#define K_SYSCALL_W1_READ_BIT 549
#define K_SYSCALL_W1_READ_BLOCK 550
#define K_SYSCALL_W1_READ_BYTE 551
#define K_SYSCALL_W1_RESET_BUS 552
#define K_SYSCALL_W1_SEARCH_BUS 553
#define K_SYSCALL_W1_WRITE_BIT 554
#define K_SYSCALL_W1_WRITE_BLOCK 555
#define K_SYSCALL_W1_WRITE_BYTE 556
#define K_SYSCALL_WDT_DISABLE 557
#define K_SYSCALL_WDT_FEED 558
#define K_SYSCALL_WDT_SETUP 559
#define K_SYSCALL_XTENSA_USER_FAULT 560
#define K_SYSCALL_ZSOCK_ACCEPT 561
#define K_SYSCALL_ZSOCK_BIND 562
#define K_SYSCALL_ZSOCK_CLOSE 563
#define K_SYSCALL_ZSOCK_CONNECT 564
#define K_SYSCALL_ZSOCK_FCNTL_IMPL 565
#define K_SYSCALL_ZSOCK_GETHOSTNAME 566
#define K_SYSCALL_ZSOCK_GETPEERNAME 567
#define K_SYSCALL_ZSOCK_GETSOCKNAME 568
#define K_SYSCALL_ZSOCK_GETSOCKOPT 569
#define K_SYSCALL_ZSOCK_GET_CONTEXT_OBJECT 570
#define K_SYSCALL_ZSOCK_INET_PTON 571
#define K_SYSCALL_ZSOCK_IOCTL_IMPL 572
#define K_SYSCALL_ZSOCK_LISTEN 573
#define K_SYSCALL_ZSOCK_RECVFROM 574
#define K_SYSCALL_ZSOCK_RECVMSG 575
#define K_SYSCALL_ZSOCK_SENDMSG 576
#define K_SYSCALL_ZSOCK_SENDTO 577
#define K_SYSCALL_ZSOCK_SETSOCKOPT 578
#define K_SYSCALL_ZSOCK_SHUTDOWN 579
#define K_SYSCALL_ZSOCK_SOCKET 580
#define K_SYSCALL_ZSOCK_SOCKETPAIR 581
#define K_SYSCALL_ZVFS_POLL 582
#define K_SYSCALL_ZVFS_SELECT 583
#define K_SYSCALL_Z_ERRNO 584
#define K_SYSCALL_Z_ZSOCK_GETADDRINFO_INTERNAL 585


#ifndef _ASMLANGUAGE

#include <stdarg.h>
#include <stdint.h>

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_SYSCALL_LIST_H */
