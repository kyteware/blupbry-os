all:
	cd src && \
		if [ ! -d libpi ]; \
		then \
			git clone https://github.com/dddrrreee/cs140e-23win; \
			mv cs140e-23win/libpi .; \
			rm -rf cs140e-23win; \
		fi && \
		$(MAKE) && \
		cp kernel.bin ../

clean:
	rm -rf *.bin
	rm -rf src/cs140e-23win src/libpi
	cd src && $(MAKE) clean
