lua-linuxsys
============

Lua bindings for selected Linux syscalls

Functions
---------
* chroot(path)
* mount(source, target, [type, flags, data])
* umount(target, [flags])
* unshare(flags)

Examples
--------
```lua
s = require 'linuxsys'
s.unshare(s.CLONE_NEWNS)
s.mount("/dev/sda1", "/test", "ext4")
s.mount("/tmp/a", "/tmp/b", nil, s.MS_BIND)
```
