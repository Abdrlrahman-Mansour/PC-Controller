import speech_recognition as sr
import requests

recognizer = sr.Recognizer()

while True:
    with sr.Microphone() as source:
        print("Say something!")
        audio = recognizer.listen(source)

    try:
        command = recognizer.recognize_google(audio).lower().strip()
        print(f"You said: {command}")
        # Send command to laptop
        requests.post("http://192.168.1.8:8080", data=command)
        
        if "thank you" in command:
            print("Exiting loop.")
            break
    except sr.UnknownValueError:
        print("Could not understand audio")
    except sr.RequestError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")