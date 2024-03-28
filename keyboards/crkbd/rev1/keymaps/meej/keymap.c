#include QMK_KEYBOARD_H

// Keys
#define C_RGHT  C(KC_RGHT)      // control(word) right
#define C_LEFT  C(KC_LEFT)      // control(word) left
#define C_CUT   C(KC_X)
#define C_PSTE  C(KC_V)
#define C_COPY  C(KC_C)
#define C_UNDO  C(KC_Z)

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

enum custom_keycodes {
    WM_RSET = SAFE_RANGE,
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Base Layer
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  KC_SPC,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(5),   MO(2),      MO(1), KC_RCTL, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  // Edit
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   C(KC_PGUP), KC_PGUP,   KC_UP, KC_PGDN, C(KC_PGDN),  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TILDE,RCS(KC_Z),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, C_LEFT,  XXXXXXX,  C_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LCTL, KC_LSFT,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols and WM
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,WM_SC_TG,                      KC_PEQL, KC_LPRN, KC_ASTR, KC_RPRN, KC_AMPR,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      WM_PGUP, C(KC_Z), C(KC_X), C(KC_C), C(KC_V),WM_SC_VW,                      KC_MINS, KC_LBRC, KC_QUOT, KC_RBRC, KC_COLN, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      WM_PGDN, WM_LCTR, WM_LEFT, WM_CNTR, WM_RCTR, G(KC_R),                      KC_UNDS, KC_LCBR, KC_DQUO, KC_RCBR, KC_BSLS, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LCTL, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // Func.
  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_CIRC,    KC_7,    KC_8,    KC_9, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      KC_PLUS,    KC_4,    KC_5,    KC_6,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LCTL, KC_LALT, KC_VOLD, KC_VOLU, KC_MPLY,                     X(MDASH),    KC_1,    KC_2,    KC_3,  KC_DOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    KC_RSFT, KC_RCTL, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )

};


// Macros
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

//void set_layer_color(int layer) {
//    switch (layer) {
//        case 0:
//            // Set RGB to Green
//            rgblight_setrgb(0x00, 0xFF, 0x00);
//            break;
//        case 1:
//            // Set RGB to Red
//            rgblight_setrgb(0xFF, 0x00, 0x00);
//            break;
//        case 2:
//            // Set RGB to Blue
//            rgblight_setrgb(0x00, 0x00, 0xFF);
//            break;
//        case 5:
//            rgblight_setrgb(0x00, 0x00, 0x00);
//            break;
//        default:
//            rgblight_setrgb(0xFF, 0xFF, 0xFF);
//            break;
//    }
//}

//layer_state_t layer_state_set_user(layer_state_t state) {
//    set_layer_color(get_highest_layer(state));
//    return state;
//}


//void keyboard_post_init_user(void) {
//    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
//    rgb_matrix_sethsv_noeeprom(HSV_OFF);
//}
//
////orange,rose,violet,azure,springgreen,chartreuse
//bool rgb_matrix_indicators_user(void) {
//        switch(get_highest_layer(layer_state|default_layer_state)) {
//            case 0:
//                rgb_matrix_set_color_all(RGB_RED);
//                break;
//            case 1:
//                rgb_matrix_set_color_all(RGB_MAGENTA);
//                break;
//            case 2:
//                rgb_matrix_set_color_all(RGB_BLUE);
//                break;
//            case 3:
//                rgb_matrix_set_color_all(RGB_CYAN);
//                break;
//            default:
//                rgb_matrix_set_color_all(255, 102, 102);
//                break;
//        }
//        return false;
//}
