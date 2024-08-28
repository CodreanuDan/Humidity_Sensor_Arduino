
from flask import Flask, render_template, jsonify
import plotly.express as px
import pandas
import time
import json
import csv

app = Flask(__name__)

class Senzori:
    
    def incarca_din_fisier(self):
        with open('temp_data.json', 'r') as file:
            data = json.load(file)
            self.umiditate_dht = data['dht_rh']
            self.umiditate_condensator = data['rh']
            self.capacitate_condensator = data['cap_value']
            self.nr_masurari = data['iteration']
            self.date_time = data['date_time']

# O singură instanță globală a clasei Senzori
senzori = Senzori()

@app.route("/")
def index():
    senzori.incarca_din_fisier()
    return render_template("index.html", senzori=senzori)

@app.route("/")
def index_grph():
    senzori.incarca_din_fisier()
    return render_template("index.html", nr_masurari=senzori.nr_masurari, umiditate_condensator=senzori.umiditate_condensator)


@app.route('/date_senzori')
def date_senzori():
    senzori.incarca_din_fisier()
    return jsonify({
        'dht_rh': senzori.umiditate_dht,
        'rh': senzori.umiditate_condensator,
        'cap_value': senzori.capacitate_condensator,
        'iteration': senzori.nr_masurari,
        'date_time': senzori.date_time
    })

if __name__ == "__main__":
    app.run(debug=True)


