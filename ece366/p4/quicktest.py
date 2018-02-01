class BinaryNumber:

    def __init__(self, value=0, length=32):
        self.value = int(format(value, 'b')[-1*length:], 2)
        self.length = length

    def pull_chunk(self, start, end):
        if start > end: return None
        if end >= self.length: return None
        print('chunk=' + format(self.value, 'b'))
        print('chunkfrom=' + str(-1*(end+1)) + ' - chunkto:' + str(self.length-start))
        return int(format(self.value, 'b')[-1*(end+1):self.length-start])
