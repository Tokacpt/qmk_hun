/**
 * Charybdis Nano - Hungarian keymap
 * Based on the vendor keymap, fully remapped for Windows Hungarian input.
 *
 * HOW TO TYPE HUNGARIAN:
 *   Accented vowels: HOLD the key slightly longer
 *     Hold A = á, Hold E = é, Hold O = ó, Hold U = ú, Hold I = í
 *
 *   For ö/ő/ü/ű: hold TAB (left inner thumb) then tap Z to toggle Hungarian layer
 *     S=ö, D=ő, J=ü, K=ű
 *     Tap Z again to turn Hungarian layer off
 *
 *   All symbols (numeral/symbol layers) are remapped to output correctly
 *   on Windows Hungarian input without needing to change Windows language.
 *
 *   NOTE: ^ and $ are not remapped (dead key / complex combo issues)
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_HUNGARIAN,
};

#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;
#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif
#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif
#endif

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif

// ── Windows Hungarian remapped symbols ───────────────────────────────────────
// To output English symbols while Windows is set to Hungarian input:
#define HU_MINS KC_SLSH        // - (slash key = minus in HU)
#define HU_EQL  S(KC_7)        // = (shift+7 = = in HU)
#define HU_LBRC RALT(KC_F)     // [ (AltGr+F in HU)
#define HU_RBRC RALT(KC_G)     // ] (AltGr+G in HU)
#define HU_BSLS RALT(KC_Q)     // \ (AltGr+Q in HU)
#define HU_SCLN RALT(KC_COMM)  // ; (AltGr+, in HU)
#define HU_QUOT S(KC_1)        // ' (shift+1 in HU)
#define HU_GRV  RALT(KC_7)     // ` (AltGr+7 in HU)
#define HU_SLSH S(KC_6)        // / (shift+6 in HU)
#define HU_TILD RALT(KC_1)     // ~ (AltGr+1 in HU)
#define HU_EXLM S(KC_4)        // ! (shift+4 in HU)
#define HU_AT   RALT(KC_V)     // @ (AltGr+V in HU)
#define HU_HASH RALT(KC_X)     // # (AltGr+X in HU)
#define HU_PERC S(KC_5)        // % (shift+5 in HU)
#define HU_AMPR RALT(KC_C)     // & (AltGr+C in HU)
#define HU_ASTR RALT(KC_MINS)  // * (AltGr+- in HU)
#define HU_LPRN S(KC_8)        // ( (shift+8 in HU)
#define HU_RPRN S(KC_9)        // ) (shift+9 in HU)
#define HU_UNDS S(KC_SLSH)     // _ (shift+- in HU)
#define HU_PLUS S(KC_3)        // + (shift+3 in HU)
#define HU_LCBR RALT(KC_B)     // { (AltGr+B in HU)
#define HU_RCBR RALT(KC_N)     // } (AltGr+N in HU)
#define HU_PIPE RALT(KC_W)     // | (AltGr+W in HU)
#define HU_DLR  RALT(KC_SCLN)  // $ (AltGr+; in HU - approximation)
#define HU_COLN S(KC_DOT)      // : (shift+. in HU)
#define HU_DQUT S(KC_2)        // " (shift+2 in HU)
#define HU_0    RALT(KC_GRV)   // 0 (AltGr+` in HU, since ` = 0)
#define HU_DOT  KC_DOT         // . (same in HU)
#define HU_COMM KC_COMM        // , (same in HU)

// ── Hungarian accented vowels (tap=normal, hold=accented) ─────────────────────
// á=KC_QUOT, é=KC_SCLN, ó=KC_EQL, ú=KC_RBRC in Windows HU
// í uses Unicode since it's on an ISO-only key
#define A_ACUT  MT(MOD_LCTL, KC_A)   // placeholder, handled via custom keycode
#define E_ACUT  MT(MOD_LCTL, KC_E)
// We use custom keycodes for tap-hold accents to avoid mod-tap conflicts

enum custom_keycodes {
    KA = SAFE_RANGE, // tap=a, hold=á
    KE,              // tap=e, hold=é
    KI,              // tap=i, hold=í (unicode)
    KO,              // tap=o, hold=ó
    KU,              // tap=u, hold=ú
    // Hungarian layer
    HUN_OE,          // ö
    HUN_OX,          // ő
    HUN_UE,          // ü
    HUN_UX,          // ű
};

// Tap-hold timing
#define TAPPING_TERM 200

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t key_timer;

    switch (keycode) {
        case KA:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    // tap: send a
                    tap_code(KC_A);
                } else {
                    // hold: send á (KC_QUOT in Windows HU)
                    tap_code(KC_QUOT);
                }
            }
            return false;

        case KE:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_E);
                } else {
                    // hold: send é (RALT+COMM in Windows HU)
                    tap_code16(RALT(KC_COMM));
                }
            }
            return false;

        case KI:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_I);
                } else {
                    // hold: send í via Unicode (Alt+numpad)
                    register_unicode(0x00ED);
                }
            }
            return false;

        case KO:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_O);
                } else {
                    // hold: send ó (S(KC_7) → = → but wait, = is ó in HU)
                    // KC_EQL = ó in Windows HU
                    tap_code(KC_EQL);
                }
            }
            return false;

        case KU:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_U);
                } else {
                    // hold: send ú (KC_RBRC in Windows HU)
                    tap_code(KC_RBRC);
                }
            }
            return false;

        case HUN_OE:
            if (record->event.pressed) tap_code(KC_0);   // ö in Windows HU
            return false;

        case HUN_OX:
            if (record->event.pressed) tap_code(KC_LBRC); // ő in Windows HU
            return false;

        case HUN_UE:
            if (record->event.pressed) tap_code(KC_MINS); // ü in Windows HU
            return false;

        case HUN_UX:
            if (record->event.pressed) tap_code(KC_BSLS); // ű in Windows HU
            return false;
    }
    return true;
}

// ── Layer definitions ─────────────────────────────────────────────────────────

// Base layer: letters remapped for Windows HU, tap-hold for accented vowels
// Note: Y and Z are correct because Windows HU keeps them as typed on this board
#define LAYOUT_LAYER_BASE                                                                      \
       KC_Q,    KC_W,    KE,      KC_R,    KC_T,    KC_Y,    KU,      KI,      KO,      KC_P, \
       KA,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  HU_QUOT, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  HU_COMM, HU_DOT,  HU_SLSH, \
                       ESC_MED, SPC_NAV, TAB_FUN, ENT_SYM, BSP_NUM

#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

// Function layer: Z = toggle Hungarian layer
#define LAYOUT_LAYER_FUNCTION                                                                  \
    _______________DEAD_HALF_ROW_______________, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, \
    ______________HOME_ROW_GACS_L______________, KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
    TG(LAYER_HUNGARIAN), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS, KC_F1,  KC_F2,  KC_F3, KC_F10, \
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX

#define LAYOUT_LAYER_MEDIA                                                                     \
    XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, \
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT, QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY

#define LAYOUT_LAYER_POINTER                                                                   \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

#define LAYOUT_LAYER_NAVIGATION                                                                \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
    ______________HOME_ROW_GACS_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    _______________DEAD_HALF_ROW_______________,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC

// Numeral layer: remapped for Windows HU
#define LAYOUT_LAYER_NUMERAL                                                                   \
    HU_LBRC,    KC_7,    KC_8,    KC_9, HU_RBRC, _______________DEAD_HALF_ROW_______________, \
    HU_SCLN,    KC_4,    KC_5,    KC_6,  HU_EQL, ______________HOME_ROW_GACS_R______________, \
    HU_GRV,     KC_1,    KC_2,    KC_3, HU_BSLS, _______________DEAD_HALF_ROW_______________, \
                       HU_DOT,   HU_0,  HU_MINS, XXXXXXX, _______

// Symbols layer: remapped for Windows HU
#define LAYOUT_LAYER_SYMBOLS                                                                   \
    HU_LCBR, HU_AMPR, HU_ASTR, HU_LPRN, HU_RCBR, _______________DEAD_HALF_ROW_______________, \
    HU_COLN,  HU_DLR, HU_PERC, XXXXXXX, HU_PLUS, ______________HOME_ROW_GACS_R______________, \
    HU_TILD, HU_EXLM,   HU_AT, HU_HASH, HU_PIPE, _______________DEAD_HALF_ROW_______________, \
                      HU_LPRN, HU_RPRN, HU_UNDS, _______, XXXXXXX

// Hungarian layer: ö/ő/ü/ű + toggle off on Z
#define LAYOUT_LAYER_HUNGARIAN                                                                 \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, HUN_OE,  HUN_OX,  XXXXXXX, XXXXXXX, XXXXXXX, HUN_UE,  HUN_UX,  XXXXXXX, XXXXXXX, \
    TG(LAYER_HUNGARIAN), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, _______, _______, _______, _______

// ── Home row mod and pointer mod macros ──────────────────────────────────────

#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// ── Keymaps ───────────────────────────────────────────────────────────────────

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE]       = LAYOUT_wrapper(POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))),
    [LAYER_FUNCTION]   = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
    [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
    [LAYER_MEDIA]      = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
    [LAYER_POINTER]    = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
    [LAYER_NUMERAL]    = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
    [LAYER_SYMBOLS]    = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
    [LAYER_HUNGARIAN]  = LAYOUT_wrapper(LAYOUT_LAYER_HUNGARIAN),
};

// ── Init ──────────────────────────────────────────────────────────────────────

void keyboard_post_init_user(void) {
    set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
}

// ── Pointing device ───────────────────────────────────────────────────────────

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif
    }
}
#    endif

layer_state_t layer_state_set_user(layer_state_t state) {
#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
#    endif
    return state;
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_update_pwm_buffers(void);
#endif
