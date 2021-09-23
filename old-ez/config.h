#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(ZELDA_PUZZLE)
//#define STARTUP_SONG SONG(MARIO_MUSHROOM)
//#define STARTUP_SONG SONG(PACMAN_THEME)
#endif

#define AUDIO_CLICKY

#define DAC_SAMPLE_MAX 65535U

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define PLANCK_EZ_LED_LOWER 1
#define PLANCK_EZ_LED_RAISE 2
#define PLANCK_EZ_LED_ADJUST 3

#define FIRMWARE_VERSION u8"wNE7d/5Bgb4"
