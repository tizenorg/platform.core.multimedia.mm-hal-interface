/*
 * tizen-camera.h
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

#ifndef __TIZEN_CAMERA_HAL_H__
#define __TIZEN_CAMERA_HAL_H__

#include <stdint.h>
#include <tbm_bufmgr.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @file tizen-camera.h
 * @brief This file contains the Tizen camera HAL API, related structures and enumerations.
 * @since_tizen 3.0
 */

#define BUFFER_PLANE_MAX                    4
#define DEVICE_COUNT_MAX                    16
#define DEVICE_NAME_LENGTH_MAX              32
#define RESOLUTION_COUNT_MAX                10

/**
 * @addtogroup TIZEN_CAMERA_HAL_MODULE
 * @{
 */

/**
 * @brief Enumeration for the camera error.
 * @since_tizen 3.0
 */
typedef enum camera_error {
	CAMERA_ERROR_NONE                   = 0x00000000,
	CAMERA_ERROR_INVALID_PARAMETER      = 0x80002001,
	CAMERA_ERROR_INVALID_STATE          = 0x80002002,
	CAMERA_ERROR_PERMISSION_DENIED      = 0x80002003,
	CAMERA_ERROR_OUT_OF_MEMORY          = 0x80002004,
	CAMERA_ERROR_DEVICE_OPEN            = 0x80002005,
	CAMERA_ERROR_DEVICE_NOT_FOUND       = 0x80002006,
	CAMERA_ERROR_DEVICE_UNAVAILABLE     = 0x80002007,
	CAMERA_ERROR_DEVICE_NOT_SUPPORTED   = 0x80002008,
	CAMERA_ERROR_DEVICE_ESD             = 0x80002009,
	CAMERA_ERROR_INTERNAL               = 0x8000200a,

	CAMERA_ERROR_UNKNOWN                = 0x80002fff
} camera_error_t;

/**
 * @brief Enumeration for the camera state.
 * @since_tizen 3.0
 */
typedef enum camera_state {
	CAMERA_STATE_INITIALIZED,
	CAMERA_STATE_OPENED,
	CAMERA_STATE_PREVIEWING,
	CAMERA_STATE_CAPTURING,
	CAMERA_STATE_RECORDING,
	CAMERA_STATE_RECORDING_SNAPSHOT
} camera_state_t;

/**
 * @brief The structure type of the resolution.
 * @since_tizen 3.0
 */
typedef struct camera_resolution {
	uint32_t width;
	uint32_t height;
} camera_resolution_t;

/**
 * @brief The structure type of the fraction.
 * @since_tizen 3.0
 */
typedef struct camera_fraction {
	int numerator;
	int denominator;
} camera_fraction_t;

/**
 * @brief The structure type of the rectangle.
 * @since_tizen 3.0
 */
typedef struct camera_rectangle {
	int x;
	int y;
	uint32_t width;
	uint32_t height;
} camera_rectangle_t;

/**
 * @brief Enumeration for the camera pixel format.
 * @since_tizen 3.0
 */
typedef enum camera_pixel_format {
	/* YUV */
	CAMERA_PIXEL_FORMAT_NV12 = 0x0000,
	CAMERA_PIXEL_FORMAT_NV21,
	CAMERA_PIXEL_FORMAT_I420,
	CAMERA_PIXEL_FORMAT_YV12,
	CAMERA_PIXEL_FORMAT_YUYV,
	CAMERA_PIXEL_FORMAT_UYVY,

	/* RGB */
	CAMERA_PIXEL_FORMAT_BGRA8888,
	CAMERA_PIXEL_FORMAT_ARGB8888,

	/* ENCODED */
	CAMERA_PIXEL_FORMAT_ENCODED_JPEG,
	CAMERA_PIXEL_FORMAT_ENCODED_H264,

	/* MAX */
	CAMERA_PIXEL_FORMAT_MAX
} camera_pixel_format_t;

/**
 * @brief The structure type of the camera plane.
 * @since_tizen 3.0
 */
typedef struct camera_plane {
	unsigned char *data;
	uint32_t align_width;
	uint32_t align_height;
	uint32_t size;
} camera_plane_t;

/**
 * @brief The structure type of the camera buffer.
 * @since_tizen 3.0
 */
typedef struct camera_buffer {
	int index;
	camera_pixel_format_t format;
	camera_resolution_t resolution;
	uint32_t num_planes;
	camera_plane_t planes[BUFFER_PLANE_MAX];
	uint32_t num_bos;
	tbm_bo bos[BUFFER_PLANE_MAX];
} camera_buffer_t;

/**
 * @brief The structure type of the camera metadata.
 * @since_tizen 3.0
 */
typedef struct camera_metadata {
	int is_flashed;
	camera_fraction_t focal_length;
	camera_fraction_t aperture_f_number;
	camera_fraction_t shutter_speed;
	camera_fraction_t exposure_time;
	camera_fraction_t brightness;
	camera_resolution_t exif_image;
	int iso;
	int metering_mode;
	int color_space;
	int component_configuration;
	int aperture_in_apex;
} camera_metadata_t;

/**
 * @brief Enumeration for the focus state.
 * @since_tizen 3.0
 */
typedef enum camera_focus_state {
	CAMERA_FOCUS_STATE_RELEASED,
	CAMERA_FOCUS_STATE_ONGOING,
	CAMERA_FOCUS_STATE_FOCUSED,
	CAMERA_FOCUS_STATE_FAILED
} camera_focus_state_t;

/**
 * @brief Enumeration for the facing direction of camera device.
 * @since_tizen 3.0
 */
typedef enum camera_facing_direction {
	CAMERA_FACING_DIRECTION_REAR,
	CAMERA_FACING_DIRECTION_FRONT,
	CAMERA_FACING_DIRECTION_EXTERNAL
} camera_facing_direction_t;

/**
 * @brief Enumeration for the camera rotation.
 * @since_tizen 3.0
 */
typedef enum camera_rotation {
	CAMERA_ROTATION_0,
	CAMERA_ROTATION_90,
	CAMERA_ROTATION_180,
	CAMERA_ROTATION_270
} camera_rotation_t;

/**
 * @brief Enumeration for the camera flip.
 * @since_tizen 3.0
 */
typedef enum camera_flip {
	CAMERA_FLIP_NONE,
	CAMERA_FLIP_HORIZONTAL,
	CAMERA_FLIP_VERTICAL,
	CAMERA_FLIP_BOTH
} camera_flip_t;

/**
 * @brief The structure type of the camera format.
 * @since_tizen 3.0
 */
typedef struct camera_format {
	camera_pixel_format_t preview_format;
	camera_resolution_t preview_resolution;
	uint32_t preview_fps;
	camera_rotation_t stream_rotation;
	camera_flip_t stream_flip;
	camera_pixel_format_t capture_format;
	camera_resolution_t capture_resolution;
	uint32_t capture_quality;
} camera_format_t;

/**
 * @brief Enumeration for the focus mode.
 * @since_tizen 3.0
 */
typedef enum camera_focus_mode {
	CAMERA_FOCUS_MODE_PAN,
	CAMERA_FOCUS_MODE_AUTO,
	CAMERA_FOCUS_MODE_CONTINUOUS_AUTO
} camera_focus_mode_t;

/**
 * @brief Enumeration for the white balance.
 * @since_tizen 3.0
 */
typedef enum camera_white_balance {
	CAMERA_WHITE_BALANCE_AUTO,          /**< Automatic */
	CAMERA_WHITE_BALANCE_DAYLIGHT,      /**< Daylight */
	CAMERA_WHITE_BALANCE_CLOUDY,        /**< Cloudy */
	CAMERA_WHITE_BALANCE_FLUORESCENT,   /**< Fluorescent */
	CAMERA_WHITE_BALANCE_INCANDESCENT,  /**< Incandescent */
	CAMERA_WHITE_BALANCE_SHADE,         /**< Shade */
	CAMERA_WHITE_BALANCE_HORIZON,       /**< Horizon */
	CAMERA_WHITE_BALANCE_FLASH          /**< Flash */
} camera_white_balance_t;

/**
 * @brief Enumeration for the effect.
 * @since_tizen 3.0
 */
typedef enum camera_effect {
	CAMERA_EFFECT_NONE,                 /**< None */
	CAMERA_EFFECT_MONO,                 /**< Mono */
	CAMERA_EFFECT_SEPIA,                /**< Sepia */
	CAMERA_EFFECT_NEGATIVE,             /**< Negative */
	CAMERA_EFFECT_RED,                  /**< Red */
	CAMERA_EFFECT_GREEN,                /**< Green */
	CAMERA_EFFECT_BLUE,                 /**< Blue */
	CAMERA_EFFECT_AQUA,                 /**< Aqua */
	CAMERA_EFFECT_ANTIQUE,              /**< Antique */
	CAMERA_EFFECT_WARM,                 /**< Warm */
	CAMERA_EFFECT_EMBOSS,               /**< Emboss */
	CAMERA_EFFECT_SKETCH,               /**< Sketch */
	CAMERA_EFFECT_SOLARIZATION,         /**< Solarization */
	CAMERA_EFFECT_POSTERIZATION,        /**< Posterization */
	CAMERA_EFFECT_CARTOON               /**< Cartoon */
} camera_effect_t;

/**
 * @brief Enumeration for the scene mode.
 * @since_tizen 3.0
 */
typedef enum camera_scene_mode {
	CAMERA_SCENE_MODE_NORMAL,           /**< Normal */
	CAMERA_SCENE_MODE_PORTRAIT,         /**< Portrait */
	CAMERA_SCENE_MODE_LANDSCAPE,        /**< Landscape */
	CAMERA_SCENE_MODE_SPORTS,           /**< Sports */
	CAMERA_SCENE_MODE_PARTY_N_INDOOR,   /**< Party & indoor */
	CAMERA_SCENE_MODE_BEACH_N_INDOOR,   /**< Beach & indoor */
	CAMERA_SCENE_MODE_SUNSET,           /**< Sunset */
	CAMERA_SCENE_MODE_DUSK_N_DAWN,      /**< Dusk & dawn */
	CAMERA_SCENE_MODE_FALL_COLOR,       /**< Fall */
	CAMERA_SCENE_MODE_NIGHT_SCENE,      /**< Night scene */
	CAMERA_SCENE_MODE_FIREWORK,         /**< Firework */
	CAMERA_SCENE_MODE_TEXT,             /**< Text */
	CAMERA_SCENE_MODE_SHOW_WINDOW,      /**< Show window */
	CAMERA_SCENE_MODE_CANDLE_LIGHT,     /**< Candle light */
	CAMERA_SCENE_MODE_BACKLIGHT,        /**< Backlight */
	CAMERA_SCENE_MODE_AQUA              /**< Aqua */
} camera_scene_mode_t;

/**
 * @brief Enumeration for the exposure mode.
 * @since_tizen 3.0
 */
typedef enum camera_exposure_mode {
	CAMERA_EXPOSURE_MODE_OFF = 0,       /**< Off */
	CAMERA_EXPOSURE_MODE_ALL,           /**< All mode */
	CAMERA_EXPOSURE_MODE_CENTER,        /**< Center mode */
	CAMERA_EXPOSURE_MODE_SPOT,          /**< Spot mode */
	CAMERA_EXPOSURE_MODE_CUSTOM         /**< Custom mode */
} camera_exposure_mode_t;

/**
 * @brief Enumeration for the shot mode.
 * @since_tizen 3.0
 */
typedef enum camera_shot_mode {
	CAMERA_SHOT_MODE_NORMAL = 0,        /**< Normal */
	CAMERA_SHOT_MODE_CONTINUOUS,        /**< Continuous */
	CAMERA_SHOT_MODE_HDR,               /**< HDR */
	CAMERA_SHOT_MODE_NIGHT              /**< Night */
} camera_shot_mode_t;

/**
 * @brief Definitions for the camera command.
 * @since_tizen 3.0
 */
#define CAMERA_COMMAND_WHITE_BALANCE            ((int64_t)1),
#define CAMERA_COMMAND_ISO                      ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 1))
#define CAMERA_COMMAND_CONTRAST                 ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 2))
#define CAMERA_COMMAND_SATURATION               ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 3))
#define CAMERA_COMMAND_EFFECT                   ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 4))
#define CAMERA_COMMAND_SCENE_MODE               ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 5))
#define CAMERA_COMMAND_EXPOSURE_MODE            ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 6))
#define CAMERA_COMMAND_EXPOSURE                 ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 7))
#define CAMERA_COMMAND_ROTATION                 ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 8))
#define CAMERA_COMMAND_FLIP                     ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 9))
#define CAMERA_COMMAND_FOCUS_MODE               ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 10))
#define CAMERA_COMMAND_SHOT_MODE                ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 11))
#define CAMERA_COMMAND_ANTI_HAND_SHAKE          ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 12))
#define CAMERA_COMMAND_FOCUS_AREA               ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 13))
#define CAMERA_COMMAND_DIGITAL_ZOOM             ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 14))
#define CAMERA_COMMAND_OPTICAL_ZOOM             ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 15))
#define CAMERA_COMMAND_RECORDING_HINT           ((int64_t)(CAMERA_COMMAND_WHITE_BALANCE << 16))

typedef struct camera_batch_command_control {
	/* flag for modified command */
	int64_t command_set_flag;

	/* value list */
	camera_white_balance_t white_balance;
	int iso;
	int contrast;
	int saturation;
	camera_effect_t effect;
	camera_scene_mode_t scene_mode;
	camera_exposure_mode_t exposure_mode;
	int exposure;
	camera_rotation_t rotation;
	camera_flip_t flip;
	camera_focus_mode_t focus_mode;
	camera_exposure_mode_t shot_mode;
	int anti_hand_shake;
	camera_rectangle_t focus_area;
	int digital_zoom;
	int optical_zoom;
	int recording_hint;
} camera_batch_command_control_t;

/**
 * @brief The structure type of the format list.
 * @since_tizen 3.0
 */
typedef struct camera_pixel_format_list {
	uint32_t count;
	camera_pixel_format_t formats[CAMERA_PIXEL_FORMAT_MAX];
} camera_format_list_t;

/**
 * @brief The structure type of the resolution list.
 * @since_tizen 3.0
 */
typedef struct camera_resolution_list {
	uint32_t count;
	camera_resolution_t resolutions[RESOLUTION_COUNT_MAX];
} camera_resolution_list_t;

/**
 * @brief The structure type of the camera device information.
 * @since_tizen 3.0
 */
typedef struct camera_device_info {
	uint32_t index;
	const char name[DEVICE_NAME_LENGTH_MAX];
	camera_facing_direction_t facing_direction;
	camera_format_list_t format_list;
	camera_resolution_list_t preview_list;
	camera_resolution_list_t video_list;
} camera_device_info_t;

/**
 * @brief The structure type of the camera device list.
 * @since_tizen 3.0
 */
typedef struct camera_device_list {
	uint32_t count;
	camera_device_info_t device_info[DEVICE_COUNT_MAX];
} camera_device_list_t;

/**
 * @brief Enumeration for the camera message type.
 * @since_tizen 3.0
 */
typedef enum camera_message_type {
	CAMERA_MESSAGE_TYPE_FOCUS_CHANGED,
	CAMERA_MESSAGE_TYPE_CAPTURED,
	CAMERA_MESSAGE_TYPE_CAPTURE_DATA,
	CAMERA_MESSAGE_TYPE_HDR_PROGRESS,
	CAMERA_MESSAGE_TYPE_ERROR
} camera_message_type_t;

/**
 * @brief The structure type of the camera message.
 * @since_tizen 3.0
 */
typedef struct camera_message {
	camera_message_type_t type;
	union {
		camera_focus_state_t focus_state;
		camera_buffer_t capture_data;
		uint32_t hdr_progress;
		camera_error_t error_code;
	} message;
} camera_message_t;

/**
 * @brief Callback function for notification from camera HAL.
 * @since_tizen 3.0
 * @param[in] message The message from camera HAL
 * @param[in] user_data The user data for callback
 * @see camera_add_message_callback()
 * @see camera_remove_message_callback()
 */
typedef void (*camera_message_cb)(camera_message_t *message, void *user_data);

/**
 * @brief Callback function for captured preview frame from camera device.
 * @since_tizen 3.0
 * @param[in] buffer The preview buffer
 * @param[in] meta The meta data for the preview frame
 * @param[in] user_data The user data for callback
 * @pre       camera_start_preview() will invoke this callback.
 * @see camera_start_preview()
 * @see camera_stop_preview()
 */
typedef void (*camera_preview_frame_cb)(camera_buffer_t *buffer, camera_metadata_t *meta, void *user_data);

/**
 * @brief Callback function for captured video frame from camera device.
 * @since_tizen 3.0
 * @param[in] buffer The video buffer
 * @param[in] meta The meta data for the video frame
 * @param[in] user_data The user data for callback
 * @pre       camera_start_record() will invoke this callback.
 * @see camera_start_record()
 * @see camera_stop_record()
 */
typedef void (*camera_video_frame_cb)(camera_buffer_t *buffer, camera_metadata_t *meta, void *user_data);

/**
 * @brief Callback function for captured still image from camera device.
 * @since_tizen 3.0
 * @param[in] main The main image data
 * @param[in] postview The image data of the postview (it could be @c NULL if the available data does not exist)
 * @param[in] thumbnail The image data of the thumbnail (it could be @c NULL if the available data does not exist)
 * @param[in] user_data The user data passed from the callback registration function
 * @pre       camera_start_capture() will invoke this callback function.
 * @see camera_start_capture()
 * @see camera_stop_capture()
 */
typedef void (*camera_capture_cb)(camera_buffer_t *main, camera_buffer_t *postview, camera_buffer_t *thumbnail, void *user_data);

/**
 * @brief The structure type of the camera interface.
 * @since_tizen 3.0
 */
typedef struct camera_interface {
	int (*init)(void **camera_handle);
	int (*deinit)(void *camera_handle);
	int (*get_device_list)(void *camera_handle, camera_device_list_t *device_list);
	int (*open_device)(void *camera_handle, int device_index);
	int (*close_device)(void *camera_handle);
	int (*add_message_callback)(void *camera_handle, camera_message_cb callback, void *user_data, uint32_t *cb_id);
	int (*remove_message_callback)(void *camera_handle, uint32_t cb_id);
	int (*set_preview_stream_format)(void *camera_handle, camera_format_t *format);
	int (*get_preview_stream_format)(void *camera_handle, camera_format_t *format);
	int (*start_preview)(void *camera_handle, camera_preview_frame_cb callback, void *user_data);
	int (*release_preview_buffer)(void *camera_handle, int buffer_index);
	int (*stop_preview)(void *camera_handle);
	int (*start_auto_focus)(void *camera_handle);
	int (*stop_auto_focus)(void *camera_handle);
	int (*start_capture)(void *camera_handle, camera_capture_cb callback, void *user_data);
	int (*stop_capture)(void *camera_handle);
	int (*set_video_stream_format)(void *camera_handle, camera_format_t *format);
	int (*get_video_stream_format)(void *camera_handle, camera_format_t *format);
	int (*start_record)(void *camera_handle, camera_video_frame_cb callback, void *user_data);
	int (*release_video_buffer)(void *camera_handle, int buffer_index);
	int (*stop_record)(void *camera_handle);
	int (*set_command)(void *camera_handle, int command, void *value);
	int (*get_command)(void *camera_handle, int command, void *value);
} camera_interface_t;


/**
 * @brief Initializes new handle of camera HAL.
 * @since_tizen 3.0
 * @param[out] camera_handle A newly returned handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #CAMERA_ERROR_PERMISSION_DENIED The access to the resources can not be granted
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @post   If it succeeds, the camera state will be #CAMERA_STATE_INITIALIZED.
 *
 * @see camera_deinit()
 */
int camera_init(void **camera_handle);

/**
 * @brief Deinitializes handle of camera HAL.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @see camera_init()
 */
int camera_deinit(void *camera_handle);

/**
 * @brief Gets the device list of camera.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[out] device_list The device list of the camera
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 */
int camera_get_device_list(void *camera_handle, camera_device_list_t *device_list);

/**
 * @brief Opens camera device.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] device_index The device index of the camera
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #CAMERA_ERROR_PERMISSION_DENIED The access to the resources can not be granted
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @retval CAMERA_ERROR_DEVICE_NOT_FOUND Failed to find camera device
 * @retval CAMERA_ERROR_DEVICE_UNAVAILABLE The camera device is unavailable
 * @pre    The camera state must be set to #CAMERA_STATE_INITIALIZED.
 * @post   If it succeeds, the camera state will be #CAMERA_STATE_OPENED.
 * @see camera_close_device()
 */
int camera_open_device(void *camera_handle, int device_index);

/**
 * @brief Closes camera device.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @pre    The camera state must be set to #CAMERA_STATE_OPENED.
 * @post   If it succeeds, the camera state will be #CAMERA_STATE_INITIALIZED.
 * @see camera_open_device()
 */
int camera_close_device(void *camera_handle);

/**
 * @brief Registers a callback function to be called to send a message by camera HAL.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] callback The callback function to be registered
 * @param[in] user_data The user data to be passed to the callback function
 * @param[out] cb_id The callback id
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_OUT_OF_MEMORY Out of memory
 * @see camera_remove_message_callback()
 */
int camera_add_message_callback(void *camera_handle, camera_message_cb callback, void *user_data, uint32_t *cb_id);

/**
 * @brief Unregisters a callback function.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] cb_id The callback id
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @see camera_remove_message_callback()
 */
int camera_remove_message_callback(void *camera_handle, uint32_t cb_id);

/**
 * @brief Sets the format of the preview stream.
 * @since_tizen 3.0
 * @remarks This function should be called before previewing (see camera_start_preview()).
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] format The format of the preview stream
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @pre    The camera state must be set to #CAMERA_STATE_OPENED.
 * @see camera_start_preview()
 * @see camera_start_capture()
 * @see camera_get_preview_stream_format()
 */
int camera_set_preview_stream_format(void *camera_handle, camera_format_t *format);

/**
 * @brief Gets the format of the preview stream.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[out] format The format of the preview stream
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @see camera_start_preview()
 * @see camera_start_capture()
 * @see camera_set_preview_stream_format()
 * @see camera_foreach_supported_preview_format()
 */
int camera_get_preview_stream_format(void *camera_handle, camera_format_t *format);

/**
 * @brief Starts preview frames on the screen.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] callback The callback for preview frame
 * @param[in] user_data The user data for callback
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_DEVICE_BUSY The device is being used in another application or is performing other operations
 * @retval #CAMERA_ERROR_DEVICE_NOT_FOUND No camera device
 * @retval #CAMERA_ERROR_PERMISSION_DENIED The access to the resources can not be granted
 * @pre    The camera state must be set to #CAMERA_STATE_OPENED.
 * @post   If it succeeds, the camera state will be #CAMERA_STATE_PREVIEWING.
 * @see camera_stop_preview()
 */
int camera_start_preview(void *camera_handle, camera_preview_frame_cb callback, void *user_data);

/**
 * @brief Release the preview buffer.
 * @since_tizen 3.0
 * @remarks The preview buffer should be released with this function after use it.
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] buffer_index The index of preview buffer
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @see camera_start_preview()
 */
int camera_release_preview_buffer(void *camera_handle, int buffer_index);

/**
 * @brief Stops preview frames.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @pre    The camera state must be set to #CAMERA_STATE_PREVIEWING.
 * @post   The camera state will be #CAMERA_STATE_OPENED.
 * @see camera_start_preview()
 */
int camera_stop_preview(void *camera_handle);

/**
 * @brief Starts camera auto focusing operation.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @pre    The camera state must be set to #CAMERA_STATE_PREVIEWING or #CAMERA_STATE_RECORDING.
 * @post   The camera focus state will be #CAMERA_FOCUS_STATE_ONGOING.
 * @see camera_stop_auto_focus()
 * @see camera_add_message_callback()
 * @see camera_message_cb()
 * @see camera_set_command()
 */
int camera_start_auto_focus(void *camera_handle);

/**
 * @brief Stops camera auto focusing operation.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @pre    The camera state must be set to #CAMERA_STATE_PREVIEWING or #CAMERA_STATE_RECORDING.
 * @post   The camera focus state will be #CAMERA_FOCUS_STATE_ONGOING.
 * @see camera_start_auto_focus()
 * @see camera_add_message_callback()
 * @see camera_message_cb()
 */
int camera_stop_auto_focus(void *camera_handle);

/**
 * @brief Starts capturing of still images.
 * @since_tizen 3.0
 * @remarks In case of zero shutter lag capture, preview frame won't be stopped while capturing.
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] callback The callback for captured data
 * @param[in] user_data The user data for callback
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @pre    The camera state must be set to #CAMERA_STATE_PREVIEWING or #CAMERA_STATE_RECORDING.
 * @post   If it succeeds the camera state will be #CAMERA_STATE_CAPTURING or #CAMERA_STATE_RECORDING_SNAPSHOT.
 * @see camera_start_preview()
 * @see camera_start_record()
 * @see camera_set_preview_stream_format()
 * @see camera_get_preview_stream_format()
 */
int camera_start_capture(void *camera_handle, camera_capture_cb callback, void *user_data);

/**
 * @brief Stops capturing of still images.
 * @since_tizen 3.0
 * @remarks In case of zero shutter lag, this function will changes only the state of camera HAL \n
 *          from #CAMERA_STATE_PREVIEWING or #CAMERA_STATE_RECORDING to #CAMERA_STATE_PREVIEWING or #CAMERA_STATE_RECORDING.\n
 *          Otherwise, preview frame will be restarted.
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] callback The callback for captured data
 * @param[in] user_data The user data
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @pre    The camera state must be set to #CAMERA_STATE_CAPTURING or #CAMERA_STATE_RECORDING_SNAPSHOT.
 * @post   If it succeeds the camera state will be #CAMERA_STATE_PREVIEWING or #CAMERA_STATE_RECORDING.
 * @see camera_start_capture()
 * @see camera_start_record()
 * @see camera_set_preview_stream_format()
 * @see camera_get_preview_stream_format()
 * @see camera_set_video_stream_format()
 * @see camera_get_video_stream_format()
 */
int camera_stop_capture(void *camera_handle);

/**
 * @brief Sets the format of the video stream for recording.
 * @since_tizen 3.0
 * @remarks This function should be called before recording (see camera_start_record()).
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] format The format of the video stream
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @pre    The camera state must be set to #CAMERA_STATE_OPENED.
 * @see camera_start_record()
 * @see camera_start_capture()
 * @see camera_get_video_stream_format()
 */
int camera_set_video_stream_format(void *camera_handle, camera_format_t *format);

/**
 * @brief Gets the format of the video stream for recording.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[out] format The format of the video stream
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @see camera_start_preview()
 * @see camera_start_capture()
 * @see camera_set_preview_stream_format()
 * @see camera_foreach_supported_preview_format()
 */
int camera_get_video_stream_format(void *camera_handle, camera_format_t *format);

/**
 * @brief Starts the video frame for recording.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] callback The callback for video frame
 * @param[in] user_data The user data for callback
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_PERMISSION_DENIED The access to the resources can not be granted
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @pre The camera state must be #CAMERA_STATE_PREVIEWING.
 * @post The camera state will be #CAMERA_STATE_RECORDING.
 * @see camera_set_video_stream_format()
 * @see camera_get_video_stream_format()
 * @see camera_stop_record()
 */
int camera_start_record(void *camera_handle, camera_video_frame_cb callback, void *user_data);

/**
 * @brief Release the video buffer.
 * @remarks The video buffer should be released with this function after use it.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] buffer_index The index of video buffer
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @pre    The camera state must be set to #CAMERA_STATE_PREVIEWING.
 * @see camera_start_record()
 */
int camera_release_video_buffer(void *camera_handle, int buffer_index);

/**
 * @brief Stops the video frame.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @pre The camera state must be #CAMERA_STATE_RECORDING.
 * @post The camera state will be #CAMERA_STATE_PREVIEWING.
 * @see camera_set_video_stream_format()
 * @see camera_get_video_stream_format()
 * @see camera_start_record()
 */
int camera_stop_record(void *camera_handle);

/**
 * @brief Sets the various command and value to control camera device.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] command The command to control the camera device
 * @param[in] value The value to set
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @see camera_get_command()
 */
int camera_set_command(void *camera_handle, int64_t command, void *value);

/**
 * @brief Gets the current value of command.
 * @since_tizen 3.0
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] command The command to control the camera device
 * @param[out] value The value to get
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @see camera_get_command()
 */
int camera_get_command(void *camera_handle, int64_t command, void *value);

/**
 * @brief Sets the current value of command.
 * @since_tizen 3.0
 * @remarks error_command will be set if error is returned from the function.
 * @param[in] camera_handle The handle to the camera HAL
 * @param[in] batch_command The batch command to set
 * @param[in] error_command The error command
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @retval #CAMERA_ERROR_NOT_SUPPORTED The feature is not supported
 * @see camera_set_command()
 * @see camera_get_command()
 */
int camera_set_batch_command(void *camera_handle, camera_batch_command_t *batch_command, int64_t *error_command);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_CAMERA_HAL_H__ */
