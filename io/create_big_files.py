from multiprocessing import Process
from threading import Thread
import time
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
from concurrent.futures import wait
from concurrent.futures import FIRST_COMPLETED

def crea_archivo(archivo):
    try:
        archivo_grande = open("files/" + archivo + ".dat", "w")
        for i in range(25000000):
            archivo_grande.write(str(i) + " datos irrelevantes \n")
        archivo_grande.close()
    except:
        return False
    return True
    

if __name__ == "__main__":
    inicio = time.time()
    # archivos de un giga
    archivos = ["uno", "dos", "tres", "cuatro", "cindo"]
    for archivo in archivos:
        archivo_grande = open("files/"+archivo+".dat", "w")
        for i in range(25000000):
            archivo_grande.write(str(i) + " datos irrelevantes \n")
        archivo_grande.close()

    fin = time.time()

    print("Tiempo:", fin-inicio, "segundos")
    # Tiempo: 131.68787384033203 segundos serial
    # Tiempo: 120.78286957740784 segundos serial




if __name__ == "__main__":
    inicio = time.time()    
    archivos = ["uno", "dos", "tres", "cuatro", "cinco"]
    hilos = []
    for i in range(len(archivos)):
        print("-----------------------------------",archivos[i])
        hilos.append(Thread(target=crea_archivo, args=(archivos[i],)))
        hilos[i].start()
        
    for i in range(len(archivos)):
        hilos[i].join()
    fin = time.time()

    print("Tiempo:", fin-inicio, "segundos")
    #Tiempo: 112.28289127349854 segundos hilos
    #Tiempo: 112.3550169467926 segundos hilos



if __name__ == "__main__":
    
    inicio = time.time()    
    archivos = ["uno", "dos", "tres", "cuatro", "cinco"]
    hilos = []

    for i in range(len(archivos)):
        print("-----------------------------------",archivos[i])
        hilos.append(Process(target=crea_archivo, args=(archivos[i],)))
        hilos[i].start()
        
    for i in range(len(archivos)):
        hilos[i].join()
    fin = time.time()

    print("Tiempo:", fin-inicio, "segundos")
    # Tiempo: 29.527978897094727 segundos procesos
    # Tiempo: 31.538975954055786 segundos  procesos































if __name__ == "__main__":
    inicio = time.time()    
    archivos = ["uno", "dos", "tres", "cuatro", "cinco"]
    hilos = []
    #executor = ProcessPoolExecutor(max_workers=5)    
    executor = ThreadPoolExecutor(max_workers=5)
    futures = [executor.submit(crea_archivo, archivos[i]) for i in range(len(archivos))]
    for future in futures:
        print(future.result())
    
    fin = time.time()
    executor.shutdown()
    print("Tiempo:", fin-inicio, "segundos")
    # Tiempo: 110.20279169082642 segundos ThreadPoolExecutor
    # Tiempo: 29.544140815734863 segundos ProcessPoolExecutor

    

"""
if __name__ == "__main__":
    inicio = time.time()    
    archivos = ["uno", "dos", "tres", "cuatro", "cinco"]
    hilos = []

    executor = ProcessPoolExecutor(max_workers=5)
    #futures = [executor.submit(crea_archivo, archivos[i]) for i in range(len(archivos))]
    for result in executor.map(crea_archivo, archivos):
        print(result)
    executor.shutdown()    
    fin = time.time()

    print("Tiempo:", fin-inicio, "segundos")
    # Tiempo: 29.46215653419494 segundos ProcessPoolExecutor with map
"""


if __name__ == "__main__":
    
    inicio = time.time()    
    archivos = ["uno", "dos", "tres", "cuatro", "cinco"]
    hilos = []

    executor = ProcessPoolExecutor(max_workers=5)
    futures = [executor.submit(crea_archivo, archivos[i]) for i in range(len(archivos))]
    completado, sin_completar = wait(futures, return_when=FIRST_COMPLETED)    
    print(completado.pop().result())    
    executor.shutdown(wait=False, cancel_futures=True)
    fin = time.time()
    print("Tiempo:", fin-inicio, "segundos")
    # Tiempo: 29.46215653419494 segundos ProcessPoolExecutor with map