### _Disclaimer: I forgot to make a branch for part 1 so for now the master branch is the part 1 and the part 2 branch explains itself_

# EndlessRunner
## CPP course assignment 

For this assignment i did a three lane base where the objects come towards you while you have to avoid them. For the spawning of the cube I am using myself of an Actor that spawns the obstacles. The obstacles are an Actor class in itself which controls its movements but reads from a unreal game instance what speed it should have. The obstacle spawner sends the difficulty progress at the time to the game instance which later will supply the obstacles with it. The game instance is like a singleton in which it is accesible everywhere. 



## Part 2

Firstly for the part 2 I had to implement the destruction of the next obstacle when an obstacle is passed. When first making this project I used myself of unreals collision system. To know when the obstacles have passed the player I needed to get a reference to the player in the obstacles. Then i realised that it would be more efficent to calculate my own collision since it did not need physics. What i did was check the relative x position between the obstacle and the player. If it was less then 0 it would have passed and if the distance between them was less than a threshold they had collided. 

I also made a bot that will join the player in the game. The bot right now has 90% chance to dodge the obstacles. The bot can collide with the obstacles and the life between bot and player is shared right now.
