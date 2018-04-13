from elftools.elf.elffile import ELFFile
import os
import struct

class codeobject:
    CC = '../resource/riscvgnutools/bin/riscv-none-embed-gcc'
    AS = '../resource/riscvgnutools/bin/riscv-none-embed-as'
    LD = '../resource/riscvgnutools/bin/riscv-none-embed-ld'

    def __init__(self, ctype = 'assembly'):
        self.code = ''
        self.ctype = ctype

    def addstring(self, text):
        self.code += text

    def compile(self):
        filename = 'temp'

        #Create source file
        ext = 's' if self.ctype == 'assembly' else 'c'
        with open('{filename}.{ext}'.format(filename=filename, ext=ext), 'w') as f:
            f.write(self.code)

        #Compile file
        if self.ctype == 'assembly':
            #--specs=nosys.specs
            os.system('{AS}  -c {filename}.{ext} -o {filename}.o'.format(AS=self.AS, filename=filename, ext=ext))
            os.system('{LD} {filename}.o -o {filename}'.format(LD=self.LD, filename=filename, ext=ext))
        else:
            os.system('{CC} -O0 {filename}.{ext} -o {filename}.o'.format(CC=self.CC, filename=filename, ext=ext))

        #Parse out the machine code
        with open('{filename}'.format(filename=filename), 'rb') as f:
            elffile = ELFFile(f)

            textsection = elffile.get_section_by_name('.crt0')
            nsym = len(textsection.data()) // 4
            symbols = struct.unpack('I' * nsym, textsection.data())

        #Clean up files
        #os.system('rm {filename}.{ext}'.format(filename=filename, ext=ext))
        #os.system('rm {filename}.o'.format(filename=filename))
        #os.system('rm {filename}'.format(filename=filename))

        return symbols

    def create_image(self):
        filename = 'temp'

        #Create source file
        ext = 's' if self.ctype == 'assembly' else 'c'
        with open('{filename}.{ext}'.format(filename=filename, ext=ext), 'w') as f:
            f.write(self.code)

        #Compile file
        if self.ctype == 'assembly':
            #--specs=nosys.specs
            os.system('{AS}  -c {filename}.{ext} -o {filename}.o'.format(AS=self.AS, filename=filename, ext=ext))
            os.system('{LD} {filename}.o -o {filename}'.format(LD=self.LD, filename=filename, ext=ext))
        else:
            os.system('{CC} -O0 {filename}.{ext} -o {filename}.o'.format(CC=self.CC, filename=filename, ext=ext))

        #Parse out the machine code
        with open('{filename}'.format(filename=filename), 'rb') as f:
            elffile = ELFFile(f)

            textsection = elffile.get_section_by_name('.crt0')

            tsize = len(textsection.data())
            text = textsection.data()
            dsize = 16000
            data = b''*16000
            ssize = 0
            stack = b''

        filebytes = struct.pack('I', tsize) + struct.pack('I', dsize) + struct.pack('I', ssize)
        print(filebytes)
        filebytes += text + data + stack
        return filebytes


if __name__ == '__main__':
    co = codeobject(ctype = 'c')
    co.addstring('int main(){return 0;}')
    bytes = co.compile()