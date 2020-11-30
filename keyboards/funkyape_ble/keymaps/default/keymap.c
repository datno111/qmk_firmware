#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "eeprom.h"

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

const uint8_t is_master = IS_LEFT_HAND;

void nrfmicro_power_enable(bool enable);

bool has_usb(void);

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _BT_ADJ
};

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    QWERTY,
    LOWER,
    RAISE,
    ADJUST,
    BT_ADJ,
    RGBRST
};


extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_XXXXX KC_NO
#define KC_RST   RESET

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define MIN_BTA LT(_BT_ADJ,KC_MINS)
#define EQL_BTA LT(_BT_ADJ,KC_EQL)

#define HT_LFCA SFT_T(KC_CAPS)
#define HT_RSFQ RSFT_T(KC_QUOT)
#define HT_BSCT RCTL_T(KC_BSLS)

#define SH_TG KC_TRNS


uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, HT_RSFQ,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           KC_LCTRL,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DOWN,          KC_UP,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, HT_BSCT,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              KC_MINS, KC_LBRC, KC_LALT, LT(_LOWER,KC_SPC),       LT(_RAISE,KC_ENT),KC_RGUI, KC_RBRC, KC_EQL
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, XXXXXXX, KC_UP,   XXXXXXX, KC_PGUP, XXXXXXX,                            KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_END,                             KC_MUTE, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, KC_BTN4,          KC_BTN5, KC_VOLD, KC_MPRV, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              RAISE,   _______, _______,     _______,                   _______,    _______, _______, LOWER
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCA(KC_DEL),
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_INS,  KC_PAUS, KC_PSCR, KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_WH_L, KC_BTN3, KC_WH_R, KC_WH_D, XXXXXXX, KC_BTN4,          KC_BTN5, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, _______,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              RAISE,   _______, _______,     _______,                   _______,    _______, _______, LOWER
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           RGBRST,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGBRST,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG, XXXXXXX,                            XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_MOD, XXXXXXX, _______,          _______, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              _______, _______, _______,     _______,                   _______,    _______, _______, _______
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
  ),

  [_BT_ADJ] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, ADV_ID4, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADV_ID0,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           DEL_ID0, DEL_ID1, DEL_ID2, DEL_ID3, DEL_ID4, BATT_LV,                            BATT_LV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEL_ID0,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           ENT_DFU, XXXXXXX, XXXXXXX, BLE_EN,  USB_EN,  AD_WO_L,                            AD_WO_L, USB_EN,  BLE_EN,  XXXXXXX, XXXXXXX, ENT_DFU,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           ENT_SLP, XXXXXXX, XXXXXXX, BLE_DIS, USB_DIS, AD_WO_L, _______,          _______, AD_WO_L, USB_DIS, BLE_DIS, XXXXXXX, XXXXXXX, ENT_SLP,
        //└────────┴────────┴┬───────┴┬───────┴┬───────┴┬───────┴────────┴┐      ┌┴────────┴───────┬┴───────┬┴───────┬┴───────┬┴────────┴────────┘
                              _______, _______, DELBNDS,    _______,                    _______,    DELBNDS, _______, _______
                           //└────────┴────────┴────────┴─────────────────┘      └─────────────────┴────────┴────────┴────────┘
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_state_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
       //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  //NRF_LOG_INFO("process_record_user, keycode: %d\n", keycode);

#ifdef SSD1306OLED
  iota_gfx_flush(); // wake up screen
#endif

  if (record->event.pressed) {
    set_keylog(keycode, record);
    //set_timelog();
  }

  switch (keycode) {
    case RGB_TOG:
        if (record->event.pressed) {
            // only enable the power for now, never disable
            if (!rgblight_config.enable) {
                //nrfmicro_power_enable(!rgblight_config.enable);
            }
            #ifdef SSD1306OLED
                //iota_gfx_init(!IS_LEFT_HAND); // enable the OLED screen
            #endif
        }
    break;

    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(16);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case BT_ADJ:
      if (record->event.pressed) {
        layer_on(_BT_ADJ);
      } else {
        layer_off(_BT_ADJ);
      }
      return false;
      break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
          NRF_LOG_INFO("RGB_MOD, RGB_current_mode: %d\n", RGB_current_mode);
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          nrfmicro_power_enable(true);
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          NRF_LOG_INFO("RGBRST, RGB_current_mode: %d\n", RGB_current_mode);
        }
      #endif

      #ifdef SSD1306OLED
      //iota_gfx_init(!IS_LEFT_HAND); // enable the OLED screen
      #endif
      break;
    }

  if (record->event.pressed) {
    switch(keycode) {
    case DELBNDS:
      delete_bonds();
      //super weird issue - RGBTOG overlaps DELBNDS
      //not sure why, matrix issue probably
      //use 3 thumb keys + reset button for now
      // NRF_LOG_INFO("DELBNDS overlaps RGBTOG, temporarily disabled");
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }
  }

  return true;
}
;


#ifdef SSD1306OLED

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//const char *read_host_led_state(void);
//const char *read_mode_icon(bool swap);

const char *read_rgb_info(void);

void matrix_render_user(struct CharacterMatrix *matrix) {


//  if (is_master)
{
    //matrix_write_ln(matrix, read_layer_state());
    //matrix_write_ln(matrix, read_keylog());

    {
    char str[64];

#if (IS_LEFT_HAND)
      sprintf (str, "Master: %s%s%s",
        get_usb_enabled() && !get_ble_enabled() ? "USB mode":"",
        get_ble_enabled() && ble_connected() ? "connected":"",
        get_ble_enabled() && !ble_connected() ? "disconnected":""
      );
#else
      sprintf(str, "Slave: %s", ble_connected() ? "connected" : "disconnected");
#endif

      matrix_write_ln(matrix, str);
    }

    matrix_write_ln(matrix, read_rgb_info());

    {
      char vc[16], str[32];
      int vcc = get_vcc();
      sprintf(vc, "%4dmV", vcc);
      sprintf(str, "Bat: %s USB: %s", vcc<500 || vcc>4400 ? "off   " : vc, has_usb()? "on":"off");
      matrix_write_ln(matrix, str);
    }

    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  }
// else {
//    matrix_write_ln(matrix, read_layer_state()); // somehow removes the dead pixel
//    matrix_write(matrix, read_logo());
//  }

}

void iota_gfx_task_user(void) {
  ScreenOffInterval = has_usb() ? 60*10*1000 : 60*5*1000; // ms
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

#endif
