# weirdOS

### Requirements:
  * x86 CPU
  * GNU GRUB
### Install for linux:
Add this to grub.cfg
```
### BEGIN MYKERNEL ###
menuentry 'weirdOS' {
    multiboot /boot/mykernel.bin
    boot
}
### END MYKERNEL ###
```
Then run
```
make mykernel.bin
make install
```
