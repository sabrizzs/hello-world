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
        resolution: (724, 724)
        play: False

    BoxLayout:
        orientation: 'horizontal'
        size_hint_y: None
        height: '54dp'
        Label:
            text: 'Garfo'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_class("garfo") if self.active else None
        Label:
            text: 'Lapis'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_class("lapis") if self.active else None
        Label:
            text: 'Livro'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_class("livro") if self.active else None
        Label:
            text: 'Capinha'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_class("capinha") if self.active else None
        Label:
            text: 'Mouse'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_class("mouse") if self.active else None
                    
    BoxLayout:
        orientation: 'horizontal'
        size_hint_y: None
        height: '54dp'
        Label:
            text: 'Claro'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_background("claro") if self.active else None
        Label:
            text: 'Escuro'
            color: 0, 0, 0, 1 
        CheckBox:
            on_active: root.set_current_background("escuro") if self.active else None

    ToggleButton:
        text: 'Abrir câmera'
        on_press: camera.play = not camera.play
        size_hint_y: None
        height: '54dp'

    Button:
        text: 'Tirar foto'
        size_hint_y: None
        height: '54dp'
        on_press: root.capture()
''')

class CameraClick(BoxLayout):
    def _init_(self, **kwargs):
        super(CameraClick, self)._init_(**kwargs)
        self.current_class = "None"
        self.current_background = "None"

    def set_current_class(self, class_name):
        self.current_class = class_name
        print("Current Class:", self.current_class)

    def set_current_background(self, background):
        self.current_background = background
        print("Current background:", self.current_background)

    def capture(self):
        if not os.path.exists(f"dataset/{self.current_class}"):
            os.makedirs(f"dataset/{self.current_class}")

        camera = self.ids['camera']
        timestr = time.strftime("%Y%m%d_%H%M%S")
        file_name = "dataset/{}/{}_{}_{}.png".format(self.current_class, self.current_class, self.current_background, timestr)
        camera.export_to_png(file_name)
        print("Captured:", file_name)
        
        content = Label(text=f'Foto capturada:\n{file_name}')
        popup = Popup(title='Captura Concluída', content=content, auto_dismiss=True)
        
        popup.open()
        
        Clock.schedule_once(popup.dismiss, 2)

class TestCamera(App):
    def build(self):
        return CameraClick()

TestCamera().run()