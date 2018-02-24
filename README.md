# pixel-Di

Today, programming multiple core CPUs is an expert friendly job. 

Can this be simplified? Can we hide the complexity cleverly into a library for users to express and utilize for varoious use cases? Perhaps programming multicores can be made as simple as using a declarative programming language like SQL? 

I hear you laugh! But, I happen to beleive this is a necessity for modern day applications are compute hungry and programing them needs a balance between "the edge" and "the cloud".

The quest here is to learn from what others have done and provide a simpler programming model for multi-cores. 

Computing today live on the Edge!
==============

Please allow me to explain. 

Have you seen the movie I Robot? 

You know the thing that defies Will Smith and tries to out run him probably has tens of hundreads of processors running inside it. It has no time to contact the cloud while it is busy escaping from Will Smith, who intends to destroy it, you see! 

The same is the case with an autonomous vehical that google, ford, uber etc. are all busy creating! 

Why, even my dingy 3 years old mobile phone now carries a multicore CPU!

Why choose C++?
==============

There are many programming languages such as erlang that do a fine job of abstracting the multiple-cores and to present a lightweight process and programming model that helps hide the complexity. However, these languages have a different origin and purpose. Erlang is far from offering a declarative language, although it does a fine job about how a distributed service is included or called from your program.

IOT projects frequently employ resource constrained devices as well as rich devices and they expect your application platform to run on both! This can be a challenge with some languges such as Java. In a recent project, the minimum memory requirement for a simple control application written in Java could not be brought below 2 GB. This forced the manufacturer to keep the device memory above a certain threshold. Now, C++ or C offers much more control over the memory requirement with the caveat that some of the most basic protocols and services such as HTTP that you take for granted in Java needs to be built!

Hopefully, I have you nodding that a library written in C++ and providing a simple descriptive programming language can be a worthy attempt! 

Early in my career, I had to program a super scalar, super computing Intel CPU by hand. Yes. Hand transcribing the opcodes without the help of a compiler or a translator. Call me crazy!  I was coding this graphics accelerator library and the Intel CPU provided specialized instructions with two parallel cores! So, I learnt to program the two cores!

This experience should allow me to approach the problem(s) of parallel execution of CPU, GPU and FPU cores with some level of confidence, I hope. 

Distributed experiements
==============

This is my scratch space to run some experimental code. So you can skip these without loosing anything.

*Experiments:*

1. Initial experiment builds a balanced binary search tree with 250K random keys. 

2. Metrics: Measures the time taken to build the tree. The goal is to cut the time to build the tree using multi-cores effectively.

3. System used: Intel i7 with 4 cores and 8 HW threads of execution with 8 GB memory.

Results 
=======

The initial experiments use the pixel-Da static library and the pixel-Di framework.

                                 	n	                t(ms)	  stl_map			
1). Single thread runs the BST builder	

   {tree_builder_single_thread	 7570ms} | { stl map   3488ms}

2). Tree_builder uses two threads using multiple cores

Time cut to  4205ms for bst 234 tree. Time measured includes thread creation and launch.
These threads use OS scheduled CPU core;

3). User assigns specifs cpu_core to the two threads		

Tiem take: 4389	ms

* Note the comparison is with stl map which uses a red-black tree. Our code is a 2-3-4 balanced tree and the code is hardly optimized for memory or speed. So there are a lot of improvements to be had.
