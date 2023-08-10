all:
	cd src && $(MAKE) && cp kernel.bin ../

clean:
	rm kernel.bin
	cd src && $(MAKE) clean
