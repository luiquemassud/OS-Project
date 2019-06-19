make:	runsc	runcs

runsc:	system_call.c
	gcc	-std=gnu99	-lrt	-o	runsc	system_call.c

runcs:	context_switch.c
	gcc	-std=gnu99	-lrt	-o	runcs	context_switch.c 

clean:
	rm	make	runsc	runcs	system_call.c	context_switch.c	makefile