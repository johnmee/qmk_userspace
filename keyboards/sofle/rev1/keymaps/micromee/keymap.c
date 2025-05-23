// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _ONE,
    _TWO,
    _THREE,
};

enum custom_keycodes {
    ALTTAB = SAFE_RANGE,
    FWDTAB,
    BCKTAB
};

// Keys
#define C_RGHT  C(KC_RGHT)      // control(word) right
#define C_LEFT  C(KC_LEFT)      // control(word) left
#define C_CUT   C(KC_X)
#define C_PSTE  C(KC_V)
#define C_COPY  C(KC_C)
#define C_UNDO  C(KC_Z)

// Window Manager (Windows 11)
#define WM_LEFT  A(KC_LEFT)
#define WM_RGHT  G(KC_RGHT)
#define WM_UP    G(KC_UP)
#define WM_DOWN  G(KC_DOWN)
#define WM_PGUP  G(C(KC_LEFT))
#define WM_PGDN  G(C(KC_RGHT))
#define WM_CNTR  A(KC_TAB)


enum unicode_names {
    MDASH, NDASH, SMILE, THUMB, ROFL, WINK, OK
};
const uint32_t PROGMEM unicode_map[] = {
    [MDASH] = 0x2014,
    [NDASH] = 0x2013,
    [SMILE] = 0x1F642,   // 🙂
    [ROFL] = 0x1F923,
    [THUMB] = 0x1F44D,   // 👍
    [WINK] = 0x1F609,    // 😉
    [OK] = 0x1F44C       // 👌
};


// State tracking for alt-tab functionality
static bool alt_tab_active = false;
static bool alt_held = false;
static uint16_t alttab_timer = 0;

#define TAPPING_TERM_ALTTAB 200  // Adjust this value for tap/hold timing


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,  KC_SPC,  KC_ENT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    XXXXXXX,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                XXXXXXX, KC_LGUI, MO(_THREE), ALTTAB, XXXXXXX,       KC_RSFT, MO(_ONE),  KC_RCTL, KC_RALT, KC_RGUI
),

[_ONE] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
   KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   C(KC_PGUP), KC_PGUP,   KC_UP, KC_PGDN, C(KC_PGDN),  KC_DEL,
 KC_TILDE, KC_CIRC, KC_AMPR, KC_ASTR,  KC_EQL, KC_MINS,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, XXXXXXX,
  KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_UNDS, _______,    _______, XXXXXXX,  C_LEFT, XXXXXXX,  C_RGHT, XXXXXXX, KC_RSFT,
                    _______, _______, KC_LALT, KC_LCTL, KC_LSFT,    XXXXXXX, _______, _______, _______, _______
),

[_TWO] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  XXXXXXX, UM(THUMB), UM(OK), UM(WINK), UM(SMILE), XXXXXXX,                           KC_EQL,  KC_LPRN, KC_ASTR, KC_RPRN, KC_AMPR,  KC_DEL,
  G(C(KC_RGHT)), C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,                                KC_MINS, KC_LBRC, KC_QUOT, KC_RBRC, KC_COLN, KC_SCLN,
  G(C(KC_LEFT)), RCS(KC_Z), WM_CNTR, BCKTAB, FWDTAB, G(KC_R), _______,    _______,      KC_UNDS, KC_LCBR, KC_DQUO, KC_RCBR, KC_BSLS, KC_PIPE,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

[_THREE] = LAYOUT(
      _______, _______ , _______ , _______ , _______ , _______,                    _______,  _______  , _______,  _______ ,  _______ ,_______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_EQL,    KC_7,    KC_8,    KC_9, KC_ASTR,  KC_DEL,
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      KC_MINS,    KC_4,    KC_5,    KC_6,    KC_0, XXXXXXX,
      KC_LSFT, KC_LCTL, KC_LALT, _______, _______, KC_VOLD,  _______, _______,   KC_PLUS,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_RSFT,
                   _______, _______, _______, _______, _______,     KC_RSFT, KC_RCTL, KC_RALT, _______, _______
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALTTAB:
            if (record->event.pressed) {
                // Key pressed - start timer and activate layer
                alttab_timer = timer_read();
                alt_tab_active = true;
                layer_on(_TWO);
            } else {
                // Key released
                if (alt_tab_active) {
                    uint16_t elapsed = timer_elapsed(alttab_timer);

                    if (elapsed < TAPPING_TERM_ALTTAB && !alt_held) {
                        // Short press - send single Alt+Tab
                        tap_code16(A(KC_TAB));
                    }

                    // Clean up state
                    if (alt_held) {
                        unregister_code(KC_LALT);
                        alt_held = false;
                    }

                    alt_tab_active = false;
                    layer_off(_TWO);
                }
            }
            return false;

        case FWDTAB:
            if (record->event.pressed && alt_tab_active) {
                // Ensure Alt is held for navigation
                if (!alt_held) {
                    register_code(KC_LALT);
                    alt_held = true;
                }
                tap_code(KC_TAB);  // Send Tab (Alt is now held)
            }
            return false;

        case BCKTAB:
            if (record->event.pressed && alt_tab_active) {
                // Ensure Alt is held for navigation
                if (!alt_held) {
                    register_code(KC_LALT);
                    alt_held = true;
                }
                tap_code16(S(KC_TAB));  // Send Shift+Tab (Alt is now held)
            }
            return false;

        default:
            // Handle other keys on the alt-tab layer
            if (alt_tab_active && record->event.pressed) {
                // Check if we're on the alt-tab layer and this isn't a transparent key
                if (layer_state_is(_TWO)) {
                    // Release Alt if it was held, so other keys work normally
                    if (alt_held) {
                        unregister_code(KC_LALT);
                        alt_held = false;
                    }
                }
            }
            return true;  // Process all other keycodes normally
    }
}

//bool encoder_update_user(uint8_t index, bool clockwise) {
//    if (clockwise) {
//        if (!is_alt_tab_active) {
//            is_alt_tab_active = true;
//            unregister_code(KC_LSFT);
//            register_code(KC_LALT);
//        }
//        alt_tab_timer = timer_read();
//        tap_code(KC_TAB);
//    } else {
//        if (!is_alt_shift_tab_active) {
//            is_alt_shift_tab_active = true;
//            register_code(KC_LALT);
//            register_code(KC_LSFT);
//        }
//        alt_tab_timer = timer_read();
//        tap_code(KC_TAB);
//    }
//    return false;
//};



/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | QK_BOOT|      |QWERTY|COLEMAK|      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
