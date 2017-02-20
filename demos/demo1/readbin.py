import struct

def readbin(filename):
    datas = []
    with open(filename, "rb") as infile:
        buf = infile.read(4)
        while buf:
            size = struct.unpack("i", buf)[0]
            buf = infile.read(8*size)
            datas.append(struct.unpack("d"*size, buf))
            buf = infile.read(4)
    return datas

if __name__ == "__main__":
    d = readbin("couple_simconc_distance.cols")
    print(d)
