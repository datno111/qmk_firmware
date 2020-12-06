#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
    };

// Tap Dance declarations
enum tap_dances {
    ALTGUI,
    GUIALT,
    SFTCAP
    };

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [ALTGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    [GUIALT] = ACTION_TAP_DANCE_DOUBLE(KC_RGUI, KC_RALT),
    [SFTCAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
    };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define HT_RSFQ RSFT_T(KC_QUOT)
#define HT_BSCT RCTL_T(KC_BSLS)
#define TD_ALGU TD(ALTGUI)
#define TD_GUAL TD(GUIALT)
#define TD_SCAP TD(SFTCAP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        [_QWERTY] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           TD_SCAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, HT_RSFQ,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           KC_LCTRL,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,          KC_MUTE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, HT_BSCT,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              KC_MINS, KC_LBRC, TD_ALGU, LT(_LOWER,KC_SPC),       LT(_RAISE,KC_ENT),TD_GUAL, KC_RBRC, KC_EQL
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
            ),

        [_LOWER] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, XXXXXXX, KC_UP,   XXXXXXX, KC_PGUP, XXXXXXX,                            KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_END,                             KC_MUTE, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX,  _______,         _______, KC_VOLD, KC_MPRV, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              RAISE,   _______, _______,     _______,                   _______,    _______, _______, LOWER
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
        ),

        [_RAISE] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  LCA(KC_DEL),
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_INS,  KC_PAUS, KC_PSCR, KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3, XXXXXXX,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_WH_L, KC_BTN3, KC_WH_R, KC_WH_D, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, _______,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              RAISE,   _______, _______,     _______,                   _______,    _______, _______, LOWER
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
        ),

        [_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG, XXXXXXX,                            XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_MOD, XXXXXXX, _______,          _______, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              _______, _______, _______,     _______,                   _______,    _______, _______, _______
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
        )
        };

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_BTN5);
        } else {
            tap_code(KC_BTN4);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        // oled_write_ln(read_host_led_state(), false);
        // oled_write_ln(read_timelog(), false);
    } else {
        oled_write(read_logo(), false);
    }
}
#endif  // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }
    return true;
}
