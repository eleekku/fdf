FDF is short for ’fil de fer’ in French which means ’wireframe model’.

"This project is about creating a simple wireframe
model of a landscape." -Subject

The representation in 3D of a landscape is a critical aspect of modern mapping. For
example, in these times of spatial exploration, to have a 3D representation of Mars is a
prerequisite condition to its conquest.

This project uses a graphical library called MLX42. This library can be found from GitHub and needs to be cloned in a dir called "lib".

As an input the program takes a file which is the map it is going to draw. The map consists of cordinates where the number tells the height. So for examle "0 5 0" would be three units on x axis, one unit on 1 axis and 0, 5 and 0 for the z axis.
The program also read rgb values attached to the z values in the map (see examples in test maps). 
The program does not validate the map so it is on users resposibility to give it a valid map as input. 

Keys:
Arrows: move the frame to different directions
Mouse wheel: zoom the frame. 
1 & 2: change the height multiplier.

This was the first graphics projects I have done and I really enjoyed it. It took me a while to finish this because I did not have clear plan for it.
I started with the idea that I want to draw a line and then to draw a 2d grid but that was not the most efficent way because I faced some trouble when I wanted to add the 3rd element to it. 
I ended up using the trigonometric approach for the 3d illusion but if I now did the project again I would probably try with matrixes. After all it's a learning journey and I really found out new stuff during this. 
