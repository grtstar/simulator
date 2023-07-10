"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class ColorRGBA(object):
    __slots__ = ["r", "g", "b", "a"]

    __typenames__ = ["float", "float", "float", "float"]

    __dimensions__ = [None, None, None, None]

    def __init__(self):
        self.r = 0.0
        self.g = 0.0
        self.b = 0.0
        self.a = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(ColorRGBA._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">ffff", self.r, self.g, self.b, self.a))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != ColorRGBA._get_packed_fingerprint():
            raise ValueError("Decode error")
        return ColorRGBA._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = ColorRGBA()
        self.r, self.g, self.b, self.a = struct.unpack(">ffff", buf.read(16))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if ColorRGBA in parents: return 0
        tmphash = (0x3719400fc6e3011a) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if ColorRGBA._packed_fingerprint is None:
            ColorRGBA._packed_fingerprint = struct.pack(">Q", ColorRGBA._get_hash_recursive([]))
        return ColorRGBA._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", ColorRGBA._get_packed_fingerprint())[0]

