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
    ALTLAYER = SAFE_RANGE,
    ALTTAB,
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,  KC_SPC,  KC_ENT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    XXXXXXX,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
             KC_LGUI,  KC_LALT, KC_LCTL, MO(_THREE), ALTLAYER,       MO(_ONE),  KC_RCTL, KC_RALT, KC_RGUI, KC_RSFT
),

[_ONE] = LAYOUT(
   KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
   KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   C(KC_PGUP), KC_PGUP,   KC_UP, KC_PGDN, C(KC_PGDN),  KC_DEL,
 KC_TILDE, KC_CIRC, KC_AMPR, KC_ASTR,  KC_EQL, KC_MINS,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, XXXXXXX,
  KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_UNDS, _______,    _______, XXXXXXX,  C_LEFT, XXXXXXX,  C_RGHT, XXXXXXX, KC_RSFT,
                    _______, _______, KC_LALT, KC_LCTL, KC_LSFT,    XXXXXXX, _______, _______, _______, _______
),

[_TWO] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  XXXXXXX, UM(THUMB), UM(OK), UM(WINK), UM(SMILE), XXXXXXX,                            KC_EQL,  KC_LPRN, KC_ASTR, KC_RPRN, KC_AMPR,  KC_DEL,
  G(C(KC_RGHT)), C(KC_Z), C(KC_X), C(KC_C), C(KC_V), G(KC_UP),                         KC_MINS, KC_LBRC, KC_QUOT, KC_RBRC, KC_COLN, KC_SCLN,
  G(C(KC_LEFT)), RCS(KC_Z), BCKTAB, ALTTAB, FWDTAB, G(KC_DOWN), _______,    _______,     KC_UNDS, KC_LCBR, KC_DQUO, KC_RCBR, KC_BSLS, KC_PIPE,
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



// State tracking
static bool alt_layer_active = false;
static bool alt_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALTLAYER:
            if (record->event.pressed) {
                // Key pressed - activate layer 1
                alt_layer_active = true;
                layer_on(_TWO);
            } else {
                // Key released - deactivate layer and clean up
                if (alt_layer_active) {
                    // Release Alt if it's being held
                    if (alt_held) {
                        unregister_code(KC_LALT);
                        alt_held = false;
                    }

                    alt_layer_active = false;
                    layer_off(_TWO);
                }
            }
            return false;

        case ALTTAB:
            if (record->event.pressed && alt_layer_active) {
                // Send Alt+Tab with release (toggle between current and last window)
                tap_code16(A(KC_TAB));
            }
            return false;

        case FWDTAB:
            if (record->event.pressed && alt_layer_active) {
                // Hold Alt if not already held, then send Tab
                if (!alt_held) {
                    register_code(KC_LALT);
                    alt_held = true;
                }
                tap_code(KC_TAB);
            }
            return false;

        case BCKTAB:
            if (record->event.pressed && alt_layer_active) {
                // Hold Alt if not already held, then send Shift+Tab
                if (!alt_held) {
                    register_code(KC_LALT);
                    alt_held = true;
                }
                tap_code16(S(KC_TAB));
            }
            return false;

        default:
            return true;  // Process all other keycodes normally
    }
}



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
