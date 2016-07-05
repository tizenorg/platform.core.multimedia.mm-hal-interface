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

/**
 * @file tizen-radio.h
 * @brief This file contains the Tizen radio HAL API, related structures and enumerations.
 * @since_tizen 3.0
 */

/**
 * @addtogroup TIZEN_RADIO_HAL_MODULE
 * @{
 */

/**
 * @brief Enumeration for the radio error.
 * @since_tizen 3.0
 */
typedef enum radio_error {
	RADIO_ERROR_NONE,
	RADIO_ERROR_INVALID_PARAMETER,
	RADIO_ERROR_INVALID_STATE,
	RADIO_ERROR_INVALID_OPERATION,
	RADIO_ERROR_PERMISSION_DENIED,
	RADIO_ERROR_NOT_SUPPORTED,
	RADIO_ERROR_OUT_OF_MEMORY,
	RADIO_ERROR_DEVICE_NOT_PREPARED,
	RADIO_ERROR_DEVICE_NOT_OPENED,
	RADIO_ERROR_DEVICE_NOT_FOUND,
	RADIO_ERROR_DEVICE_NOT_SUPPORTED,
	RADIO_ERROR_INTERNAL,
	RADIO_ERROR_UNKNOWN
} radio_error_t;

/**
 * @brief Enumeration for the radio seek direction.
 * @since_tizen 3.0
 */
typedef enum radio_seek_direction_type {
	RADIO_SEEK_DIRECTION_UP,	/**< Seek upward */
	RADIO_SEEK_DIRECTION_DOWN	/**< Seek downward */
} radio_seek_direction_type_t;

typedef struct radio_interface {
	/* create & destroy */
	radio_error_t (*init)(void **radio_hanle);
	radio_error_t (*deinit)(void *radio_handle);
	radio_error_t (*prepare)(void *radio_handle);
	radio_error_t (*unprepare)(void *radio_handle);
	radio_error_t (*open)(void *radio_handle);
	radio_error_t (*close)(void *radio_handle);
	radio_error_t (*start)(void *radio_handle);
	radio_error_t (*stop)(void *radio_handle);
	radio_error_t (*seek)(void *radio_handle, radio_seek_direction_type_t direction);
	radio_error_t (*get_frequency)(void *radio_handle, uint32_t *frequency);
	radio_error_t (*set_frequency)(void *radio_handle, uint32_t frequency);
	radio_error_t (*mute)(void *radio_handle);
	radio_error_t (*unmute)(void *radio_handle);
	radio_error_t (*get_signal_strength)(void *radio_handle, uint32_t *strength);
} radio_interface_t;

/**
 * @brief Initializes new handle of radio HAL.
 * @since_tizen 3.0
 * @param[out] radio_handle A newly returned handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_OUT_OF_MEMORY Out of memory
 * @see radio_deinit()
 */
radio_error_t radio_init(void **radio_handle);

/**
 * @brief Deinitializes handle of camera HAL.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @see radio_init()
 */
radio_error_t radio_deinit(void *radio_handle);

/**
 * @brief Prepare the device of radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_DEVICE_NOT_OPENED The radio device is not opened
 * @see radio_unprepare()
 */
radio_error_t radio_prepare(void *radio_handle);

/**
 * @brief Unprepare the device of radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @see radio_prepare()
 */
radio_error_t radio_unprepare(void *radio_handle);

/**
 * @brief Opens the device of radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_DEVICE_NOT_FOUND Failed to find radio device
 * @retval #RADIO_ERROR_DEVICE_NOT_OPENED The radio device is not opened
 * @retval #RADIO_ERROR_PERMISSION_DENIED The access to the resources can not be granted.
 * @retval #RADIO_ERROR_DEVICE_NOT_PREPARED Not prepared the radio device
 * @see radio_close()
 */
radio_error_t radio_open(void *radio_handle);

/**
 * @brief Closes the device of radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @see radio_open()
 */
radio_error_t radio_close(void *radio_handle);

/**
 * @brief Starts the device of radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @see radio_stop()
 */
radio_error_t radio_start(void *radio_handle);

/**
 * @brief Stops the device of radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @see radio_start()
 */
radio_error_t radio_stop(void *radio_handle);

/**
 * @brief Seeks (up or down) the effective frequency of the radio.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @param[in] direction The seek direction type (up or down)
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_DEVICE_NOT_OPENED The radio device is not opened
 * @retval #RADIO_ERROR_INVALID_OPERATION Invalid operation
 */
radio_error_t radio_seek(void *radio_handle, radio_seek_direction_type_t direction);

/**
 * @brief Gets the radio frequency.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @param[out] frequency The current frequency (khz)
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_DEVICE_NOT_OPENED The radio device is not opened
 * @retval #RADIO_ERROR_INVALID_OPERATION Invalid operation
 */
radio_error_t radio_get_frequency(void *radio_handle, uint32_t *frequency);

/**
 * @brief Sets the radio frequency.
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @param[in] frequency The frequency to set (khz)
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_DEVICE_NOT_OPENED The radio device is not opened
 * @retval #RADIO_ERROR_INVALID_OPERATION Invalid operation
 */
radio_error_t radio_set_frequency(void *radio_handle, uint32_t frequency);

/**
 * @brief Sets the radio's mute
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_INVALID_OPERATION Invalid operation
 */
radio_error_t radio_mute(void *radio_handle);

/**
 * @brief Unsets the radio's mute
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_INVALID_OPERATION Invalid operation
 */
radio_error_t radio_unmute(void *radio_handle);

/**
 * @brief Gets the current signal strength of the radio
 * @since_tizen 3.0
 * @param[in] radio_handle The handle to the radio HAL
 * @param[out] strength The current signal strength (dBm)
 * @return @c 0 on success, otherwise a negative error value
 * @retval #RADIO_ERROR_NONE Successful
 * @retval #RADIO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #RADIO_ERROR_INVALID_OPERATION Invalid operation
 */
radio_error_t radio_get_signal_strength(void *radio_handle, uint32_t *strength);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_RADIO_HAL_H__ */

