# pixel-Di
The quest to discover simple primitives and techniques to effectively provision and divide the work between multiple cores makes this project interesting. This is a test bed for distributed experiements.

*Experiements:*

1. Initial experiment builds a balanced binary search tree with 250K random keys. 

2. Metrics: Measures the time taken to build the tree. The goal is to cut the time to build the tree using multi-cores effectively.

3. System used: Intel i7 with 4 cores and 8 HW threads of execution with 8 GB memory.

4. Results 

The initial experiments use the pixel-Da static library and the pixel-Di framework.

                                 	n	                t(ms)	  stl_map			
i). uses a single thread	

   {tree_builder_single_thread	 7570ms} | { stl map   3488ms}

ii). tree_builder_two_threads	  

Time cut to  4205ms for bst 234 tree. These threads use OS scheduled CPU core; Time measured includes thread creation and 
launch.	

iii). tree_builder_two_threads_user_Specified_cpu_core		4389				

* Note the comparison with stl map which uses a red-black tree. Our code is a 2-3-4 balanced tree and the code is hardly optimized for memory or speed. So there is a lot of improvements possible.



