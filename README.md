### Readme

This code doesn't work. I messed up and waited until spring break to start the homework, and I wasn't able to get it done.

I basically wrote the code for all of the features requested, but none of it works. I weighed my options and have come to the conclusion that while I could spend as much time as I could trying to debug the program, I would not have enough time to get it up and running before the due date, and even if I submitted late the grade deduction vs more working code would probably not be in my favor.

So, here's how it is: the written questions are complete. I cleaned up the code and added comments where I could. I have written code that would do the following, had there been no bugs: code that reads in and parses the scene file, code that computes image and changes eye position for DoF, code that reflects AA, code that works to create soft shadows, code that does both glossy refraction and reflaction (though this code I'm least sure on--ignoring bugs and the like, I have no idea if I wrote that part right), code that displays the image in SDL and allows the user to adjust samples, and files that represent the best capability of my ray tracer.

Since my ray tracer doesn't work, the scene file does not contain any surfaces or any lights. The ppm is just a black square. As of right now, the code spits out an SDL error, saying the texture data I'm trying to display is invalid--using VS, I find that the array is NULL. I'm truly sorry that this assignment went this way and I'm turning in broken code, but I just can't put anymore into this homework. I promise to do my best on the next few assignments.

Again, really sorry.


**References**

Sphere/ray intersection taken from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

Plane/ray intersection taken from
https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

Cross product taken from
http://www.sanfoundry.com/cpp-program-compute-cross-product-two-vectors/
