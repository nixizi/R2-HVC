"""
Parallize the HVC calculation

The idea is simple. Initialize the tasks in a queue.
Then initialize some consumer to pick up one task and calculate it.
The calculation result will be push into the result queue.
"""

import multiprocessing
import numpy as np
import pygmo
import scipy.io as sio

class Consumer(multiprocessing.Process):
    def __init__(self, task_queue, result_queue):
        multiprocessing.Process.__init__(self)
        self.task_queue = task_queue
        self.result_queue = result_queue
    
    def run(self):
        proc_name = self.name
        while True:
            next_task = self.task_queue.get()
            if next_task is None:
                # Poison pill means shutdown
                print('%s: Exiting' % proc_name)
                self.task_queue.task_done()
                break
            print('%s: %s' % (proc_name, next_task))
            answer = next_task()
            print("Finish %dth HVC" % answer[0])
            self.task_queue.task_done()
            self.result_queue.put(answer)
        return

class Task(object):
    def __init__(self, index, data_set):
        self.index = index
        self.data_set = data_set
        (point_num, dimension) = np.shape(data_set)
        self.point_num = point_num
        self.dimension = dimension
        self.reference_point = [0 for i in range(self.dimension)]
    
    def __call__(self):
        result = np.zeros((1, self.point_num))
        hv = pygmo.hypervolume(self.data_set)
        for p in range(self.point_num):
            result[0, p] = hv.exclusive(p, self.reference_point)
        return [self.index, result]
    
    def __str__(self):
        return '%d' % self.index

def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data

if __name__=="__main__":
    #for data_type in ["linear_triangular", "linear_invertedtriangular", "concave_triangular", "concave_invertedtriangular", "convex_triangular", "convex_invertedtriangular"]:
    for data_type in ["concave_triangular1"]:
      for reference_point in range(5):
   # Establish communication queues
        tasks = multiprocessing.JoinableQueue()
        results = multiprocessing.Queue()

        # Start consumers
        num_consumers = multiprocessing.cpu_count() - 2
        print('Creating %d consumers' % num_consumers)
        consumers = [Consumer(tasks, results) for i in range(num_consumers)]
        print("Initalize workers")
        for w in consumers:
            w.start()
        
        point_num = 100
        dimension = 10
        data_set_size = 100
        #reference_point = 0
        data = read_data("data_set_{0}_{1}_{2}_{3}_{4}.mat".format(dimension, point_num, data_type, data_set_size, reference_point), "data_set")

        # Enqueue Jobs
        (point_num, dimension, data_set_size) = np.shape(data)
        HVC = np.zeros((1, point_num, data_set_size))
        data = data * -1
        for s in range(data_set_size):
            tasks.put(Task(s, data[:, :, s]))

        # Add a poison pill for each consumer
        for i in range(num_consumers):
            tasks.put(None)
        
        # Wait for all of the tasks to finish
        tasks.join()

        for s in range(data_set_size):
            result = results.get()
            HVC[0, :, result[0]] = result[1]
        
        save_name = "HVC_{0}_{1}_{2}_{3}_{4}.mat".format(dimension, point_num, data_type, data_set_size, reference_point)
        save_dict = {'HVC': HVC}
        sio.savemat(save_name, save_dict)
