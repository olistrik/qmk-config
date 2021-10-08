# My QMK configs

This repo hosts the configs for my qmk keyboards as well as the build and flash script that I use for
programming them.

You are more than welcome to copy this repo and use it for your own keymaps.

# Rationale

I don't like how the typical way to manage keymaps with QMK is to fork the main repo. It's huge, I only
care about the keymap directory for my keyboard, and I cannot be bothered to deal with the hassle of
keeping my fork up to date with the main branch. The new QMK Cli tool basically does this for you, but
I don't feel that it is the solution.

My solution is docker, and not in the way that is described in the QMK documentation.
[There already exists a docker image of qmk](https://hub.docker.com/r/qmkfm/qmk_firmware), how well it
will be maintained is still to be seen, at the time of writing the last update to it was 2 months ago.
If needs be, I make my own image for QMK as part of this repo.

The basic structure of this repo is as follows:

- /
  - `flash` : the script that does all the legwork.
  - `.build`: for caching qmk build outputs.
  - `.env.local` : the system dependent variables for docker.
  - `<keymap>/`: arbitrarily named directories for keyboard configurations.
    - `.env.config`: the variables that the flash script needs to flash the keymap to the correct keyboard.
    - `config.h, keymap.c, etc.`: the keyboard configuration that would typically be placed in `/keyboards/<keyboard>/keymaps/<keymap>/`


That's it.

# How to use

## Setting up system settings.

First of all you need to create a `.env.local` file with the variables `IMAGE`, `ADD_GROUPS`, and `DEVICES`.

The first variable, `IMAGE` is optional, you may specify a different docker image to use instead of
the default `qmkfm/qmk_firmware:latest`.

The second variable is a group or list of groups to add to the user in the docker container to give it
permission to write to the keyboard. For me, I added this udev rule to allow the `plugdev` group
to write to my usb keyboards:

```
ACTION=="add", SUBSYSTEM=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE="664", GROUP="plugdev"
```

The vendor and product ids can probably be found with `dmesg`.

The final variable. `DEVICES` is the /dev device paths for your keyboards when they are in bootloader mode.
I haven't found a good reliable way of doing this, I used `tree` and `diff` to work out what changed
in `/dev` when I plugged in my keyboard. You'll have to find your own way.

From my limited experience though, if it's an ATMega based board then It's probably attaching as a serial
device on `/dev/ttyS{0, 1, 2, ...}`. If it's got a fancy dfu bootloader, like my Planck EZ and Elite-C lily58's do,
then it might be attaching somewhere in `/dev/bus/usb/XXX/YYY`.
If you specify a folder for the devices, that entire folder will be mounted into the docker container,
masking whatever was there originally. To this extent, if you know for sure it's mounting somewhere in `/dev/bus/usb`
you can specify that and docker will do the rest.

As an example, here is my `.env.local`:

```
  IMAGE=qmkfm/qmk_firmware:latest
  ADD_GROUPS=( "plugdev" "tty" "dialout" )
  DEVICES=( "/dev/bus/usb/001" )
```

Some notes on this, while I should only need the `plugdev` group, I seem to also require
`tty` and `dialout`.
I haven't specified a usb hub (001), but not a specific device. Depending on which USB socket I
plug my keyboard into it can end up being `/dev/bus/usb/001/{001,002,003, ...}` by mounting
the entire group, it doesn't matter where it's mounted to.

## creating a keymap.

Keymaps can be placed in any directory, at any depth. Organise them however you like.
At the end though, you should have a directory that contains whatever you would
normally have in `/qmk_firmware/keyboards/<my_keyboard>/keymaps/<my_keymap>/`. In addition to this,
you need to add a `.env.config` file that contains the three variables: `BOARD`, `VARIANT`, and `TARGET`.

`BOARD` is the name of the keyboard you are flashing as it is in the `/qmk_firmware/keyboards` directory of the qmk repo. This is the only required field.

`VARIANT` is the variant of the board you are building, they are usually found in subdirectories of the keyboard folder.

`TARGET` is the default build target of the keyboard. If you leave this out you will need to specify it when running the flash command.

As an example, if the command you would normally run to flash you keyboard would be:

```
$ make planck/ez/glow:kranex:dfu
```

Then your `.env.config` would look like:

```
BOARD=planck
VARIANT=ez/glow
TARGET=dfu
```

## Flashing

Once all of the above is configured, then you can flash your keymap using the flash script at the root of this repository.

It has the following usage:

```
flash <keymap_directory> [target]
```

You can override the default target specified in the `.env.config` by providing a target to the flash script.
This can be useful for flashing handedness to a split keyboard's eprom:

```
$ ./flash lily58 dfu-split-left
```
