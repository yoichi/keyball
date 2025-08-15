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

#ifdef TAP_DANCE_ENABLE
#include "keymap_japanese.h"
// Tap Dance
enum {
    TD_JP_EQL_MO2,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            if (QK_MOMENTARY <= tap_hold->hold && tap_hold->hold <= QK_MOMENTARY_MAX) {
                layer_on(QK_MOMENTARY_GET_LAYER(tap_hold->hold));
            } else {
                register_code16(tap_hold->hold);
            }
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        if (QK_MOMENTARY <= tap_hold->held && tap_hold->held <= QK_MOMENTARY_MAX) {
            layer_off(QK_MOMENTARY_GET_LAYER(tap_hold->held));
        } else {
            unregister_code16(tap_hold->held);
        }
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_JP_EQL_MO2] = ACTION_TAP_DANCE_TAP_HOLD(JP_EQL, MO(2)),
};
#endif // TAP_DANCE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // default layer for macOS (US)
  [0] = LAYOUT_universal(
 LT(3,KC_TAB), KC_Q     , KC_W     , KC_E    , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , LT(2,KC_EQL),
LCTL_T(KC_ESC),KC_A     , KC_S     , KC_D    , KC_F     , KC_G     ,                                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_MINS),
    KC_LSFT  , KC_Z     , KC_X     , KC_C    , KC_V     , KC_B     ,                                         KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                  KC_LALT  , KC_LGUI , KC_BTN1  ,    LT(2,KC_SPC)  , MO(4)    ,                   KC_BSPC,LT(3,KC_ENT), _______       , _______  , KC_RGUI
  ),

  // default layer for Windows (JP)
  [1] = LAYOUT_universal(
#ifdef TAP_DANCE_ENABLE
 LT(3,KC_TAB), KC_Q     , KC_W     , KC_E    , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , TD(TD_JP_EQL_MO2),
#else
 LT(3,KC_TAB), KC_Q     , KC_W     , KC_E    , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , LT(2,KC_EQL),
#endif
LCTL_T(KC_ESC),KC_A     , KC_S     , KC_D    , KC_F     , KC_G     ,                                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_MINS),
    KC_LSFT  , KC_Z     , KC_X     , KC_C    , KC_V     , KC_B     ,                                         KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                  KC_LGUI  , KC_LALT , KC_BTN1  ,    LT(2,KC_SPC)  , MO(4)    ,                   KC_BSPC,LT(3,KC_ENT), _______       , _______  , KC_RALT
  ),

  [2] = LAYOUT_universal(
    KC_QUOT  , KC_1     , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSLS  ,
    _______  , KC_INT1  , KC_INT3  , KC_GRV  , KC_LBRC  , KC_RBRC  ,                                         KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_INS   , _______  ,
    _______  , KC_CAPS  , _______  ,S(KC_HOME),S(KC_END), KC_DEL   ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______ , KC_HOME  ,         _LAYER_  , KC_END   ,                   _______  , _______  , _______       , _______  , RCTL(KC_RALT)
  ),

  [3] = LAYOUT_universal(
   S(KC_QUOT), S(KC_1)  , S(KC_2)  , S(KC_3) , S(KC_4)  , S(KC_5)  ,                                         S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  ,S(KC_BSLS),
    _______  ,S(KC_INT1),S(KC_INT3),S(KC_GRV),S(KC_LBRC),S(KC_RBRC),                                         S(KC_LEFT),S(KC_DOWN),S(KC_UP) ,S(KC_RGHT), _______  , _______  ,
    _______  , KC_F1    , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
                  _______  , KC_BTN2 , KC_BTN1  ,        S(KC_HOME), S(KC_END),                   _______  , _LAYER_  , _______       , _______  , _______
  ),

  [4] = LAYOUT_universal(
    MO(5)    , G(KC_1)  , G(KC_2)  , G(KC_3) , G(KC_4)  , G(KC_5)  ,                                         G(KC_6)  , G(KC_7)  , G(KC_8)  , G(KC_9)  , KC_BRIU  , KC_VOLU  ,
    _______  ,S(KC_LEFT),S(KC_DOWN), S(KC_UP),S(KC_RGHT), KC_PGUP  ,                                         C(KC_LEFT),C(KC_DOWN),C(KC_UP) ,C(KC_RGHT), KC_BRID  , KC_VOLD  ,
    _______  ,RWIN(KC_1),RWIN(KC_2),RWIN(KC_3),RWIN(KC_4),KC_PGDN  ,                                 RWIN(KC_LEFT),RWIN(KC_DOWN),RWIN(KC_UP),RWIN(KC_RGHT),_______, KC_MUTE  ,
                  _______  , _______ , _______  ,         _______  , _LAYER_  ,                   IME_TGL  , _______  , _______       , _______  , _______
  ),

  [5] = LAYOUT_universal(
    _LAYER_  , _______  , _______  , _______ , _______  , EE_CLR   ,                                         SSNP_FRE , SSNP_VRT , SSNP_HOR , SREV_VRT , SREV_HOR , _______  ,
    KBC_RST  , KBC_SAVE , CPI_D1K  , CPI_D100, CPI_I100 , CPI_I1K  ,                                         _______  , _______  , AG_RNRM  , _______  , _______  , _______  ,
    QK_BOOT  , _______  , SCRL_DVD , SCRL_DVI, _______  , _______  ,                                         _______  , _______  , AG_LNRM  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  , QK_KEY_OVERRIDE_ON,QK_KEY_OVERRIDE_OFF, _______       , _______  , _______
  ),
};
// clang-format on

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
uint32_t os_detect_callback(uint32_t trigger_time, void *cb_arg) {
    keyball.detected_host_os = detected_host_os();
    switch (keyball.detected_host_os) {
        case OS_WINDOWS:
#ifdef KEY_OVERRIDE_ENABLE
            key_override_on();
#endif
            set_single_persistent_default_layer(1);
            break;
        case OS_MACOS: {
            uint8_t mode = KEYBALL_SCROLL_REVERSE_VERTICAL | KEYBALL_SCROLL_REVERSE_HORIZONTAL;
            keyball_set_scroll_reverse_mode(mode);
#ifdef KEY_OVERRIDE_ENABLE
            key_override_off();
#endif
            set_single_persistent_default_layer(0);
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
    defer_exec(100, os_detect_callback, NULL);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 4:
            keyball_set_scroll_mode(true);
            keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
            break;
        case 5:
            keyball_set_scroll_mode(true);
            keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL);
            break;
        default:
            keyball_set_scroll_mode(false);
            keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
            break;
    }
    return state;
}

#ifdef KEY_OVERRIDE_ENABLE
#include "process_key_override.h"
#include "keymap_japanese.h"
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT), // @
    &ko_make_basic(MOD_MASK_SHIFT, S(KC_2), JP_AT), // @
    &ko_make_basic(0, S(KC_2), JP_AT), // @

    &ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC), // ^
    &ko_make_basic(MOD_MASK_SHIFT, S(KC_6), JP_CIRC), // ^
    &ko_make_basic(0, S(KC_6), JP_CIRC), // ^

    &ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR), // &
    &ko_make_basic(0, S(KC_7), JP_AMPR), // &

    &ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR), // *
    &ko_make_basic(0, S(KC_8), JP_ASTR), // *

    &ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN), // (
    &ko_make_basic(0, S(KC_9), JP_LPRN), // (

    &ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN), // )
    &ko_make_basic(0, S(KC_0), JP_RPRN), // )

    &ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN), // :

#ifdef TAP_DANCE_ENABLE
    &ko_make_basic(MOD_MASK_SHIFT, TD(TD_JP_EQL_MO2), JP_PLUS), // +
    // treat Ctrl+= as Zoom-in like US layout (=, + are on the same key)
    // cf. Ctrl+= is treated as Zoom-out in JP layout (-, = are on the same key)
    &ko_make_basic(MOD_MASK_CTRL, TD(TD_JP_EQL_MO2), C(JP_SCLN)),
#else
    // we can apply overrides but loose LT(layer,) effect
    &ko_make_with_layers_and_negmods(0, LT(2,KC_EQL), JP_EQL, ~0, (uint8_t) MOD_MASK_SHIFT | MOD_MASK_CTRL), // =
    &ko_make_basic(MOD_MASK_SHIFT, LT(2,KC_EQL), JP_PLUS), // +
    // treat Ctrl+= as Zoom-in like US layout (=, + are on the same key)
    // cf. Ctrl+= is treated as Zoom-out in JP layout (-, = are on the same key)
    &ko_make_basic(MOD_MASK_CTRL, LT(2,KC_EQL), C(JP_SCLN)),
#endif

    // we can apply overrides but loose RCTL_T() effect
    &ko_make_basic(MOD_MASK_SHIFT, RCTL_T(KC_MINS), JP_UNDS), // _

    &ko_make_with_layers_and_negmods(0, KC_QUOT, JP_QUOT, ~0, (uint8_t) MOD_MASK_SHIFT), // '
    &ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO), // "
    &ko_make_basic(0, S(KC_QUOT), JP_DQUO), // "

    &ko_make_with_layers_and_negmods(0, KC_GRV, JP_GRV, ~0, (uint8_t) MOD_MASK_SHIFT), // `
    &ko_make_basic(MOD_MASK_SHIFT, KC_GRV, JP_TILD), // ~
    &ko_make_basic(0, S(KC_GRV), JP_TILD), // ~

    &ko_make_with_layers_and_negmods(0, KC_BSLS, JP_BSLS, ~0, (uint8_t) MOD_MASK_SHIFT), // (backslash)
    &ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE), // |
    &ko_make_basic(0, S(KC_BSLS), JP_PIPE), // |

    &ko_make_with_layers_and_negmods(0, KC_LBRC, JP_LBRC, ~0, (uint8_t) MOD_MASK_SHIFT), // [
    &ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, JP_LCBR), // {
    &ko_make_basic(0, S(KC_LBRC), JP_LCBR), // {

    &ko_make_with_layers_and_negmods(0, KC_RBRC, JP_RBRC, ~0, (uint8_t) MOD_MASK_SHIFT), // ]
    &ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, JP_RCBR), // }
    &ko_make_basic(0, S(KC_RBRC), JP_RCBR), // }

    &ko_make_basic(0, KC_CAPS, JP_CAPS), // (CapsLock)

    NULL
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef TAP_DANCE_ENABLE
        case TD(TD_JP_EQL_MO2):  // list all tap dance keycodes with tap-hold configurations
            {
                tap_dance_action_t *action = &tap_dance_actions[TD_INDEX(keycode)];
                if (!record->event.pressed && action->state.count && !action->state.finished) {
                    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                    tap_code16(tap_hold->tap);
                }
            }
            break;
#endif
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
        case IME_TGL:
            switch (keyball.detected_host_os) {
            case OS_WINDOWS:
                if (record->event.pressed) {
#ifdef KEY_OVERRIDE_ENABLE
                    if (key_override_is_enabled()) {
                        tap_code16(JP_ZKHK);
                    } else {
#else
                    {
#endif
                        register_code16(KC_RALT);
                        wait_ms(10);
                        tap_code16(KC_GRV);
                        unregister_code16(KC_RALT);
                    }
                }
                return false;
            case OS_MACOS:
                if (record->event.pressed) {
                    register_code16(KC_LGUI);
                    wait_ms(10);
                    tap_code16(KC_SPC);
                    unregister_code16(KC_LGUI);
                }
                return false;
            }
            break;
#endif
        default:
            break;
    }
    return true;
}

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_btn1[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_btn2[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_btn3[] = {KC_J, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_btn1, KC_BTN1),
    COMBO(combo_btn2, KC_BTN2),
    COMBO(combo_btn3, KC_BTN3),
};
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
