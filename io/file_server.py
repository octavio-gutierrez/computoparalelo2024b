from flask import Flask, request, render_template, send_file
import pickle

app = Flask(__name__)

@app.route("/archivo", methods=["GET"])
def archivo():
    print(request.args["nombre"])
    archivo = request.args["nombre"] + ".dat"
    return send_file("files/"+ archivo, download_name=archivo)

@app.route('/')
def home():
    return render_template('index.html')

if __name__ == "__main__":
    #app.run(host="0.0.0.0", port=90, threaded=True, processes=3)
    app.run(host="0.0.0.0", port=90, threaded=True)