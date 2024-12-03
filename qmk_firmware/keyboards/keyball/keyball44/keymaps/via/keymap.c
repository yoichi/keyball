/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "os_detection.h"

enum custom_user_keycodes {
    IME_TGL = QK_USER_0,
};

#define _LAYER_ _______ // should keep as transparent for momentarily layer activation

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
 LT(2,KC_TAB), KC_Q     , KC_W     , KC_E    , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , LT(1,KC_EQL),
LCTL_T(KC_ESC),KC_A     , KC_S     , KC_D    , KC_F     , KC_G     ,                                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_MINS),
    KC_LSFT  , KC_Z     , KC_X     , KC_C    , KC_V     , KC_B     ,                                         KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                  KC_LALT  , KC_LGUI , KC_BTN1  ,    LT(1,KC_SPC)  , MO(3)    ,                   KC_BSPC,LT(2,KC_ENT), _______       , _______  , KC_RALT
  ),

  [1] = LAYOUT_universal(
    _______  , KC_1     , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _LAYER_  ,
    _______  ,S(KC_HOME), S(KC_END), KC_LBRC , KC_RBRC  , KC_BSLS  ,                                         KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_INS   , _______  ,
    _______  , _______  , _______  , _______ , _______  , KC_DEL   ,                                         KC_GRV   , KC_QUOT  , KC_INT1  , KC_INT3  , KC_CAPS  , _______  ,
                  _______  , _______ , KC_HOME  ,         _LAYER_  , _______  ,                   _______  , KC_END   , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _LAYER_  , S(KC_1)  , S(KC_2)  , S(KC_3) , S(KC_4)  , S(KC_5)  ,                                         S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  , _______  ,
    _______  , _______  , _______ ,S(KC_LBRC),S(KC_RBRC),S(KC_BSLS),                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , KC_F1    , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         S(KC_GRV),S(KC_QUOT),S(KC_INT1),S(KC_INT3), _______  , _______  ,
                  _______  , KC_BTN2 , KC_BTN1  ,         _______  , _______  ,                   _______  , _LAYER_  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    MO(4)    , G(KC_1)  , G(KC_2)  , G(KC_3) , G(KC_4)  , G(KC_5)  ,                                         G(KC_6)  , G(KC_7)  , G(KC_8)  , G(KC_9)  , KC_BRMU  , KC_KB_VOLUME_UP,
    _______  , _______  , _______  , _______ , _______  , KC_PGUP  ,                                         C(KC_LEFT),C(KC_DOWN),C(KC_UP) ,C(KC_RGHT), KC_BRMD  , KC_KB_VOLUME_DOWN,
    _______  ,RWIN(KC_1),RWIN(KC_2),RWIN(KC_3),RWIN(KC_4),KC_PGDN  ,                                 RWIN(KC_LEFT),RWIN(KC_DOWN),RWIN(KC_UP),RWIN(KC_RGHT),_______, KC_KB_MUTE,
                  _______  , _______ , _______  ,         KC_WH_L  , _LAYER_  ,                   IME_TGL  , KC_WH_R  , _______       , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _LAYER_  , _______  , _______  , _______ , _______  , EE_CLR   ,                                         SSNP_FRE , SSNP_VRT , SSNP_HOR , SREV_VRT , SREV_HOR , _______  ,
    KBC_RST  , KBC_SAVE , CPI_D1K  , CPI_D100, CPI_I100 , CPI_I1K  ,                                         _______  , AG_RSWP  , AG_RNRM  , _______  , _______  , _______  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI, _______  , _______  ,                                         _______  , AG_LSWP  , AG_LNRM  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
uint32_t os_detect_callback(uint32_t trigger_time, void *cb_arg) {
    keyball.detected_host_os = detected_host_os();
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
    keymap_config.raw = eeconfig_read_keymap();
#endif
    switch (keyball.detected_host_os) {
        case OS_WINDOWS:
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_ralt_rgui = false;
#endif
            break;
        case OS_MACOS: {
            uint8_t mode = KEYBALL_SCROLL_REVERSE_VERTICAL | KEYBALL_SCROLL_REVERSE_HORIZONTAL;
            keyball_set_scroll_reverse_mode(mode);
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_ralt_rgui = true;
#endif
            break;
    }
    default:
        break;
    }
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
    eeconfig_update_keymap(keymap_config.raw);
#endif
    return 0;
}
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(100, os_detect_callback, NULL);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case IME_TGL:
            switch (keyball.detected_host_os) {
            case OS_WINDOWS:
                if (record->event.pressed) {
                    register_code16(RALT(KC_GRV));
                } else {
                    unregister_code16(RALT(KC_GRV));
                }
                return false;
            case OS_MACOS:
                if (record->event.pressed) {
                    register_code16(G(KC_SPC));
                } else {
                    unregister_code16(G(KC_SPC));
                }
                return false;
            }
            break;
    }
    return true;
}
#endif

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}

#ifdef DISPLAY_PMW3360_CPI_VALUE
void oledkit_render_logo_user(void) {
    oledkit_render_info_user();
}
#endif
#endif
