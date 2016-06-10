/*
 * tizen-radio.h
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __TIZEN_RADIO_HAL_H__
#define __TIZEN_RADIO_HAL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum radio_return {
	RADIO_ERROR_NONE,
	RADIO_ERROR_INVALID_PARAMETER,
	RADIO_ERROR_PERMITSSION_DENIED,
	RADIO_ERROR_DEVICE_OPEN,
	RADIO_ERROR_DEVICE_NOT_SUPPORTED,
	RADIO_ERROR_INTERNAL,
	RADIO_ERROR_UNKNOWN
} radio_return_t;

typedef enum radio_seek_direction_type {
	RADIO_SEEK_UP,					/**< Seek upward */
	RADIO_SEEK_DOWN,				/**< Seek downward */
	RADIO_SEEK_NUM,				/**< Number of seeking direction */
} radio_seek_direction_type_t;

typedef struct radio_interface {
	/* create & destroy */
	radio_return_t (*init)(void **radio_hanle);
	radio_return_t (*deinit)(void *radio_handle);
	radio_return_t (*open_device)(void *radio_handle);
	radio_return_t (*close_device)(void *radio_handle);
	radio_return_t (*prepare_device)(void *radio_handle);
	radio_return_t (*unprepare_device)(void *radio_handle);
	radio_return_t (*get_state)(void *radio_handle, uint32_t *state);
	radio_return_t (*seek)(void *radio_handle, radio_seek_direction_type_t direction);
	radio_return_t (*get_frequency)(void *radio_handle, uint32_t *frequency);
	radio_return_t (*set_frequency)(void *radio_handle, uint32_t frequency);
	radio_return_t (*scan_start)(void *radio_handle);
	radio_return_t (*scan_stop)(void *radio_handle);
	radio_return_t (*mute)(void *radio_handle);
	radio_return_t (*unmute)(void *radio_handle);
	radio_return_t (*get_volume)(void *radio_handle, uint32_t *volume);
	radio_return_t (*set_volume)(void *radio_handle, uint32_t volume);
	radio_return_t (*get_signal_strength)(void *radio_handle, uint32_t *strength);
	radio_return_t (*set_band_range)(void *radio_handle, uint32_t rangelow, uint32_t rangehigh);
} radio_interface_t;

radio_return_t radio_init(void **radio_hanle);
radio_return_t radio_deinit(void *radio_handle);
radio_return_t radio_open_device(void *radio_handle);
radio_return_t radio_close_device(void *radio_handle);
radio_return_t radio_prepare_device(void *radio_handle);
radio_return_t radio_unprepare_device(void *radio_handle);
radio_return_t radio_get_state(void *radio_handle, uint32_t *state);
radio_return_t radio_seek(void *radio_handle, radio_seek_direction_type_t direction);
radio_return_t radio_get_frequency(void *radio_handle, uint32_t *frequency);
radio_return_t radio_set_frequency(void *radio_handle, uint32_t frequency);
radio_return_t radio_scan_start(void *radio_handle);
radio_return_t radio_scan_stop(void *radio_handle);
radio_return_t radio_mute(void *radio_handle);
radio_return_t radio_unmute(void *radio_handle);
radio_return_t radio_get_volume(void *radio_handle, uint32_t *volume);
radio_return_t radio_set_volume(void *radio_handle, uint32_t volume);
radio_return_t radio_get_signal_strength(void *radio_handle, uint32_t *strength);
radio_return_t radio_set_band_range(void *radio_handle, uint32_t rangelow, uint32_t rangehigh);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_RADIO_HAL_H__ */

