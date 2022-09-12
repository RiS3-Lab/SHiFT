#/bin/bash
AFL_NO_FORKSRV=1 ./afl-fuzz -i ./test/in -o ./test/out
