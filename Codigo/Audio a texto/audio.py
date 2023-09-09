import speech_recognition as sr
import time
import sys
from unidecode import unidecode

# Abre un archivo output.txt para escribir en él
with open("output.txt", "w") as file:
    r = sr.Recognizer()

    while True:
        with sr.Microphone() as source:
            print("Di tu frase :")
            time.sleep(3)
            r.adjust_for_ambient_noise(source)
            print("Ahora!")
            audio = r.listen(source)

        try:
            text = r.recognize_google(audio, language='es-ES')
            text = text.lower()
            print("Lo que dijiste: {}".format(text))

            # Elimina las tildes y acentos
            text_sin_tildes = unidecode(text)

            # Escribe la salida en el archivo output.txt
            file.write("{}\n".format(text_sin_tildes))
            
        except:
            print("No entiendo")
        
        test = text_sin_tildes.split()
        texto = ""
        texto = text_sin_tildes

        if texto == "salir":
            break

        print(test)
        print(type(test))