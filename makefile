"StrongholdSim.exe":
	g++ StrongholdSim.cpp robot.cpp utils/graph.cpp field/fieldnode.cpp game.cpp utils/utils.cpp field/field.cpp ui/console.cpp ui/interface.cpp -o "StrongholdSim.exe"  -ISDL2 -LSDL2 -lmingw32 -lSDL2main -lSDL2
