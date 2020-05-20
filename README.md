# weirdOS

### Requirements:
  * x86 32-bit CPU
  * GNU GRUB
### Install for linux:
Add this to /etc/grub.d/40_custom
```
menuentry 'weirdOS' {
    multiboot /boot/mykernel.bin
    boot
}
```
Then run
```
make mykernel.bin
make install
sudo grub-mkconfig
```
