all:
	@$(MAKE) -C src

clean:
	rm -rf pesim
	@$(MAKE) clean -C src
