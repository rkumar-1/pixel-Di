#pragma once
#include "bst_234_v3.h"

#include "hw__concurrency.h"
#include "CpuTopology.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <random>
#include <map>


using namespace pixelda;


// levers to control thread life cycle properties
enum class thread_config_variants {
	os_scheduled_threads,
	user_assigned_cpu_core,
	user_assigned_cpu_core_with_realtime_boost
};

// scheduler
class di_testbed
{
	std::mutex iomutex;
	using Keys = vector<pair<int, int>>;
public:
	di_testbed() {

	}

	~di_testbed() {

	}

	// intel 
	long GetCurrentProcessorNumberXP(void)
	{
		_asm {mov eax, 1}
		_asm {cpuid}
		_asm {shr ebx, 24}
		_asm {mov eax, ebx}
	}

	void measure_tree_construction_performance() {
		//launch_tree_builder_one_thread();
		//launch_tree_builder_os_assigned_two_threads();
		build__a_search_tree_user_assigned_cpu_bound_threads();
	}

	void build_2_3_4_search_tree(Keys& kv) {
		// build the 2-3-4 search tree
		bst_234_v3 bst2(kv);

		// lookup a random key
		int search_key = kv[kv.size() / 4].first;
		int value = bst2.find(search_key);

		//bst2.print_bfs();
	}

	void build_stl_red_black_search_tree(Keys& kv) {
		// stl measurement (uses red-black tree)
		map<int, int> m;
		for (auto x : kv) {
			m[x.first] = x.second;
		}

		// lookup a random key
		int search_key = kv[kv.size() / 4].first;
		auto result = m.find(search_key);
	}

	void builder_thread_handler_single(string& our_name) {
		print_cpu(our_name);

		long number_of_elements = 250000; // -100000;

		// produces a given count of key-value pairs to seed the Tree
		Keys&& kv = build_key_value_random_inputs(number_of_elements);

		// now go build your search tree
		build_2_3_4_search_tree(kv);
		build_stl_red_black_search_tree(kv);
	}

	void launch_tree_builder_one_thread() {

		string processor_name("tree_builder");
		thread tree_builder(&di_testbed::builder_thread_handler_single, this, processor_name);
		tree_builder.join();
	}

	void builder_thread_handler_two_threads_shared_load(string& our_name, Keys& kv) {
		print_cpu(our_name);

		// now go build your search tree
		build_2_3_4_search_tree(kv);
		//build_stl_red_black_search_tree(kv);
	}

	void launch_tree_builder_os_assigned_two_threads() {

	   // produces a given count of key-value pairs to seed the Tree
		long number_of_elements = 250000; // -100000;
		Keys&& kv_set_1 = build_key_value_random_inputs(number_of_elements / 2);
		Keys&& kv_set_2 = build_key_value_random_inputs(number_of_elements / 2);

		string processor_name("tree_builder os_assigned_two_threads");
		thread tree_builder_1(&di_testbed::builder_thread_handler_two_threads_shared_load, this, processor_name, kv_set_1);
		thread tree_builder_2(&di_testbed::builder_thread_handler_two_threads_shared_load, this, processor_name, kv_set_2);

		tree_builder_1.join();
		tree_builder_2.join();
	}

	void builder_thread_handler_two_threads_user_assigned_shared_load(string& our_name, Keys& kv) {
		print_cpu(our_name);

		// now go build your search tree
		build_2_3_4_search_tree(kv);
		//build_stl_red_black_search_tree(kv);
	}

	void build__a_search_tree_user_assigned_cpu_bound_threads() {

		// produces a given count of key-value pairs to seed the Tree
		long number_of_elements = 250000; // -100000;
		Keys&& kv_set_1 = build_key_value_random_inputs(number_of_elements / 2);
		Keys&& kv_set_2 = build_key_value_random_inputs(number_of_elements / 2);

		string processor_name("tree_builder two_threads_user_assigned_shared_load");

		thread tree_builder_1(&di_testbed::builder_thread_handler_two_threads_user_assigned_shared_load, this, processor_name, kv_set_1);
		int cpu_core_id = 5;
		DWORD assignment_mask = 0x10;
		CpuTopology cpu;

		DWORD_PTR dwCoreAffinity = cpu.CoreAffinityMask(cpu_core_id);
		if (dwCoreAffinity) {
			bind_to_cpu_user_specified_cpu_cores(tree_builder_1, (dwCoreAffinity & assignment_mask));
		}

		thread tree_builder_2(&di_testbed::builder_thread_handler_two_threads_user_assigned_shared_load, this, processor_name, kv_set_2);
		cpu_core_id = 6;
		assignment_mask = 0x20;

		dwCoreAffinity = cpu.CoreAffinityMask(cpu_core_id);
		if (dwCoreAffinity) {
			bind_to_cpu_user_specified_cpu_cores(tree_builder_1, (dwCoreAffinity & assignment_mask));
		}

		tree_builder_1.join();
		tree_builder_2.join();
	}

	// ToDo
	void build__a_search_tree_cpu_bound__realtime_priority_threads() {

	}

	//=============== HELPER FNS =========================
	void print_cpu(string& our_name) {
		std::cout << "Thread #"
			<< our_name << ": on CPU " << GetCurrentProcessorNumberXP() << "\n";
	}

	// produces key-value pairs to seed the Tree
	vector<pair<int, int>> build_key_value_random_inputs(int count) {
		vector<pair<int, int>> kv;

		std::random_device rd;
		std::mt19937 mt(8967);
		std::uniform_int_distribution<int> dist(0, 1000000);

		long number_of_elements = count; // -100000;
		pair<int, int> saved;
		while (number_of_elements--) {
			saved = { dist(mt), dist(mt) };
			kv.push_back(saved);
		}

		return std::move(kv);
	}

	void bind_to_cpu_user_specified_cpu_cores(thread& t, DWORD_PTR dwCoreAffinity) {
		CpuTopology cpu;

		// The number of system cores will not change for the duration of
		// the sample.  We only need to query it once.
		const DWORD dwSystemCores = cpu.NumberOfSystemCores();

		// The number of process cores can vary during execution of the
		// sample depending on if the process affinity has changed.
		// We need to query it each time through the loop to account
		// for any changes.
		const DWORD dwProcessCores = cpu.NumberOfProcessCores();

		wprintf(L"(%u Thread%s): ", dwProcessCores,
			dwProcessCores > 1 ? L"s" : L"");

		//DWORD_PTR dwCoreAffinity = cpu.CoreAffinityMask(core_id);
		if (dwCoreAffinity)
		{
			SuspendThread(t.native_handle());
			dwCoreAffinity = 0x60;
			SetThreadAffinityMask(t.native_handle(), dwCoreAffinity);
			ResumeThread(t.native_handle());
		}
	}

};

