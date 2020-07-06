cc = gcc
deps = $(shell find ./-name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c = %.o)
prom = searck-cli

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.c$(deps)
	$(cc) -c $ < -o $@

clean:
	rm -rf $(obj) $(prom)
