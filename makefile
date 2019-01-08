a.out:test.cc
	g++ -o $@ $^ -lpthread -g
.PHONY:clean 
clean:
	rm -f a.out

