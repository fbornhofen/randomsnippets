INCDIR=-I/System/Library/Frameworks/JavaVM.framework/Headers 

CFLAGS=$(INCDIR) 

all: libjniex c

libjniex: jniex.c JniEx.h
	javac JniEx.java
	javah -jni JniEx
	gcc -fpic -shared jniex.c -o libjniexc.dylib $(CFLAGS)
	g++ -fpic -shared jniexcpp.cpp -o libjniexcpp.dylib $(CFLAGS)

c: libjniex
	rm -f libjniex.dylib
	ln -s libjniexc.dylib libjniex.dylib

cpp: libjniex
	rm -f libjniex.dylib
	ln -s libjniexcpp.dylib libjniex.dylib

clean:
	rm *.dylib *.class JniEx.h
