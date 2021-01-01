#include QMK_KEYBOARD_H


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

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define HT_RSFQ RSFT_T(KC_QUOT)
#define HT_BSCT RCTL_T(KC_BSLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, HT_RSFQ,
    //├────────┼────────┼────────┼────────┼────────┼────────┐                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_LCTRL,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, HT_BSCT,
    //└────────┴────────┴────────┴┬───────┴┬───────┴┬───────┴─────────┐      ┌─────────┴───────┬┴───────┬┴───────┬┴────────┴────────┴────────┘
                                   KC_LBRC, KC_LALT, LT(_LOWER,KC_SPC),       LT(_RAISE,KC_ENT),KC_RGUI, KC_RBRC
                                //└────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_ESC,  XXXXXXX, KC_UP,   XXXXXXX, KC_PGUP, XXXXXXX,                            KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_END,                             KC_MUTE, KC_MPLY, XXXXXXX, XXXXXXX, KC_PSCR, KC_RSFT,
    //├────────┼────────┼────────┼────────┼────────┼────────┐                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX,                            KC_VOLD, KC_MPRV, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    //└────────┴────────┴────────┴┬───────┴┬───────┴┬───────┴─────────┐      ┌─────────┴───────┬┴───────┬┴───────┬┴────────┴────────┴────────┘
                                   KC_MINS, _______,     _______,                   _______,    _______, KC_EQL
                                //└────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_LSFT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_LSFT,
    //├────────┼────────┼────────┼────────┼────────┼────────┐                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    //└────────┴────────┴────────┴┬───────┴┬───────┴┬───────┴─────────┐      ┌─────────┴───────┬┴───────┬┴───────┬┴────────┴────────┴────────┘
                                   _______, _______,     _______,                   _______,    _______, _______
                                //└────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG, XXXXXXX,                            XXXXXXX, KC_PWR,  XXXXXXX, XXXXXXX, KC_BRIU, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┐                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_MOD, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, XXXXXXX,
    //└────────┴────────┴────────┴┬───────┴┬───────┴┬───────┴─────────┐      ┌─────────┴───────┬┴───────┬┴───────┬┴────────┴────────┴────────┘
                                   _______, _______,     _______,                   _______,    _______, _______
                                //└────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┘
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
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

    }
    return true;
}
