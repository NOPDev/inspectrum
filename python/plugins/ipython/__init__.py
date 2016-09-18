from PyQt5.QtWidgets import QMainWindow
from PyQt5.Qt import QApplication
from PyQt5.QtCore import Qt
from plugins.ipython.widgets import JupyterDockWidget

global ipython_widget

class InspectrumConsole():
    def __init__(self, global_vars=None):
        global_vars['console'] = self
        a = QApplication.instance()
        main_window = [x for x in a.allWidgets() if x.__class__ == QMainWindow][0]
        self.widget = JupyterDockWidget()
        self.widget.ipyconsole.pushVariables(global_vars)
        main_window.addDockWidget(Qt.BottomDockWidgetArea, self.widget)
        self.widget.show()
        print('InspectrumConsole loaded.')
