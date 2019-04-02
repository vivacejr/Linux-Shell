shell: \
			start.o \
			input_parsing.o \
			mainloop_execute.o \
			prompt.o \
			built_in.o \
			ls.o \
		    pinfo.o \
			clock.o \
			remindme.o \
			piping.o \
			redirect.o \
			
	gcc -g -o shell $^


clean:
	@rm -f *.o shell

start.o:  header.h 
	gcc -g -c start.c

input_parsing.o:  header.h 
	gcc -g -c input_parsing.c

mainloop_execute.o:  header.h  
	gcc -g -c mainloop_execute.c

prompt.o:  header.h  
	gcc -g -c prompt.c

built_in.o:  header.h  
	gcc -g -c built_in.c

ls.o:  header.h  ls.c
	gcc -g -c ls.c


pinfo.o:  header.h  
	gcc -g -c  pinfo.c

clock.o:  header.h  
	gcc -g -c  clock.c

remindme.o:  header.h  
	gcc -g -c  remindme.c

piping.o: header.h
	gcc -g -c piping.c

redirect.o: header.h
	gcc -g -c redirect.c