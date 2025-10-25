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

enum layer_number {
    _BASE = 0,
    _NUMBER,
    _SYMBOL,
    _MEDIA,
    _CONFIG,
};

enum custom_user_keycodes {
    IME_TGL = QK_USER_0,
};

#define _LAYER_ _______ // should keep as transparent for momentarily layer activation

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_universal(
LT(_SYMBOL,KC_TAB), KC_Q, KC_W     , KC_E    , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , LT(_NUMBER,KC_EQL),
LCTL_T(KC_ESC),KC_A     , KC_S     , KC_D    , KC_F     , KC_G     ,                                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_MINS),
    KC_LSFT  , KC_Z     , KC_X     , KC_C    , KC_V     , KC_B     ,                                         KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                  KC_LALT  , KC_LGUI , KC_BTN1,LT(_NUMBER,KC_SPC)  ,LT(_MEDIA,KC_QUOT),     KC_BSPC,LT(_SYMBOL,KC_ENT), XXXXXXX       , XXXXXXX  , RALT_T(KC_BSLS)
  ),

  [_NUMBER] = LAYOUT_universal(
    KC_QUOT  , KC_1     , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSLS  ,
    _______  , KC_INT1  , KC_INT3  , KC_GRV  , KC_LBRC  , KC_RBRC  ,                                         KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_INS   , TT(_SYMBOL),
    KC_LSFT  , KC_CAPS  , _______  ,S(KC_HOME),S(KC_END), KC_DEL   ,                                         _______  , _______  , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                  _______  , _______ , KC_HOME  ,         _LAYER_  , KC_END   ,                   KC_BSPC  , _______  , XXXXXXX       , XXXXXXX  , RCTL(KC_RALT)
  ),

  [_SYMBOL] = LAYOUT_universal(
   S(KC_QUOT), S(KC_1)  , S(KC_2)  , S(KC_3) , S(KC_4)  , S(KC_5)  ,                                         S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  ,S(KC_BSLS),
    _______  ,S(KC_INT1),S(KC_INT3),S(KC_GRV),S(KC_LBRC),S(KC_RBRC),                                         _______  , KC_BTN1  , KC_BTN2  ,MO(_MEDIA),MO(_CONFIG),TG(_SYMBOL),
    _______  , KC_F1    , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
            LCTL(KC_LGUI)  , KC_LGUI , KC_BTN2  ,        S(KC_HOME), S(KC_END),                   KC_BSPC  , _LAYER_  , XXXXXXX       , XXXXXXX  , KC_RALT
  ),

  [_MEDIA] = LAYOUT_universal(
  MO(_CONFIG), G(KC_1)  , G(KC_2)  , G(KC_3) , G(KC_4)  , G(KC_5)  ,                                         G(KC_6)  , G(KC_7)  , G(KC_8)  , G(KC_9)  , KC_BRIU  , KC_VOLU  ,
    _______  , _______  , _______  , _______ , _______  , KC_PGUP  ,                                         C(KC_LEFT),C(KC_DOWN),C(KC_UP) ,C(KC_RGHT), KC_BRID  , KC_VOLD  ,
    KC_LSFT  , _______  , _______  , _______ , _______  , KC_PGDN  ,                                     LCA(KC_LEFT),LCA(KC_DOWN),LCA(KC_UP),LCA(KC_RGHT),_______, KC_MUTE  ,
                  _______  , _______ , _______  ,         _______  , _LAYER_  ,                   IME_TGL  , _______  , XXXXXXX       , XXXXXXX  , _______
  ),

  [_CONFIG] = LAYOUT_universal(
    _LAYER_  , _______  , _______  , _______ , _______  , EE_CLR   ,                                         SSNP_FRE , SSNP_VRT , SSNP_HOR , SREV_VRT , SREV_HOR , _______  ,
    KBC_RST  , KBC_SAVE , CPI_D1K  , CPI_D100, CPI_I100 , CPI_I1K  ,                                         _______  , _______  , AG_RNRM  , _______  , _______  , QK_RBT   ,
    QK_BOOT  , _______  , SCRL_DVD , SCRL_DVI, _______  , _______  ,                                         _______  , _______  , AG_LNRM  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  , QK_KEY_OVERRIDE_ON,QK_KEY_OVERRIDE_OFF, XXXXXXX       , XXXXXXX  , _______
  ),
};
// clang-format on

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
uint32_t os_detect_callback(uint32_t trigger_time, void *cb_arg) {
    keyball.detected_host_os = detected_host_os();
    if (keyball.detected_host_os != OS_MACOS) {
        // otherwise fallback to OS_WINDOWS
        keyball.detected_host_os = OS_WINDOWS;
    }
    switch (keyball.detected_host_os) {
        case OS_WINDOWS:
#ifdef KEY_OVERRIDE_ENABLE
            key_override_on();
#endif
            break;
        case OS_MACOS: {
            uint8_t mode = KEYBALL_SCROLL_REVERSE_VERTICAL | KEYBALL_SCROLL_REVERSE_HORIZONTAL;
            keyball_set_scroll_reverse_mode(mode);
#ifdef KEY_OVERRIDE_ENABLE
            key_override_off();
#endif
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
        case _MEDIA:
            keyball_set_scroll_mode(true);
            keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
            break;
        case _CONFIG:
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

    // LT(_NUMBER,KC_EQL) is handled in process_record_user

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
#ifdef KEY_OVERRIDE_ENABLE
        case LT(_NUMBER,KC_EQL):
            if (key_override_is_enabled()) {
                if (record->tap.count) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        uint8_t mod_state = get_mods();
                        if (mod_state & MOD_MASK_SHIFT) {
                            del_mods(MOD_MASK_SHIFT);
                            kc = JP_PLUS;
                        } else if (mod_state & MOD_MASK_CTRL) {
                            // treat Ctrl+= as Zoom-in like US layout (=, + are on the same key)
                            // cf. Ctrl+= is treated as Zoom-out in JP layout (-, = are on the same key)
                            del_mods(MOD_MASK_SHIFT);
                            kc = JP_SCLN; // ;, + are on the same key in JIS layout
                        } else {
                            kc = JP_EQL;
                        }
                        register_code16(kc);
                        set_mods(mod_state);
                        return false;
                    } else if (kc) {
                        unregister_code16(kc);
                        kc = 0;
                        return false;
                    }
                }
            }
            break;
        case LT(_MEDIA,KC_BSLS):
            if (key_override_is_enabled()) {
                if (record->tap.count) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        uint8_t mod_state = get_mods();
                        if (mod_state & MOD_MASK_SHIFT) {
                            del_mods(MOD_MASK_SHIFT);
                            kc = JP_PIPE;
                        } else {
                            kc = JP_BSLS;
                        }
                        register_code16(kc);
                        set_mods(mod_state);
                        return false;
                    } else if (kc) {
                        unregister_code16(kc);
                        kc = 0;
                        return false;
                    }
                }
            }
            break;
        case RALT_T(KC_QUOT):
            if (key_override_is_enabled()) {
                if (record->tap.count) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        uint8_t mod_state = get_mods();
                        if (mod_state & MOD_MASK_SHIFT) {
                            del_mods(MOD_MASK_SHIFT);
                            kc = JP_DQUO;
                        } else {
                            kc = JP_QUOT;
                        }
                        register_code16(kc);
                        set_mods(mod_state);
                        return false;
                    } else if (kc) {
                        unregister_code16(kc);
                        kc = 0;
                        return false;
                    }
                }
            }
            break;
#endif
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
        case KC_LALT:
            switch (keyball.detected_host_os) {
            case OS_WINDOWS:
                if (record->event.pressed) {
                    register_code16(KC_LGUI);
                } else {
                    unregister_code16(KC_LGUI);
                }
                return false;
            default:
                break;
            }
            break;
        case KC_LGUI:
            switch (keyball.detected_host_os) {
            case OS_WINDOWS:
                if (record->event.pressed) {
                    register_code16(KC_LALT);
                } else {
                    unregister_code16(KC_LALT);
                }
                return false;
            default:
                break;
            }
            break;
        case LCA(KC_LEFT):
        case LCA(KC_DOWN):
        case LCA(KC_UP):
        case LCA(KC_RGHT):
            switch (keyball.detected_host_os) {
            case OS_WINDOWS:
                keycode ^= (QK_LCTL | QK_LALT);
                keycode = RWIN(keycode);
                if (record->event.pressed) {
                    register_code16(keycode);
                } else {
                    unregister_code16(keycode);
                }
                return false;
            default:
                break;
            }
            break;
        case C(KC_LEFT):
        case C(KC_DOWN):
        case C(KC_UP):
        case C(KC_RGHT):
            switch (keyball.detected_host_os) {
            case OS_WINDOWS:
                keycode = RWIN(keycode);
                if (record->event.pressed) {
                    register_code16(keycode);
                } else {
                    unregister_code16(keycode);
                }
                return false;
            default:
                break;
            }
            break;
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
