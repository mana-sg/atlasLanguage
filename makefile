.PHONY: run

run:
	@gcc -o atlas main.c modules/*.c && ./atlas && rm atlas
