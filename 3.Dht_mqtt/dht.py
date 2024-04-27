import paho.mqtt.client as mqtt
import mysql.connector

broker_address = "mqtt.eclipse.org"
topic = "sensor/dht"

def on_message(client, userdata, message):
    data = message.payload.decode("utf-8")
    temperature, humidity = data.split(',')
    save_to_database(temperature, humidity)

def save_to_database(temperature, humidity):
    try:
        # Koneksi ke database MySQL
        mydb = mysql.connector.connect(
            host="localhost",
            user="username",
            password="password",
            database="sensordb"
        )

        # Membuat cursor
        mycursor = mydb.cursor()

        # Query SQL untuk menyimpan data
        sql = "INSERT INTO sensor_data (temperature, humidity) VALUES (%s, %s)"
        val = (temperature, humidity)

        # Menjalankan query
        mycursor.execute(sql, val)

        # Commit perubahan
        mydb.commit()

        print("Data berhasil disimpan di database")

    except mysql.connector.Error as error:
        print("Error:", error)

# Inisialisasi klien MQTT
client = mqtt.Client("Receiver")
client.on_message = on_message

# Koneksi ke broker MQTT dan subscribe ke topik
client.connect(broker_address)
client.subscribe(topic)

# Loop forever untuk menerima pesan
client.loop_forever()

