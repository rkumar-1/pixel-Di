# pixel-Di
The quest to discover simple primitives and techniques to effectively provision and divide the work between multiple cores makes this project interesting. This is a test bed for distributed experiements.

Experiements:

1. Initial experiment is a Tree builder. It builds a BST with about 250K random key value pairs utilizing a single core of a multi-core system and then expands the load to multiple cores. It then assigns specific cores to process specific part of the task of building a tree.

                                 	n	                t(ms)	  stl_map			
tree_builder_single_thread	250,000	                7570	3488		uses one thread	
tree_builder_two_threads	  250,000	                4205			    uses 2 threads - OS scheduled CPU core; time includes thread creation and launch.	
tree_builder_two_threads_user_Specified_cpu_core		4389				

* Note the comparison with stl map which uses a red-black tree. Our code is a 2-3-4 balanced tree and the code is hardly optimized for memory or speed. So there is a lot of improvements possible.



