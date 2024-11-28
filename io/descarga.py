from multiprocessing import Process
from threading import Thread
import time
import requests

def download_file(url):
    local_file = url.split("=")[-1] + ".dat"
    print(local_file)
    with requests.get(url, stream=True) as request:
        request.raise_for_status()
        with open(local_file, "wb") as file:
            for chunk in request.iter_content(chunk_size=8192): 
                file.write(chunk)
    return local_file

if __name__ == "__main__":    
    inicio = time.time()
    #archivo = download_file("http://10.10.20.128:90/archivo?nombre=uno")
    
    #download_file("http://10.10.20.128:90/archivo?nombre=uno")
    #download_file("http://10.10.20.128:90/archivo?nombre=dos")
    #download_file("http://10.10.20.128:90/archivo?nombre=tres")
    #download_file("http://10.10.20.128:90/archivo?nombre=cuatro")
    #download_file("http://10.10.20.128:90/archivo?nombre=cinco")
    fin = time.time()
    print(fin - inicio)

    inicio = time.time()
    descarga1 = Process(target=download_file, args=("http://10.10.20.128:90/archivo?nombre=uno",))
    descarga2 = Process(target=download_file, args=("http://10.10.20.128:90/archivo?nombre=dos",))
    descarga3 = Process(target=download_file, args=("http://10.10.20.128:90/archivo?nombre=tres",))
    descarga4 = Process(target=download_file, args=("http://10.10.20.128:90/archivo?nombre=cuatro",))
    descarga5 = Process(target=download_file, args=("http://10.10.20.128:90/archivo?nombre=cinco",))
    descarga1.start()
    descarga2.start()
    descarga3.start()
    descarga4.start()
    descarga5.start()
    descarga1.join()
    descarga2.join()
    descarga3.join()
    descarga4.join()
    descarga5.join()
    fin = time.time()
    print(fin - inicio)
        


