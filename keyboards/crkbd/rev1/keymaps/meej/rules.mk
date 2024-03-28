# Seems to configure all the hardware features.
# https://beta.docs.qmk.fm/using-qmk/hardware-features
# https://beta.docs.qmk.fm/developing-qmk/qmk-reference/getting_started_make_guide#rules-mk-options

# BOOTLOADER = caterina     # Pro-micro pin compatible controller
# BOOTMAGIC_ENABLE = no     # Access to the eeprom with a keyboard combo
# MOUSEKEY_ENABLE = no      # Keys to simulate mouse movements
# EXTRAKEY_ENABLE = yes     # System and Audio key control codes
# CONSOLE_ENABLE = no       # Enables debugging; send print messages to hid_listen
# COMMAND_ENABLE = no       # Send "magic" commands via key combo; eg turn NKRO on/off or console debug on/off
# SLEEP_LED_ENABLE = no     # Keyboard lights stay on although computer/cpu is in sleep mode
# NKRO_ENABLE = no          # Tell the OS to expect combinations of more than 6 keys simultaneously
# BACKLIGHT_ENABLE = no     # Some old thing. Specify the backlights pin in config.h

# RGBLIGHT_ENABLE = no      # Addressable RGB backlights.
# RGBLIGHT_SLEEP = no       # Turn out the lights when the host sleeps
# RGBLIGHT_SPLIT  = no      # Sync
# RGB_MATRIX_ENABLE = yes    # There is an RGB LED on every key.

# MIDI_ENABLE = no          # MIDI is a sound module. We don't have sound.
# UNICODE_ENABLE = no       # Unicode chars via UC(<code point>); covers most languages and symbols but not emojis.
# UNICODEMAP_ENABLE = yes   # Unicode chars via X(map_index); you'll need a map table in a keymap file.
# UCIS_ENABLE = no          # Unicode chars via mnemonic; needs map table in a keymap file.
# AUDIO_ENABLE = no         # A speaker is wired to the C6 pin.
# VARIABLE_TRACE = no       # Debugging/unit-testing trace on variables
# API_SYSEX_ENABLE = no     # Something to do with quantum Sysex API
# KEY_LOCK_ENABLE = no      # Key locking; artificially hold down a BASIC KEYCODE. 7%.
SPLIT_KEYBOARD = yes        # Dual MCUs need to work together.

OLED_ENABLE = no          # An OLED, or two, is attached.
# TAP_DANCE_ENABLE = no     # Double, or more, tapping


RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no
