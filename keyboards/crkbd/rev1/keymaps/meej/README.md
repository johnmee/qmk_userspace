# JohnMee layout

They have moved everything around again, so now that I have thought I should follow the kool-aid and use
my own fork, they appear to have appreciated that everyone in the world commiting their own keymaps is 
going to get unmanageable, and have some new concoction of userspaces I'm not sure I grok.

On this read-through I have forked and added my corne keymap to `./keyboards/crkbd/keymaps/meej/`.

```buildoutcfg
# To flash (and press the little reset button). Switch the word `right` and `left` respective to the half you are flashing.
$ qmk flash -bl dfu-split-right

# Or to bypass the user config and specify the keyboard and keymap
$ qmk flash -bl dfu-split-left -keyboard crkbd -keymap default
```

This is what it used to be:
```
# I used to establish my keebs with a symlink... (adjust to suit).
$ ln -s ~/projects/keebs/meej/niumini ~/projects/keebs/qmk/qmk_firmware/keyboards/niu_mini/keymaps/meej
$ ln -s ~/projects/keebs/meej/planckez ~/projects/keebs/qmk/qmk_firmware/keyboards/planck/keymaps/meej


qmk flash -kb crkbd -km meej -bl :dfu-split-right
```

I installed it with linuxbrew this time.
And set `~/.config/qmk/qmk.ini` defaults to `crkbd` and `meej`.

```
$ git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
$ (git pull --recurse-submodules)   
$ cd qmk_firmware
$ util/qmk_install.sh

$ ln -s ~/projects/keebs/myplanck ~/projects/keebs/qmk_firmware/keyboards/planck/keymaps/meej
$ make git-submodule
$ make planck/ez:meej:flash
$ make niu_mini:meej:flash  (plug the keeb directly into the computer--no usb hub!!)
```
