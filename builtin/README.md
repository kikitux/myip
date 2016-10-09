#

## deps

```
git://dev.alpinelinux.org/aports
cd ~/aports/main/bash/
cp APKBUILD
abuild unpack && abuild prepare && abuild build
```

## compile

```
BASH_DIR=../../aports/main/bash/src/bash-4.3 cmake .
make
make install
```


## use
```bash
enable -f ./builtin_myip builtin_myip 
```

