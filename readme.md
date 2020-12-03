# Stronghold Sim
Stronghold Sim is an application designed as my final project for ELEC278 2020F at Queen's University.

It simulates a single robot playing the 2016 FIRST Robotics Compeition game, Stronghold. After the simulation is complete, users can navigate the list of events that occured during the simulation, alongisde a graphical representation of the field.

Due to it's dependancy on SDL2 and Windows.h, it can only be run on Windows.

Graphics are run with the SDL2 library, which is used under the [zlib license](https://www.zlib.net/zlib_license.html). A copy of the [license from the website](https://www.libsdl.org/license.php) can be found in the SDL2 folder. SDL2 source code can be found in ther [Mercurial repository](https://wiki.libsdl.org/SourceCode).

# Building
The source code includes the rquired SDL2 headers, libraries, and required dll file to build and run the application on Windows.

## makefile
There is a makefile in the root directory that can be used to build the executable.
## g++/gcc
The program can be built using g++ with the following command from the project root:
```
g++ main.cpp robot.cpp utils/graph.cpp field/fieldnode.cpp game.cpp utils/utils.cpp field/field.cpp ui/console.cpp ui/interface.cpp -o "main.exe"  -ISDL2 -LSDL2 -lmingw32 -lSDL2main -lSDL2
```

# Running
## Configuration
Information related to robot performance (such a speed, defenses, etc) is read from a confugraion file. This file is a CSV with the below columns. If the values exceed limits which would prevent simulation, errors are thrown. If values exceed limits which would hinder results, warnings are thrown which can be overriden.
| Name              | Type          | Description                                                                                                   |Values
|------             |------         |------------                                                                                                   |------
|team               |int            |Team number, used in output                                                                                    |0-9999
|can_low            |boolean        |Flag indicating if robot can go under low bar                                                                  |0 or 1
|shot_range         |unsigned char  |Maximum range for high goal shot [inches]                                                                      |0-170
|centre_shot_time   |unsigned char  |Time needed for centre high goal shot, 0 indicates unable [seconds]                                            |0-255
|side_shot_time     |int            |Time needed for side high goal shot, 0 indicates unable [seconds]                                              |0-255
|centre_angle       |unsigned char  |Maximum angle for shot at centre goal [degrees]                                                                |0-40
|side_angle         |unsigned char  |Angle for shot at side goal [degrees]                                                                          |0-40
|low_time           |unsigned char  |Time needed to store in low goal 0 indicates unable [seconds]                                                  |0-255
|defenses           |long int (hex) |Hex value representing time to cross defenses , `0` means cannot cross and `F` means it takes 15s [seconds]    |See below
|speed              |unsigned char  |Robot's speed [fpm]                                                                                            |1-255

### Defense Configuration
|Category   |Defense        |ID |Position  
|--------   |-------        |-- |--------  
|A          |Portcullis     |0  |0x0000000**F**
|"          |Cheval de Frise|1  |0x000000**F**0
|B          |Moat           |2  |0x00000**F**00
|"          |Ramparts       |3  |0x0000**F**000
|C          |Drawbridge     |4  |0x000**F**0000
|"          |Sally Port     |5  |0x00**F**00000
|D          |Rock Wall      |6  |0x0**F**000000
|"          |Rough Terrain  |7  |0x**F**0000000

## Inputs
Upon running the code, you will be asked to provide the following inputs:
 - Config File: Path to the config file, defaults to `../robots.csv`
 - Defense configuration: IDs for defenses to use, in order of position. Input should include one defense from each categotry. Defaults to `0 2 4 6`
 - Simulation length: The number of seconds of match time to be simulated, defaults to `150`

## Simulation
After inputs are provided, robot will be loaded and simulation will begin. This will take a shot amount of time to complete, depending on sim duration.

## Event View
Once the simulation is complete, you will be able to see the list of events that occured during the math. Events include driving between nodes, crossing defense, intaking a ball, and scoring goals.

### Console
The console is the primary UI component. It shows the complete event list, with time, robot, location and a description for each event. 

Events can be navigated using the up/down arrow keys. The currently selected event will be coloured light-blue.

On the right, the time, score, and defense stats at the selected event can be seen

Press escape at any time to exit

### Field GUI
The Field GUI is a complimentary window which shows an image of the field with a marker at the robot's currrent location, a line to it's previous, and a line showing the planned path, all with respect to the currently selected node.

By pressing `g` in the console window, the graph will cylce between hidden, nodes only, and nodes + edges.