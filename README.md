# EndlessRunner
CPP course assignment 

For this assignment i did a three lane base where the objects come towards you while you have to avoid them. For the spawning of the cube I am using myself of an Actor that spawns the obstacles. The obstacles are an Actor class in itself which controls its movements but reads from a unreal game instance what speed it should have. The obstacle spawner sends the difficulty progress at the time to the game instance which later will supply the obstacles with it. The game instance is like a singleton in which it is accesible everywhere. 
