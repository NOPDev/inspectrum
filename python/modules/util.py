
def manchester_decode(v):
    data = [1 if x>1 else 0 for x in v]
    return [data[x:x+2][1] for x in range(0, len(data), 2)]

def am_demod(v):
    return [1 if x>1 else 0 for x in v]

def bits_to_bytes(bits, endian='MSB'):
    bit_arrays = [bits[i*8:(i+1)*8] for i in range(int(len(bits)/8))]
    byte_array = [int(''.join([str(x) for x in bit_arrays[i]]), 2) for i in range(len(bit_arrays))]
    return bytes(byte_array)


class Inspectrum:
    def __init__(self, window=main):
        self._window = window

    @property
    def symbols(self):
        plots = self._window.getPlots()
        return [self._window.symbols(plots[i]) for i in range(0, len(plots))]
    
    @property
    def plots(self):
        return self._window.getPlots()

    def setSampleRate(self, rate):
        self._window.setSampleRate(str(int(rate)))

    def openFile(self, filename):
        self._window.openFile(filename)

m = Inspectrum()                                                                                                                    

