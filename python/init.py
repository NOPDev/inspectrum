import sys, glob
from os.path import expanduser
from PythonQt import inspectrum
inspectrum.app = app
inspectrum.main_window = main

INSPECTRUM_PYTHON_PATH = '/usr/share/inspectrum/python'
DEV_PATH = '/home/ubuntu/src/inspectrum/pyinspectrum/python'
USER_PLUGINS = expanduser('~') + '/.inspectrum/python'
sys.path.append(DEV_PATH)
sys.path.append(INSPECTRUM_PYTHON_PATH)
sys.path.append(USER_PLUGINS)

# modules are automatically executed, not imported so that they have access the inspectrum ctx.
path = glob.glob(INSPECTRUM_PYTHON_PATH + '/modules/*.py')

for x in path:
    with open(x, 'r') as f:
        exec(f.read(), globals(), locals())


# Load the ipython console
from plugins.ipython import InspectrumConsole
InspectrumConsole(global_vars=globals())
