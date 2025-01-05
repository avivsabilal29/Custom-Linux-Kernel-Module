savedcmd_/ldd/ldd.mod := printf '%s\n'   ldd.o | awk '!x[$$0]++ { print("/ldd/"$$0) }' > /ldd/ldd.mod
