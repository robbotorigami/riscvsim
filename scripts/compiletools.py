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
        os.system('rm {filename}.{ext}'.format(filename=filename, ext=ext))
        os.system('rm {filename}.o'.format(filename=filename))
        os.system('rm {filename}'.format(filename=filename))

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
    cmds = ["ADD x1, x13, x15",
            "SUB x11, x6, x7",
            "SLL x2, x4, x8",
            "SLT x12, x7, x5",
            "SLTU x16, x10, x9",
            "XOR x9, x14, x4",
            "SRL x1, x6, x3",
            "SRA x3, x12, x15",
            "OR x2, x15, x3",
            "AND x15, x13, x10",
            "ADDW x2, x8, x11",
            "SUBW x8, x9, x14",
            "SLLW x3, x5, x2",
            "SRLW x10, x6, x7",
            "SRAW x2, x4, x9"]

    co = codeobject()
    co.addstring('\n'.join(cmds) + '\n')
    print(['0x{:08x}'.format(i) for i in co.compile()])