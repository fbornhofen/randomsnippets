#!/bin/sh

make c
java -Djava.library.path=. JniEx

make cpp
java -Djava.library.path=. JniEx

