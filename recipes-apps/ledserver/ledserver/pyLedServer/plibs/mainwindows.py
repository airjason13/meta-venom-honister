from PyQt5.QtWidgets import *
from PyQt5.QtCore import *


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        #self.resize(400, 300)

        self.subwindow = SubWindow()
        self.subwindow.show()

    def closeEvent(self, QCloseEvent):
        self.destroy()

    def destroy(self, destroyWindow=True, destroySubWindows=True):
        self.subwindow.destroy()

    def __del__(self):
        print("MainWindow Quit")
        self.subwindow.__del__()

class SubWindow(QWidget):
    def __init__(self):
        super(SubWindow, self).__init__()
        self.resize(400, 300)

        # Label
        self.label = QLabel(self)
        self.label.setGeometry(0, 0, 400, 300)
        self.label.setText('Sub Window')
        self.label.setAlignment(Qt.AlignCenter)
        self.label.setStyleSheet('font-size:40px')

    def __del__(self):
        print("Quit")