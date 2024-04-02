#include QMK_KEYBOARD_H

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _MORE
};

enum custom_keycodes {
    KC_QWERTY = QK_USER,
    WM_RCTR,
    WM_LCTR
};

enum unicode_names {
    MDASH, NDASH, SMILE, THUMB, ROFL, WINK, OK
};
const uint32_t PROGMEM unicode_map[] = {
    [MDASH] = 0x2014,
    [NDASH] = 0x2013,
    [SMILE] = 0x1F642,
    [ROFL] = 0x1F923,
    [THUMB] = 0x1F44D,
    [WINK] = 0x1F609,
    [OK] = 0x1F44C
};

#define C_RGHT  C(KC_RGHT)      // control(word) right
#define C_LEFT  C(KC_LEFT)      // control(word) left

// Window Manager (Gnome PaperWM)
#define WM_LEFT  G(KC_LEFT)
#define WM_MONL  G(S(KC_LEFT))
#define WM_RGHT  G(KC_RGHT)
#define WM_MONR  G(S(KC_RGHT))
#define WM_UP    G(KC_UP)
#define WM_DOWN  G(KC_DOWN)
#define WM_PGUP  G(KC_PGUP)
#define WM_PGDN  G(KC_PGDN)
#define WM_CNTR  G(KC_C)
#define WM_FULL  G(S(KC_F))     // Full screen
#define WM_VIEW  G(KC_TAB)
#define WM_SC_VW G(S(KC_ESC))   // Scratch View
#define WM_SC_TG G(C(KC_ESC))   // Scratch Toggle

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,  KC_SPC,  KC_ENT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,   XXXXXXX, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
              KC_LGUI,KC_LALT,KC_LCTL, MO(_MORE), MO(_RAISE),      MO(_LOWER),  KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX
),

[_LOWER] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
   KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                    C(KC_PGUP), KC_PGUP, KC_UP, KC_PGDN, C(KC_PGDN), KC_DEL,
 KC_TILDE, KC_CIRC, KC_AMPR, KC_ASTR,  KC_EQL, KC_MINS,                       KC_HOME, C_LEFT, KC_DOWN, C_RGHT,  KC_END,  XXXXXXX,
  KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_UNDS, _______,     _______, XXXXXXX, C(KC_LEFT), XXXXXXX, C(KC_RGHT), XXXXXXX, XXXXXXX,
                    _______, _______, _______, KC_LCTL, KC_LSFT,     XXXXXXX, _______, _______, _______, _______
),

[_RAISE] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                     _______,  _______  , _______,  _______ ,  _______ ,_______,
  XXXXXXX, XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , WM_SC_TG,                     KC_EQL,  KC_LPRN  , KC_ASTR,  KC_RPRN ,  KC_AMPR , KC_DEL,
  WM_PGUP, C(KC_Z) , C(KC_X) , C(KC_C) , C(KC_V) , WM_SC_VW,                     KC_MINS, KC_LBRC, KC_QUOT, KC_RBRC, KC_COLN, KC_SCLN,
  WM_PGDN, WM_LCTR , WM_LEFT , WM_CNTR , WM_RCTR , G(KC_R), _______,   _______,  KC_UNDS, KC_LCBR, KC_DQUO, KC_RCBR, KC_BSLS, KC_PIPE,
                    _______, _______, KC_LALT, KC_LCTL, _______,       _______,  _______, _______, _______, _______
),

[_MORE] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                     _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______, _______ , _______ , _______ , _______ , _______,                       KC_PEQL,    KC_7,    KC_8,    KC_9, XXXXXXX,  KC_DEL,
  _______, C(KC_Y) , _______ , _______ , _______ , _______,                       KC_PLUS,    KC_4,    KC_5,    KC_6,    KC_0, XXXXXXX,
  KC_LSFT, KC_LCTL,   KC_LALT,  KC_VOLD,  KC_VOLU, KC_MPLY, _______,  _______,  X(MDASH),    KC_1,    KC_2,    KC_3,  KC_DOT, XXXXXXX,
                        _______, _______, _______, _______, _______,  KC_RSFT, KC_RCTL, KC_RALT, _______, _______
)

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // Auto center window when going right with paperwm.
    case WM_RCTR:
      if (record->event.pressed) {
        tap_code16(G(KC_RGHT));
        tap_code16(G(KC_C));
      }
      break;

    // Auto center window when going left with paperwm.
    case WM_LCTR:
      if (record->event.pressed) {
        tap_code16(G(KC_LEFT));
        tap_code16(G(KC_C));
      }
      break;

    // Reset gnome display manager.
//    case WM_RSET:
//      if (record->event.pressed) {
//        tap_code16(A(KC_F2));
//        SEND_STRING(SS_DELAY(700) "r" SS_TAP(X_ENT));
//      }
//      break;

  }
  return true;
};


bool encoder_update_user(uint8_t index, bool clockwise) {
  switch (get_highest_layer(layer_state)) {
    case _RAISE:
        if (index == 0) {
            tap_code(clockwise ? KC_PGUP : KC_PGDN);
        } else if (index == 1) {
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
        }
        break;
    case _LOWER:
    case _MORE:
    default:
        if (index == 0) {
            tap_code(clockwise ? KC_RIGHT : KC_LEFT);
        } else if (index == 1) {
            tap_code(clockwise ? KC_UP : KC_DOWN);
        }
        break;
  }
  return false;
};
