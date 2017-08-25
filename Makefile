OBJS:=LCD1602.rel main.rel
all:$(OBJS)
	sdcc $(OBJS) -o DHT11.hex

$(OBJS):%.rel:%.c
	sdcc -c -o $@ $<

clean:
	-rm -f $(OBJS) *.ihx *.lk *.lst *.map *.mem *.rst *.sym *.asm
