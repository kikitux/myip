# myip-cli
myip-cli tool to show external/internal ip

## Build

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
mkdir build
cd build

 ./myip -h
use: ./myip [-6] [-i ethN]

 ./myip 
202.202.202.151

 ./myip -6
2222:ca7c:6097:2222:90aa:a4e8:cca9:e09c

 ./myip -i en1
192.168.1.201

 ./myip -i en1 -6
2222:ca7c:6097:2222:90aa:a4e8:cca9:e09c
```
