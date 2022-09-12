#!/usr/bin/env python3

import random

randomGuard = "uint16_t randomGuard [] = {\n"

element = 0


for i in range(65536):
    auxStr = str(random.randint(1, 1024*64))
    randomGuard =  randomGuard + auxStr + ", "
    element = element + 1
    if(element == 16):
        randomGuard = randomGuard +"\n"
        element = 0

randomGuard = randomGuard[:-2] + "}"

f=open("./Core/Inc/random_guard.h","w")
f.write("#include <stdint.h>\n\n")
f.write(randomGuard)
f.close()