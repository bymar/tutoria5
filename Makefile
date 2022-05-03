bin: tutoria5.c
	gcc $< -o $@ -lpthread

.PHONY: clean run

clean:
	rm bin
	
run:
	./bin -pthread