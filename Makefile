OBJS:=LCD1602.rel main.rel
TARGET_EXEC:=DHT11.hex
$(TARGET_EXEC):$(OBJS)
	sdcc $(OBJS) -o $(TARGET_EXEC)

$(OBJS):%.rel:%.c
	sdcc -c -o $@ $<

.PHONY: all clean

all:$(TARGET_EXEC)

clean:
	-rm -f $(TARGET_EXEC) $(OBJS) *.ihx *.lk *.lst *.map *.mem *.rst *.sym *.asm
