import time

import NeuroPy
import matplotlib.pyplot as plt
plt.axis([0, 100, 0, 100])
neuropy =  NeuroPy.NeuroPy('COM5', 57600)

def attention_callback(attention_value):

    print ("Value of attention is: ", attention_value)
    return None

neuropy.setCallBack("attention", attention_callback)
neuropy.start()
i =0
try:
   while True:

        # print("at " +str(neuropy.attention))
        time.sleep(0.1)
        # y =neuropy.attention


   #
   #     print()
   # for i in range(100):
   #      sleep(0.2)

   #      plt.scatter(i, y)
   #      plt.pause(0.05)
   #      i = i +1
   #  plt.show()
finally:

    neuropy.stop()