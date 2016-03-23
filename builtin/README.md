#

#

git://dev.alpinelinux.org/aports
cd ~/aports/main/bash/

cp APKBUILD

abuild unpack && abuild prepare && abuild build

use:
```bash
enable -f ./builtin_myip builtin_myip 
```

