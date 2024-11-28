from multiprocessing import Process
from threading import Thread
import time


def suma(a, b):
    print("Suma: ", a + b)
    time.sleep(5)

def resta(a, b):
    print("Resta: ", a - b)
    time.sleep(10)
    

if __name__ == "__main__":

    a = 25
    b = 30
    
    proceso_suma = Process(target=suma, args=(a, b))
    proceso_resta = Process(target=resta, args=(a, b))
    
    proceso_suma.start()
    proceso_resta.start()

    proceso_suma.join()
    proceso_resta.join()

    """
    hilo_suma = Thread(target=suma, args=(a, b))
    hilo_resta = Thread(target=resta, args=(a, b))
    
    hilo_suma.start()
    hilo_resta.start()

    hilo_suma.join()
    hilo_resta.join()
    """
