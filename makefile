"main.exe":
	g++ main.cpp robot.cpp utils/graph.cpp utils/linkedlist.cpp field/fieldnode.cpp game.cpp utils/utils.cpp field/field.cpp ui/console.cpp ui/interface.cpp -o "main.exe"  -ISDL2 -LSDL2 -lmingw32 -lSDL2main -lSDL2
