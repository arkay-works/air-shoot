from flask import Flask, render_template
import requests
import random

app = Flask(__name__)

# List of IP addresses
ip_addresses = [
    'http://192.168.0.3/rotate',
    'http://192.168.0.9/rotate',
    'http://192.168.0.5/rotate',
    'http://192.168.0.6/rotate',
    'http://192.168.0.8/rotate'
]

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/rotate', methods=['POST'])
def rotate():
#     # Randomly select an IP address
    selected_ip = random.choice(ip_addresses)
    
    # Make a request to the selected IP address
    resp = requests.get(selected_ip)
    
    # Return the response status code and text
    return f"Requested IP: {selected_ip}<br>Response: {resp.status_code} - {resp.text}"

if __name__ == '__main__':
    app.run(debug=True)