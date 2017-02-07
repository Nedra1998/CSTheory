.PHONY : cpp
cpp:
	@setterm -fore blue
	@printf "COMPILING\n"
	@setterm -fore white
	clang++ string_num.cpp -o b.out
	@setterm -fore red
	@printf "TESTING\n"
	@setterm -fore white
	@./b.out test_file this

.PHONY : c
c:
	@setterm -fore blue
	@printf "COMPILING\n"
	@setterm -fore white
	clang string_num.c -o a.out
	@setterm -fore red
	@printf "TESTING\n"
	@setterm -fore white
	@./a.out test_file this
