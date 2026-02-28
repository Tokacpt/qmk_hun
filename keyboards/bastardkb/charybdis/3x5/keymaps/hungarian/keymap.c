#include QMK_KEYBOARD_H

enum custom_keycodes {
    HUN_A = SAFE_RANGE,
    HUN_E,
    HUN_I,
    HUN_O,
    HUN_OE,
    HUN_OX,
    HUN_U,
    HUN_UE,
    HUN_UX,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    bool shifted = get_mods() & MOD_MASK_SHIFT;

    switch (keycode) {
        case HUN_A:  register_unicode(shifted ? 0x00C1 : 0x00E1); return false;
        case HUN_E:  register_unicode(shifted ? 0x00C9 : 0x00E9); return false;
        case HUN_I:  register_unicode(shifted ? 0x00CD : 0x00ED); return false;
        case HUN_O:  register_unicode(shifted ? 0x00D3 : 0x00F3); return false;
        case HUN_OE: register_unicode(shifted ? 0x00D6 : 0x00F6); return false;
        case HUN_OX: register_unicode(shifted ? 0x0150 : 0x0151); return false;
        case HUN_U:  register_unicode(shifted ? 0x00DA : 0x00FA); return false;
        case HUN_UE: register_unicode(shifted ? 0x00DC : 0x00FC); return false;
        case HUN_UX: register_unicode(shifted ? 0x0170 : 0x0171); return false;
    }
    return true;
}

enum charybdis_keymap_layers { LAYER_BASE = 0, LAYER_HUN, LAYER_NAV };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LAYER_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        MO(LAYER_NAV), KC_ESC, KC_SPC,              KC_ENT,  MO(LAYER_HUN)
    ),

    [LAYER_HUN] = LAYOUT(
        XXXXXXX, XXXXXXX, HUN_E,   XXXXXXX, XXXXXXX, XXXXXXX, HUN_U,   HUN_I,   HUN_O,   XXXXXXX,
        HUN_A,   HUN_OE,  HUN_OX,  XXXXXXX, XXXXXXX, XXXXXXX, HUN_UE,  HUN_UX,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UC_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______,                   _______, _______
    ),

    [LAYER_NAV] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______,                   _______, _______
    ),
};

void keyboard_post_init_user(void) {
    set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
}
