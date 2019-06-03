slave: bot.o bot_func.o execute.o bot.h
	gcc -o slave bot.o bot_func.o execute.o bot.h
bot.o: bot.c bot.h
	gcc -c bot.c bot.h
bot_func.o: bot_func.c bot.h
	gcc -c bot_func.c bot.h
execute.o: execute.c bot.h
	gcc -c execute.c bot.h
