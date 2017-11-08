# pixel-Di
The quest to discover simple primitives and techniques to effectively provision and divide the work between multiple cores makes this project interesting. This is a test bed for distributed experiements.

*Experiments:*

1. Initial experiment builds a balanced binary search tree with 250K random keys. 

2. Metrics: Measures the time taken to build the tree. The goal is to cut the time to build the tree using multi-cores effectively.

3. System used: Intel i7 with 4 cores and 8 HW threads of execution with 8 GB memory.

# Results 

The initial experiments use the pixel-Da static library and the pixel-Di framework.

                                 	n	                t(ms)	  stl_map			
1). Single thread runs the BST builder	

   {tree_builder_single_thread	 7570ms} | { stl map   3488ms}

2). Tree_builder uses two threads using multiple cores

Time cut to  4205ms for bst 234 tree. Time measured includes thread creation and launch.
These threads use OS scheduled CPU core;

3). User assigns specifs cpu_core to the two threads		

Tiem take: 4389	ms

* Note the comparison with stl map which uses a red-black tree. Our code is a 2-3-4 balanced tree and the code is hardly optimized for memory or speed. So there are a lot of improvements to be had.
