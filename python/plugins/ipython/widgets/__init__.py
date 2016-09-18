from qtconsole.inprocess import QtInProcessKernelManager, QtInProcessRichJupyterWidget
from qtconsole.qt import QtCore, QtGui

class IJupWidget(QtInProcessRichJupyterWidget):

    def __init__(self, custom_banner=None, *args, **kwargs):
        super(IJupWidget, self).__init__(*args, **kwargs)
        self.kernel_manager = kernel_manager = QtInProcessKernelManager()
        kernel_manager.start_kernel()
        kernel_manager.kernel.gui = 'qt'
#        kernel_manager.kernel.shell.enable_matplotlib()

        self.kernel_client = kernel_client = self._kernel_manager.client()
        kernel_client.start_channels()

        def stop():
            kernel_client.stop_channels()
            kernel_manager.shutdown_kernel()
        self.exit_requested.connect(stop)

    def sizeHint(self):
        """Return a reasonable default size for usage in :class:`PlotWindow`"""
        return QtCore.QSize(500, 300)

    def pushVariables(self, variable_dict):
        self.kernel_manager.kernel.shell.push(variable_dict)



class JupyterDockWidget(QtGui.QDockWidget):
    def __init__(self, available_vars=None, custom_banner=None,
                 title="Console", parent=None):
        super(JupyterDockWidget, self).__init__(title, parent)

        self.ipyconsole = IJupWidget(custom_banner=custom_banner)

        self.layout().setContentsMargins(0, 0, 0, 0)
        self.setWidget(self.ipyconsole)

        if available_vars is not None:
            self.ipyconsole.pushVariables(available_vars)
