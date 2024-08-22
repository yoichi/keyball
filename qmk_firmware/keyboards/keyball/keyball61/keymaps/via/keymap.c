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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSLS  ,
LCTL_T(KC_GRV),KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_EQL),
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,LCTL_T(KC_RBRC),         KC_LBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT,
LT(1,KC_QUOT), KC_LCTL  , KC_LALT  , KC_LGUI,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),        KC_BSPC,LT(2,KC_ENT), _______, _______  , _______  ,RGUI_T(S(KC_CAPS)),LT(1,KC_QUOT)
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_F12   ,
    _______  , _______  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   ,                                  KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_INS   , _______  ,
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_INT1  ,             KC_CAPS , KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , KC_INT3  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    KC_BRMU  , _______  , _______  , _______  , _______  , _______  ,                                  KC_HOME  , _______  , _______  , _______  ,KC_KB_MUTE,KC_KB_VOLUME_UP,
    KC_BRMD  , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  KC_END   , KC_LEFT  , KC_UP    , KC_RGHT  , _______  ,KC_KB_VOLUME_DOWN,
    _______  , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            KC_BTN4  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , KC_BTN5
  ),

  [3] = LAYOUT_universal(
    _______  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  KC_HOME  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  KC_END   , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , _______  ,
    KBC_RST  , KBC_SAVE , CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  ,                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , _______  ,            KC_BTN4  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , KC_BTN5
  ),
};
// clang-format on

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
