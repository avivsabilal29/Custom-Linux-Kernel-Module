savedcmd_/ldd/ldd.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T scripts/module.lds -o /ldd/ldd.ko /ldd/ldd.o /ldd/ldd.mod.o
