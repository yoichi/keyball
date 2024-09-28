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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
 LT(2,KC_TAB), KC_Q     , KC_W     , KC_E    , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , LT(3,KC_MINS),
LCTL_T(KC_ESC),KC_A     , KC_S     , KC_D    , KC_F     , KC_G     ,                                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_EQL),
    KC_LSFT  ,LT(1,KC_Z), KC_X     , KC_C    , KC_V     , KC_B     ,                                         KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                  KC_LALT  , KC_LGUI ,LT(1,KC_BTN1),      KC_SPC   , MO(3)    ,                   KC_BSPC,LT(2,KC_ENT), _______       , _______  , KC_RALT
  ),

  [1] = LAYOUT_universal(
    _______  ,  KC_1    , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _______  ,
    _______  ,  KC_BSLS , KC_GRV   , KC_QUOT , KC_LBRC  , KC_RBRC  ,                                         KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_INS   , _______  ,
    _______  ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , _______  , KC_CAPS  , _______  ,
                  _______  , _______ , _______  ,         KC_HOME  , KC_DEL   ,                   _______  , KC_END   , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,  S(KC_1) , S(KC_2)  , S(KC_3) , S(KC_4)  , S(KC_5)  ,                                         S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  , _______  ,
    _______  ,S(KC_BSLS),S(KC_GRV),S(KC_QUOT),S(KC_LBRC),S(KC_RBRC),                                         _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
                  _______  , KC_BTN2 , KC_BTN1  ,         KC_WH_L  , _______  ,                   _______  , KC_WH_R  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  , _______  , _______  , _______ , _______  , EE_CLR   ,                                         SSNP_FRE , SSNP_VRT , SSNP_HOR , SREV_VRT , SREV_HOR , _______  ,
    KBC_RST  , KBC_SAVE , CPI_D1K  , CPI_D100, CPI_I100 , CPI_I1K  ,                                         KC_PGUP  , AG_RSWP  , AG_RNRM  ,KC_BRMU,KC_KB_VOLUME_UP, KC_INT1,
    _______  , _______  , SCRL_DVD , SCRL_DVI, _______  , _______  ,                                         KC_PGDN  , AG_LSWP  , AG_LNRM  ,KC_BRMD,KC_KB_VOLUME_DOWN,KC_INT3,
                  _______  , _______ , _______  ,         KC_WH_L  , _______  ,                RALT(KC_GRV), KC_WH_R  , _______       , _______  , KC_KB_MUTE
  ),
};
// clang-format on

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
uint32_t os_detect_callback(uint32_t trigger_time, void *cb_arg) {
    switch (detected_host_os()) {
    case OS_WINDOWS:
        keymap_config.swap_lalt_lgui = true;
        break;
    case OS_MACOS: {
        uint8_t mode = KEYBALL_SCROLL_REVERSE_VERTICAL | KEYBALL_SCROLL_REVERSE_HORIZONTAL;
        keyball_set_scroll_reverse_mode(mode);
        keymap_config.swap_ralt_rgui = true;
        break;
    }
    default:
        break;
    }
    return 0;
}
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(200, os_detect_callback, NULL);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

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
