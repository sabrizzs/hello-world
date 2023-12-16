from kivy.app import App
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.checkbox import CheckBox
from kivy.uix.camera import Camera
from kivy.uix.togglebutton import ToggleButton
from kivy.uix.button import Button
import time
from kivy.clock import Clock
from kivy.uix.label import Label
from kivy.uix.popup import Popup

from joblib import load
import cv2
import numpy as np
import pickle
import os

Builder.load_string('''
<CameraClick>:
    orientation: 'vertical'
    canvas.before:
        Color:
            rgba: 1, 1, 1, 1
        Rectangle:
            pos: self.pos
            size: self.size

    Camera:
        id: camera
        play: False

    BoxLayout:
        orientation: 'horizontal'
        size_hint_y: None
        height: '54dp'
        Label:
            id: classified_label
            text: 'Classificado: None'
            color: 0, 0, 0, 1 

    ToggleButton:
        text: 'Abrir câmera'
        on_press: camera.play = not camera.play
        size_hint_y: None
        height: '54dp'

    Button:
        text: 'Classificar'
        size_hint_y: None
        height: '54dp'
        on_press: root.capture()
''')

class CameraClick(BoxLayout):
    def __init__(self, **kwargs):
        super(CameraClick, self).__init__(**kwargs)
        self.classified_label = self.ids['classified_label']

    def capture(self):
        if not os.path.exists(f"fotos"):
            os.makedirs(f"fotos")

        camera = self.ids['camera']
        timestr = time.strftime("%Y%m%d_%H%M%S")
        file_name = "fotos/{}.png".format(timestr)
        camera.export_to_png(file_name)
        print("Captured:", file_name)

        class_name = self.process_captured_image(file_name)

        content = Label(text=f'Objeto classificado: {class_name}')
        popup = Popup(title='Objeto classificado!', content=content, auto_dismiss=True)

        popup.open()
        Clock.schedule_once(popup.dismiss, 2)
        
    def process_captured_image(self, file_name):
        model_arq = open('modelo_knc.pkl', 'rb')    
        model = pickle.load(model_arq)
        captured_image = cv2.imread(file_name)
        resized_image = cv2.resize(captured_image, (224, 224))
        gray_image = self.RGB2GRAY(resized_image)
        image_features = self.imagens_caracteristicas(gray_image)
           
        result = model.predict(image_features.reshape(1,-1))
        print("Predicted Class:", result)

        self.classified_label.text = f'Classificado: {result[0]}'
        return result

    def RGB2GRAY(self, imagem):
        imagem_cinza = cv2.cvtColor(imagem, cv2.COLOR_RGB2GRAY)
        return imagem_cinza

    def imagens_caracteristicas(self, imagem):
        x, y = imagem.shape
        caracteristicas = np.reshape(imagem, (x * y))
        return caracteristicas

class TestCamera(App):
    def build(self):
        return CameraClick()

TestCamera().run()